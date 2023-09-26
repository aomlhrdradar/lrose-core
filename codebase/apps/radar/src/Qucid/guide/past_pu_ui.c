/*
 * past_pu_ui.c - User interface object initialization functions.
 * This file was generated by `gxv' from `past_pu.G'.
 * DO NOT EDIT BY HAND.
 */

#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <xview/xview.h>
#include <xview/canvas.h>
#include <xview/panel.h>
#include <xview/scrollbar.h>
#include <xview/svrimage.h>
#include <xview/termsw.h>
#include <xview/text.h>
#include <xview/tty.h>
#include <xview/xv_xrect.h>
#include "past_pu_ui.h"

/*
 * Initialize an instance of object `past_pu'.
 */
past_pu_past_pu_objects *
past_pu_past_pu_objects_initialize(past_pu_past_pu_objects *ip, Xv_opaque owner)
{
	if (!ip && !(ip = (past_pu_past_pu_objects *) calloc(1, sizeof (past_pu_past_pu_objects))))
		return (past_pu_past_pu_objects *) NULL;
	if (!ip->past_pu)
		ip->past_pu = past_pu_past_pu_past_pu_create(ip, owner);
	if (!ip->controls1)
		ip->controls1 = past_pu_past_pu_controls1_create(ip, ip->past_pu);
	if (!ip->past_hr_st)
		ip->past_hr_st = past_pu_past_pu_past_hr_st_create(ip, ip->controls1);
	return ip;
}

/*
 * Create object `past_pu' in the specified instance.
 */
Xv_opaque
past_pu_past_pu_past_pu_create(past_pu_past_pu_objects *ip, Xv_opaque owner)
{
	Xv_opaque	obj;
	
	obj = xv_create(owner, FRAME_CMD,
		XV_KEY_DATA, INSTANCE, ip,
		XV_WIDTH, 78,
		XV_HEIGHT, 65,
		XV_LABEL, "Past",
		XV_SHOW, FALSE,
		FRAME_SHOW_FOOTER, FALSE,
		FRAME_SHOW_RESIZE_CORNER, FALSE,
		FRAME_CMD_PUSHPIN_IN, FALSE,
		NULL);
	xv_set(xv_get(obj, FRAME_CMD_PANEL), WIN_SHOW, FALSE, NULL);
	return obj;
}

/*
 * Create object `controls1' in the specified instance.
 */
Xv_opaque
past_pu_past_pu_controls1_create(past_pu_past_pu_objects *ip, Xv_opaque owner)
{
	Xv_opaque	obj;
	
	obj = xv_create(owner, PANEL,
		XV_KEY_DATA, INSTANCE, ip,
		XV_X, 0,
		XV_Y, 0,
		XV_WIDTH, WIN_EXTEND_TO_EDGE,
		XV_HEIGHT, WIN_EXTEND_TO_EDGE,
		WIN_BORDER, FALSE,
		NULL);
	return obj;
}

/*
 * Create object `past_hr_st' in the specified instance.
 */
Xv_opaque
past_pu_past_pu_past_hr_st_create(past_pu_past_pu_objects *ip, Xv_opaque owner)
{
	extern void		past_hr_proc(Panel_item, int, Event *);
	Xv_opaque	obj;
	
	obj = xv_create(owner, PANEL_CHOICE,
		XV_KEY_DATA, INSTANCE, ip,
		XV_X, 4,
		XV_Y, 6,
		PANEL_CHOICE_NCOLS, 1,
		PANEL_LAYOUT, PANEL_HORIZONTAL,
		PANEL_CHOOSE_NONE, FALSE,
		PANEL_NOTIFY_PROC, past_hr_proc,
		NULL);
	return obj;
}

