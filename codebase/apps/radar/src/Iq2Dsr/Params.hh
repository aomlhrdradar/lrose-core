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
// Code for program Iq2Dsr
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
    DEBUG_EXTRA_VERBOSE = 3
  } debug_t;

  typedef enum {
    FILELIST = 0,
    ARCHIVE = 1,
    REALTIME = 2,
    SIMULATE = 3,
    FMQ = 4
  } mode_t;

  typedef enum {
    PLATFORM_FIXED = 1,
    PLATFORM_VEHICLE = 2,
    PLATFORM_SHIP = 3,
    PLATFORM_AIRCRAFT = 4,
    PLATFORM_AIRCRAFT_FORE = 5,
    PLATFORM_AIRCRAFT_AFT = 6,
    PLATFORM_AIRCRAFT_TAIL = 7,
    PLATFORM_AIRCRAFT_BELLY = 8,
    PLATFORM_AIRCRAFT_ROOF = 9,
    PLATFORM_AIRCRAFT_NOSE = 10,
    PLATFORM_SATELLITE_ORBIT = 11,
    PLATFORM_SATELLITE_GEOSTAT = 12
  } platform_type_t;

  typedef enum {
    PRIMARY_AXIS_Z = 0,
    PRIMARY_AXIS_Y = 1,
    PRIMARY_AXIS_X = 2,
    PRIMARY_AXIS_Z_PRIME = 3,
    PRIMARY_AXIS_Y_PRIME = 4,
    PRIMARY_AXIS_X_PRIME = 5
  } primary_axis_t;

  typedef enum {
    SCAN_MODE_UNKNOWN = 0,
    SCAN_MODE_SECTOR = 1,
    SCAN_MODE_COPLANE = 2,
    SCAN_MODE_RHI = 3,
    SCAN_MODE_VERTICAL_POINTING = 4,
    SCAN_MODE_IDLE = 7,
    SCAN_MODE_SURVEILLANCE = 8,
    SCAN_MODE_SUNSCAN = 11,
    SCAN_MODE_POINTING = 12,
    SCAN_MODE_MANUAL_PPI = 15,
    SCAN_MODE_MANUAL_RHI = 16
  } scan_mode_t;

  typedef enum {
    SINGLE_POL = 0,
    DP_ALT_HV_CO_ONLY = 1,
    DP_ALT_HV_CO_CROSS = 2,
    DP_ALT_HV_FIXED_HV = 3,
    DP_SIM_HV_FIXED_HV = 4,
    DP_SIM_HV_SWITCHED_HV = 5,
    DP_H_ONLY_FIXED_HV = 6,
    DP_V_ONLY_FIXED_HV = 7,
    SINGLE_POL_V = 10
  } xmit_rcv_mode_t;

  typedef enum {
    WINDOW_RECT = 0,
    WINDOW_VONHANN = 1,
    WINDOW_BLACKMAN = 2,
    WINDOW_BLACKMAN_NUTTALL = 3,
    WINDOW_TUKEY_10 = 4,
    WINDOW_TUKEY_20 = 5,
    WINDOW_TUKEY_30 = 6,
    WINDOW_TUKEY_50 = 7
  } window_t;

  typedef enum {
    PROC_FLAGS_NONE = 0,
    PROC_FLAGS_DUAL_PRT = 1
  } processing_flags_t;

  typedef enum {
    BEAM_SPECIFY_N_SAMPLES = 0,
    BEAM_SPECIFY_ANGLE = 1,
    BEAM_CONSTANT_STEERING_ANGLE = 2,
    BEAM_CONSTANT_PULSE_WIDTH = 3
  } beam_method_t;

  typedef enum {
    WIDTH_METHOD_R0R1 = 0,
    WIDTH_METHOD_R1R2 = 1,
    WIDTH_METHOD_HYBRID = 2
  } spectrum_width_method_t;

  typedef enum {
    RX_CHANNEL_HC = 0,
    RX_CHANNEL_VC = 1,
    RX_CHANNEL_HX = 2,
    RX_CHANNEL_VX = 3
  } rx_channel_t;

  typedef enum {
    ATMOS_ATTEN_NONE = 0,
    ATMOS_ATTEN_CONSTANT = 1,
    ATMOS_ATTEN_CRPL = 2
  } atmos_atten_method_t;

  typedef enum {
    CLUTTER_FILTER_ADAPTIVE = 0,
    CLUTTER_FILTER_REGRESSION = 1,
    CLUTTER_FILTER_NOTCH = 2,
    CLUTTER_FILTER_NONE = 3
  } clutter_filter_type_t;

  typedef enum {
    INTERP_METHOD_NONE = 0,
    INTERP_METHOD_LINEAR = 1,
    INTERP_METHOD_GAUSSIAN = 2
  } notch_interp_method_t;

  typedef enum {
    FIR_LEN_125 = 0,
    FIR_LEN_60 = 1,
    FIR_LEN_40 = 2,
    FIR_LEN_30 = 3,
    FIR_LEN_20 = 4,
    FIR_LEN_10 = 5
  } fir_filter_len_t;

  typedef enum {
    NOISE_RAY_BY_RAY = 0,
    NOISE_RUNNING_MEDIAN = 1
  } noise_method_t;

  typedef enum {
    CENSORING_NONE = 0,
    CENSORING_BY_NOISE_FLAG = 1,
    CENSORING_BY_SNR_AND_NCP = 2
  } censoring_mode_t;

  typedef enum {
    PHASE_DECODE_NONE = 0,
    PHASE_DECODE_RANDOM = 1,
    PHASE_DECODE_SZ = 2,
    PHASE_DECODE_SZ1 = 3
  } phase_decoding_t;

  typedef enum {
    DBZ = 0,
    DBZ_NO_ATMOS_ATTEN = 1,
    DBZHC = 2,
    DBZVC = 3,
    DBZHX = 4,
    DBZVX = 5,
    VEL = 6,
    VEL_ALT = 7,
    VEL_HV = 8,
    VEL_H_ONLY = 9,
    VEL_V_ONLY = 10,
    VEL_ALT_FOLD_INTERVAL = 11,
    VEL_ALT_FOLD_CONFIDENCE = 12,
    VEL_CORR_VERT = 13,
    VEL_CORR_MOTION = 14,
    VEL_PRT_SHORT = 15,
    VEL_PRT_LONG = 16,
    VEL_DIFF = 17,
    VEL_UNFOLD_INTERVAL = 18,
    WIDTH = 19,
    WIDTH_R0R1 = 20,
    WIDTH_R1R2 = 21,
    WIDTH_R1R3 = 22,
    WIDTH_PPLS = 23,
    WIDTH_H_ONLY = 24,
    WIDTH_V_ONLY = 25,
    WIDTH_PRT_LONG = 26,
    WIDTH_PRT_SHORT = 27,
    WIDTH_CORR_MOTION = 28,
    NCP = 29,
    NCP_H_ONLY = 30,
    NCP_V_ONLY = 31,
    NCP_H_MINUS_V = 32,
    NCP_TRIP1 = 33,
    NCP_TRIP2 = 34,
    NCP_TRIP3 = 35,
    NCP_TRIP4 = 36,
    NCP_PRT_LONG = 37,
    NCP_PRT_SHORT = 38,
    NCP_TRIP_FLAG = 39,
    NOISE_BIAS_DB_HC = 40,
    NOISE_BIAS_DB_HX = 41,
    NOISE_BIAS_DB_VC = 42,
    NOISE_BIAS_DB_VX = 43,
    SNR = 44,
    SNRHC = 45,
    SNRHX = 46,
    SNRVC = 47,
    SNRVX = 48,
    DBM = 49,
    DBMHC = 50,
    DBMHX = 51,
    DBMVC = 52,
    DBMVX = 53,
    DBMHC_NS = 54,
    DBMHX_NS = 55,
    DBMVC_NS = 56,
    DBMVX_NS = 57,
    ZDRM = 58,
    ZDR = 59,
    ZDR_BIAS = 60,
    LDR = 61,
    LDRHM = 62,
    LDRH = 63,
    LDRVM = 64,
    LDRV = 65,
    LDR_DIFF = 66,
    LDR_MEAN = 67,
    RHOHV = 68,
    RHOHV_NNC = 69,
    PHIDP0 = 70,
    PHIDP = 71,
    PHIDP_COND = 72,
    PHIDP_FILT = 73,
    PHIDP_SDEV_4KDP = 74,
    PHIDP_JITTER_4KDP = 75,
    ZDR_SDEV_4KDP = 76,
    KDP = 77,
    PSOB = 78,
    KDP_HB = 79,
    RHO_HC_VX = 80,
    RHO_VC_HX = 81,
    RHO_VX_HX = 82,
    RHO_PHIDP = 83,
    CPR_MAG = 84,
    CPR_PHASE = 85,
    CPR_LDR = 86,
    DBZ_ATTEN_CORRECTION = 87,
    ZDR_ATTEN_CORRECTION = 88,
    DBZ_ATTEN_CORRECTED = 89,
    ZDR_ATTEN_CORRECTED = 90,
    CPA = 91,
    TDBZ = 92,
    SPIN = 93,
    MAX_TDBZ_SPIN = 94,
    ZDR_SDEV = 95,
    PHIDP_SDEV = 96,
    DBZ_DIFF_SQ = 97,
    DBZ_SPIN_CHANGE = 98,
    CMD = 99,
    CMD_FLAG = 100,
    TDBZ_INTEREST = 101,
    SPIN_INTEREST = 102,
    CPA_INTEREST = 103,
    ZDR_SDEV_INTEREST = 104,
    PHIDP_SDEV_INTEREST = 105,
    CLUT = 106,
    CLUT_2_WX_RATIO = 107,
    SPECTRAL_NOISE = 108,
    SPECTRAL_SNR = 109,
    REGR_FILT_POLY_ORDER = 110,
    REGR_FILT_CNR_DB = 111,
    NOISE_FLAG = 112,
    NOISE_INTEREST = 113,
    SIGNAL_FLAG = 114,
    SIGNAL_INTEREST = 115,
    AIQ_HC = 116,
    NIQ_HC = 117,
    AIQ_VC = 118,
    NIQ_VC = 119,
    SZ_TRIP_FLAG = 120,
    SZ_LEAKAGE = 121,
    CENSORING_FLAG = 122,
    LAG0_HC_DB = 123,
    LAG0_HX_DB = 124,
    LAG0_VC_DB = 125,
    LAG0_VX_DB = 126,
    LAG0_HC_SHORT_DB = 127,
    LAG0_VC_SHORT_DB = 128,
    LAG0_HC_LONG_DB = 129,
    LAG0_VC_LONG_DB = 130,
    LAG0_VCHX_DB = 131,
    LAG0_VCHX_PHASE = 132,
    LAG0_HCVX_DB = 133,
    LAG0_HCVX_PHASE = 134,
    LAG1_HC_DB = 135,
    LAG1_HC_PHASE = 136,
    LAG1_VC_DB = 137,
    LAG1_VC_PHASE = 138,
    LAG1_HCVC_DB = 139,
    LAG1_HCVC_PHASE = 140,
    LAG1_VCHC_DB = 141,
    LAG1_VCHC_PHASE = 142,
    LAG1_VXHX_DB = 143,
    LAG1_VXHX_PHASE = 144,
    LAG1_HC_LONG_DB = 145,
    LAG1_HC_LONG_PHASE = 146,
    LAG1_VC_LONG_DB = 147,
    LAG1_VC_LONG_PHASE = 148,
    LAG1_HC_SHORT_DB = 149,
    LAG1_HC_SHORT_PHASE = 150,
    LAG1_VC_SHORT_DB = 151,
    LAG1_VC_SHORT_PHASE = 152,
    LAG1_HC_LONG_TO_SHORT_DB = 153,
    LAG1_HC_LONG_TO_SHORT_PHASE = 154,
    LAG1_VC_LONG_TO_SHORT_DB = 155,
    LAG1_VC_LONG_TO_SHORT_PHASE = 156,
    LAG1_HC_SHORT_TO_LONG_DB = 157,
    LAG1_HC_SHORT_TO_LONG_PHASE = 158,
    LAG1_VC_SHORT_TO_LONG_DB = 159,
    LAG1_VC_SHORT_TO_LONG_PHASE = 160,
    LAG2_HC_DB = 161,
    LAG2_HC_PHASE = 162,
    LAG2_VC_DB = 163,
    LAG2_VC_PHASE = 164,
    LAG3_HC_DB = 165,
    LAG3_HC_PHASE = 166,
    LAG3_VC_DB = 167,
    LAG3_VC_PHASE = 168,
    RVVHH0_DB = 169,
    RVVHH0_PHASE = 170,
    RVVHH0_LONG_DB = 171,
    RVVHH0_LONG_PHASE = 172,
    RVVHH0_SHORT_DB = 173,
    RVVHH0_SHORT_PHASE = 174,
    SDEV_VV = 175,
    PRT = 176,
    NUM_PULSES = 177,
    TEST = 178,
    TEST0 = 179,
    TEST1 = 180,
    TEST2 = 181,
    TEST3 = 182,
    TEST4 = 183,
    TEST5 = 184,
    TEST6 = 185,
    TEST7 = 186,
    TEST8 = 187,
    TEST9 = 188
  } field_id_t;

  typedef enum {
    TRANSITION_FLAG_AT_CENTER = 0,
    TRANSITION_FLAG_AT_BOTH_ENDS = 1,
    TRANSITION_FLAG_AT_EITHER_END = 2,
    TRANSITION_FLAG_MISSING = 3
  } transition_method_t;

  // struct typedefs

  typedef struct {
    tdrp_bool_t check_scan_mode;
    scan_mode_t scan_mode;
    tdrp_bool_t check_prf;
    double prf_lower_limit;
    double prf_upper_limit;
    tdrp_bool_t check_antenna_rate;
    double antenna_rate_lower_limit;
    double antenna_rate_upper_limit;
    beam_method_t beam_method;
    int beam_n_samples;
    double beam_angle_deg;
    tdrp_bool_t index_the_beams;
    double indexed_resolution;
    double min_antenna_rate_for_indexing;
    window_t window;
    tdrp_bool_t switching_receiver;
    xmit_rcv_mode_t xmit_rcv_mode;
    tdrp_bool_t apply_clutter_filter;
    tdrp_bool_t apply_sz;
    tdrp_bool_t change_velocity_sign;
    processing_flags_t proc_flags;
    tdrp_bool_t check_scan_name;
    char* scan_name;
  } moments_params_t;

  typedef struct {
    double pulse_width_us;
    char* cal_dir;
    tdrp_bool_t check_xmit_rcv_mode;
    xmit_rcv_mode_t xmit_rcv_mode;
    double zdr_correction_db;
    double system_phidp_deg;
  } pulse_width_cal_t;

  typedef struct {
    rx_channel_t rx_channel;
    double slope;
    double intercept;
    char* temp_tag_list_in_status_xml;
  } rx_temp_gain_correction_t;

  typedef struct {
    double value;
    double interest;
  } interest_map_point_t;

  typedef struct {
    int length;
    double min_valid_cmd;
  } speckle_threshold_t;

  typedef struct {
    field_id_t id;
    char* name;
    char* units;
    double scale;
    double bias;
    tdrp_bool_t write_unfiltered;
    tdrp_bool_t write_filtered;
  } output_field_t;

  typedef struct {
    double min_el;
    double max_el;
    double min_az;
    double max_az;
    double min_range;
    double max_range;
  } selected_region_t;

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

  int beam_count_for_debug_print;

  char* instance;

  tdrp_bool_t use_multiple_threads;

  int n_compute_threads;

  mode_t mode;

  char* input_fmq;

  tdrp_bool_t position_fmq_at_start;

  char* input_dir;

  tdrp_bool_t use_ldata_info_file;

  int max_realtime_valid_age;

  tdrp_bool_t invert_hv_flag;

  tdrp_bool_t swap_receiver_channels;

  tdrp_bool_t cohere_iq_to_burst_phase;

  tdrp_bool_t prt_is_for_previous_interval;

  tdrp_bool_t compute_prt_from_interpulse_periods;

  tdrp_bool_t change_velocity_sign_staggered;

  tdrp_bool_t use_pulse_width_from_ts_proc;

  tdrp_bool_t override_primary_prt;

  double primary_prt_secs;

  double georef_time_margin_secs;

  tdrp_bool_t use_secondary_georeference;

  tdrp_bool_t check_radar_id;

  int radar_id;

  double nsecs_for_antenna_rate;

  tdrp_bool_t interpolate_antenna_angles;

  double angle_interp_max_change;

  int angle_interp_max_queue_size;

  tdrp_bool_t angle_interp_adjust_for_latency;

  double angle_interp_latency;

  tdrp_bool_t angle_interp_debug;

  platform_type_t platform_type;

  tdrp_bool_t override_primary_axis;

  primary_axis_t primary_axis;

  tdrp_bool_t override_radar_name;

  char* radar_name;

  tdrp_bool_t override_radar_location;

  double radar_latitude_deg;

  double radar_longitude_deg;

  double radar_altitude_meters;

  tdrp_bool_t override_gate_geometry;

  double gate_spacing_meters;

  double start_range_meters;

  tdrp_bool_t override_radar_wavelength;

  double radar_wavelength_cm;

  tdrp_bool_t apply_azimuth_offset;

  double azimuth_offset;

  tdrp_bool_t apply_elevation_offset;

  double elevation_offset;

  tdrp_bool_t override_scan_mode;

  scan_mode_t scan_mode_for_override;

  moments_params_t *_moments_params;
  int moments_params_n;

  int min_n_samples;

  int max_n_samples;

  tdrp_bool_t specify_pulse_width;

  double fixed_pulse_width_us;

  tdrp_bool_t control_beam_indexing_from_time_series;

  tdrp_bool_t discard_non_indexed_beams;

  tdrp_bool_t control_n_samples_from_time_series;

  tdrp_bool_t control_xmit_rcv_mode_from_time_series;

  tdrp_bool_t compute_zdr_using_snr;

  tdrp_bool_t adjust_dbz_for_measured_xmit_power;

  tdrp_bool_t adjust_zdr_for_measured_xmit_power;

  double min_measured_xmit_power_dbm;

  double max_measured_xmit_power_dbm;

  tdrp_bool_t check_for_missing_pulses;

  tdrp_bool_t discard_beams_with_missing_pulses;

  tdrp_bool_t correct_for_system_phidp;

  int zdr_median_filter_len;

  int rhohv_median_filter_len;

  int staggered_prt_median_filter_len;

  tdrp_bool_t compute_velocity_corrected_for_platform_motion;

  tdrp_bool_t compute_width_corrected_for_platform_motion;

  double width_correction_beamwidth_deg;

  spectrum_width_method_t spectrum_width_method;

  char* startup_cal_file;

  tdrp_bool_t set_cal_by_pulse_width;

  pulse_width_cal_t *_pulse_width_cals;
  int pulse_width_cals_n;

  int cal_recheck_period;

  tdrp_bool_t use_cal_from_time_series;

  tdrp_bool_t override_cal_dbz_correction;

  double dbz_correction;

  tdrp_bool_t override_cal_zdr_correction;

  double zdr_correction_db;

  tdrp_bool_t threshold_zdr_using_snr;

  double min_snr_db_for_zdr;

  tdrp_bool_t override_cal_ldr_corrections;

  double ldr_correction_db_h;

  double ldr_correction_db_v;

  tdrp_bool_t threshold_ldr_using_snr;

  double min_snr_db_for_ldr;

  tdrp_bool_t override_cal_system_phidp;

  double system_phidp_deg;

  tdrp_bool_t change_phidp_sign;

  tdrp_bool_t correct_rx_gains_for_temperature;

  rx_temp_gain_correction_t *_rx_temp_gain_corrections;
  int rx_temp_gain_corrections_n;

  tdrp_bool_t correct_hcr_v_rx_gain_for_temperature;

  char* hcr_delta_gain_spdb_url;

  int hcr_delta_gain_search_margin_secs;

  char* hcr_v_rx_delta_gain_tag_list;

  tdrp_bool_t correct_altitude_for_egm;

  char* egm_2008_geoid_file;

  tdrp_bool_t noise_mon_correct_cal_rx_gain;

  char* noise_mon_spdb_url;

  int noise_mon_search_margin_secs;

  char* noise_mon_tag_main;

  char* noise_mon_tag_list_zdr;

  char* noise_mon_tag_list_dbmhc;

  char* noise_mon_tag_list_dbmvc;

  char* noise_mon_tag_list_site_temp;

  double noise_mon_zdrm_corr;

  double noise_mon_mean_site_temp;

  double noise_mon_zdr_temp_slope;

  tdrp_bool_t apply_precip_attenuation_correction;

  tdrp_bool_t specify_coefficients_for_attenuation_correction;

  double dbz_attenuation_coefficient;

  double dbz_attenuation_exponent;

  double zdr_attenuation_coefficient;

  double zdr_attenuation_exponent;

  atmos_atten_method_t atmos_atten_method;

  double atmos_atten_db_per_km;

  clutter_filter_type_t clutter_filter_type;

  double clutter_model_width_in_adaptive_filter;

  double init_notch_width_in_adaptive_filter;

  tdrp_bool_t apply_residue_correction_in_adaptive_filter;

  double min_snr_db_for_residue_correction;

  tdrp_bool_t regression_filter_determine_order_from_cnr;

  int regression_filter_specified_polynomial_order;

  double regression_filter_clutter_width_factor;

  double regression_filter_cnr_exponent;

  double regression_filter_min_cnr_db;

  double regression_filter_min_csr_db;

  notch_interp_method_t regression_filter_notch_interp_method;

  double simple_notch_filter_width_mps;

  tdrp_bool_t use_h_only_for_alt_mode_clutter_vel;

  tdrp_bool_t write_alt_mode_vel_debug_fields;

  fir_filter_len_t KDP_fir_filter_len;

  int KDP_n_filt_iterations_unfolded;

  int KDP_n_filt_iterations_conditioned;

  tdrp_bool_t KDP_use_iterative_filtering;

  double KDP_phidp_difference_threshold;

  int KDP_ngates_for_stats;

  double KDP_phidp_sdev_max;

  double KDP_phidp_jitter_max;

  tdrp_bool_t KDP_check_snr;

  double KDP_snr_threshold;

  tdrp_bool_t KDP_check_rhohv;

  double KDP_rhohv_threshold;

  tdrp_bool_t KDP_check_zdr_sdev;

  double KDP_zdr_sdev_max;

  double KDP_min_valid_abs_kdp;

  tdrp_bool_t KDP_debug;

  tdrp_bool_t KDP_write_ray_files;

  char* KDP_ray_files_dir;

  tdrp_bool_t KDP_compute_using_hubbert_bringi_method;

  fir_filter_len_t KDP_HB_fir_filter_len;

  double KDP_HB_phidp_difference_threshold;

  double KDP_HB_phidp_sdev_threshold;

  double KDP_HB_zdr_sdev_threshold;

  double KDP_HB_rhohv_threshold;

  tdrp_bool_t use_estimated_noise_for_noise_subtraction;

  double max_valid_noise_bias_db;

  int noise_ngates_kernel;

  int noise_min_ngates_for_ray_median;

  noise_method_t noise_method;

  int noise_ngates_for_running_median;

  tdrp_bool_t set_equal_noise_bias_in_all_channels;

  interest_map_point_t *_phase_change_error_for_noise_interest_map;
  int phase_change_error_for_noise_interest_map_n;

  double phase_change_error_for_noise_interest_weight;

  interest_map_point_t *_dbm_sdev_for_noise_interest_map;
  int dbm_sdev_for_noise_interest_map_n;

  double dbm_sdev_for_noise_interest_weight;

  interest_map_point_t *_ncp_mean_for_noise_interest_map;
  int ncp_mean_for_noise_interest_map_n;

  double ncp_mean_for_noise_interest_weight;

  double interest_threshold_for_noise;

  interest_map_point_t *_phase_change_error_for_signal_interest_map;
  int phase_change_error_for_signal_interest_map_n;

  double phase_change_error_for_signal_interest_weight;

  interest_map_point_t *_dbm_sdev_for_signal_interest_map;
  int dbm_sdev_for_signal_interest_map_n;

  double dbm_sdev_for_signal_interest_weight;

  double interest_threshold_for_signal;

  censoring_mode_t censoring_mode;

  double censoring_snr_threshold;

  double censoring_ncp_threshold;

  int censoring_min_valid_run;

  tdrp_bool_t change_aiq_sign;

  phase_decoding_t phase_decoding;

  int phase_decoding_ntrips_check;

  int phase_decoding_ntrips_save;

  double phase_decoding_ncp_threshold;

  double phase_decoding_snr_threshold;

  double phase_decoding_notch_width;

  tdrp_bool_t sz1_negate_phase_codes;

  double sz1_strong_to_weak_power_ratio_threshold;

  double sz1_out_of_trip_power_ratio_threshold;

  int sz1_out_of_trip_power_n_replicas;

  tdrp_bool_t sz1_use_regression_filter;

  int cmd_kernel_ngates_tdbz;

  int cmd_kernel_ngates_spin;

  int cmd_kernel_ngates_zdr_sdev;

  int cmd_kernel_ngates_phidp_sdev;

  double cmd_spin_dbz_threshold;

  double cmd_snr_threshold;

  int cpa_median_filter_len;

  tdrp_bool_t cpa_compute_using_alternative;

  double cmd_threshold_for_clutter;

  tdrp_bool_t cmd_check_for_offzero_weather;

  double cmd_threshold_for_offzero_weather;

  double min_snr_for_offzero_weather;

  double notch_width_for_offzero_snr;

  tdrp_bool_t cmd_check_for_windfarm_clutter;

  double min_spectral_snr_for_windfarm_clutter;

  double min_snr_for_windfarm_clutter_check;

  double min_cpa_for_windfarm_clutter_check;

  tdrp_bool_t apply_db_for_db_correction;

  double db_for_db_ratio;

  double db_for_db_threshold;

  tdrp_bool_t apply_cmd_speckle_filter;

  speckle_threshold_t *_cmd_speckle_filter_thresholds;
  int cmd_speckle_filter_thresholds_n;

  tdrp_bool_t apply_cmd_gap_filter;

  int cmd_gap_filter_len;

  double cmd_gap_filter_threshold;

  tdrp_bool_t apply_nexrad_spike_filter_after_cmd;

  interest_map_point_t *_tdbz_interest_map;
  int tdbz_interest_map_n;

  double tdbz_interest_weight;

  interest_map_point_t *_spin_interest_map;
  int spin_interest_map_n;

  double spin_interest_weight;

  double max_of_tdbz_and_spin_interest_weight;

  interest_map_point_t *_cpa_interest_map;
  int cpa_interest_map_n;

  double cpa_interest_weight;

  interest_map_point_t *_zdr_sdev_interest_map;
  int zdr_sdev_interest_map_n;

  double zdr_sdev_interest_weight;

  interest_map_point_t *_phidp_sdev_interest_map;
  int phidp_sdev_interest_map_n;

  double phidp_sdev_interest_weight;

  tdrp_bool_t apply_rhohv_test_after_cmd;

  double rhohv_test_min_rhohv;

  double rhohv_test_max_rhohv;

  double rhohv_improvement_factor_threshold;

  tdrp_bool_t run_spectral_cmd;

  clutter_filter_type_t spec_cmd_clutter_filter_type;

  window_t spec_cmd_window_type;

  int spec_cmd_tdbz_kernel_ngates;

  int spec_cmd_tdbz_kernel_nsamples;

  int spec_cmd_sdev_zdr_kernel_ngates;

  int spec_cmd_sdev_zdr_kernel_nsamples;

  int spec_cmd_sdev_phidp_kernel_ngates;

  int spec_cmd_sdev_phidp_kernel_nsamples;

  interest_map_point_t *_spec_cmd_snr_interest_map;
  int spec_cmd_snr_interest_map_n;

  double spec_cmd_snr_interest_weight;

  interest_map_point_t *_spec_cmd_tdbz_interest_map;
  int spec_cmd_tdbz_interest_map_n;

  double spec_cmd_tdbz_interest_weight;

  interest_map_point_t *_spec_cmd_zdr_sdev_interest_map;
  int spec_cmd_zdr_sdev_interest_map_n;

  double spec_cmd_zdr_sdev_interest_weight;

  interest_map_point_t *_spec_cmd_phidp_sdev_interest_map;
  int spec_cmd_phidp_sdev_interest_map_n;

  double spec_cmd_phidp_sdev_interest_weight;

  double spec_cmd_threshold_for_detection;

  double spec_cmd_threshold_for_moments;

  double spec_cmd_fraction_threshold_for_wind_turbine;

  char* output_fmq_url;

  tdrp_bool_t output_moments_in_radx_format;

  int output_fmq_size;

  int output_fmq_nslots;

  tdrp_bool_t output_fmq_compress;

  int nbeams_for_params_and_calib;

  tdrp_bool_t write_blocking;

  int beam_wait_msecs;

  output_field_t *_output_fields;
  int output_fields_n;

  tdrp_bool_t use_sweep_info_from_time_series;

  tdrp_bool_t delay_tilt_start_msg_during_ant_trans;

  tdrp_bool_t set_end_of_sweep_when_antenna_changes_direction;

  double required_delta_angle_for_antenna_direction_change;

  int min_rays_in_sweep_for_antenna_direction_change;

  int max_sweeps_in_vol_for_antenna_direction_change;

  tdrp_bool_t use_volume_info_from_time_series;

  tdrp_bool_t set_end_of_vol_from_elev_angle;

  tdrp_bool_t vol_starts_at_bottom;

  double elev_change_for_end_of_vol;

  int min_beams_per_vol;

  tdrp_bool_t set_end_of_vol_on_prf_change;

  tdrp_bool_t set_end_of_vol_on_pulse_width_change;

  transition_method_t transition_method;

  tdrp_bool_t check_transition_from_fixed_angle_error;

  double max_fixed_angle_error_ppi;

  double max_fixed_angle_error_rhi;

  selected_region_t selected_region;

  tdrp_bool_t do_selected_print;

  char* spectra_dir;

  tdrp_bool_t write_individual_spectra_files;

  tdrp_bool_t write_combined_spectra_file;

  double min_snr_for_combined_spectra_file;

  int data_mapper_report_interval;

  char _end_; // end of data region
              // needed for zeroing out data

private:

  void _init();

  mutable TDRPtable _table[321];

  const char *_className;

  bool _exitDeferred;

};

#endif

