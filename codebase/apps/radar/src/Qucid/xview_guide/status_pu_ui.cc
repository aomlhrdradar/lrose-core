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
/*
 * status_pu_ui.c - User interface object initialization functions.
 * This file was generated by `gxv' from `status_pu.G'.
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
#include "status_pu_ui.h"

/*
 * Initialize an instance of object `status_pu'.
 */
status_pu_status_pu_objects *
status_pu_status_pu_objects_initialize(status_pu_status_pu_objects *ip, Xv_opaque owner)
{
	if (!ip && !(ip = (status_pu_status_pu_objects *) calloc(1, sizeof (status_pu_status_pu_objects))))
		return (status_pu_status_pu_objects *) NULL;
	if (!ip->status_pu)
		ip->status_pu = status_pu_status_pu_status_pu_create(ip, owner);
	if (!ip->controls1)
		ip->controls1 = status_pu_status_pu_controls1_create(ip, ip->status_pu);
	if (!ip->dismiss_bt)
		ip->dismiss_bt = status_pu_status_pu_dismiss_bt_create(ip, ip->controls1);
	if (!ip->clear_bt)
		ip->clear_bt = status_pu_status_pu_clear_bt_create(ip, ip->controls1);
	if (!ip->status_list)
		ip->status_list = status_pu_status_pu_status_list_create(ip, ip->controls1);
	return ip;
}

/*
 * Create object `status_pu' in the specified instance.
 */
Xv_opaque
status_pu_status_pu_status_pu_create(status_pu_status_pu_objects *ip, Xv_opaque owner)
{
	extern Notify_value	status_pu_status_pu_event_callback(Xv_window, Event *, Notify_arg, Notify_event_type);
	Xv_opaque	obj;
	
	obj = xv_create(owner, FRAME_CMD,
		XV_KEY_DATA, INSTANCE, ip,
		XV_WIDTH, 543,
		XV_HEIGHT, 435,
		XV_LABEL, "CIDD Status",
		XV_SHOW, FALSE,
		FRAME_SHOW_FOOTER, FALSE,
		FRAME_SHOW_RESIZE_CORNER, TRUE,
		FRAME_CMD_PUSHPIN_IN, TRUE,
		NULL);
	xv_set(obj, WIN_CONSUME_EVENTS,
		NULL, NULL);
	notify_interpose_event_func(obj,
		(Notify_func) status_pu_status_pu_event_callback, NOTIFY_SAFE);
	xv_set(xv_get(obj, FRAME_CMD_PANEL), WIN_SHOW, FALSE, NULL);
	return obj;
}

/*
 * Create object `controls1' in the specified instance.
 */
Xv_opaque
status_pu_status_pu_controls1_create(status_pu_status_pu_objects *ip, Xv_opaque owner)
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
 * Create object `dismiss_bt' in the specified instance.
 */
Xv_opaque
status_pu_status_pu_dismiss_bt_create(status_pu_status_pu_objects *ip, Xv_opaque owner)
{
	extern void		status_dismiss_proc(Panel_item, Event *);
	Xv_opaque	obj;
	
	obj = xv_create(owner, PANEL_BUTTON,
		XV_KEY_DATA, INSTANCE, ip,
		XV_X, 466,
		XV_Y, 6,
		PANEL_LABEL_STRING, "Dismiss",
		PANEL_NOTIFY_PROC, status_dismiss_proc,
		NULL);
	return obj;
}

/*
 * Create object `clear_bt' in the specified instance.
 */
Xv_opaque
status_pu_status_pu_clear_bt_create(status_pu_status_pu_objects *ip, Xv_opaque owner)
{
	extern void		status_clear_proc(Panel_item, Event *);
	Xv_opaque	obj;
	
	obj = xv_create(owner, PANEL_BUTTON,
		XV_KEY_DATA, INSTANCE, ip,
		XV_X, 16,
		XV_Y, 8,
		PANEL_LABEL_STRING, "Clear",
		PANEL_NOTIFY_PROC, status_clear_proc,
		NULL);
	return obj;
}

/*
 * Create object `status_list' in the specified instance.
 */
Xv_opaque
status_pu_status_pu_status_list_create(status_pu_status_pu_objects *ip, Xv_opaque owner)
{
	Xv_opaque	obj;
	
	obj = xv_create(owner, PANEL_LIST,
		XV_KEY_DATA, INSTANCE, ip,
		XV_X, 16,
		XV_Y, 36,
		PANEL_LIST_WIDTH, 500,
		PANEL_LIST_DISPLAY_ROWS, 20,
		PANEL_LAYOUT, PANEL_VERTICAL,
		PANEL_READ_ONLY, TRUE,
		PANEL_CHOOSE_ONE, TRUE,
		PANEL_CHOOSE_NONE, TRUE,
		NULL);
	return obj;
}

