// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
///////////////////////////////////////////////////////////////
// OdimHdf5ToMdv.cc
//
// Mike Dixon, EOL, NCAR
// P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// July 2021
//
///////////////////////////////////////////////////////////////
//
// OdimHdf5ToMdv reads ODIM OPERA data in HDF5 format, and
// converts to MDV.
//
////////////////////////////////////////////////////////////////

#include <algorithm>
#include <toolsa/toolsa_macros.h>
#include <toolsa/umisc.h>
#include <toolsa/pmu.h>
#include <toolsa/str.h>
#include <toolsa/DateTime.hh>
#include <toolsa/Path.hh>
#include <toolsa/TaArray.hh>
#include <Mdv/MdvxField.hh>
#include <dsserver/DsLdataInfo.hh>
#include <euclid/search.h>
#include "OdimHdf5ToMdv.hh"
using namespace std;

const fl32 OdimHdf5ToMdv::_missingFloat = -9999.0;

// Constructor

OdimHdf5ToMdv::OdimHdf5ToMdv(int argc, char **argv)

{

  isOK = true;
  _input = NULL;

  // set programe name

  _progName = "OdimHdf5ToMdv";
  ucopyright((char *) _progName.c_str());

  // get command line args

  if (_args.parse(argc, argv, _progName)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with command line args" << endl;
    isOK = false;
    return;
  }

  // get TDRP params
  
  _paramsPath = (char *) "unknown";
  if (_params.loadFromArgs(argc, argv, _args.override.list,
			   &_paramsPath)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with TDRP parameters" << endl;
    isOK = false;
  }

  // check that file list set in archive mode
  
  if (_params.mode == Params::FILELIST && _args.inputFileList.size() == 0) {
    cerr << "ERROR: OdimHdf5ToMdv" << endl;
    cerr << "  Mode is ARCHIVE."; 
    cerr << "  You must use -f to specify files on the command line."
	 << endl;
    _args.usage(_progName, cerr);
    isOK = false;
  }

  // init process mapper registration

  PMU_auto_init((char *) _progName.c_str(),
		_params.instance,
		_params.reg_interval);

  // initialize the data input object
  
  if (_params.mode == Params::REALTIME) {
    _input = new DsInputPath(_progName,
			     _params.debug >= Params::DEBUG_VERBOSE,
			     _params.input_dir,
			     _params.max_realtime_age,
			     PMU_auto_register,
			     _params.use_ldata_info_file,
			     _params.process_latest_file_only);
  } else if (_params.mode == Params::ARCHIVE) {
    _input = new DsInputPath(_progName,
			     _params.debug >= Params::DEBUG_VERBOSE,
			     _params.input_dir,
			     _args.startTime, _args.endTime);
  } else if (_params.mode == Params::FILELIST) {
    if (_params.debug) {
      for (int ii = 0; ii < (int) _args.inputFileList.size(); ii++) {
        cerr << "Adding path: " << _args.inputFileList[ii] << endl;
      }
    }
    _input = new DsInputPath(_progName,
			     _params.debug >= Params::DEBUG_VERBOSE,
			     _args.inputFileList);
  }

  if (strlen(_params.file_name_ext) > 0) {
    _input->setSearchExt(_params.file_name_ext);
  }

  if (strlen(_params.file_name_substr) > 0) {
    _input->setSubString(_params.file_name_substr);
  }

}

// destructor

OdimHdf5ToMdv::~OdimHdf5ToMdv()

{

  // unregister process

  PMU_auto_unregister();

  // free up

  if (_input) {
    delete _input;
  }

}

//////////////////////////////////////////////////
// Run

int OdimHdf5ToMdv::Run ()
{
  
  int iret = 0;
  PMU_auto_register("Run");
  
  // create the output fields
  
  for (int ifield = 0; ifield < _params.output_fields_n; ifield++) {
    OutputField *fld = new OutputField(_params._output_fields[ifield]);
    _outputFields.push_back(fld);
  }

  // loop until end of data
  
  char *inputPath;
  while ((inputPath = _input->next()) != NULL) {
    
    PMU_auto_register("Reading file");
    ta_file_uncompress(inputPath);

    if (_processFile(inputPath)) {
      cerr << "ERROR = OdimHdf5ToMdv::Run" << endl;
      cerr << "  Processing file: " << inputPath << endl;
      iret = -1;
    }
    
    // clear the output fields
    
    for (size_t ii = 0; ii < _outputFields.size(); ii++) {
      _outputFields[ii]->clear();
    }
    
  }
  
  return iret;

}

///////////////////////////////
// process file

int OdimHdf5ToMdv::_processFile(const char *input_path)

{

  PMU_auto_register("Processing file");
  
  if (_params.debug) {
    cerr << "Processing file: " << input_path << endl;
  }

  // use try block to catch any exceptions
  
  try {
    
    // open file

    H5File file(input_path, H5F_ACC_RDONLY);
    if (_params.debug) {
      cerr << "==>> File size: " << file.getFileSize() << endl;
    }
    if (_params.debug < Params::DEBUG_VERBOSE) {
      H5x::Exception::dontPrint();
    }
    
    // get the root group
    
    Group root(file.openGroup("/"));
    if (_params.debug >= Params::DEBUG_EXTRA) {
      Hdf5xx::printFileStructure(root, 0, cerr);
    }

    // root attributes

    _conventions = Hdf5xx::getStringAttribute(root, "Conventions");

    if (_params.debug >= Params::DEBUG_VERBOSE) {
      cerr << "Conventions: " << _conventions << endl;
    }

    // read the metadata from the main what and how groups
    
    if (_readMetadata(root)) {
      return -1;
    }
    // read the where group - grid location etc.
    
    _readWhere(root);

    // read in the fields

    if (_readFields(root)) {
      cerr << "ERROR processing file: " << input_path << endl;
      cerr << "  Cannot read in the fields" << endl;
    }
    
    return 0;


  } // try
  
  catch (H5x::Exception &e) {
    // _addErrStr("ERROR - reading GPM HDF5 file");
    // _addErrStr(e.getDetailMsg());
    return -1;
  }

  // create output Mdvx file object
  
  DsMdvx mdvx;
  if (_params.debug >= Params::DEBUG_VERBOSE) {
    mdvx.setDebug(true);
  }
    
  // set master header
  
  _setMasterHeader(mdvx);
  
  // interpolate fields onto latlon grid, and add to the mdvx object

  for (size_t ifield = 0; ifield < _outputFields.size(); ifield++) {
    
    // get field as it was read in
    
    OutputField *fld = _outputFields[ifield];
    if (!fld->valid) {
      delete fld;
      continue;
    }
    
    // interpolate
    
    _interpField(fld);
    
    // for DBZ invert the gate levels because the radar gate data is stored
    // top-down instead of bottom-up
    
    _invertDbzGateLevels(fld);
  
    // optionally remap onto specified output grid vlevels
    
    // if (_params.remap_gates_to_vert_levels) {

    //   // zlevels are specified
      
    //   _zLevels.resize(_params.output_z_levels_km_n);
    //   for (int iz = 0; iz < _params.output_z_levels_km_n; iz++) {
    //     _zLevels[iz] = _params._output_z_levels_km[iz];
    //   }

    //   _remapVertLevels(fld);

    // }

    // add to mdvx object
    
    _addFieldToMdvx(mdvx, fld);

    // delete the field

    delete fld;

  } // ifield
    
  // clean up

  _outputFields.clear();

  // write output file
  
  if (_params.debug) {
    cerr << "Writing file to url: " << _params.output_url << endl;
  }
  
  if (mdvx.writeToDir(_params.output_url)) {
    cerr << "ERROR - OdimHdf5ToMdv" << endl;
    cerr << "  Cannot write file to url: " << _params.output_url << endl;
    cerr << mdvx.getErrStr() << endl;
    return -1;
  }
  
  if (_params.debug) {
    cerr << "  Wrote output file: " << mdvx.getPathInUse() << endl;
  }

  return 0;

}

