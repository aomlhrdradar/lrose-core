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
// HaloRadxFile.hh
//
// HaloRadxFile object
//
// Halosphere support for lidar radial data
//
// Mike Dixon, RAP, NCAR
// P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Feb 2013
//
// Brenda Javornik, EOL, NCAR
// July 2023
//
///////////////////////////////////////////////////////////////

#ifndef HaloRadxFile_HH
#define HaloRadxFile_HH

#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include <cmath>

#include <Radx/Radx.hh>
#include <Radx/RadxFile.hh>
#include <Radx/RadxRangeGeom.hh>
#include <Radx/RadxArray.hh>

class RadxVol;
class RadxRay;
class RadxBuf;
using namespace std;

///////////////////////////////////////////////////////////////////
/// This subclass of RadxFile handles I/O for Halosphere lidar files.

class HaloRadxFile : public RadxFile

{
  
public:

  /// Constructor
  
  HaloRadxFile();
  
  /// Destructor
  
  virtual ~HaloRadxFile();
  
  /// clear all data
  
  virtual void clear();

  //////////////////////////////////////////////////////////////
  /// \name File inspection:
  //@{
  
  /// Check if specified file is a leosphere file.
  /// Returns true on success, false on failure
  
  virtual bool isSupported(const string &path);
    
  /// Check if the specifed file is a leosphere file.
  ///
  /// Returns true on success, false on failure.
  
  bool isHaloPhotonics(const string &path);
  
  //@}
  
  //////////////////////////////////////////////////////////////
  /// \name Perform writing:
  //@{
  
  //////////////////////////////////////////////////////////////
  /// Write data from RadxVol volume to the specified directory.
  ///
  /// If addDaySubDir is true, a subdirectory will be
  /// created with the name dir/yyyymmdd/.
  ///
  /// If addYearSubDir is true, a subdirectory will be
  /// created with the name dir/yyyy/.
  ///
  /// If both addDaySubDir and addYearSubDir are true,
  /// the subdirectory will be dir/yyyy/yyyymmdd/.
  ///
  /// Returns 0 on success, -1 on failure
  ///
  /// Use getErrStr() to get error message if error occurs.
  /// Use getDirInUse() for directory to which the data was written.
  /// Use getPathInUse() for path to which the data was written.
  
  virtual int writeToDir(const RadxVol &vol,
                         const string &dir,
                         bool addDaySubDir,
                         bool addYearSubDir);
  
  //////////////////////////////////////////////////////////////
  /// Write data from RadxVol volume to the specified path.
  //
  /// Returns 0 on success, -1 on failure
  //
  /// Use getErrStr() to get error message if error occurs.
  /// Use getPathInUse() for path to which the data was written.
  
  virtual int writeToPath(const RadxVol &vol,
                          const string &path);

  //@}

  //////////////////////////////////////////////////////////////
  /// \name Perform the read:
  //@{
  
  /// Read in data file from specified path,
  /// load up volume object.
  /// Returns 0 on success, -1 on failure
  /// Use getErrStr() if error occurs
  
  virtual int readFromPath(const string &path,
                           RadxVol &vol);

  //@}

  ////////////////////////
  /// \name Printing:
  //@{
  
  /// Print summary after read.
  
  virtual void print(ostream &out) const;
  
  /// Print UF data file in native format.
  ///
  /// Returns 0 on success, -1 on failure.
  ///
  /// Use getErrStr() if error occurs
  
  virtual int printNative(const string &path, ostream &out,
                          bool printRays, bool printData);

  //@}
  
protected:
private:

  string _configFileName;
  string _configXml;
  string _modelStr;
  int _modelNum;
  int _modelID;

  // objects to be set on read
  
  string _instrumentName;
  string _siteName;
  string _comments;

  double _latitude;
  double _longitude;
  double _altitudeM;

  double _wavelengthM;
  double _nyquist;
  
  int _nSamples;

  double _startRangeKm;
  double _gateSpacingKm;
  vector<double> _ranges;
  vector<string> _columnLabels;

  int _timeStampIndex;
  int _elevationIndex;
  int _azimuthIndex;
  int _rangeColumnIndex;

  double _directionOffset;
  double _headingAngle;
  
  double _azLimit1, _azLimit2;
  double _elLimit1, _elLimit2;
  double _fixedAngle;
  bool _rhiMode;

  class Field {
  public:
    string label;
    string origName;
    string name;
    string longName;
    string standardName;
    string units;
    bool folds;
    int index;
    vector<Radx::fl32> data;    
    Field() {
      folds = false;
    }
  };
  vector<Field> _fields;
  vector<Field> _rayQualifiers;

  set<string> _fieldNames;
  map<string, size_t> _fieldCols;

  std::unordered_map<std::string, std::string> _rawHeaderInfo;

  vector<RadxRay *> _rays;

  // file handle
 
  FILE *_file;

  //const static string NGatesLabel("Number of gates");

  // private methods
  
  void _clearRays();
  void _clearHeaderData();

  int _readHeaderData(string &xml);
  void _getFields(unordered_map<string, string> &dictionary);
  void _getRayQualifiers(unordered_map<string, string> &dictionary);

  void _findFields(string &columnLabel);
  void _findRayQualifiers(string &columnLabel);
  void _addField(string &name, string &units, int columnIndex);

  //void _checkForFieldQualifier(string columnLabel, size_t columnIndex);
  //void _printFieldQualifiers();
  void _addRayQualifiers(RadxRay *ray, vector<string> &tok);


  int _readRayQualifiers(RadxRay *ray, char *line);
  int _readRayData(int  nRaysInFile, int nGatesPerRay);
  int _readRayData(RadxRay *ray, vector<Field> &fields);

  void _fillRay(RadxRay *ray, vector<Field> &fields);
  void _readNStoreFieldData(char *line, vector<Field> &fields,
    int gateIdx);  
  int _getNGates(unordered_map<string, string> &dictionary);
  int _getNRays(unordered_map<string, string> &dictionary);
/*
  int _readRayDataModel200();
  int _readRayDataModel70();
  int _readRayDataModel866();
  int _readRayDataModel7();
  int _readRayDataModel100();
*/
  bool findAzimuthAngle(string &columnLabel);
  bool findElevationAngle(string &columnLabel);
  int findTimeStamp();
  int findAzimuthAngle();
  int findElevationAngle();

  int identifyModel(unordered_map<string, string> &dictionary);

  int _openRead(const string &path);
  void _close();

  int _loadReadVolume();
  
  int _printConfig(const string &path, ostream &out);
  int _loadConfigXml(const string &path);
  void _setStatusFromXml(const string &xml);
  void _setAnglesFromXml(const string &xml);

  string _substituteChar(const string &source, char find, char replace);
  string _stripLine(const char *line);
  bool _contains(string &s1, string &s2);
  void decipherField(RadxRay *ray, Field &field, string value);
  
};

#endif
