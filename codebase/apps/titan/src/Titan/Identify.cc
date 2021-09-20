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
/////////////////////////////////////////////////////////////
// Identify.cc
//
// Identify class
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// November 1998
//
///////////////////////////////////////////////////////////////

#include "Identify.hh"
#include "Props.hh"
#include "Verify.hh"
#include "Sounding.hh"
#include "OutputMdv.hh"

#include <iostream>
#include <toolsa/umisc.h>
#include <toolsa/str.h>
#include <toolsa/pmu.h>
using namespace std;

//////////////
// constructor
//

Identify::Identify(const string &prog_name, const Params &params,
		   const InputMdv &input_mdv, TitanStormFile &storm_file):
  Worker(prog_name, params),
  _inputMdv(input_mdv),
  _sfile(storm_file),
  _clumping()

{

  _props = NULL;
  _verify = NULL;
  
  if (_params.create_verification_files) {
    _verify = new Verify(_progName, _params, _inputMdv);
  }

  _props = new Props(_progName, _params, _inputMdv, _sfile, _verify);

}

/////////////
// destructor
//

Identify::~Identify()

{

  if (_verify) {
    delete (_verify);
  }
  if (_props) {
    delete (_props);
  }

}

//////////////////////////////////////////////////////
// run()
//
// Perform storm identification for given scan number
//
// Returns 0 on success, -1 on failure.

int Identify::run(int scan_num)

{

  PMU_auto_register("Identifying storms");
    
  // initialize

  _nStorms = 0;
  const titan_grid_t &tgrid = _inputMdv.grid;
  int nBytesPlane = tgrid.nx * tgrid.ny;
  int nplanes = _inputMdv.nPlanes;

  // prepare verification and morphology objects as required

  if (_verify) {
    _verify->prepareGrids();
  }

  // initialize grid geometry
  
  _gridGeom.setNx(tgrid.nx);
  _gridGeom.setNy(tgrid.ny);
  _gridGeom.setDx(tgrid.dx);
  _gridGeom.setDy(tgrid.dy);
  _gridGeom.setMinx(tgrid.minx);
  _gridGeom.setMiny(tgrid.miny);

  _gridGeom.clearZKm();
  for (int ii = 0; ii < tgrid.nz; ii++) {
    _gridGeom.addZKm(tgrid.minz + ii * tgrid.dz);
  }

  _gridGeom.setIsLatLon(false);
  switch (tgrid.proj_type) {
    case TITAN_PROJ_LATLON:
      _gridGeom.setProjType(PjgTypes::PROJ_LATLON);
      _gridGeom.setIsLatLon(true);
      break;
    case TITAN_PROJ_FLAT:
      _gridGeom.setProjType(PjgTypes::PROJ_FLAT);
      break;
    case TITAN_PROJ_STEREOGRAPHIC:
      _gridGeom.setProjType(PjgTypes::PROJ_STEREOGRAPHIC);
      break;
    case TITAN_PROJ_LAMBERT_CONF:
      _gridGeom.setProjType(PjgTypes::PROJ_LAMBERT_CONF);
      break;
    case TITAN_PROJ_MERCATOR:
      _gridGeom.setProjType(PjgTypes::PROJ_MERCATOR);
      break;
    case TITAN_PROJ_POLAR_STEREO:
      _gridGeom.setProjType(PjgTypes::PROJ_POLAR_STEREO);
      break;
    case TITAN_PROJ_POLAR_ST_ELLIP:
      _gridGeom.setProjType(PjgTypes::PROJ_POLAR_ST_ELLIP);
      break;
    case TITAN_PROJ_CYL_EQUIDIST:
      _gridGeom.setProjType(PjgTypes::PROJ_CYL_EQUIDIST);
      break;
    case TITAN_PROJ_OBLIQUE_STEREO:
      _gridGeom.setProjType(PjgTypes::PROJ_OBLIQUE_STEREO);
      break;
    case TITAN_PROJ_TRANS_MERCATOR:
      _gridGeom.setProjType(PjgTypes::PROJ_TRANS_MERCATOR);
      break;
    case TITAN_PROJ_ALBERS:
      _gridGeom.setProjType(PjgTypes::PROJ_ALBERS);
      break;
    case TITAN_PROJ_LAMBERT_AZIM:
      _gridGeom.setProjType(PjgTypes::PROJ_LAMBERT_AZIM);
      break;
  }
  
  // set the parameters and input data for dual threshold object

  if (_params.debug >= Params::DEBUG_VERBOSE) {
    _dualT.setDebug(true);
  }
  _dualT.setPrimaryThreshold(_params.low_dbz_threshold);
  _dualT.setSecondaryThreshold(_params.dual_threshold.dbz_threshold);
  _dualT.setMinFractionAllParts(_params.dual_threshold.min_fraction_all_parts);
  _dualT.setMinFractionEachPart(_params.dual_threshold.min_fraction_each_part);
  _dualT.setMinAreaEachPart(_params.dual_threshold.min_area_each_part);
  _dualT.setMinClumpVolume(_params.min_storm_size);
  _dualT.setMaxClumpVolume(_params.max_storm_size);
  _dualT.setInputData(_gridGeom, _inputMdv.dbzVol);

  // perform clumping

  fl32 *startDbz = _inputMdv.dbzVol + _inputMdv.minValidLayer * nBytesPlane;
  _nClumps = _clumping.performClumping(tgrid.nx, tgrid.ny, nplanes,
                                       startDbz,
                                       _params.min_grid_overlap,
                                       _params.low_dbz_threshold);
  
  if (_params.debug >= Params::DEBUG_VERBOSE) {
    fprintf(stderr, "Number of clumps  =  %d\n", _nClumps);
  }

  // update the verification grid

  if (_verify) {
    const Clump_order *clump = _clumping.getClumps();
    for (int i = 0; i < _clumping.getNClumps(); i++, clump++) {
      _verify->updateAllStormsGrid(*clump);
    }
  }
  
  // lock the header file

  if (_sfile.LockHeaderFile("w")) {
    cerr << "ERROR - " << _progName << "Identify::run" << endl;
    cerr << _sfile.getErrStr() << endl;
    return(-1);
  }

  // process the clumps found

  if (_processClumps(scan_num)) {
    return (-1);
  }
  
  // unlock the header file

  if (_sfile.UnlockHeaderFile()) {
    cerr << "ERROR - " << _progName << "Identify::run" << endl;
    cerr << _sfile.getErrStr() << endl;
    return(-1);
  }

  if (_verify) {
    _verify->writeOutputMdv();
  }
  
  if (_params.create_dual_threshold_files) {
    _writeDualThreshMdv();
  }

  return (0);

}