//////////////////////////////////////////////
// read the main what and how group

int OdimHdf5ToMdv::_readMetadata(Group &root)
  
{

  Group what(root.openGroup("what"));

  string dateStr = Hdf5xx::getStringAttribute(what, "date");
  string timeStr = Hdf5xx::getStringAttribute(what, "time");
  _midTime.set(dateStr + timeStr);
  _version = Hdf5xx::getStringAttribute(what, "version");
  _source = Hdf5xx::getStringAttribute(what, "source");
  
  Group how(root.openGroup("how"));

  _history = Hdf5xx::getStringAttribute(how, "nodes");
  
  if (_params.debug >= Params::DEBUG_VERBOSE) {
    cerr << "Reading main what and how groups" << endl;
    cerr << "  midTime: " << _midTime.asString() << endl;
    cerr << "  version: " << _version << endl;
    cerr << "  source: " << _source << endl;
    cerr << "  history: " << _history << endl;
  }

  return 0;
  
}

//////////////////////////////////////////////
// read the where group - grid location etc.

int OdimHdf5ToMdv::_readWhere(Group &root)
  
{

  Group where(root.openGroup("where"));

  _projStr = Hdf5xx::getStringAttribute(where, "projdef");

  _nx = Hdf5xx::getIntAttribute(where, "xsize");
  _ny = Hdf5xx::getIntAttribute(where, "ysize");
  
  _dxM = Hdf5xx::getDoubleAttribute(where, "xscale");
  _dyM = Hdf5xx::getDoubleAttribute(where, "yscale");

  _llLon = Hdf5xx::getDoubleAttribute(where, "LL_lon");
  _llLat = Hdf5xx::getDoubleAttribute(where, "LL_lat");
  _ulLon = Hdf5xx::getDoubleAttribute(where, "UL_lon");
  _ulLat = Hdf5xx::getDoubleAttribute(where, "UL_lat");
  _urLon = Hdf5xx::getDoubleAttribute(where, "UR_lon");
  _urLat = Hdf5xx::getDoubleAttribute(where, "UR_lat");
  _lrLon = Hdf5xx::getDoubleAttribute(where, "LR_lon");
  _lrLat = Hdf5xx::getDoubleAttribute(where, "LR_lat");
  
  if (_params.debug >= Params::DEBUG_VERBOSE) {
    cerr << "Reading where group" << endl;
    cerr << "  projStr: " << _projStr << endl;
    cerr << "  nx: " << _nx << endl;
    cerr << "  ny: " << _ny << endl;
    cerr << "  dxM: " << _dxM << endl;
    cerr << "  dyM: " << _dyM << endl;
    cerr << "  llLon: " << _llLon << endl;
    cerr << "  llLat: " << _llLat << endl;
    cerr << "  ulLon: " << _ulLon << endl;
    cerr << "  ulLat: " << _ulLat << endl;
    cerr << "  urLon: " << _urLon << endl;
    cerr << "  urLat: " << _urLat << endl;
    cerr << "  lrLon: " << _lrLon << endl;
    cerr << "  lrLat: " << _lrLat << endl;
  }
  
  return 0;
  
}

/////////////////////////////////////////////
// Read in the data fields

int OdimHdf5ToMdv::_readFields(Group &root)
  
{
  
  for (int ii = 1; ii < 999; ii++) {

    char datasetGrpName[1024];
    snprintf(datasetGrpName, 1024, "dataset%d", ii);
    try {
      if (root.nameExists(datasetGrpName)) {
        Group datasetGrp(root.openGroup(datasetGrpName));
        _readField(datasetGrp);
      } else {
        if (_params.debug >= Params::DEBUG_VERBOSE) {
          cerr << "N dataset groups found: " << ii - 1 << endl;
          cerr << "  End of data" << endl;
        }
        return 0;
      }
    } catch (H5x::Exception &e) {
      return -1;
    }

  } // ii

  return 0;

}
    
//////////////////////////////////////////////
// read in a field, if required

int OdimHdf5ToMdv::_readField(Group &dataGrp)
  
{

  // get field attributes from the what group

  try {
    
    Group what(dataGrp.openGroup("what"));
    string fieldName = Hdf5xx::getStringAttribute(what, "quantity");

    // do we want this field
    
    OutputField *fld = NULL;
    bool fieldWanted = false;
    for (size_t ifield = 0; ifield < _outputFields.size(); ifield++) {
      fld = _outputFields[ifield];
      if (fieldName == string(fld->params.hdf5Quantity)) {
        fieldWanted = true;
        break;
      }
    }

    if (fieldWanted) {
      
      if (_params.debug >= Params::DEBUG_VERBOSE) {
        cerr << "Found field: " << fieldName << endl;
      }

      // read attributes
      
      _readFieldAttributes(what, fieldName, fld);

      // read data
      
      _readFieldData(dataGrp, fieldName, fld);

    }
    
    
  } catch (H5x::Exception &e) {

    cerr << "WARNING - cannot read metadata and data in data group: "
         << dataGrp.getObjName() << endl;
    return -1;

  }
  
  return 0;
  
}

//////////////////////////////////////////////
// read in field attributes

int OdimHdf5ToMdv::_readFieldAttributes(Group &what,
                                        const string &fieldName,
                                        OutputField *fld)
  
{

  string startDateStr = Hdf5xx::getStringAttribute(what, "startdate");
  string startTimeStr = Hdf5xx::getStringAttribute(what, "starttime");
  string endDateStr = Hdf5xx::getStringAttribute(what, "enddate");
  string endTimeStr = Hdf5xx::getStringAttribute(what, "endtime");

  fld->startTime.set(startDateStr + startTimeStr);
  fld->endTime.set(endDateStr + endTimeStr);

  fld->gain = Hdf5xx::getDoubleAttribute(what, "gain");
  fld->offset = Hdf5xx::getDoubleAttribute(what, "offset");
  fld->nodata = Hdf5xx::getDoubleAttribute(what, "nodata");
  fld->undetect = Hdf5xx::getDoubleAttribute(what, "undetect");
  
  if (_params.debug >= Params::DEBUG_VERBOSE) {
    cerr << "Reading attributes, field: " << fieldName << endl;
    cerr << "  start time: " << fld->startTime.asString() << endl;
    cerr << "  end time: " << fld->endTime.asString() << endl;
    cerr << "  gain: " << fld->gain << endl;
    cerr << "  offset: " << fld->offset << endl;
    cerr << "  nodata: " << fld->nodata << endl;
    cerr << "  undetect: " << fld->undetect << endl;
  }
  
  return 0;
  
}

//////////////////////////////////////////////
// read in field data

