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
// Params.hh
//
// TDRP header file for 'Params' class.
//
// Code for program FixFieldVals
//
// This header file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.hh
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @class Params
 *
 * @author automatically generated
 *
 */

#ifndef Params_hh
#define Params_hh

#include <tdrp/tdrp.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>

using namespace std;

// Class definition

class Params {

public:

  // enum typedefs

  typedef enum {
    DEBUG_OFF = 0,
    DEBUG_NORM = 1,
    DEBUG_VERBOSE = 2,
    DEBUG_EXTRA = 3
  } debug_t;

  typedef enum {
    ANALYSIS_STAGE = 0,
    CORRECTION_STAGE = 1
  } stage_t;

  typedef enum {
    ARCHIVE = 0,
    FILELIST = 1
  } mode_t;

  typedef enum {
    ATTR_STRING = 0,
    ATTR_INT = 1,
    ATTR_DOUBLE = 2,
    ATTR_INT_ARRAY = 3,
    ATTR_DOUBLE_ARRAY = 4
  } attr_type_t;

  typedef enum {
    OUTPUT_ENCODING_ASIS = 0,
    OUTPUT_ENCODING_FLOAT32 = 1,
    OUTPUT_ENCODING_INT32 = 2,
    OUTPUT_ENCODING_INT16 = 3,
    OUTPUT_ENCODING_INT08 = 4
  } output_encoding_t;

  typedef enum {
    SCALING_DYNAMIC = 0,
    SCALING_SPECIFIED = 1
  } output_scaling_t;

  typedef enum {
    LOGICAL_AND = 0,
    LOGICAL_OR = 1
  } logical_t;

  typedef enum {
    START_AND_END_TIMES = 0,
    START_TIME_ONLY = 1,
    END_TIME_ONLY = 2,
    SPECIFY_FILE_NAME = 3
  } filename_mode_t;

  // struct typedefs

  typedef struct {
    char* correction_field_name;
    char* truth_field_name;
  } comparison_field_t;

  typedef struct {
    char* field_name;
    double nyquist_mps;
  } nyquist_field_t;

  typedef struct {
    char* name;
    attr_type_t attrType;
    char* val;
  } attr_t;

  typedef struct {
    char* input_field_name;
    char* output_field_name;
    char* long_name;
    char* standard_name;
    char* output_units;
    output_encoding_t encoding;
    output_scaling_t output_scaling;
    double output_scale;
    double output_offset;
  } output_field_t;

  typedef struct {
    char* name;
    double min_valid_value;
    double max_valid_value;
    logical_t combination_method;
  } censoring_field_t;

  typedef struct {
    char* input_field_name;
    double transform_scale;
    double transform_offset;
    tdrp_bool_t field_folds;
    double folding_value;
  } transform_field_t;

  ///////////////////////////
  // Member functions
  //

  ////////////////////////////////////////////
  // Default constructor
  //

  Params ();

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params (const Params&);

  ////////////////////////////////////////////
  // Destructor
  //

  virtual ~Params ();

  ////////////////////////////////////////////
  // Assignment
  //

  void operator=(const Params&);

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

  int loadFromArgs(int argc, char **argv,
                   char **override_list,
                   char **params_path_p,
                   bool defer_exit = false);

  bool exitDeferred() { return (_exitDeferred); }

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

  int loadApplyArgs(const char *params_path,
                    int argc, char **argv,
                    char **override_list,
                    bool defer_exit = false);

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  static bool isArgValid(const char *arg);

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  // return number of args consumed.
  //

  static int isArgValidN(const char *arg);

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

  int load(const char *param_file_path,
           char **override_list,
           int expand_env, int debug);

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

  int loadFromBuf(const char *param_source_str,
                  char **override_list,
                  const char *inbuf, int inlen,
                  int start_line_num,
                  int expand_env, int debug);

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int loadDefaults(int expand_env);

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void sync() const;

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

  void print(FILE *out, tdrp_print_mode_t mode = PRINT_NORM);

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int checkAllSet(FILE *out);

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int checkIsSet(const char *param_name);

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

  int arrayRealloc(const char *param_name,
                   int new_array_n);

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

  int array2DRealloc(const char *param_name,
                     int new_array_n1,
                     int new_array_n2);

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void freeAll(void);

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  static void usage(ostream &out);