////////////////////
// _processClumps()
//
//
// Checks storm props
// If necessary splits storms.
// Passes clumps to props_compute for computations of storm properties.
//
// Returns 0 on success, -1 on failure
//

int Identify::_processClumps(int scan_num)
     
{

  // read in storm file header

  if (_sfile.ReadHeader()) {
    cerr << "ERROR - " << _progName << "Identify::_processClumps" << endl;
    cerr << _sfile.getErrStr() << endl;
    return(-1);
  }

  // initialize the computation module for storm props
  
  _props->init();

  // loop through the clumps - index starts at 1
  
  const Clump_order *clump = _clumping.getClumps();
  
  for (int iclump = 0; iclump < _nClumps; iclump++, clump++) {
    
    ClumpGrid gclump;
    gclump.init(clump, _gridGeom, 0, 0);

    // dual threshold takes precedence over morphology

    if (_params.use_dual_threshold) {
      
      if (_params.debug >= Params::DEBUG_EXTRA) {
        fprintf(stderr,
                "==>> processing clump: size, startIx, startIy, nx, ny, offsetx, offsety: "
                "%g, %d, %d, %d, %d, %g, %g\n",
                gclump.clumpSize,
                gclump.startIx, gclump.startIy,
                gclump.nX, gclump.nY,
                gclump.offsetX, gclump.offsetY);
      }
      
      int n_sub_clumps = _dualT.compute(gclump);

      if (n_sub_clumps == 1) {
	
	if (_processThisClump(gclump)) {
	  return (-1);
	}

      } else {

	for (int i = 0; i < n_sub_clumps; i++) {
	  if (_processThisClump(_dualT.subClumps()[i])) {
	    return (-1);
	  }
	}

      }

    } else {
      
      if (_processThisClump(gclump)) {
	return (-1);
      }
      
    }

  } // iclump
  
  // load up scan structure
  
  storm_file_scan_header_t &scan_hdr = _sfile._scan;
  
  scan_hdr.nbytes_char = TITAN_N_GRID_LABELS * TITAN_GRID_UNITS_LEN;
  scan_hdr.scan_num = scan_num;
  scan_hdr.nstorms = _nStorms;
  scan_hdr.time = _inputMdv.mdvx.getMasterHeader().time_centroid;
  scan_hdr.min_z = _props->getMinValidZ();
  scan_hdr.delta_z = _inputMdv.grid.dz;
  scan_hdr.grid = _inputMdv.grid;

  // for now height of freezing is a static user parameter
  // eventually it may be derived dynamically from a sounding

  Sounding &sndg = Sounding::inst();
  scan_hdr.ht_of_freezing = sndg.getProfile().getFreezingLevel();
  
  // read in storm file header

  if (_sfile.ReadHeader()) {
    cerr << "ERROR - " << _progName << "Identify::_processClumps" << endl;
    cerr << _sfile.getErrStr() << endl;
    return(-1);
  }

  // write the scan header and global props

  if (_sfile.WriteScan(scan_num)) {
    cerr << "ERROR - " << _progName << "Identify::_processClumps" << endl;
    cerr << _sfile.getErrStr() << endl;
    return(-1);
  }

  // update the file header
  
  if (scan_num == 0) {
    _sfile._header.start_time = scan_hdr.time;
  }
  
  _sfile._header.end_time = scan_hdr.time;
  
  // fill in number of scans, tracks and current file size
  
  _sfile._header.n_scans = scan_num + 1;
  
  // rewrite header
  
  if (_sfile.WriteHeader()) {
    cerr << "ERROR - " << _progName << "Identify::_processClumps" << endl;
    cerr << _sfile.getErrStr() << endl;
    return(-1);
  }
  _sfile.FlushFiles();

  // printout

  if (_params.debug) {
    fprintf(stderr, "========== identification ========\n");
    fprintf(stderr, "Scan number %d\n", scan_num);
    fprintf(stderr, "  nstorms : %d\n", _nStorms);
    fprintf(stderr, "  Time: %s\n",
	    utimstr(_sfile._header.end_time));
  }
    
  return (0);
  
}