int OdimHdf5ToMdv::_readFieldData(Group &dataGrp,
                                  const string &fieldName,
                                  OutputField *fld)
  
{

  // open the data set subgroup

  Group data1Grp(dataGrp.openGroup("data1"));

  // get the field properties
  
  if (fld->hdf5.getVarProps(data1Grp, "data",
                            fld->dims, fld->units, 
                            fld->h5class, fld->h5sign, fld->h5order, fld->h5size)) {
    cerr << fld->hdf5.getErrStr() << endl;
    fld->valid = false;
    return -1;
  }
  
  // set interp type
  
  if (fld->h5class == H5T_INTEGER) {
    fld->nearestNeighbor = true;
  } else {
    fld->nearestNeighbor = _params.interp_using_nearest_neighbor;
  }
  
  cerr << "DDDDDDDDDDDDDDDDDDDDD" << endl;
  
  // debug print
  
  if (_params.debug >= Params::DEBUG_VERBOSE) {
    cerr << "Reading fields" << endl;
    cerr << "  groupName: " << fld->params.groupName << endl;
    cerr << "  hdf5Quantity: " << fld->params.hdf5Quantity << endl;
    cerr << "  dims: ";
    for (size_t ii = 0; ii < fld->dims.size(); ii++) {
      cerr << fld->dims[ii];
      if (ii == fld->dims.size() - 1) {
        cerr << endl;
      } else {
        cerr << ", ";
      }
    }
    if (fld->units.size() > 0) {
      cerr << "  units: " << fld->units << endl;
    }
    if (fld->h5class == H5T_INTEGER) {
      if (fld->h5sign == H5T_SGN_NONE) {
        cerr << "  Is unsigned integer" << endl;
      } else {
        cerr << "  Is signed integer" << endl;
      }
    } else {
      cerr << "  Is float" << endl;
    }
    if (fld->h5order == H5T_ORDER_LE) {
      cerr << "  Byte order: little-endian" << endl;
    } else {
      cerr << "  Byte order: big-endian" << endl;
    }
    cerr << "  Byte len: " << fld->h5size << endl;
  }
  
  // set number of levels
    
  if (fld->dims.size() == 3) {
    _nz = fld->dims[2];
    _zLevels.resize(_nz);
    for (size_t iz = 0; iz < _nGates; iz++) {
      _zLevels[iz] = _minzKm + iz * _dzKm;
    }
  }

  // read in the field data 
  
  if (fld->h5class == H5T_INTEGER && fld->h5size == 2) {
    
    // 16-bit integer
    
    if (fld->dims.size() == 2) {
      // 2D field
      if (_readField2D(data1Grp, "data",
                       fld->si16Input,
                       fld->si16Missing,
                       fld->units) == 0) {
        fld->valid = true;
      }
    } else {
      // 3D field
      if (_readField3D(data1Grp, "data",
                       fld->si16Input,
                       fld->si16Missing,
                       fld->units) == 0) {
        fld->valid = true;
      }
    } // if (fld->dims.size() == 2)
    
  } else { // if (fld->h5class == H5T_INTEGER && fld->h5size == 2) {
    
    // read as floats
    
    if (fld->dims.size() == 2) {
      // 2D field
      if (_readField2D(data1Grp, "data",
                       fld->fl32Input,
                       fld->fl32Missing,
                       fld->units) == 0) {
        fld->valid = true;
      }
    } else {
      // 3D field
      if (_readField3D(data1Grp, "data",
                       fld->fl32Input,
                       fld->fl32Missing,
                       fld->units) == 0) {
        fld->valid = true;
      }
    } // if (fld->dims.size() == 2)
    
    cerr << "111111111 fl32Input.size(): " << fld->fl32Input.size() << endl;
    cerr << "111111111 si16Input.size(): " << fld->si16Input.size() << endl;

  } // if (fld->h5class == H5T_INTEGER && fld->h5size == 2) {
    
  return 0;

}

//////////////////////////////////////////////
// read 3D float field

int OdimHdf5ToMdv::_readField3D(Group &grp,
                                const string &dsetName,
                                vector<NcxxPort::fl32> &vals,
                                NcxxPort::fl32 &missingVal,
                                string &units)
  
{
  
  Hdf5xx hdf5;
  
  // read Latitude
  
  vector<size_t> dims;
  if (hdf5.readFl32Array(grp, dsetName,
                         dims, missingVal, vals, units)) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField3D()" << endl;
    cerr << "  Cannot read group/dataset: " << grp.getObjName() << "/" << dsetName << endl;
    return -1;
  }

  // check dimensions for consistency
  
  if (dims.size() != 3) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField3D()" << endl;
    cerr << "  Cannot read group/dataset: " << grp.getObjName() << "/" << dsetName << endl;
    cerr << "  zFactorCorrected must have 3 dimensions" << endl;
    cerr << "  dims.size(): " << dims.size() << endl;
    return -1;
  }
  if (dims[0] != _ny || dims[1] != _nx) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField3D()" << endl;
    cerr << "  Cannot read group/dataset: " << grp.getObjName() << "/" << dsetName << endl;
    cerr << "  DBZ dimensions must match ny and nx" << endl;
    cerr << "  dims[0]: " << dims[0] << endl;
    cerr << "  dims[1]: " << dims[1] << endl;
    cerr << "  _ny: " << _ny << endl;
    cerr << "  _nRays: " << _nRays << endl;
    return -1;
  }

  _nz = dims[2];
  // _minzKm = _params.radar_min_z_km;
  // _dzKm = _params.radar_delta_z_km;

  if (_params.debug >= Params::DEBUG_VERBOSE) {
    cerr << "====>> Read 3D fl32 group/dataset: " 
         << grp.getObjName() << "/" << dsetName << " <<====" << endl;
    cerr << "  nScans, nRays, nGates: " 
         << _ny << ", " << _nRays << ", " << _nGates << endl;
    cerr << "  missingVal: " << missingVal << endl;
    if (_params.debug >= Params::DEBUG_EXTRA) {
      for (size_t iscan = 0; iscan < _ny; iscan++) {
        for (size_t iray = 0; iray < _nRays; iray++) {
          for (size_t igate = 0; igate < _nGates; igate++) {
            size_t ipt = iscan * _nRays * _nGates + iray * _nGates + igate;
            if (vals[ipt] != missingVal) {
              cerr << "  iscan, iray, igate, val: "
                   << iscan << ", "
                   << iray << ", "
                   << igate << ", "
                   << vals[ipt] << endl;
            }
          } // igate
        } // iray
      } // iscan
    } // extra
  } // verbose
  
  return 0;

}

//////////////////////////////////////////////
// read 3D int32 field

int OdimHdf5ToMdv::_readField3D(Group &grp,
                                const string &dsetName,
                                vector<NcxxPort::si16> &vals,
                                NcxxPort::si16 &missingVal,
                                string &units)
  
