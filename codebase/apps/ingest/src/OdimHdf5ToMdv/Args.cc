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
//////////////////////////////////////////////////////////
// Args.cc : command line args
//
// Mike Dixon, EOL, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// May 2021
//
//////////////////////////////////////////////////////////

#include "Args.hh"
#include "Params.hh"
#include <cstring>
#include <iostream>
#include <toolsa/DateTime.hh>
#include <toolsa/umisc.h>
using namespace std;

// parse

int Args::parse(int argc, char **argv, string &prog_name)

{

  int iret = 0;
  char tmp_str[256];

  // intialize

  TDRP_init_override(&override);
  startTime = 0;
  endTime = 0;

  // loop through args
  
  for (int i =  1; i < argc; i++) {

    if (!strcmp(argv[i], "--") ||
	!strcmp(argv[i], "-h") ||
	!strcmp(argv[i], "-help") ||
	!strcmp(argv[i], "-man")) {
      
      usage(prog_name, cout);
      exit (0);
      
    } else if (!strcmp(argv[i], "-debug") ||
	       !strcmp(argv[i], "-d")) {
      
      sprintf(tmp_str, "debug = DEBUG_NORM;");
      TDRP_add_override(&override, tmp_str);
      
    } else if (!strcmp(argv[i], "-verbose") ||
	       !strcmp(argv[i], "-v")) {
      
      sprintf(tmp_str, "debug = DEBUG_VERBOSE;");
      TDRP_add_override(&override, tmp_str);
      
    } else if (!strcmp(argv[i], "-extra") ||
	       !strcmp(argv[i], "-vv")) {
      
      sprintf(tmp_str, "debug = DEBUG_EXTRA;");
      TDRP_add_override(&override, tmp_str);
      
    } else if (!strcmp(argv[i], "-i")) {
      if (i < argc - 1) {
	sprintf(tmp_str, "instance = \"%s\";", argv[i+1]);
	TDRP_add_override(&override, tmp_str);
      } else {
	iret = -1;
      }
    } else if (!strcmp(argv[i], "-in_dir")) {
      if(i < argc - 1) {
	sprintf(tmp_str, "input_dir = \"%s\";", argv[i+1]);
	TDRP_add_override(&override, tmp_str);
      } else {
	iret = -1;
      }
    } else if (!strcmp(argv[i], "-out_url")) {
      if(i < argc - 1) {
	sprintf(tmp_str, "output_url = \"%s\";", argv[i+1]);
	TDRP_add_override(&override, tmp_str);
      }
      else {
	iret = -1;
      }
    } else if (!strcmp(argv[i], "-start")) {
      
      if (i < argc - 1) {
	startTime = DateTime::parseDateTime(argv[++i]);
	if (startTime == DateTime::NEVER)
	{
	  iret = -1;
	}
	else
	{
	  sprintf(tmp_str, "mode = ARCHIVE;");
	  TDRP_add_override(&override, tmp_str);
	}
      } else {
	iret = -1;
      }
	
    } else if (!strcmp(argv[i], "-end")) {
      
      if (i < argc - 1) {
	endTime = DateTime::parseDateTime(argv[++i]);
	if (endTime == DateTime::NEVER)
	{
	  iret = -1;
	}
	else
	{
	  sprintf(tmp_str, "mode = ARCHIVE;");
	  TDRP_add_override(&override, tmp_str);
	}
      } else {
	iret = -1;
      }
	
    } else if (!strcmp(argv[i], "-if") ||
               !strcmp(argv[i], "-f")) {
	
      if (i < argc - 1) {
	// load up file list vector. Break at next arg which
	// start with -
	for (int j = i + 1; j < argc; j++) {
	  if (argv[j][0] == '-') {
	    break;
	  } else {
	    inputFileList.push_back(argv[j]);
	  }
	}
	sprintf(tmp_str, "mode = FILELIST;");
	TDRP_add_override(&override, tmp_str);
      } else {
	iret = -1;
      }
      
    } // if
    
  } // i

  if (iret) {
    usage(prog_name, cerr);
  }

  return (iret);
    
}

void Args::usage(string &prog_name, ostream &out)
{

  out << "Usage: " << prog_name << " [options as below]\n"
      << "options:\n"
      << "       [ --, -h, -help, -man ] produce this list.\n"
      << "       [ -debug, -d ] print debug messages\n"
      << "       [ -extra, -vv ] print extra verbose debug messages\n"
      << "       [ -end \"yyyy mm dd hh mm ss\"] end time\n"
      << "         Sets mode to ARCHIVE\n"
      << "       [ -in_dir ?] Input direcetory - REALTIME and ARCHIVE\n"
      << "       [ -out_url ?] Output URL\n"
      << "       [ -if ?, -f ?] input file list\n"
      << "         Sets mode to FILELIST\n"
      << "       [ -mode ?] ARCHIVE, REALTIME  or FILELIST\n"
      << "       [ -start \"yyyy mm dd hh mm ss\"] start time\n"
      << "         Sets mode to ARCHIVE\n"
      << "       [ -verbose, -v ] print verbose debug messages\n"
      << endl;

  out << "Note: you must specify start and end dates." << endl << endl;
  
  Params::usage(out);

}