  ///////////////////////////
  // Data Members
  //

  char _start_; // start of data region
                // needed for zeroing out data
                // and computing offsets

  debug_t debug;

  char* instance;

  stage_t processing_stage;

  char* correction_input_dir;

  char* truth_input_dir;

  double truth_file_time_margin_secs;

  double truth_ray_az_margin_deg;

  double truth_ray_el_margin_deg;

  double truth_ray_time_margin_secs;

  comparison_field_t *_comparison_fields;
  int comparison_fields_n;

  double min_npts_for_valid_diff;

  mode_t mode;

  char* search_ext;

  char* field_bias_spdb_url;

  tdrp_bool_t trim_surveillance_sweeps_to_360deg;

  tdrp_bool_t set_max_range;

  double max_range_km;

  tdrp_bool_t set_ngates_constant;

  tdrp_bool_t remap_to_predominant_range_geometry;

  tdrp_bool_t remap_to_finest_range_geometry;

  tdrp_bool_t override_beam_width;

  double beam_width_deg_h;

  double beam_width_deg_v;

  tdrp_bool_t override_antenna_gain;

  double antenna_gain_db_h;

  double antenna_gain_db_v;

  tdrp_bool_t set_nyquist_velocity;

  nyquist_field_t *_nyquist_fields;
  int nyquist_fields_n;

  char* version_override;

  char* title_override;

  char* institution_override;

  char* references_override;

  char* source_override;

  char* history_override;

  char* comment_override;

  char* author_override;

  tdrp_bool_t add_user_specified_global_attributes;

  attr_t *_user_defined_global_attributes;
  int user_defined_global_attributes_n;

  tdrp_bool_t set_output_fields;

  output_field_t *_output_fields;
  int output_fields_n;

  tdrp_bool_t write_other_fields_unchanged;

  tdrp_bool_t exclude_specified_fields;

  char* *_excluded_fields;
  int excluded_fields_n;

  tdrp_bool_t set_output_encoding_for_all_fields;

  output_encoding_t output_encoding;

  tdrp_bool_t apply_censoring;

  censoring_field_t *_censoring_fields;
  int censoring_fields_n;

  int censoring_min_valid_run;

  tdrp_bool_t specify_fields_to_be_censored;

  char* *_fields_to_be_censored;
  int fields_to_be_censored_n;

  tdrp_bool_t censor_test_pulse_ring;

  double test_pulse_min_range_km;

  double test_pulse_max_range_km;

  double test_pulse_margin_km;

  char* test_pulse_field_name;

  tdrp_bool_t apply_linear_transforms;

  transform_field_t *_transform_fields;
  int transform_fields_n;

  tdrp_bool_t output_force_ngates_vary;

  char* corrected_files_output_dir;

  filename_mode_t output_filename_mode;

  char* output_filename_prefix;

  char* output_filename_suffix;

  tdrp_bool_t include_instrument_name_in_file_name;

  tdrp_bool_t include_site_name_in_file_name;

  tdrp_bool_t include_subsecs_in_file_name;

  tdrp_bool_t include_scan_type_in_file_name;

  tdrp_bool_t include_scan_name_in_file_name;

  tdrp_bool_t include_scan_id_in_file_name;

  tdrp_bool_t include_range_resolution_in_file_name;

  tdrp_bool_t include_vol_num_in_file_name;

  tdrp_bool_t use_hyphen_in_file_name_datetime_part;

  char* output_filename;

  tdrp_bool_t append_day_dir_to_output_dir;

  tdrp_bool_t append_year_dir_to_output_dir;

  tdrp_bool_t write_using_proposed_standard_name_attr;

  tdrp_bool_t override_missing_metadata_values;

  double missing_metadata_double;

  float missing_metadata_float;

  int missing_metadata_int;

  int missing_metadata_char;

  tdrp_bool_t override_missing_field_values;

  double missing_field_fl64;

  double missing_field_fl32;

  int missing_field_si32;

  int missing_field_si16;

  int missing_field_si08;

  char _end_; // end of data region
              // needed for zeroing out data

private:

  void _init();

  mutable TDRPtable _table[105];

  const char *_className;

  bool _exitDeferred;

};

#endif