{
  
  Hdf5xx hdf5;
  
  // read Latitude
  
  vector<size_t> dims;
  if (hdf5.readSi16Array(grp, dsetName,
                         dims, missingVal, vals, units)) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField3D()" << endl;
    cerr << "  Cannot read group/dataset: " << grp.getObjName() << "/" << dsetName << endl;
    return -1;
  }

  // check dimensions for consistency
  
  if (dims.size() != 3) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField3D()" << endl;
    cerr << "  Cannot read group/dataset: " << grp.getObjName() << "/" << dsetName << endl;
    cerr << "  zFactorCorrected must have 3 dimensions" << endl;
    cerr << "  dims.size(): " << dims.size() << endl;
    return -1;
  }
  if (dims[0] != _ny || dims[1] != _nRays) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField3D()" << endl;
    cerr << "  Cannot read group/dataset: " << grp.getObjName() << "/" << dsetName << endl;
    cerr << "  DBZ dimensions must match nScans and nRays" << endl;
    cerr << "  dims[0]: " << dims[0] << endl;
    cerr << "  dims[1]: " << dims[1] << endl;
    cerr << "  _ny: " << _ny << endl;
    cerr << "  _nRays: " << _nRays << endl;
    return -1;
  }

  _nz = dims[2];
  // _minzKm = _params.radar_min_z_km;
  // _dzKm = _params.radar_delta_z_km;

  if (_params.debug >= Params::DEBUG_VERBOSE) {
    cerr << "====>> Read 3D int 32 group/dataset: " 
         << grp.getObjName() << "/" << dsetName << " <<====" << endl;
    cerr << "  nScans, nRays, nGates: " 
         << _ny << ", " << _nRays << ", " << _nGates << endl;
    cerr << "  missingVal: " << missingVal << endl;
    if (_params.debug >= Params::DEBUG_EXTRA) {
      for (size_t iscan = 0; iscan < _ny; iscan++) {
        for (size_t iray = 0; iray < _nRays; iray++) {
          for (size_t igate = 0; igate < _nGates; igate++) {
            size_t ipt = iscan * _nRays * _nGates + iray * _nGates + igate;
            if (vals[ipt] != missingVal) {
              cerr << "  iscan, iray, igate, val: "
                   << iscan << ", "
                   << iray << ", "
                   << igate << ", "
                   << vals[ipt] << endl;
            }
          } // igate
        } // iray
      } // iscan
    } // extra
  } // verbose
  
  return 0;

}

//////////////////////////////////////////////
// read a 2D field - floats

int OdimHdf5ToMdv::_readField2D(Group &grp,
                                const string &dsetName,
                                vector<NcxxPort::fl32> &vals,
                                NcxxPort::fl32 &missingVal,
                                string &units)
  
{

  cerr << "2D2D2D2D2D" << endl;
  
  Hdf5xx hdf5;

  // read Latitude
  
  vector<size_t> dims;
  
  if (hdf5.readFl32Array(grp, dsetName,
                         dims, missingVal, vals, units)) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField2D()" << endl;
    cerr << "  Cannot read group/dataset: " << grp.getObjName() << "/" << dsetName << endl;
    return -1;
  }

  // check dimensions for consistency
  
  if (dims.size() != 2) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField2D()" << endl;
    cerr << "  Cannot read group/dataset: " << grp.getObjName() << "/" << dsetName << endl;
    cerr << "  2D fields must have 2 dimensions" << endl;
    cerr << "  dims.size(): " << dims.size() << endl;
    return -1;
  }
  if (dims[0] != _ny || dims[1] != _ny) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField2D()" << endl;
    cerr << "  Cannot read group/dataset: " << grp.getObjName() << "/" << dsetName << endl;
    cerr << "  dimensions must match nScans and nRays" << endl;
    cerr << "  dims[0]: " << dims[0] << endl;
    cerr << "  dims[1]: " << dims[1] << endl;
    cerr << "  _ny: " << _ny << endl;
    cerr << "  _nx: " << _nx << endl;
    return -1;
  }

  if (_params.debug >= Params::DEBUG_VERBOSE) {
    cerr << "====>> Read 2D fl32 group/dataset: "
         << grp.getObjName() << "/" << dsetName << " <<====" << endl;
    cerr << "  nScans, nRays: " 
         << _ny << ", " << _nRays << endl;
    cerr << "  missingVal: " << missingVal << endl;
    if (_params.debug >= Params::DEBUG_EXTRA) {
      for (size_t iscan = 0; iscan < _ny; iscan++) {
        for (size_t iray = 0; iray < _nRays; iray++) {
          size_t ipt = iscan * _nRays + iray;
          if (vals[ipt] != missingVal) {
            cerr << "  iscan, iray, val: "
                 << iscan << ", "
                 << iray << ", "
                 << vals[ipt] << endl;
          }
        } // iray
      } // iscan
    } // extra
  } // verbose
  
  return 0;

}

//////////////////////////////////////////////
// read a 2D field - int16s

int OdimHdf5ToMdv::_readField2D(Group &grp,
                                const string &dsetName,
                                vector<NcxxPort::si16> &vals,
                                NcxxPort::si16 &missingVal,
                                string &units)
  
{
  
  Hdf5xx hdf5;

  // read Latitude
  
  vector<size_t> dims;
  
  if (hdf5.readSi16Array(grp, dsetName,
                         dims, missingVal, vals, units)) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField2D()" << endl;
    cerr << "  Cannot read group/dataset: "
         << grp.getObjName() << "/" << dsetName << endl;
    return -1;
  }

  // check dimensions for consistency
  
  if (dims.size() != 2) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField2D()" << endl;
    cerr << "  Cannot read group/dataset: "
         << grp.getObjName() << "/" << dsetName << endl;
    cerr << "  2D fields must have 2 dimensions" << endl;
    cerr << "  dims.size(): " << dims.size() << endl;
    return -1;
  }
  if (dims[0] != _ny || dims[1] != _nx) {
    cerr << "ERROR - OdimHdf5ToMdv::_readField2D()" << endl;
    cerr << "  Cannot read group/dataset: "
         << grp.getObjName() << "/" << dsetName << endl;
    cerr << "  dimensions must match nScans and nRays" << endl;
    cerr << "  dims[0]: " << dims[0] << endl;
    cerr << "  dims[1]: " << dims[1] << endl;
    cerr << "  _ny: " << _ny << endl;
    cerr << "  _nRays: " << _nRays << endl;
    return -1;
  }

  if (_params.debug >= Params::DEBUG_VERBOSE) {
    cerr << "====>> Read 2D int16 group/dataset: "
         << grp.getObjName() << "/" << dsetName << " <<====" << endl;
    cerr << "  nScans, nRays: " 
         << _ny << ", " << _nRays << endl;
    cerr << "  missingVal: " << missingVal << endl;
    if (_params.debug >= Params::DEBUG_EXTRA) {
      for (size_t iscan = 0; iscan < _ny; iscan++) {
        for (size_t iray = 0; iray < _nRays; iray++) {
          size_t ipt = iscan * _nRays + iray;
          if (vals[ipt] != missingVal) {
            cerr << "  iscan, iray, val: "
                 << iscan << ", "
                 << iray << ", "
                 << vals[ipt] << endl;
          }
        } // iray
      } // iscan
    } // extra
  } // verbose
  
  return 0;

}

//////////////////////////////////////////////
// interpolate the fields

void OdimHdf5ToMdv::_interpField(OutputField *fld)

