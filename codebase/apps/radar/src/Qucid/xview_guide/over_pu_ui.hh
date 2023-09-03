/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/* ** Copyright UCAR (c) 1990 - 2016                                         */
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
/* ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  */
/* ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      */
/* ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    */
/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
#ifndef	over_pu_HEADER
#define	over_pu_HEADER

/*
 * over_pu_ui.h - User interface object and function declarations.
 * This file was generated by `gxv' from `over_pu.G'.
 * DO NOT EDIT BY HAND.
 */

extern Attr_attribute	INSTANCE;


typedef struct {
	Xv_opaque	over_pu;
	Xv_opaque	over_cp;
	Xv_opaque	over_lst;
	Xv_opaque	over_pu_st;
} over_pu_over_pu_objects;

extern over_pu_over_pu_objects	*over_pu_over_pu_objects_initialize(over_pu_over_pu_objects *, Xv_opaque);

extern Xv_opaque	over_pu_over_pu_over_pu_create(over_pu_over_pu_objects *, Xv_opaque);
extern Xv_opaque	over_pu_over_pu_over_cp_create(over_pu_over_pu_objects *, Xv_opaque);
extern Xv_opaque	over_pu_over_pu_over_lst_create(over_pu_over_pu_objects *, Xv_opaque);
extern Xv_opaque	over_pu_over_pu_over_pu_st_create(over_pu_over_pu_objects *, Xv_opaque);
#endif