/////////////////////////////////
// _processThisClump()
//

int Identify::_processThisClump(const ClumpGrid &clump_grid)

{

  // check size

  if (clump_grid.clumpSize < _params.min_storm_size ||
      clump_grid.clumpSize > _params.max_storm_size) {
    return(0);
  }

  if (_params.debug >= Params::DEBUG_EXTRA) {
    fprintf(stderr,
	    "Clump: size, startIx, startIy, nx, ny, offsetx, offsety: "
	    "%g, %d, %d, %d, %d, %g, %g\n",
	    clump_grid.clumpSize,
	    clump_grid.startIx, clump_grid.startIy,
	    clump_grid.nX, clump_grid.nY,
	    clump_grid.offsetX, clump_grid.offsetY);
  }
  
  _sfile.AllocGprops(_nStorms + 1);

  if (_props->compute(clump_grid, _nStorms) == 0) {
    
    // success - write the storm props to storm file

    if (_sfile.WriteProps(_nStorms)) {
      cerr << "ERROR - " << _progName << "Identify::_processThisClump" << endl;
      cerr << _sfile.getErrStr() << endl;
      return(-1);
    }

    _nStorms++;

  }

  return (0);

}

/////////////////////////////////////////////////////////
// writeDualThreshMdv()
//
// Write out debug fields for dual threshold clumps

int Identify::_writeDualThreshMdv()
  
{
  
  // set info str
  
  char info[256];
  
  sprintf(info,
	  "\n"
	  "  Dual threshold analysis: \n"
 	  "    dbz_threshold: %g\n"
 	  "    min_fraction_all_parts: %g\n"
 	  "    min_fraction_each_part: %g\n",
	  _params.dual_threshold.dbz_threshold,
	  _params.dual_threshold.min_fraction_all_parts,
	  _params.dual_threshold.min_fraction_each_part);
  
  // create output MDV object
  
  OutputMdv out(_progName, _params,
		_inputMdv, info,
		"TITAN dual thresholds",
		_params.dual_threshold_url);
  
  // Add the fields

  out.addField("Composite reflectivity", "CompDbz", "dBZ", "dBZ", 
               _dualT.getCompFileGrid());
  out.addField("All clumps", "All", "count", "none", 1.0, 0.0, 
               _dualT.getAllFileGrid());
  out.addField("Valid clumps", "Valid", "count", "none", 1.0, 0.0, 
               _dualT.getValidFileGrid());
  out.addField("Grown clumps", "Grown", "count", "none", 1.0, 0.0, 
               _dualT.getGrownFileGrid());

  // write out file
  
  if (out.writeVol()) {
    cerr << "ERROR - Identify::writeDualThreshMdv()" << endl;
    return -1;
  }
  
  return 0;

}