{

  if (fld->si16Input.size() > 0) {

    _interpField(fld->si16Input,
                 fld->si16Missing,
                 fld->si16Interp);

    fld->si16Output = fld->si16Interp;

  } else if (fld->fl32Input.size() > 0) {

    _interpField(fld->fl32Input,
                 fld->fl32Missing,
                 fld->fl32Interp,
                 fld->nearestNeighbor);

    fld->fl32Output = fld->fl32Interp;

  }
  
}

//////////////////////////////////////////////
// interpolate float field

void OdimHdf5ToMdv::_interpField(vector<NcxxPort::fl32> &valsInput,
                                 NcxxPort::fl32 missingVal,
                                 vector<NcxxPort::fl32> &valsInterp,
                                 bool nearestNeighbor)
  
{

  // check for 2D field

  bool is2D = false;
  if (valsInput.size() == _nRays * _nScans) {
    is2D = true;
  }
  size_t nz = _nz;
  size_t nGates = _nGates;
  if (is2D) {
    nz = 1;
    nGates = 1;
  }
  
  // initialize dbz grid

  size_t nOutput = _nx * _ny * nz;
  valsInterp.resize(nOutput);
  for (size_t ii = 0; ii < nOutput; ii++) {
    valsInterp[ii] = missingVal;
  }

  // loop through the vertical levels
  
  for (size_t iz = 0; iz < nz; iz++) {
    
    double zM = (_minzKm + iz * _dzKm) * 1000.0;
    
    // load input vals for this level
    size_t nPtsScan = _nRays * nGates;
    vector<vector<NcxxPort::fl32> > valsThisZ;
    for (size_t iscan = 0; iscan < _nScans; iscan++) {
      vector<NcxxPort::fl32> valsScan;
      for (size_t iray = 0; iray < _nRays; iray++) {
        size_t ipt = iscan * nPtsScan + iray * nGates + iz;
        valsScan.push_back(valsInput[ipt]);
      } // iray
      valsThisZ.push_back(valsScan);
    } // iscan
    
    // loop through the input (scan, ray) grid

    for (size_t iscan = 0; iscan < _nScans - 1; iscan++) {
      for (size_t iray = 0; iray < _nRays - 1; iray++) {
        
        // corner locations adjusted for radar slant
        Point_d corners[4];
        corners[0] = _getCornerLatLon(iscan, iray, zM);
        corners[1] = _getCornerLatLon(iscan, iray + 1, zM);
        corners[2] = _getCornerLatLon(iscan + 1, iray + 1, zM);
        corners[3] = _getCornerLatLon(iscan + 1, iray, zM);

        // vals at corners
        NcxxPort::fl32 vals[4];
        vals[0] = valsThisZ[iscan][iray];
        vals[1] = valsThisZ[iscan][iray + 1];
        vals[2] = valsThisZ[iscan + 1][iray + 1];
        vals[3] = valsThisZ[iscan + 1][iray];

        // interp for the output grid points inside the polygon
        
        _interpInsidePolygon(corners, vals, missingVal, 
                             iz, valsInterp, nearestNeighbor);
        
      } // iray
    } // iscan

  } // iz

}

//////////////////////////////////////////////
// interpolate int 16 field

void OdimHdf5ToMdv::_interpField(vector<NcxxPort::si16> &valsInput,
                                 NcxxPort::si16 missingVal,
                                 vector<NcxxPort::si16> &valsInterp)
  
{

  // check for 2D field

  bool is2D = false;
  if (valsInput.size() == _nRays * _nScans) {
    is2D = true;
  }
  size_t nz = _nz;
  size_t nGates = _nGates;
  if (is2D) {
    nz = 1;
    nGates = 1;
  }
  
  // initialize dbz grid

  size_t nOutput = _nx * _ny * nz;
  valsInterp.resize(nOutput);
  for (size_t ii = 0; ii < nOutput; ii++) {
    valsInterp[ii] = missingVal;
  }

  // loop through the vertical levels

  for (size_t iz = 0; iz < nz; iz++) {

    double zM = (_minzKm + iz * _dzKm) * 1000.0;
    
    // load input vals for this level
    
    vector<vector<NcxxPort::si16> > valsIn;
    for (size_t iscan = 0; iscan < _nScans; iscan++) {
      vector<NcxxPort::si16> valsScan;
      for (size_t iray = 0; iray < _nRays; iray++) {
        size_t ipt = iscan * _nRays * nGates + iray * nGates + iz;
        valsScan.push_back(valsInput[ipt]);
      } // iray
      valsIn.push_back(valsScan);
    } // iscan
    
    // loop through the input (scan, ray) grid

    for (size_t iscan = 0; iscan < _nScans - 1; iscan++) {
      for (size_t iray = 0; iray < _nRays - 1; iray++) {
        
        // corner locations adjusted for radar slant
        Point_d corners[4];
        corners[0] = _getCornerLatLon(iscan, iray, zM);
        corners[1] = _getCornerLatLon(iscan, iray + 1, zM);
        corners[2] = _getCornerLatLon(iscan + 1, iray + 1, zM);
        corners[3] = _getCornerLatLon(iscan + 1, iray, zM);

        // dbz vals at corners
        NcxxPort::si16 vals[4];
        vals[0] = valsIn[iscan][iray];
        vals[1] = valsIn[iscan][iray + 1];
        vals[2] = valsIn[iscan + 1][iray + 1];
        vals[3] = valsIn[iscan + 1][iray];

        // interp for the output grid points inside the polygon
        
        _interpInsidePolygon(corners, vals, missingVal, iz, valsInterp);
        
      } // iray
    } // iscan

  } // iz

}

//////////////////////////////////////////////
// interpolate points within polygon - floats

void OdimHdf5ToMdv::_interpInsidePolygon(const Point_d *corners,
                                         const NcxxPort::fl32 *vals,
                                         NcxxPort::fl32 missingVal,
                                         size_t iz,
                                         vector<NcxxPort::fl32> &valsInterp,
                                         bool nearestNeighbor)
 
{

  // check we have 4 valid corners
  
  for (int ii = 0; ii < 4; ii++) {
    if (corners[ii].x == _missingLon ||
        corners[ii].y == _missingLat) {
      return;
    }
  }

  // check we have valid data
  
  int nGood = 0;
  for (int ii = 0; ii < 4; ii++) {
    if (vals[ii] != missingVal) {
      nGood++;
    }
  }
  if (nGood == 0) {
    return;
  }

  // compute the min/max grid indices

  int minIx, maxIx, minIy, maxIy;
  _computeMinMaxIndices(corners, minIx, maxIx, minIy, maxIy);

  // loop through the output grid points, finding if they are inside the polygon

  for (int iy = minIy; iy <= maxIy; iy++) {
    for (int ix = minIx; ix <= maxIx; ix++) {
      Point_d pt;
      pt.x = _minxDeg + ix * _dxDeg;
      pt.y = _minyDeg + iy * _dyDeg;
      if (EGS_point_in_polygon(pt, (Point_d *) corners, 4)) {
        double interpVal = _interpPt(pt, corners, vals,
                                     missingVal, nearestNeighbor);
        size_t outputIndex = iz * _nx * _ny + iy * _nx + ix;
        valsInterp[outputIndex] = interpVal;
      }
    } // ix
  } // iy

}

//////////////////////////////////////////////
// interpolate points within polygon - int 32

void OdimHdf5ToMdv::_interpInsidePolygon(const Point_d *corners,
                                         const NcxxPort::si32 *vals,
                                         NcxxPort::si32 missingVal,
                                         size_t iz,
                                         vector<NcxxPort::si32> &valsInterp)
 
{

  // check we have 4 valid corners
  
  for (int ii = 0; ii < 4; ii++) {
    if (corners[ii].x == _missingLon ||
        corners[ii].y == _missingLat) {
      return;
    }
  }

  // check we have valid data
  
  int nGood = 0;
  for (int ii = 0; ii < 4; ii++) {
    if (vals[ii] != missingVal) {
      nGood++;
    }
  }
  if (nGood == 0) {
    return;
  }
  
  // compute the min/max grid indices

  int minIx, maxIx, minIy, maxIy;
  _computeMinMaxIndices(corners, minIx, maxIx, minIy, maxIy);

  // loop through the output grid points,
  // finding if they are inside the polygon

  for (int iy = minIy; iy <= maxIy; iy++) {
    for (int ix = minIx; ix <= maxIx; ix++) {
      Point_d pt;
      pt.x = _minxDeg + ix * _dxDeg;
      pt.y = _minyDeg + iy * _dyDeg;
      if (EGS_point_in_polygon(pt, (Point_d *) corners, 4)) {
        NcxxPort::si32 interpVal = _interpPt(pt, corners, vals, missingVal);
        size_t outputIndex = iz * _nx * _ny + iy * _nx + ix;
        valsInterp[outputIndex] = interpVal;
      }
    } // ix
  } // iy

}

//////////////////////////////////////////////
// interpolate points within polygon - int 16

void OdimHdf5ToMdv::_interpInsidePolygon(const Point_d *corners,
                                         const NcxxPort::si16 *vals,
                                         NcxxPort::si16 missingVal,
                                         size_t iz,
                                         vector<NcxxPort::si16> &valsInterp)
 
{

  // check we have 4 valid corners
  
  for (int ii = 0; ii < 4; ii++) {
    if (corners[ii].x == _missingLon ||
        corners[ii].y == _missingLat) {
      return;
    }
  }

  // check we have valid data
  
  int nGood = 0;
  for (int ii = 0; ii < 4; ii++) {
    if (vals[ii] != missingVal) {
      nGood++;
    }
  }
  if (nGood == 0) {
    return;
  }
  
  // compute the min/max grid indices

  int minIx, maxIx, minIy, maxIy;
  _computeMinMaxIndices(corners, minIx, maxIx, minIy, maxIy);

  // loop through the output grid points, finding if they are inside the polygon

  for (int iy = minIy; iy <= maxIy; iy++) {
    for (int ix = minIx; ix <= maxIx; ix++) {
      Point_d pt;
      pt.x = _minxDeg + ix * _dxDeg;
      pt.y = _minyDeg + iy * _dyDeg;
      if (EGS_point_in_polygon(pt, (Point_d *) corners, 4)) {
        NcxxPort::si16 interpVal = _interpPt(pt, corners, vals, missingVal);
        size_t outputIndex = iz * _nx * _ny + iy * _nx + ix;
        valsInterp[outputIndex] = interpVal;
      }
    } // ix
  } // iy

}

//////////////////////////////////////////////
// compute the min/max indices in the grid
// for the lat/lon corners

void OdimHdf5ToMdv::_computeMinMaxIndices(const Point_d *corners,
                                          int &minIx, int &maxIx,
                                          int &minIy, int &maxIy) 

{
  
  // compute lat/lon bounding box
  
  double minLat = corners[0].y;
  double maxLat = corners[0].y;
  double minLon = corners[0].x;
  double maxLon = corners[0].x;
  
  for (int ii = 1; ii < 4; ii++) {
    minLat = min(minLat, corners[ii].y);
    maxLat = max(maxLat, corners[ii].y);
    minLon = min(minLon, corners[ii].x);
    maxLon = max(maxLon, corners[ii].x);
  }
  
  // compute the output grid limits for the bounding box
  
  minIx = (int) ((minLon - _minxDeg) / _dxDeg);
  maxIx = (int) ((maxLon - _minxDeg) / _dxDeg + 1.0);
  
  minIy = (int) ((minLat - _minyDeg) / _dyDeg);
  maxIy = (int) ((maxLat - _minyDeg) / _dyDeg + 1.0);
  
  minIx = max(minIx, 0);
  minIy = max(minIy, 0);
  maxIx = min(maxIx, (int) _nx - 1);
  maxIy = min(maxIy, (int) _ny - 1);

}
  
//////////////////////////////////////////////
// interpolate point within polygon - double

NcxxPort::fl32 OdimHdf5ToMdv::_interpPt(const Point_d &pt,
                                        const Point_d *corners,
                                        const NcxxPort::fl32 *vals,
                                        NcxxPort::fl32 missingVal,
                                        bool nearestNeighbor)
  
{
  
  // compute the distances from the pt to the corners
  
  double dist[4];
  for (int ii = 0; ii < 3; ii++) {
    double dx = pt.x - corners[ii].x;
    double dy = pt.y - corners[ii].y;
    dist[ii] = sqrt(dx * dx + dy * dy);
  }
  
  // nearest neighbor?

  if (nearestNeighbor) {
    double minDist = 1.0e99;
    int minIndex = -1;
    for (int ii = 0; ii < 3; ii++) {
      if (dist[ii] < minDist) {
        minDist = dist[ii];
        if (vals[ii] != missingVal) {
          minIndex = ii;
        }
      }
    }
    return vals[minIndex];
  }
  
  // inverse distance weighted interpolation
  
  double weight[4];
  double sumWt = 0.0;
  double sumInterp = 0.0;
  for (int ii = 0; ii < 3; ii++) {
    if (vals[ii] != missingVal) {
      weight[ii] = pow(1.0 / dist[ii], _params.interp_power_parameter);
      sumWt += weight[ii];
      sumInterp += weight[ii] * vals[ii];
    }
  }
  double interpVal = sumInterp / sumWt;

  return interpVal;

}
  
//////////////////////////////////////////////
// interpolate point within polygon - int 32
// always uses nearest neighbor

int OdimHdf5ToMdv::_interpPt(const Point_d &pt,
                             const Point_d *corners,
                             const NcxxPort::si32 *vals,
                             int missingVal)
  
{
  
  // compute the distances from the pt to the corners
  
  double dist[4];
  for (int ii = 0; ii < 3; ii++) {
    double dx = pt.x - corners[ii].x;
    double dy = pt.y - corners[ii].y;
    dist[ii] = sqrt(dx * dx + dy * dy);
  }

  // find nearest

  double minDist = 1.0e99;
  int minIndex = -1;
  for (int ii = 0; ii < 3; ii++) {
    if (dist[ii] < minDist) {
      minDist = dist[ii];
      if (vals[ii] != missingVal) {
        minIndex = ii;
      }
    }
  }

  return vals[minIndex];
  
}
  
//////////////////////////////////////////////
// interpolate point within polygon - int 16
// always uses nearest neighbor

int OdimHdf5ToMdv::_interpPt(const Point_d &pt,
                             const Point_d *corners,
                             const NcxxPort::si16 *vals,
                             int missingVal)
  
