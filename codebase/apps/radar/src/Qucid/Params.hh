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
// Code for program Qucid
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
    IWRF_FMQ_INPUT = 0,
    IWRF_TCP_INPUT = 1,
    SIMULATED_INPUT = 2,
    DSR_FMQ_INPUT = 3
  } input_mode_t;

  typedef enum {
    POLYGONS = 0,
    FILLED_CONTOURS = 1,
    DYNAMIC_CONTOURS = 2,
    LINE_CONTOURS = 3
  } grid_render_mode_t;

  typedef enum {
    ARROW = 0,
    VECTOR = 1,
    BARB = 2,
    LABELEDBARB = 3,
    TUFT = 4,
    TICKVECTOR = 5,
    METBARB = 6,
    BARB_SH = 7,
    LABELEDBARB_SH = 8
  } wind_render_mode_t;

  typedef enum {
    POLAR_DISPLAY = 0,
    BSCAN_DISPLAY = 1
  } display_mode_t;

  typedef enum {
    HORIZ_FULL = 0,
    HORIZ_AIRBORNE = 1
  } horiz_display_type_t;

  typedef enum {
    LEGEND_TOP_LEFT = 0,
    LEGEND_TOP_RIGHT = 1,
    LEGEND_BOTTOM_LEFT = 2,
    LEGEND_BOTTOM_RIGHT = 3
  } legend_pos_t;

  typedef enum {
    RANGE_AXIS_UP = 0,
    RANGE_AXIS_DOWN = 1,
    RANGE_AXIS_ALTITUDE = 2
  } range_axis_mode_t;

  typedef enum {
    DWELL_STATS_MEAN = 0,
    DWELL_STATS_MEDIAN = 1,
    DWELL_STATS_MAXIMUM = 2,
    DWELL_STATS_MINIMUM = 3,
    DWELL_STATS_MIDDLE = 4
  } bscan_dwell_stats_t;

  typedef enum {
    CREATE_IMAGES_THEN_EXIT = 0,
    CREATE_IMAGES_ON_REALTIME_SCHEDULE = 1,
    CREATE_IMAGES_ON_ARCHIVE_SCHEDULE = 2
  } images_creation_mode_t;

  typedef enum {
    SYMPROD_DEBUG_OFF = 0,
    SYMPROD_DEBUG_NORM = 1,
    SYMPROD_DEBUG_VERBOSE = 2
  } symprod_debug_t;

  typedef enum {
    RENDER_ALL = 0,
    RENDER_ALL_VALID = 1,
    RENDER_VALID_IN_LAST_FRAME = 2,
    RENDER_LATEST_IN_FRAME = 3,
    RENDER_LATEST_IN_LOOP = 4,
    RENDER_FIRST_BEFORE_FRAME_TIME = 5,
    RENDER_FIRST_BEFORE_DATA_TIME = 6,
    RENDER_FIRST_AFTER_DATA_TIME = 7,
    RENDER_ALL_BEFORE_DATA_TIME = 8,
    RENDER_ALL_AFTER_DATA_TIME = 9,
    RENDER_GET_VALID = 10,
    RENDER_GET_VALID_AT_FRAME_TIME = 11
  } symprod_render_type_t;

  typedef enum {
    TERRAIN_RENDER_FILLED_CONT = 1,
    TERRAIN_RENDER_RECTANGLES = 2,
    TERRAIN_RENDER_DYNAMIC_CONTOURS = 3
  } terrain_render_type_t;

  typedef enum {
    IMAGE_DEBUG_OFF = 0,
    IMAGE_DEBUG_NORM = 1,
    IMAGE_DEBUG_VERBOSE = 2
  } image_debug_t;

  typedef enum {
    ROUTE_DEBUG_OFF = 0,
    ROUTE_DEBUG_NORM = 1,
    ROUTE_DEBUG_VERBOSE = 2
  } route_debug_t;

  typedef enum {
    REGULAR_INTERVALS = 0,
    EQUAL_DIVISIONS = 1
  } route_label_style_t;

  // struct typedefs

  typedef struct {
    tdrp_bool_t azimuth;
    tdrp_bool_t elevation;
    tdrp_bool_t fixed_angle;
    tdrp_bool_t volume_number;
    tdrp_bool_t sweep_number;
    tdrp_bool_t n_samples;
    tdrp_bool_t n_gates;
    tdrp_bool_t gate_length;
    tdrp_bool_t pulse_width;
    tdrp_bool_t prf_mode;
    tdrp_bool_t prf;
    tdrp_bool_t nyquist;
    tdrp_bool_t max_range;
    tdrp_bool_t unambiguous_range;
    tdrp_bool_t measured_power_h;
    tdrp_bool_t measured_power_v;
    tdrp_bool_t scan_name;
    tdrp_bool_t scan_mode;
    tdrp_bool_t polarization_mode;
    tdrp_bool_t latitude;
    tdrp_bool_t longitude;
    tdrp_bool_t altitude;
    tdrp_bool_t altitude_rate;
    tdrp_bool_t sun_elevation;
    tdrp_bool_t sun_azimuth;
    tdrp_bool_t speed;
    tdrp_bool_t heading;
    tdrp_bool_t track;
  } show_status_t;

  typedef struct {
    char* group_name;
    char* button_label;
    char* legend_label;
    char* url;
    char* field_name;
    char* color_map;
    char* field_units;
    double contour_low;
    double contour_high;
    double contour_interval;
    grid_render_mode_t render_mode;
    tdrp_bool_t display_in_menu;
    tdrp_bool_t background_render;
    tdrp_bool_t composite_mode;
    tdrp_bool_t auto_scale;
    tdrp_bool_t auto_render;
  } field_t;

  typedef struct {
    char* button_label;
    char* legend_label;
    char* url;
    char* u_field_name;
    char* v_field_name;
    char* w_field_name;
    char* units;
    int line_width;
    wind_render_mode_t render_mode;
    char* color;
    tdrp_bool_t display_in_menu;
  } wind_t;

  typedef struct {
    char* id_label;
    char* grid_list;
  } gui_field_set_t;

  typedef struct {
    char* id_label;
    char* url;
    double valid_minutes;
    int default_id_no;
    char* default_label;
  } dexport_t;

  typedef struct {
    char* menu_label;
    char* url;
    int data_type;
    symprod_render_type_t render_type;
    tdrp_bool_t on_by_default;
    double minutes_allow_before;
    double minutes_allow_after;
    double text_off_threshold;
    tdrp_bool_t request_data_on_zoom;
    tdrp_bool_t request_data_on_vert_change;
  } symprod_prod_info_t;

  typedef struct {
    char* vsection_label;
    int n_waypts;
    char* waypt_locs;
  } image_vsection_spec_t;

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

  tdrp_bool_t check_ray_alloc;

  tdrp_bool_t register_with_procmap;

  char* instance;

  char* color_scale_dir;

  input_mode_t input_mode;

  char* input_fmq_url;

  tdrp_bool_t seek_to_start_of_fmq;

  char* input_tcp_host;

  int input_tcp_port;

  int beam_queue_size;

  tdrp_bool_t begin_in_archive_mode;

  char* archive_start_time;

  double archive_time_span_secs;

  char* archive_data_url;

  show_status_t show_status_in_gui;

  field_t *_fields;
  int fields_n;

  wind_t *_winds;
  int winds_n;

  double background_render_mins;

  tdrp_bool_t use_field_label_in_title;

  tdrp_bool_t set_max_range;

  double max_range_km;

  display_mode_t display_mode;

  tdrp_bool_t override_radar_name;

  char* radar_name;

  tdrp_bool_t display_site_name;

  tdrp_bool_t override_site_name;

  char* site_name;

  int main_window_width;

  int main_window_height;

  int main_window_start_x;

  int main_window_start_y;

  int color_scale_width;

  int label_font_size;

  char* background_color2;

  char* text_color;

  char* grid_and_range_ring_color;

  int range_ring_label_font_size;

  char* click_cross_color;

  int click_cross_size;

  int click_cross_line_width;

  horiz_display_type_t horiz_display_type;

  double horiz_aspect_ratio;

  tdrp_bool_t horiz_grids_on_at_startup;

  tdrp_bool_t horiz_range_rings_on_at_startup;

  tdrp_bool_t horiz_azimuth_lines_on_at_startup;

  legend_pos_t horiz_main_legend_pos;

  tdrp_bool_t horiz_override_rendering_beam_width;

  double horiz_rendering_beam_width;

  int vert_window_width;

  int vert_window_height;

  int vert_window_start_x;

  int vert_window_start_y;

  int vert_top_margin2;

  int vert_bottom_margin;

  int vert_left_margin2;

  int vert_right_margin2;

  int vert_label_font_size;

  int vert_axis_tick_len;

  int vert_n_ticks_ideal;

  int vert_text_margin;

  tdrp_bool_t vert_display_180_degrees;

  double vert_aspect_ratio;

  double vert_max_height_km;

  int vert_color_scale_width;

  tdrp_bool_t vert_grids_on_at_startup;

  tdrp_bool_t vert_range_rings_on_at_startup;

  tdrp_bool_t vert_elevation_lines_on_at_startup;

  legend_pos_t vert_main_legend_pos;

  int vert_beam_queue_size;

  tdrp_bool_t vert_override_rendering_beam_width;

  double vert_rendering_beam_width;

  double bscan_time_span_secs;

  tdrp_bool_t bscan_truncate_start_time;

  int bscan_subsec_precision;

  double bscan_realtime_fraction_saved;

  double bscan_min_secs_between_reading_beams;

  double bscan_min_secs_between_rendering_beams;

  tdrp_bool_t bscan_specify_range_limits;

  double bscan_min_range_km;

  double bscan_max_range_km;

  double bscan_min_altitude_km;

  double bscan_max_altitude_km;

  tdrp_bool_t bscan_altitude_in_feet;

  tdrp_bool_t bscan_range_in_feet;

  range_axis_mode_t bscan_range_axis_mode;

  tdrp_bool_t bscan_specify_elevation_limits;

  double bscan_min_elevation_deg;

  double bscan_max_elevation_deg;

  tdrp_bool_t bscan_specify_azimuth_limits;

  double bscan_min_azimuth_deg;

  double bscan_max_azimuth_deg;

  tdrp_bool_t bscan_censor_data_below_surface;

  char* bscan_surface_field;

  double bscan_min_range_to_surface_km;

  double bscan_surface_range_margin_km;

  double bscan_max_field_val_below_surface;

  int bscan_top_margin;

  int bscan_bottom_margin;

  int bscan_left_margin;

  int bscan_right_margin;

  int bscan_axis_tick_len;

  int bscan_n_ticks_ideal;

  int bscan_text_margin;

  int bscan_title_font_size;

  int bscan_axis_label_font_size;

  int bscan_axis_values_font_size;

  char* bscan_axes_color;

  char* bscan_grid_color;

  char* bscan_labels_color;

  tdrp_bool_t bscan_draw_time_grid_lines;

  tdrp_bool_t bscan_draw_range_grid_lines;

  tdrp_bool_t bscan_draw_instrument_height_line;

  char* bscan_instrument_height_color;

  tdrp_bool_t bscan_add_distance_to_time_axis;

  int bscan_n_segments_for_computing_distance;

  tdrp_bool_t bscan_plot_starting_latlon_as_legend;

  legend_pos_t bscan_starting_latlon_legend_pos;

  tdrp_bool_t bscan_plot_mean_track_and_speed_as_legend;

  legend_pos_t bscan_mean_track_and_speed_legend_pos;

  tdrp_bool_t bscan_archive_dwell_auto;

  double bscan_archive_dwell_secs;

  bscan_dwell_stats_t bscan_dwell_stats;

  char* images_output_dir;

  tdrp_bool_t images_write_to_day_dir;

  char* images_file_name_category;

  char* images_file_name_platform;

  char* images_file_name_extension;

  char* images_file_name_delimiter;

  tdrp_bool_t images_include_time_part_in_file_name;

  tdrp_bool_t images_include_seconds_in_time_part;

  tdrp_bool_t images_include_field_label_in_file_name;

  tdrp_bool_t images_include_scan_type_in_file_name;

  tdrp_bool_t images_include_scan_id_in_file_name;

  tdrp_bool_t images_write_latest_data_info;

  tdrp_bool_t images_auto_create;

  images_creation_mode_t images_creation_mode;

  int images_schedule_interval_secs;

  int images_schedule_delay_secs;

  char* images_archive_start_time;

  char* images_archive_end_time;

  int images_scan_interval_secs;

  tdrp_bool_t images_set_sweep_index_list;

  int *_images_sweep_index_list;
  int images_sweep_index_list_n;

  int sim_sleep_msecs;

  int sim_n_gates;

  double sim_start_range_km;

  double sim_gate_spacing_km;

  char* click_point_fmq_url;

  gui_field_set_t *_gui_field_list;
  int gui_field_list_n;

  dexport_t *_dexport_info;
  int dexport_info_n;

  symprod_debug_t symprod_debug;

  tdrp_bool_t symprod_short_requests;

  tdrp_bool_t symprod_gzip_requests;

  symprod_prod_info_t *_symprod_prod_info;
  int symprod_prod_info_n;

  char* terrain_id_label;

  char* terrain_url;

  double terrain_height_scaler;

  char* landuse_url;

  char* landuse_colorscale;

  terrain_render_type_t land_use_render_method;

  tdrp_bool_t landuse_active;

  char* earth_color1;

  char* earth_color2;

  image_debug_t image_debug;

  tdrp_bool_t generate_vsection_images;

  tdrp_bool_t image_vsection_waypts_in_latlon;

  image_vsection_spec_t *_image_vsection_spec;
  int image_vsection_spec_n;

  route_debug_t route_debug;

  int route_font_height;

  int route_add_waypoints_labels;

  int route_add_wind_text;

  route_label_style_t route_label_style;

  double route_label_interval;

  int route_num_route_labels;

  int route_track_line_width;

  char* route_u_url;

  char* route_v_url;

  char* route_turb_url;

  double route_turb_low_thresh;

  double route_turb_mod_thresh;

  double route_turb_hi_thresh;

  char* route_icing_url;

  double route_icing_low_thresh;

  double route_icing_mod_thresh;

  double route_icing_hi_thresh;

  char* *_route_paths;
  int route_paths_n;

  tdrp_bool_t debug_flag;

  tdrp_bool_t debug1_flag;

  tdrp_bool_t debug2_flag;

  char* demo_time;

  int temporal_rounding;

  char* climo_mode;

  int max_time_list_span;

  int starting_movie_frames;

  double time_interval;

  double frame_span;

  double forecast_interval;

  double past_interval;

  double movie_magnify_factor;

  tdrp_bool_t check_data_times;

  tdrp_bool_t check_clipping;

  double stretch_factor;

  int gather_data_mode;

  int redraw_interval;

  int update_interval;

  char* datamap_host;

  int data_timeout_secs;

  int simple_command_timeout_secs;

  int complex_command_timeout_secs;

  tdrp_bool_t movie_on;

  int movie_delay;

  int movie_speed_msec;

  tdrp_bool_t reset_frames;

  int model_run_list_hours;

  int idle_reset_seconds;

  tdrp_bool_t html_mode;

  tdrp_bool_t run_once_and_exit;

  tdrp_bool_t transparent_images;

  char* image_dir;

  tdrp_bool_t save_images_to_day_subdir;

  char* image_ext;

  char* image_horiz_prefix;

  char* image_vert_prefix;

  char* image_name_separator;

  tdrp_bool_t add_height_to_filename;

  tdrp_bool_t add_frame_time_to_filename;

  tdrp_bool_t add_button_name_to_filename;

  tdrp_bool_t add_frame_num_to_filename;

  tdrp_bool_t add_gen_time_to_filename;

  tdrp_bool_t add_valid_time_to_filename;

  char* horiz_image_dir;

  char* horiz_image_fname;

  char* horiz_image_command;

  char* vert_image_dir;

  char* vert_image_fname;

  char* vert_image_command;

  tdrp_bool_t output_geo_xml;

  tdrp_bool_t use_latlon_in_geo_xml;

  char* movieframe_time_format;

  int movieframe_time_mode;

  char* image_convert_script;

  char* print_script;

  char* series_convert_script;

  tdrp_bool_t request_compressed_data;

  tdrp_bool_t request_gzip_vol_compression;

  char* projection_type;

  double lambert_lat1;

  double lambert_lat2;

  double tangent_lat;

  double tangent_lon;

  double central_scale;

  double north_angle;

  tdrp_bool_t use_cosine;

  int use_cosine_correction;

  double scale_units_per_km;

  char* scale_units_label;

  tdrp_bool_t always_get_full_domain;

  tdrp_bool_t do_not_clip_on_mdv_request;

  tdrp_bool_t do_not_decimate_on_mdv_request;

  double min_zoom_threshold;

  double aspect_ratio;

  tdrp_bool_t enable_status_window;

  tdrp_bool_t report_clicks_in_status_window;

  tdrp_bool_t report_clicks_in_degM_and_nm;

  double magnetic_variation_deg;

  tdrp_bool_t enable_save_image_panel;

  double domain_limit_min_x;

  double domain_limit_max_x;

  double domain_limit_min_y;

  double domain_limit_max_y;

  double origin_latitude;

  double origin_longitude;

  double reset_click_latitude;

  double reset_click_longitude;

  int planview_start_page;

  int xsect_start_page;

  int num_zoom_levels;

  int start_zoom_level;

  tdrp_bool_t zoom_limits_in_latlon;

  int num_cache_zooms;

  double min_ht;

  double max_ht;

  double start_ht;

  char* map_file_subdir;

  double locator_margin_km;

  char* station_loc_url;

  char* remote_ui_url;

  char* http_tunnel_url;

  char* http_proxy_url;

  char* foreground_color;

  char* background_color;

  char* margin_color;

  char* out_of_range_color;

  char* route_path_color;

  char* time_axis_color;

  char* time_frame_color;

  char* height_axis_color;

  char* height_indicator_color;

  char* range_ring_color;

  char* missing_data_color;

  char* bad_data_color;

  char* epoch_indicator_color;

  char* now_time_color;

  char* time_tick_color;

  char* latest_click_mark_color;

  tdrp_bool_t show_height_sel;

  tdrp_bool_t show_data_messages;

  int latlon_mode;

  char* label_time_format;

  char* moviestart_time_format;

  char* frame_range_time_format;

  tdrp_bool_t layer_legends_on;

  tdrp_bool_t cont_legends_on;

  tdrp_bool_t wind_legends_on;

  tdrp_bool_t display_labels;

  tdrp_bool_t display_ref_lines;

  int horiz_default_x_pos;

  int horiz_default_y_pos;

  int horiz_default_width;

  int horiz_default_height;

  int horiz_min_width;

  int horiz_min_height;

  int vert_default_x_pos;

  int vert_default_y_pos;

  int vert_default_width;

  int vert_default_height;

  int vert_min_width;

  int vert_min_height;

  int top_margin_render_style;

  int bot_margin_render_style;

  int horiz_top_margin;

  int horiz_bot_margin;

  int horiz_left_margin;

  int horiz_right_margin;

  int vert_top_margin;

  int vert_bot_margin;

  int vert_left_margin;

  int vert_right_margin;

  int horiz_legends_start_x;

  int horiz_legends_start_y;

  int horiz_legends_delta_y;

  int vert_legends_start_x;

  int vert_legends_start_y;

  int vert_legends_delta_y;

  tdrp_bool_t range_rings;

  double range_ring_spacing;

  double max_ring_range;

  tdrp_bool_t range_ring_follows_data;

  tdrp_bool_t range_ring_for_radar_only;

  tdrp_bool_t domain_follows_data;

  int range_ring_x_space;

  int range_ring_y_space;

  tdrp_bool_t range_ring_labels;

  tdrp_bool_t azmith_lines;

  double azmith_interval;

  double azmith_radius;

  tdrp_bool_t all_winds_on;

  tdrp_bool_t wind_mode;

  int barb_shaft_len;

  int ideal_x_vectors;

  int ideal_y_vectors;

  int wind_head_size;

  double wind_head_angle;

  int wind_scaler;

  double wind_time_scale_interval;

  char* wind_marker_type;

  double wind_w_scale_factor;

  double wind_units_scale_factor;

  double wind_reference_speed;

  char* wind_units_label;

  tdrp_bool_t label_contours;

  int contour_line_width;

  int smooth_contours;

  tdrp_bool_t use_alt_contours;

  tdrp_bool_t add_noise;

  double special_contour_value;

  tdrp_bool_t map_bad_to_min_value;

  tdrp_bool_t map_missing_to_min_value;

  tdrp_bool_t draw_main_on_top;

  tdrp_bool_t mark_latest_click_location;

  int latest_click_mark_size;

  char* latest_client_mark_color;

  tdrp_bool_t click_posn_rel_to_origin;

  int num_fonts;

  int font_display_mode;

  tdrp_bool_t show_clock;

  tdrp_bool_t draw_clock_local;

  tdrp_bool_t use_local_timestamps;

  int num_field_menu_cols;

  tdrp_bool_t wsddm_mode;

  tdrp_bool_t one_click_rhi;

  double rotate_coarse_adjust;

  double rotate_medium_adjust;

  double rotate_fine_adjust;

  tdrp_bool_t disable_pick_mode;

  tdrp_bool_t replace_underscores;

  tdrp_bool_t close_popups;

  tdrp_bool_t clip_overlay_fields;

  char* horiz_frame_label;

  char* no_data_message;

  char* status_info_file;

  char* help_command;

  char* canvas_help;

  char* frame_message_help;

  char* bookmark_command;

  int num_bookmarks;

  double image_inten;

  int inten_levels;

  double data_inten;

  int image_fill_threshold;

  int dynamic_contour_threshold;

  int coord_key;

  int titan_key;

  tdrp_bool_t products_on;

  int product_line_width;

  int product_font_size;

  double scale_constant;

  char _end_; // end of data region
              // needed for zeroing out data

private:

  void _init();

  mutable TDRPtable _table[481];

  const char *_className;

  bool _exitDeferred;

};

#endif

