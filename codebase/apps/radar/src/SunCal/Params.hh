// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2017
// ** University Corporation for Atmospheric Research(UCAR)
// ** National Center for Atmospheric Research(NCAR)
// ** Boulder, Colorado, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
////////////////////////////////////////////
// Params.hh
//
// TDRP header file for 'Params' class.
//
// Code for program SunCal
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

using namespace std;

#include <tdrp/tdrp.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>

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
    TS_FILELIST_INPUT = 0,
    TS_FMQ_INPUT = 1,
    TS_REALTIME_DIR_INPUT = 2,
    COVAR_REALTIME_INPUT = 3,
    COVAR_ARCHIVE_INPUT = 4,
    COVAR_FILELIST_INPUT = 5
  } input_mode_t;

  typedef enum {
    GET_NOISE_FROM_CAL_FILE = 0,
    GET_NOISE_FROM_TIME_SERIES = 1,
    COMPUTE_MEAN_NOISE = 2,
    COMPUTE_MIN_NOISE = 3
  } noise_method_t;

  // struct typedefs

  typedef struct {
    char* LAG0_HC_DB;
    char* LAG0_HX_DB;
    char* LAG0_VC_DB;
    char* LAG0_VX_DB;
    char* LAG0_HCVX_DB;
    char* LAG0_HCVX_PHASE;
    char* LAG0_VCHX_DB;
    char* LAG0_VCHX_PHASE;
    char* LAG1_VXHX_DB;
    char* LAG1_VXHX_PHASE;
    char* RVVHH0_DB;
    char* RVVHH0_PHASE;
  } covar_field_names_t;

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

  ~Params ();

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

  tdrp_bool_t register_with_procmap;

  input_mode_t input_mode;

  char* input_fmq_name;

  char* input_dir;

  char* archive_start_time;

  char* archive_end_time;

  int n_samples;

  int start_gate;

  int n_gates;

  tdrp_bool_t alternating_mode;

  tdrp_bool_t switching_receiver;

  tdrp_bool_t invert_hv_flag;

  tdrp_bool_t print_missing_pulses;

  covar_field_names_t covar_field_names;

  tdrp_bool_t scan_mode_rhi;

  tdrp_bool_t analyze_individual_volumes;

  int n_volumes_for_analysis;

  int min_n_volumes_for_analysis;

  int min_beams_per_volume;

  int max_beams_per_volume;

  tdrp_bool_t check_for_elevation_change;

  double elev_change_for_end_of_volume;

  tdrp_bool_t volume_starts_at_bottom;

  int max_time_gap_within_volume;

  double max_pointing_angle_error_deg;

  char* radar_name;

  char* radar_site;

  tdrp_bool_t get_location_from_data;

  double radar_lat;

  double radar_lon;

  double radar_alt_km;

  tdrp_bool_t specify_fixed_target_location;

  double target_elevation;

  double target_azimuth;

  double grid_min_az;

  double grid_max_az;

  double grid_delta_az;

  double grid_min_el;

  double grid_max_el;

  double grid_delta_el;

  tdrp_bool_t correct_powers_for_noise;

  noise_method_t noise_method;

  double min_angle_offset_for_noise_power;

  char* cal_xml_file_path;

  tdrp_bool_t set_max_sun_power;

  double max_valid_sun_power_dbm;

  double max_solid_angle_for_mean_correlation;

  tdrp_bool_t compute_ellipse_hv_power_diffs;

  double solid_angle_for_ellipse_power_diffs;

  double sun_edge_below_peak_db;

  int n_s1s2_ratios_computed;

  double min_solid_angle_for_s1s2;

  double delta_solid_angle_for_s1s2;

  double solid_angle_for_zdr_bias;

  int npoints_power_ranking;

  tdrp_bool_t compute_cross_polar_power_ratio;

  int cross_polar_start_gate;

  int cross_polar_n_gates;

  double cross_polar_min_snr;

  double cross_polar_max_snr;

  double cross_polar_min_valid_ratio_db;

  double cross_polar_max_valid_ratio_db;

  double cross_polar_min_rho_vx_hx;

  double min_angle_offset_for_cross_pol_ratio;

  tdrp_bool_t read_xpol_ratio_from_spdb;

  tdrp_bool_t use_xpol_ratio_from_spdb;

  char* xpol_ratio_spdb_url;

  char* xpol_ratio_radar_name;

  int xpol_ratio_search_margin_secs;

  tdrp_bool_t read_site_temp_from_spdb;

  char* site_temp_spdb_url;

  char* site_temp_station_name;

  int site_temp_data_type;

  int site_temp_search_margin_secs;

  tdrp_bool_t compute_test_pulse_powers;

  double test_pulse_min_range_km;

  double test_pulse_max_range_km;

  tdrp_bool_t compute_mean_transmit_powers;

  tdrp_bool_t only_write_for_valid_centroid;

  tdrp_bool_t write_text_files;

  char* text_output_dir;

  tdrp_bool_t append_to_global_results_file;

  char* global_file_name;

  tdrp_bool_t write_mdv_files;

  char* mdv_output_url;

  tdrp_bool_t write_summary_to_spdb;

  char* spdb_output_url;

  tdrp_bool_t test_nexrad_processing;

  char* nexrad_text_output_dir;

  char* nexrad_mdv_output_url;

  char* nexrad_spdb_output_url;

  char _end_; // end of data region
              // needed for zeroing out data

private:

  void _init();

  mutable TDRPtable _table[115];

  const char *_className;

  bool _exitDeferred;

};

#endif