{
  
  // compute the distances from the pt to the corners
  
  double dist[4];
  for (int ii = 0; ii < 3; ii++) {
    double dx = pt.x - corners[ii].x;
    double dy = pt.y - corners[ii].y;
    dist[ii] = sqrt(dx * dx + dy * dy);
  }

  // find nearest

  double minDist = 1.0e99;
  int minIndex = -1;
  for (int ii = 0; ii < 3; ii++) {
    if (dist[ii] < minDist) {
      minDist = dist[ii];
      if (vals[ii] != missingVal) {
        minIndex = ii;
      }
    }
  }

  return vals[minIndex];
  
}
  
/////////////////////////////////////////////////////////////////
// get lat/lon of a grid corner, for given height (zM)
// adjusting the corner locations for slant from radar to this point

Point_d OdimHdf5ToMdv::_getCornerLatLon(int iscan,
                                        int iray,
                                        double zM)

{

  // ht as a fraction of the spacecraft height
  
  double zFraction = zM / _scAlt[iscan];
  
  // get the point
  
  Point_d pt = _latLons[iscan][iray];
  if (pt.x == _missingLon || pt.y == _missingLat) {
    return pt;
  }
  
  double cornerLat = pt.y;
  double slantDeltaLat = (_scLat[iscan] - cornerLat) * zFraction;
  cornerLat += slantDeltaLat;
  
  double cornerLon = pt.x;
  double slantDeltaLon = (_scLon[iscan] - cornerLon) * zFraction;
  cornerLon += slantDeltaLon;

  Point_d corner;
  corner.y = cornerLat;
  corner.x = cornerLon;
  
  return corner;

}

/////////////////////////////////////////////////////////////////
// get lat/lon of a grid corner, at surface

Point_d OdimHdf5ToMdv::_getCornerLatLon(int iscan,
                                        int iray)

{
  return _latLons[iscan][iray];
}

////////////////////////////////////////////////////////
// for DBZ 3D fields,
// invert the height levels because the data is stored
// with the top first and decreasing in height 

void OdimHdf5ToMdv::_invertDbzGateLevels(OutputField *fld)
{
  
  // check for reflectivity
  
  if (fld->units != "dBZ" && fld->units != "mm/hr") {
    return;
  }

  // check for 3D float field
  
  if (fld->dims.size() != 3) {
    return;
  }
  if (fld->fl32Input.size() == 0) {
    return;
  }
    
  // prepare output grid
    
  fld->fl32Output.resize(fld->fl32Interp.size());
  
  // invert vlevels
  
  size_t nptsPlane = _nx * _ny;
  for (size_t iz = 0; iz < _nz; iz++) {
    for (size_t iy = 0; iy < _ny; iy++) {
      for (size_t ix = 0; ix < _nx; ix++) {
        size_t interpIndex = iz * nptsPlane + iy * _nx + ix;
        size_t outputIndex = (_nz - iz - 1) * nptsPlane + iy * _nx + ix;
        fld->fl32Output[outputIndex] = fld->fl32Interp[interpIndex];
      } // ix
    } // iy
  } // iz
  
}
  
////////////////////////////////////////////////////////
// for 3D fields,
// remap the gates onto specified vertical levels
// compute the max for the remapping

void OdimHdf5ToMdv::_remapVertLevels(OutputField *fld)
{
  
  // check for 3D field
  
  if (fld->dims.size() != 3) {
    return;
  }
  
  // compute heights of mid pt between specified levels
  
  vector<double> zMid;
  for (size_t ii = 0; ii < _zLevels.size() - 1; ii++) {
    zMid.push_back((_zLevels[ii] + _zLevels[ii+1]) / 2.0);
  }
  vector<int> lowIndex, highIndex;
  lowIndex.resize(_zLevels.size());
  highIndex.resize(_zLevels.size());
  lowIndex[0] = 0;
  highIndex[_zLevels.size()-1] = _nz - 1;
  for (size_t iz = 1; iz < _zLevels.size(); iz++) {
    lowIndex[iz] = (int) ((zMid[iz-1] - _minzKm) / _dzKm) + 1;
  }
  for (size_t iz = 0; iz < _zLevels.size() - 1; iz++) {
    highIndex[iz] = (int) ((zMid[iz] - _minzKm) / _dzKm);
  }

  if (fld->fl32Input.size() > 0) {
    
    // floats
    
    // save existing output in temp array
    
    vector<NcxxPort::fl32> outputOrig = fld->fl32Output;
    
    // prepare output grid
    
    size_t nPtsOutput = _nx * _ny * _zLevels.size();
    fld->fl32Output.resize(nPtsOutput);
    
    // compute max val for specified vlevels
    
    size_t nptsPlane = _nx * _ny;
    for (size_t iy = 0; iy < _ny; iy++) {
      for (size_t ix = 0; ix < _nx; ix++) {
        for (size_t iz = 0; iz < _zLevels.size(); iz++) {
          NcxxPort::fl32 maxVal = fld->fl32Missing;
          for (int jz = lowIndex[iz]; jz <= highIndex[iz]; jz++) {
            size_t interpIndex = jz * nptsPlane + iy * _nx + ix;
            if (outputOrig[interpIndex] != fld->fl32Missing) {
              maxVal = max(maxVal, outputOrig[interpIndex]);
            }
          } // jz
          size_t outputIndex = iz * nptsPlane + iy * _nx + ix;
          fld->fl32Output[outputIndex] = maxVal;
        } // iz
      } // ix
    } // iy
    
  } else if (fld->si16Input.size() > 0) {
    
    // ints
    
    // save existing output in temp array
    
    vector<NcxxPort::si16> outputOrig = fld->si16Output;
    
    // prepare output grid
    
    size_t nPtsOutput = _nx * _ny * _zLevels.size();
    fld->si16Output.resize(nPtsOutput);
    
    // compute max val for specified vlevels
    
    size_t nptsPlane = _nx * _ny;
    for (size_t iy = 0; iy < _ny; iy++) {
      for (size_t ix = 0; ix < _nx; ix++) {
        for (size_t iz = 0; iz < _zLevels.size(); iz++) {
          NcxxPort::si16 maxVal = fld->si16Missing;
          for (int jz = lowIndex[iz]; jz <= highIndex[iz]; jz++) {
            size_t interpIndex = jz * nptsPlane + iy * _nx + ix;
            if (outputOrig[interpIndex] != fld->si16Missing) {
              maxVal = max(maxVal, outputOrig[interpIndex]);
            }
          } // jz
          size_t outputIndex = iz * nptsPlane + iy * _nx + ix;
          fld->si16Output[outputIndex] = maxVal;
        } // iz
      } // ix
    } // iy
    
  } // else if (fld->si16Input.size() > 0)
  
}
  
/////////////////////////////////////////////////
// Set the master header from the NCF file
//
// Returns 0 on success, -1 on failure

void OdimHdf5ToMdv::_setMasterHeader(DsMdvx &mdvx)

{

  mdvx.clearMasterHeader();

  // time

  if (_params.debug) {
    cerr << "===========================================" << endl;
    cerr << "Found data set at start time: " << _startTime.asString(3) << endl;
  }

  mdvx.setBeginTime(_startTime.utime());
  mdvx.setEndTime(_endTime.utime());
  mdvx.setValidTime(_endTime.utime());
  
  // data collection type
  
  mdvx.setDataCollectionType(Mdvx::DATA_MEASURED);

  // data set name, source and info

  mdvx.setDataSetName(_params.data_set_name);
  mdvx.setDataSetSource("NASA-GPM");
  mdvx.setDataSetInfo(_history.c_str());

}

