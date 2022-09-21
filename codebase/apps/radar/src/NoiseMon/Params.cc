/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/* ** Copyright UCAR                                                         */
/* ** University Corporation for Atmospheric Research (UCAR)                 */
/* ** National Center for Atmospheric Research (NCAR)                        */
/* ** Boulder, Colorado, USA                                                 */
/* ** BSD licence applies - redistribution and use in source and binary      */
/* ** forms, with or without modification, are permitted provided that       */
/* ** the following conditions are met:                                      */
/* ** 1) If the software is modified to produce derivative works,            */
/* ** such modified software should be clearly marked, so as not             */
/* ** to confuse it with the version available from UCAR.                    */
/* ** 2) Redistributions of source code must retain the above copyright      */
/* ** notice, this list of conditions and the following disclaimer.          */
/* ** 3) Redistributions in binary form must reproduce the above copyright   */
/* ** notice, this list of conditions and the following disclaimer in the    */
/* ** documentation and/or other materials provided with the distribution.   */
/* ** 4) Neither the name of UCAR nor the names of its contributors,         */
/* ** if any, may be used to endorse or promote products derived from        */
/* ** this software without specific prior written permission.               */
/* ** DISCLAIMER: THIS SOFTWARE IS PROVIDED 'AS IS' AND WITHOUT ANY EXPRESS  */
/* ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      */
/* ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    */
/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
////////////////////////////////////////////
// Params.cc
//
// TDRP C++ code file for class 'Params'.
//
// Code for program NoiseMon
//
// This file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.cc
 *
 * @class Params
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @note Source is automatically generated from
 *       paramdef file at compile time, do not modify
 *       since modifications will be overwritten.
 *
 *
 * @author Automatically generated
 *
 */
