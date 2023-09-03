/*
 * h_win_stubs.c - Notify and event callback function stubs.
 * This file was generated by `gxv' from `h_win.G'.
 */

#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/textsw.h>
#include <xview/xv_xrect.h>
#include "cidd_gui.h"


/*
 * Event callback function for `cp'.
 */
Notify_value
h_pan_event_proc(Xv_window win, Event *event, Notify_arg arg, Notify_event_type type)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(win, XV_KEY_DATA, INSTANCE);
	
	fprintf(stderr, "cidd_gui: h_pan_event_proc: event %d\n", event_id(event));
	
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

	return notify_next_event_func(win, (Notify_event) event, arg, type);
}

/*
 * Notify callback function for `field_st'.
 */
void
field_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: field_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */
		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `zoom_st'.
 */
void
zoom_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: zoom_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */
		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `movie_st'.
 */
void
movie_ctl_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: movie_ctl_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */
		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `overlay_st'.
 */
void
overlay_ctl_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: overlay_ctl_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */
		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `product_st'.
 */
void
product_ctl_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: product_ctl_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */
		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `export_st'.
 */
void
export_ctl_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: export_ctl_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */
		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `x_sect_st'.
 */
void
x_sect_ctl_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: x_sect_ctl_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */
		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `field_sel_st'.
 */
void
field_sel_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: field_sel_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */
		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `vector_st'.
 */
void
set_vectors_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: set_vectors_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */
		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `slice_sl'.
 */
void
sl_proc(Panel_item item, int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	
	fprintf(stderr, "cidd_gui: sl_proc: value: %d\n", value);
	
	/* gxv_start_connections DO NOT EDIT THIS SECTION */
	/* gxv_end_connections */

}

/*
 * Event callback function for `canvas1'.
 */
Notify_value
can_event_proc(Xv_window win, Event *event, Notify_arg arg, Notify_event_type type)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(xv_get(win, CANVAS_PAINT_CANVAS_WINDOW), XV_KEY_DATA, INSTANCE);
	
	fprintf(stderr, "cidd_gui: can_event_proc: event %d\n", event_id(event));
	
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

	return notify_next_event_func(win, (Notify_event) event, arg, type);
}

/*
 * Repaint callback function for `canvas1'.
 */
void
can_repaint(Canvas canvas, Xv_window paint_window, Display *display, Window xid, Xv_xrectlist *rects)
{
	fputs("cidd_gui: can_repaint\n", stderr);
	
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

}

/*
 * Notify callback function for `main_st'.
 */
void
main_st_proc(Panel_item item, unsigned int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	short	i;
	
	fputs("cidd_gui: main_st_proc\n", stderr);
	for (i = 0; i < 1; i++) {
		if (value & 01)
			fprintf(stderr, "\t%dth item selected\n", i);
		
		/* gxv_start_connections DO NOT EDIT THIS SECTION */

		/* gxv_end_connections */

		value >>= 1;
	}
}

/*
 * Notify callback function for `im_cache_st'.
 */
void
im_cache_proc(Panel_item item, int value, Event *event)
{
	h_win_horiz_bw_objects *ip = (h_win_horiz_bw_objects *) xv_get(item, XV_KEY_DATA, INSTANCE);
	
	fprintf(stderr, "cidd_gui: im_cache_proc: value: %u\n", value);
	
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

}