///////////////////////////////////
// Add the Mdvx fields

void OdimHdf5ToMdv::_addFieldToMdvx(DsMdvx &mdvx,
                                    OutputField *fld)

{

  int nz = _zLevels.size();
  double minzKm = _zLevels[0];
  if (fld->dims.size() == 2) {
    nz = 1;
  }
  
  if (fld->si16Output.size() > 0) {
    
    MdvxField *field = _createMdvxField(fld->params.outputName,
                                        fld->params.longName,
                                        fld->units,
                                        _nx, _ny, nz,
                                        _minxDeg, _minyDeg, minzKm,
                                        _dxDeg, _dyDeg, _dzKm,
                                        fld->si16Missing,
                                        fld->si16Output.data());
    
    field->convertType((Mdvx::encoding_type_t) fld->params.encoding,
                       Mdvx::COMPRESSION_GZIP);
    
    mdvx.addField(field);
    
  } else if (fld->fl32Output.size() > 0) {
      
    MdvxField *field = _createMdvxField(fld->params.outputName,
                                        fld->params.longName,
                                        fld->units,
                                        _nx, _ny, nz,
                                        _minxDeg, _minyDeg, minzKm,
                                        _dxDeg, _dyDeg, _dzKm,
                                        fld->fl32Missing,
                                        fld->fl32Output.data());
    
    field->convertType((Mdvx::encoding_type_t) fld->params.encoding,
                       Mdvx::COMPRESSION_GZIP);
    
    mdvx.addField(field);
    
  }
  
}
      
///////////////////////////////////
// Create an Mdvx field - floats

MdvxField *OdimHdf5ToMdv::_createMdvxField(const string &fieldName,
                                           const string &longName,
                                           const string &units,
                                           size_t nx, size_t ny, size_t nz,
                                           double minx, double miny, double minz,
                                           double dx, double dy, double dz,
                                           NcxxPort::fl32 missingVal,
                                           NcxxPort::fl32 *vals)

{

  // check max levels

  if (nz > MDV_MAX_VLEVELS) {
    nz = MDV_MAX_VLEVELS;
  }

  // set up MdvxField headers

  Mdvx::field_header_t fhdr;
  MEM_zero(fhdr);
  STRncopy(fhdr.field_name, fieldName.c_str(), MDV_SHORT_FIELD_LEN);
  
  // _inputProj.syncToFieldHdr(fhdr);

  fhdr.compression_type = Mdvx::COMPRESSION_NONE;
  fhdr.transform_type = Mdvx::DATA_TRANSFORM_NONE;
  fhdr.scaling_type = Mdvx::SCALING_NONE;
  
  fhdr.native_vlevel_type = Mdvx::VERT_TYPE_Z;
  fhdr.vlevel_type = Mdvx::VERT_TYPE_Z;
  fhdr.dz_constant = true;
  if (nz == 1) {
    fhdr.data_dimension = 2;
  } else {
    fhdr.data_dimension = 3;
  }
  
  fhdr.scale = 1.0;
  fhdr.bad_data_value = missingVal;
  fhdr.missing_data_value = missingVal;
  
  fhdr.proj_type = Mdvx::PROJ_LATLON;
  fhdr.encoding_type = Mdvx::ENCODING_FLOAT32;
  fhdr.data_element_nbytes = sizeof(fl32);
  
  fhdr.nx = nx;
  fhdr.ny = ny;
  fhdr.nz = nz;

  fhdr.volume_size = fhdr.nx * fhdr.ny * fhdr.nz * sizeof(fl32);

  fhdr.grid_minx = minx;
  fhdr.grid_miny = miny;
  fhdr.grid_minz = minz;

  fhdr.grid_dx = dx;
  fhdr.grid_dy = dy;
  fhdr.grid_dz = dz;
  
  Mdvx::vlevel_header_t vhdr;
  MEM_zero(vhdr);
  
  for (size_t ii = 0; ii < nz; ii++) {
    vhdr.type[ii] = Mdvx::VERT_TYPE_Z;
    vhdr.level[ii] = _zLevels[ii];
  }

  // create MdvxField object
  // converting data to encoding and compression types
  
  MdvxField *field = new MdvxField(fhdr, vhdr, vals);

  // set names etc
  
  field->setFieldName(fieldName);
  field->setFieldNameLong(longName);
  field->setUnits(units);
  field->setTransform("");

  return field;

}
  
///////////////////////////////////
// Create an Mdvx field - ints

MdvxField *OdimHdf5ToMdv::_createMdvxField(const string &fieldName,
                                           const string &longName,
                                           const string &units,
                                           size_t nx, size_t ny, size_t nz,
                                           double minx, double miny, double minz,
                                           double dx, double dy, double dz,
                                           NcxxPort::si16 missingVal,
                                           NcxxPort::si16 *vals)

{

  // check max levels

  if (nz > MDV_MAX_VLEVELS) {
    nz = MDV_MAX_VLEVELS;
  }

  // set up MdvxField headers

  Mdvx::field_header_t fhdr;
  MEM_zero(fhdr);
  STRncopy(fhdr.field_name, fieldName.c_str(), MDV_SHORT_FIELD_LEN);
  
  // _inputProj.syncToFieldHdr(fhdr);

  fhdr.compression_type = Mdvx::COMPRESSION_NONE;
  fhdr.transform_type = Mdvx::DATA_TRANSFORM_NONE;
  fhdr.scaling_type = Mdvx::SCALING_NONE;
  
  fhdr.native_vlevel_type = Mdvx::VERT_TYPE_Z;
  fhdr.vlevel_type = Mdvx::VERT_TYPE_Z;
  fhdr.dz_constant = true;
  if (nz == 1) {
    fhdr.data_dimension = 2;
  } else {
    fhdr.data_dimension = 3;
  }
  
  fhdr.scale = 1.0;
  fhdr.bad_data_value = missingVal;
  fhdr.missing_data_value = missingVal;
  
  fhdr.proj_type = Mdvx::PROJ_LATLON;
  fhdr.encoding_type = Mdvx::ENCODING_INT16;
  fhdr.data_element_nbytes = sizeof(si16);
  
  fhdr.nx = nx;
  fhdr.ny = ny;
  fhdr.nz = nz;

  fhdr.volume_size = fhdr.nx * fhdr.ny * fhdr.nz * sizeof(si16);

  fhdr.grid_minx = minx;
  fhdr.grid_miny = miny;
  fhdr.grid_minz = minz;

  fhdr.grid_dx = dx;
  fhdr.grid_dy = dy;
  fhdr.grid_dz = dz;
  
  Mdvx::vlevel_header_t vhdr;
  MEM_zero(vhdr);
  
  for (size_t ii = 0; ii < nz; ii++) {
    vhdr.type[ii] = Mdvx::VERT_TYPE_Z;
    vhdr.level[ii] = _zLevels[ii];
  }

  // create MdvxField object
  // converting data to encoding and compression types
  
  MdvxField *field = new MdvxField(fhdr, vhdr, vals);

  // set names etc
  
  field->setFieldName(fieldName);
  field->setFieldNameLong(longName);
  field->setUnits(units);
  field->setTransform("");

  return field;

}
  