#include "Params.hh"
#include <cstring>

  ////////////////////////////////////////////
  // Default constructor
  //

  Params::Params()

  {

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // initialize table

    _init();

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params::Params(const Params& source)

  {

    // sync the source object

    source.sync();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // copy table

    tdrpCopyTable((TDRPtable *) source._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Destructor
  //

  Params::~Params()

  {

    // free up

    freeAll();

  }

  ////////////////////////////////////////////
  // Assignment
  //

  void Params::operator=(const Params& other)

  {

    // sync the other object

    other.sync();

    // free up any existing memory

    freeAll();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // copy table

    tdrpCopyTable((TDRPtable *) other._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = other._exitDeferred;

  }

  ////////////////////////////////////////////
  // loadFromArgs()
  //
  // Loads up TDRP using the command line args.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   char **params_path_p:
  //     If this is non-NULL, it is set to point to the path
  //     of the params file used.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromArgs(int argc, char **argv,
                           char **override_list,
                           char **params_path_p,
                           bool defer_exit)
  {
    int exit_deferred;
    if (_tdrpLoadFromArgs(argc, argv,
                          _table, &_start_,
                          override_list, params_path_p,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadApplyArgs()
  //
  // Loads up TDRP using the params path passed in, and applies
  // the command line args for printing and checking.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   const char *param_file_path: the parameter file to be read in
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadApplyArgs(const char *params_path,
                            int argc, char **argv,
                            char **override_list,
                            bool defer_exit)
  {
    int exit_deferred;
    if (tdrpLoadApplyArgs(params_path, argc, argv,
                          _table, &_start_,
                          override_list,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  bool Params::isArgValid(const char *arg)
  {
    return (tdrpIsArgValid(arg));
  }

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  // return number of args consumed.
  //

  int Params::isArgValidN(const char *arg)
  {
    return (tdrpIsArgValidN(arg));
  }

  ////////////////////////////////////////////
  // load()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to load
  // up more than one class for a single application. It is a
  // lower-level routine than loadFromArgs, and hence more
  // flexible, but the programmer must do more work.
  //
  //   const char *param_file_path: the parameter file to be read in.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::load(const char *param_file_path,
                   char **override_list,
                   int expand_env, int debug)
  {
    if (tdrpLoad(param_file_path,
                 _table, &_start_,
                 override_list,
                 expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadFromBuf()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to
  // load up more than one module for a single application,
  // using buffers which have been read from a specified source.
  //
  //   const char *param_source_str: a string which describes the
  //     source of the parameter information. It is used for
  //     error reporting only.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   const char *inbuf: the input buffer
  //
  //   int inlen: length of the input buffer
  //
  //   int start_line_num: the line number in the source which
  //     corresponds to the start of the buffer.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromBuf(const char *param_source_str,
                          char **override_list,
                          const char *inbuf, int inlen,
                          int start_line_num,
                          int expand_env, int debug)
  {
    if (tdrpLoadFromBuf(param_source_str,
                        _table, &_start_,
                        override_list,
                        inbuf, inlen, start_line_num,
                        expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadDefaults(int expand_env)
  {
    if (tdrpLoad(NULL,
                 _table, &_start_,
                 NULL, expand_env, FALSE)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void Params::sync(void) const
  {
    tdrpUser2Table(_table, (char *) &_start_);
  }

  ////////////////////////////////////////////
  // print()
  // 
  // Print params file
  //
  // The modes supported are:
  //
  //   PRINT_SHORT:   main comments only, no help or descriptions
  //                  structs and arrays on a single line
  //   PRINT_NORM:    short + descriptions and help
  //   PRINT_LONG:    norm  + arrays and structs expanded
  //   PRINT_VERBOSE: long  + private params included
  //

  void Params::print(FILE *out, tdrp_print_mode_t mode)
  {
    tdrpPrint(out, _table, _className, mode);
  }

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int Params::checkAllSet(FILE *out)
  {
    return (tdrpCheckAllSet(out, _table, &_start_));
  }

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int Params::checkIsSet(const char *paramName)
  {
    return (tdrpCheckIsSet(paramName, _table, &_start_));
  }

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void Params::freeAll(void)
  {
    tdrpFreeAll(_table, &_start_);
  }

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  void Params::usage(ostream &out)
  {
    out << "TDRP args: [options as below]\n"
        << "   [ -params/--params path ] specify params file path\n"
        << "   [ -check_params/--check_params] check which params are not set\n"
        << "   [ -print_params/--print_params [mode]] print parameters\n"
        << "     using following modes, default mode is 'norm'\n"
        << "       short:   main comments only, no help or descr\n"
        << "                structs and arrays on a single line\n"
        << "       norm:    short + descriptions and help\n"
        << "       long:    norm  + arrays and structs expanded\n"
        << "       verbose: long  + private params included\n"
        << "       short_expand:   short with env vars expanded\n"
        << "       norm_expand:    norm with env vars expanded\n"
        << "       long_expand:    long with env vars expanded\n"
        << "       verbose_expand: verbose with env vars expanded\n"
        << "   [ -tdrp_debug] debugging prints for tdrp\n"
        << "   [ -tdrp_usage] print this usage\n";
  }

  ////////////////////////////////////////////
  // arrayRealloc()
  //
  // Realloc 1D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::arrayRealloc(const char *param_name, int new_array_n)
  {
    if (tdrpArrayRealloc(_table, &_start_,
                         param_name, new_array_n)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // array2DRealloc()
  //
  // Realloc 2D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::array2DRealloc(const char *param_name,
                             int new_array_n1,
                             int new_array_n2)
  {
    if (tdrpArray2DRealloc(_table, &_start_, param_name,
                           new_array_n1, new_array_n2)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // _init()
  //
  // Class table initialization function.
  //
  //

  void Params::_init()

  {

    TDRPtable *tt = _table;

    // Parameter 'Comment 0'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 0");
    tt->comment_hdr = tdrpStrDup("NoiseMon analyses data from time series files to estimate the noise power in each channel.");
    tt->comment_text = tdrpStrDup("Reading moments from CfRadial files is also an option.");
    tt++;
    
    // Parameter 'Comment 1'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 1");
    tt->comment_hdr = tdrpStrDup("DEBUGGING AND PROCESS CONTROL.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'debug'
    // ctype is '_debug_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("debug");
    tt->descr = tdrpStrDup("Debug option");
    tt->help = tdrpStrDup("If set, debug messages will be printed appropriately");
    tt->val_offset = (char *) &debug - &_start_;
    tt->enum_def.name = tdrpStrDup("debug_t");
    tt->enum_def.nfields = 4;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("DEBUG_OFF");
      tt->enum_def.fields[0].val = DEBUG_OFF;
      tt->enum_def.fields[1].name = tdrpStrDup("DEBUG_NORM");
      tt->enum_def.fields[1].val = DEBUG_NORM;
      tt->enum_def.fields[2].name = tdrpStrDup("DEBUG_VERBOSE");
      tt->enum_def.fields[2].val = DEBUG_VERBOSE;
      tt->enum_def.fields[3].name = tdrpStrDup("DEBUG_EXTRA");
      tt->enum_def.fields[3].val = DEBUG_EXTRA;
    tt->single_val.e = DEBUG_OFF;
    tt++;
    
    // Parameter 'instance'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("instance");
    tt->descr = tdrpStrDup("Process instance");
    tt->help = tdrpStrDup("Used for registration with procmap.");
    tt->val_offset = (char *) &instance - &_start_;
    tt->single_val.s = tdrpStrDup("test");
    tt++;
    
    // Parameter 'register_with_procmap'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("register_with_procmap");
    tt->descr = tdrpStrDup("Option to register with the process mapper.");
    tt->help = tdrpStrDup("If true, this application will try to register with procmap once per minute. (If unable to do so, no error occurs.)");
    tt->val_offset = (char *) &register_with_procmap - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'Comment 2'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 2");
    tt->comment_hdr = tdrpStrDup("DATA INPUT");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'input_mode'
    // ctype is '_input_mode_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("input_mode");
    tt->descr = tdrpStrDup("Input mode - files or time series API.");
    tt->help = tdrpStrDup("RADX_MOMENTS_INPUT: read CfRadial files. DSR_MOMENTS_INPUT: read moments data from FMQ in DSR format. TS_FMQ_INPUT: read time series from a file message queue and process the pulses as they come in. TS_FILE_INPUT: read time series from files.");
    tt->val_offset = (char *) &input_mode - &_start_;
    tt->enum_def.name = tdrpStrDup("input_mode_t");
    tt->enum_def.nfields = 4;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("RADX_MOMENTS_INPUT");
      tt->enum_def.fields[0].val = RADX_MOMENTS_INPUT;
      tt->enum_def.fields[1].name = tdrpStrDup("DSR_MOMENTS_INPUT");
      tt->enum_def.fields[1].val = DSR_MOMENTS_INPUT;
      tt->enum_def.fields[2].name = tdrpStrDup("TS_FILE_INPUT");
      tt->enum_def.fields[2].val = TS_FILE_INPUT;
      tt->enum_def.fields[3].name = tdrpStrDup("TS_FMQ_INPUT");
      tt->enum_def.fields[3].val = TS_FMQ_INPUT;
    tt->single_val.e = TS_FILE_INPUT;
    tt++;
    
    // Parameter 'Comment 3'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 3");
    tt->comment_hdr = tdrpStrDup("REALTIME - DSR_MOMENTS_INPUT, TS_FMQ_INPUT");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'input_fmq_name'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("input_fmq_name");
    tt->descr = tdrpStrDup("FMQ name. For DSR_MOMENTS_INPUT and TS_FMQ_INPUT.");
    tt->help = tdrpStrDup("Path to FMQ files. There are 2 files, one with a .buf extension and one with a .stat extention. This path does not include the extensions.");
    tt->val_offset = (char *) &input_fmq_name - &_start_;
    tt->single_val.s = tdrpStrDup("/tmp/fmq/ts");
    tt++;
    
    // Parameter 'seek_to_start_of_input'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("seek_to_start_of_input");
    tt->descr = tdrpStrDup("Option to seek to the start of the input FMQ.");
    tt->help = tdrpStrDup("Applies to DSR_MOMENTS_INPUT and TS_FMQ_INPUT. If TRUE, the program will seek to the start of the fmq and read in data from the entire queue. If FALSE, it will only read new data as it is added to the FMQ.");
    tt->val_offset = (char *) &seek_to_start_of_input - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'Comment 4'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 4");
    tt->comment_hdr = tdrpStrDup("ARCHIVE - RADX_MOMENTS_INPUT, TS_FILE_INPUT");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'input_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("input_dir");
    tt->descr = tdrpStrDup("Input directory for searching for files between start_time and end_time.");
    tt->help = tdrpStrDup("RADX_MOMENTS_INPUT, TS_FILE_INPUT: files will be searched for in this directory. This is ignored if the list of files is  specified on the command line using the -f option.");
    tt->val_offset = (char *) &input_dir - &_start_;
    tt->single_val.s = tdrpStrDup(".");
    tt++;
    
    // Parameter 'start_time'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("start_time");
    tt->descr = tdrpStrDup("Set the start time for ARCHIVE mode analysis.");
    tt->help = tdrpStrDup(" Applies to RADX_MOMENTS_INPUT and TS_FILE_INPUT. Format is 'yyyy mm dd hh mm ss'.");
    tt->val_offset = (char *) &start_time - &_start_;
    tt->single_val.s = tdrpStrDup("1970 01 01 00 00 00");
    tt++;
    
    // Parameter 'end_time'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("end_time");
    tt->descr = tdrpStrDup("Set the end time for ARCHIVE mode analysis.");
    tt->help = tdrpStrDup(" Applies to RADX_MOMENTS_INPUT and TS_FILE_INPUT. Format is 'yyyy mm dd hh mm ss'.");
    tt->val_offset = (char *) &end_time - &_start_;
    tt->single_val.s = tdrpStrDup("1970 01 01 00 00 00");
    tt++;
    
    // Parameter 'Comment 5'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 5");
    tt->comment_hdr = tdrpStrDup("COMPUTING MOMENTS FROM TIME SERIES");
    tt->comment_text = tdrpStrDup("TS_FILE_INPUT and TS_FMQ_INPUT modes");
    tt++;
    
    // Parameter 'n_samples'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("n_samples");
    tt->descr = tdrpStrDup("Number of pulse samples in a beam.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &n_samples - &_start_;
    tt->single_val.i = 64;
    tt++;
    
    // Parameter 'invert_hv_flag'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("invert_hv_flag");
    tt->descr = tdrpStrDup("Option to invert H/V flag in pulse data.");
    tt->help = tdrpStrDup("Normally, the HV flag is set to 1 for H, 0 for V. If the flag in the data has the opposite sense, set this to true.");
    tt->val_offset = (char *) &invert_hv_flag - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'cal_xml_file_path'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("cal_xml_file_path");
    tt->descr = tdrpStrDup("Path for XML calibration file.");
    tt->help = tdrpStrDup("At a minimum, the calibration file should contain noiseDbm, receiverGainDbm, dbz0 and radarConstant values for each channel.");
    tt->val_offset = (char *) &cal_xml_file_path - &_start_;
    tt->single_val.s = tdrpStrDup("./spol_cal.xml");
    tt++;
    
    // Parameter 'adjust_dbz_for_measured_xmit_power'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("adjust_dbz_for_measured_xmit_power");
    tt->descr = tdrpStrDup("Option to adjust DBZ based on measured transmitter power.");
    tt->help = tdrpStrDup("If true, and the measured transmitter power is available, the difference between the measured power and calibration power will be used to adjust the computed DBZ fields.");
    tt->val_offset = (char *) &adjust_dbz_for_measured_xmit_power - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'adjust_zdr_for_measured_xmit_power'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("adjust_zdr_for_measured_xmit_power");
    tt->descr = tdrpStrDup("Option to adjust ZDR based on measured transmitter power.");
    tt->help = tdrpStrDup("If true, and the measured transmitter power is available, the difference between the measured power and calibration power will be used to adjust the computed ZDR fields.");
    tt->val_offset = (char *) &adjust_zdr_for_measured_xmit_power - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'xmit_rcv_mode'
    // ctype is '_xmit_rcv_mode_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("xmit_rcv_mode");
    tt->descr = tdrpStrDup("Transmit/Receive mode for radar");
    tt->help = tdrpStrDup("Mode for xmit and receive for polarization diversity\nDP_ALT_HV_CO_ONLY: Dual pol, alternating transmission, copolar receiver only (e.g. CP2 S-band)\n DP_ALT_HV_CO_CROSS: Dual pol, alternating transmission, co-polar and cross-polar receivers (e.g. SPOL with Mitch Switch and receiver in switching mode, CHILL)\n DP_ALT_HV_FIXED_HV: Dual pol, alternating transmission, fixed H and V receivers (e.g. SPOL with Mitch Switch and receivers in fixed mode)\n DP_SIM_HV_FIXED_HV: Dual pol, simultaneous transmission, fixed H and V receivers (e.g. NEXRAD upgrade, SPOL with T and receivers in fixed mode)\n DP_SIM_HV_SWITCHED_HV: Dual pol, simultaneous transmission, switching H and V receivers (e.g. SPOL with T and receivers in switching mode)\n");
    tt->val_offset = (char *) &xmit_rcv_mode - &_start_;
    tt->enum_def.name = tdrpStrDup("xmit_rcv_mode_t");
    tt->enum_def.nfields = 5;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("DP_ALT_HV_CO_ONLY");
      tt->enum_def.fields[0].val = DP_ALT_HV_CO_ONLY;
      tt->enum_def.fields[1].name = tdrpStrDup("DP_ALT_HV_CO_CROSS");
      tt->enum_def.fields[1].val = DP_ALT_HV_CO_CROSS;
      tt->enum_def.fields[2].name = tdrpStrDup("DP_ALT_HV_FIXED_HV");
      tt->enum_def.fields[2].val = DP_ALT_HV_FIXED_HV;
      tt->enum_def.fields[3].name = tdrpStrDup("DP_SIM_HV_FIXED_HV");
      tt->enum_def.fields[3].val = DP_SIM_HV_FIXED_HV;
      tt->enum_def.fields[4].name = tdrpStrDup("DP_SIM_HV_SWITCHED_HV");
      tt->enum_def.fields[4].val = DP_SIM_HV_SWITCHED_HV;
    tt->single_val.e = DP_ALT_HV_CO_CROSS;
    tt++;
    
    // Parameter 'Comment 6'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 6");
    tt->comment_hdr = tdrpStrDup("READING MOMENTS FROM FMQ");
    tt->comment_text = tdrpStrDup("DSR_MOMENTS_INPUT mode only.");
    tt++;
    
    // Parameter 'min_elevation'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("min_elevation");
    tt->descr = tdrpStrDup("Minimum elevation angle (deg).");
    tt->help = tdrpStrDup("Beams below this elevation angle will be ignored.");
    tt->val_offset = (char *) &min_elevation - &_start_;
    tt->single_val.d = 88;
    tt++;
    
    // Parameter 'input_fields'
    // ctype is '_input_field_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("input_fields");
    tt->descr = tdrpStrDup("List of input fields for moments.");
    tt->help = tdrpStrDup("Applies to RADX_MOMENTS_INPUT and DSR_MOMENTS_INPUT.");
    tt->array_offset = (char *) &_input_fields - &_start_;
    tt->array_n_offset = (char *) &input_fields_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(input_field_t);
    tt->array_n = 13;
    tt->struct_def.name = tdrpStrDup("input_field_t");
    tt->struct_def.nfields = 2;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("moments_id_t");
      tt->struct_def.fields[0].fname = tdrpStrDup("id");
      tt->struct_def.fields[0].ptype = ENUM_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &_input_fields->id - (char *) _input_fields;
        tt->struct_def.fields[0].enum_def.name = tdrpStrDup("moments_id_t");
        tt->struct_def.fields[0].enum_def.nfields = 13;
        tt->struct_def.fields[0].enum_def.fields = (enum_field_t *) tdrpMalloc
          (tt->struct_def.fields[0].enum_def.nfields * sizeof(enum_field_t));
        tt->struct_def.fields[0].enum_def.fields[0].name = tdrpStrDup("SNRHC");
        tt->struct_def.fields[0].enum_def.fields[0].val = SNRHC;
        tt->struct_def.fields[0].enum_def.fields[1].name = tdrpStrDup("SNRVC");
        tt->struct_def.fields[0].enum_def.fields[1].val = SNRVC;
        tt->struct_def.fields[0].enum_def.fields[2].name = tdrpStrDup("SNRHX");
        tt->struct_def.fields[0].enum_def.fields[2].val = SNRHX;
        tt->struct_def.fields[0].enum_def.fields[3].name = tdrpStrDup("SNRVX");
        tt->struct_def.fields[0].enum_def.fields[3].val = SNRVX;
        tt->struct_def.fields[0].enum_def.fields[4].name = tdrpStrDup("DBMHC");
        tt->struct_def.fields[0].enum_def.fields[4].val = DBMHC;
        tt->struct_def.fields[0].enum_def.fields[5].name = tdrpStrDup("DBMVC");
        tt->struct_def.fields[0].enum_def.fields[5].val = DBMVC;
        tt->struct_def.fields[0].enum_def.fields[6].name = tdrpStrDup("DBMHX");
        tt->struct_def.fields[0].enum_def.fields[6].val = DBMHX;
        tt->struct_def.fields[0].enum_def.fields[7].name = tdrpStrDup("DBMVX");
        tt->struct_def.fields[0].enum_def.fields[7].val = DBMVX;
        tt->struct_def.fields[0].enum_def.fields[8].name = tdrpStrDup("DBZ");
        tt->struct_def.fields[0].enum_def.fields[8].val = DBZ;
        tt->struct_def.fields[0].enum_def.fields[9].name = tdrpStrDup("VEL");
        tt->struct_def.fields[0].enum_def.fields[9].val = VEL;
        tt->struct_def.fields[0].enum_def.fields[10].name = tdrpStrDup("WIDTH");
        tt->struct_def.fields[0].enum_def.fields[10].val = WIDTH;
        tt->struct_def.fields[0].enum_def.fields[11].name = tdrpStrDup("PHIDP");
        tt->struct_def.fields[0].enum_def.fields[11].val = PHIDP;
        tt->struct_def.fields[0].enum_def.fields[12].name = tdrpStrDup("RHOHV");
        tt->struct_def.fields[0].enum_def.fields[12].val = RHOHV;
      tt->struct_def.fields[1].ftype = tdrpStrDup("string");
      tt->struct_def.fields[1].fname = tdrpStrDup("moments_name");
      tt->struct_def.fields[1].ptype = STRING_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &_input_fields->moments_name - (char *) _input_fields;
    tt->n_struct_vals = 26;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].e = SNRHC;
      tt->struct_vals[1].s = tdrpStrDup("SNRHC");
      tt->struct_vals[2].e = SNRVC;
      tt->struct_vals[3].s = tdrpStrDup("SNRVC");
      tt->struct_vals[4].e = SNRHX;
      tt->struct_vals[5].s = tdrpStrDup("missing");
      tt->struct_vals[6].e = SNRVX;
      tt->struct_vals[7].s = tdrpStrDup("missing");
      tt->struct_vals[8].e = DBMHC;
      tt->struct_vals[9].s = tdrpStrDup("DBMHC");
      tt->struct_vals[10].e = DBMVC;
      tt->struct_vals[11].s = tdrpStrDup("DBMVC");
      tt->struct_vals[12].e = DBMHX;
      tt->struct_vals[13].s = tdrpStrDup("missing");
      tt->struct_vals[14].e = DBMVX;
      tt->struct_vals[15].s = tdrpStrDup("missing");
      tt->struct_vals[16].e = DBZ;
      tt->struct_vals[17].s = tdrpStrDup("DBZ");
      tt->struct_vals[18].e = VEL;
      tt->struct_vals[19].s = tdrpStrDup("VEL");
      tt->struct_vals[20].e = WIDTH;
      tt->struct_vals[21].s = tdrpStrDup("WIDTH");
      tt->struct_vals[22].e = PHIDP;
      tt->struct_vals[23].s = tdrpStrDup("PHIDP");
      tt->struct_vals[24].e = RHOHV;
      tt->struct_vals[25].s = tdrpStrDup("RHOHV");
    tt++;
    
    // Parameter 'Comment 7'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 7");
    tt->comment_hdr = tdrpStrDup("COMPUTING STATISTICS");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'stats_interval_secs'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("stats_interval_secs");
    tt->descr = tdrpStrDup("Time interval for statistics (s).");
    tt->help = tdrpStrDup("The statistics are computed at this interval, achored at the top of the hour. The interval should divide into 3600 without a remainder.");
    tt->val_offset = (char *) &stats_interval_secs - &_start_;
    tt->single_val.i = 300;
    tt++;
    
    // Parameter 'min_elevation_deg'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("min_elevation_deg");
    tt->descr = tdrpStrDup("Minimum elevation angle for noise (deg).");
    tt->help = tdrpStrDup("This should be high enough to clear all terrain, because terrain adds thermal noise to the returned signal.");
    tt->val_offset = (char *) &min_elevation_deg - &_start_;
    tt->single_val.d = 5;
    tt++;
    
    // Parameter 'min_height_km'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("min_height_km");
    tt->descr = tdrpStrDup("Minimum height for noise (km).");
    tt->help = tdrpStrDup("This should be above all likely weather echoes.");
    tt->val_offset = (char *) &min_height_km - &_start_;
    tt->single_val.d = 25;
    tt++;
    
    // Parameter 'min_range_km'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("min_range_km");
    tt->descr = tdrpStrDup("Minimum range for estimating noise (km).");
    tt->help = tdrpStrDup("This should be beyond any likely side-lobe echo from ground clutter.");
    tt->val_offset = (char *) &min_range_km - &_start_;
    tt->single_val.d = 100;
    tt++;
    
    // Parameter 'max_range_km'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("max_range_km");
    tt->descr = tdrpStrDup("Maximum range for estimating noise (km).");
    tt->help = tdrpStrDup("This is important if there is a test pulse in the data at long range. If so, set this just short of the test pulse range.");
    tt->val_offset = (char *) &max_range_km - &_start_;
    tt->single_val.d = 140;
    tt++;
    
    // Parameter 'min_valid_count'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("min_valid_count");
    tt->descr = tdrpStrDup("Min number of valid points for stats.");
    tt->help = tdrpStrDup("A valid point is a range gate that satisfies the thresholds below.");
    tt->val_offset = (char *) &min_valid_count - &_start_;
    tt->single_val.d = 2000;
    tt++;
    
    // Parameter 'Comment 8'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 8");
    tt->comment_hdr = tdrpStrDup("OUTPUT STATISTICS");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'write_stats_to_text_file'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("write_stats_to_text_file");
    tt->descr = tdrpStrDup("Option to write statistics to a text file.");
    tt->help = tdrpStrDup("If true, stats for the entire run will be writted to a text file.");
    tt->val_offset = (char *) &write_stats_to_text_file - &_start_;
    tt->single_val.b = pTRUE;
    tt++;
    
    // Parameter 'text_output_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("text_output_dir");
    tt->descr = tdrpStrDup("Dir for output text files.");
    tt->help = tdrpStrDup("The results will be written to sub-directories named from the data time.");
    tt->val_offset = (char *) &text_output_dir - &_start_;
    tt->single_val.s = tdrpStrDup("./output/text");
    tt++;
    
    // Parameter 'write_stats_to_spdb'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("write_stats_to_spdb");
    tt->descr = tdrpStrDup("Option to write out stats results to SPDB.");
    tt->help = tdrpStrDup("The results will be written in XML, stored in SPDB. The data can then be retrieved for plotting or other purposes.");
    tt->val_offset = (char *) &write_stats_to_spdb - &_start_;
    tt->single_val.b = pTRUE;
    tt++;
    
    // Parameter 'spdb_output_url'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("spdb_output_url");
    tt->descr = tdrpStrDup("URL for SPDB XML.");
    tt->help = tdrpStrDup("For local writes, specify the directory. For remote writes, specify the full url: spdbp:://host::dir");
    tt->val_offset = (char *) &spdb_output_url - &_start_;
    tt->single_val.s = tdrpStrDup("./output/spdb");
    tt++;
    
    // Parameter 'radar_name'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("radar_name");
    tt->descr = tdrpStrDup("Radar name for tagging SPDB output data.");
    tt->help = tdrpStrDup("This is used to set the data_type in SPDB.");
    tt->val_offset = (char *) &radar_name - &_start_;
    tt->single_val.s = tdrpStrDup("SPOL");
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }
