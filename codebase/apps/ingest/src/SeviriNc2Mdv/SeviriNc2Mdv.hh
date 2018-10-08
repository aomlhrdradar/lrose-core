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

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*
 *  $Id: SeviriNc2Mdv.hh,v 1.8 2018/01/26 18:43:35 jcraig Exp $
 */
/**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**/

////////////////////////////////////////////////////////////////////////////////
//
// Class:	SeviriNc2Mdv
//
// Author:	G. M. Cunning
//
// Date:	Wed Jul 25 20:59:10 2007
//
// Description: This application is a reformtter fo SEVIRI satllite data. The 
//		incoming format is netcdf3, and the output format is MDV.
//
//		At this time, the netcdf file are generated by file reformatting 
//		function from within McIdas. In addition, the data is registered to a
//		equidistant cylindrical projection. At RAL, we refer to this projection
//		as lat-lon. In Mcidas, the projection is referred to as rectilinear.
//		For more information about the McIdas operations look at the auditTrail
//		variable.
//
//		An example filename is  200501010012.01.nc. This naming convention
//		encodes as <YYYY><MM><DD><HH><mm>.<BB>. <YYYY><MM><DD><HH><mm> is the 
//		date and time. <BB> is the band or channel number. 



#ifndef    SEVIRI_NC_2_MDV_H
#define    SEVIRI_NC_2_MDV_H

// C++ include files
#include <string>

// System/RAP include files
#include <toolsa/os_config.h>
#include <dataport/port_types.h>

using namespace std;

/////////////////////////
// Forward declarations
class Params;
class Args;
class OutputFile;
class SeviriData;
class SeviriConverter;
class Pjg;
class DsTrigger;

/////////////////////////
// Class declaration
class SeviriNc2Mdv {
  
public:

  // singleton instance invocations
  static SeviriNc2Mdv *instance(int argc, char **argv);
  static SeviriNc2Mdv *instance();

  // destructor  
  ~SeviriNc2Mdv();

  // getErrStr -- returns error message
  string getErrStr() const { return _errStr; }  // run 
  
  // isOK -- check on class
  bool isOK() const { return _isOK; }
  
  // run -- Execution of program 
  int run();

protected:
  
private:

  static const string _className;

  static const float TINY_VALUE; 

  bool _isOK;
  string _progName;
  string _errStr;
  Args *_args;
  Params *_params;

  OutputFile *_outputFile;

  SeviriData *_seviriData;

  SeviriConverter *_seviriConverter;

  Pjg *_seviriPjg;

  DsTrigger *_dsTrigger;

  // Singleton instance pointer
  static SeviriNc2Mdv *_instance; 

  // hide the constructors and copy operator
  SeviriNc2Mdv();
  SeviriNc2Mdv(const SeviriNc2Mdv &);
  SeviriNc2Mdv  &operator=(const SeviriNc2Mdv &);

  void _clearErrStr() { _errStr = ""; }
  bool _compressFile(const string& path, const string& ext);
  void _initialize(int argc, char **argv);
  bool _setupInput();
  string _uncompressFile(const string& in_path);
  bool _processBand();
};

# endif   // SEVIRI_NC_2_MDV_H
