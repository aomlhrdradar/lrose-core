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
// Era5Nc2Mdv.hh
//
// Mike Dixon, EOL, NCAR
// P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Nov 2023
//
///////////////////////////////////////////////////////////////
//
// Era5Nc2Mdv reads ERA5 data in NetCDF format, as generated by
// NCAR CISL software, and converts to MDV
//
////////////////////////////////////////////////////////////////

#ifndef Era5Nc2Mdv_H
#define Era5Nc2Mdv_H

#include <string>
#include <didss/DsInputPath.hh>
#include <Mdv/DsMdvx.hh>
#include <Mdv/MdvxProj.hh>
#include "Args.hh"
#include "Params.hh"
using namespace std;

////////////////////////
// This class

class Era5Nc2Mdv {
  
public:

  // constructor

  Era5Nc2Mdv (int argc, char **argv);

  // destructor
  
  ~Era5Nc2Mdv();

  // run 

  int Run();

  // data members

  bool isOK;

protected:
  
private:

  string _progName;
  char *_paramsPath;
  Args _args;
  Params _params;
  DsInputPath *_input;

  fl32 _missingFloat;

  // data set members
  
  size_t _nTimesInFile;
  size_t _nLat, _nLon;
  vector<double> _lat, _lon;
  vector<DateTime> _dataTimes;
  int _deltaTimeSecs;
  vector<double> _levels;
  vector<string> _fieldNames;

  string _dataSource;
  string _history;
  string _datasetUrl;
  string _datasetDoi;
  
  int _nTimes;
  time_t _validTime;
  int _nx, _ny, _nz;
  double _minx, _miny, _minz;
  double _dx, _dy, _dz;
  bool _inverty;

  MdvxProj _inputProj;
  
  // private methods

  int _setGeom(const vector<string> &pathsAtTime);
  int _createVol(const vector<string> &pathsAtTime, size_t timeIndex);
  void _printGeom(ostream &out);
  
  /// set MDV headers

  int _setMasterHeader(DsMdvx &mdvx, time_t volTime);
  MdvxField *_createMdvxField(const string &fieldName);
  int _addDataFields(DsMdvx &mdvx, int itime);
  //   int _addDataField(Nc3Var *var, DsMdvx &mdvx, int itime);
  
  MdvxField *_createRegularLatlonField(const string &fieldName,
                                       const string &longName,
                                       const string &units,
                                       const float *vals);

  void _remapOutput(DsMdvx &mdvx);
  void _autoRemapToLatLon(DsMdvx &mdvx);

  bool _checkDxIsConstant();
  bool _checkDyIsConstant();
  void _initMercatorFromInputCoords();
  int _findValidLatLonLimits();

  int _getClosestLatIndex(double latitude, double tolerance);
  int _getClosestLonIndex(double longitude, double tolerance);

};

#endif

