#ifndef	fields_pu_HEADER
#define	fields_pu_HEADER

/*
 * fields_pu_ui.h - User interface object and function declarations.
 * This file was generated by `gxv' from `fields_pu.G'.
 * DO NOT EDIT BY HAND.
 */

extern Attr_attribute	INSTANCE;

extern Xv_opaque	fields_pu_field_mu_create(caddr_t, Xv_opaque);
extern Xv_opaque	fields_pu_wind_mu_create(caddr_t, Xv_opaque);
extern Xv_opaque	fields_pu_prod_mu_create(caddr_t, Xv_opaque);

typedef struct {
	Xv_opaque	fields_pu;
	Xv_opaque	fields_controls;
	Xv_opaque	f_config_sel_bt;
	Xv_opaque	f_config_msg1;
	Xv_opaque	f_config_msg2;
	Xv_opaque	group5;
	Xv_opaque	f_config_tx1;
	Xv_opaque	f_config_tx4;
	Xv_opaque	f_config_tx9;
	Xv_opaque	f_config_tx3;
	Xv_opaque	f_config_msg6;
	Xv_opaque	f_config_msg7;
	Xv_opaque	group3;
	Xv_opaque	f_config_color_apply_bt;
	Xv_opaque	f_config_msg8;
	Xv_opaque	f_config_tx7;
	Xv_opaque	f_config_tx8;
	Xv_opaque	group4;
	Xv_opaque	update_st;
	Xv_opaque	max_st;
	Xv_opaque	autoscale_st;
	Xv_opaque	f_config_msg3;
	Xv_opaque	group2;
	Xv_opaque	ren_meth_st;
	Xv_opaque	f_config_msg4;
	Xv_opaque	group1;
	Xv_opaque	group6;
	Xv_opaque	display_list;
	Xv_opaque	separator1;
	Xv_opaque	w_config_sel_bt;
	Xv_opaque	w_config_msg1;
	Xv_opaque	w_config_msg2;
	Xv_opaque	w_config_color_msg;
	Xv_opaque	group7;
	Xv_opaque	w_config_url_tx;
	Xv_opaque	w_config_u_tx;
	Xv_opaque	w_config_v_tx;
	Xv_opaque	w_config_w_tx;
	Xv_opaque	w_config_line_width_tx;
	Xv_opaque	group8;
	Xv_opaque	w_style_tx;
	Xv_opaque	textfield2;
	Xv_opaque	textfield1;
	Xv_opaque	wind_alt_tx;
	Xv_opaque	group9;
	Xv_opaque	group10;
	Xv_opaque	separator2;
	Xv_opaque	render_type_st;
	Xv_opaque	p_config_sel_bt;
	Xv_opaque	prod_config_msg1;
	Xv_opaque	prod_config_msg2;
	Xv_opaque	group11;
	Xv_opaque	group13;
	Xv_opaque	p_config_url_tx;
	Xv_opaque	p_config_type_tx;
	Xv_opaque	allow_before_tx;
	Xv_opaque	allow_after_tx;
	Xv_opaque	text_thresh_tx;
	Xv_opaque	p_config_msg3;
	Xv_opaque	group12;
	Xv_opaque	group15;
	Xv_opaque	separator3;
	Xv_opaque	topo_url_tx;
	Xv_opaque	land_use_url_tx;
	Xv_opaque	group14;
} fields_pu_fields_pu_objects;

extern fields_pu_fields_pu_objects	*fields_pu_fields_pu_objects_initialize(fields_pu_fields_pu_objects *, Xv_opaque);

extern Xv_opaque	fields_pu_fields_pu_fields_pu_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_fields_controls_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_sel_bt_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_msg1_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_msg2_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group5_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_tx1_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_tx4_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_tx9_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_tx3_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_msg6_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_msg7_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group3_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_color_apply_bt_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_msg8_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_tx7_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_tx8_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group4_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_update_st_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_max_st_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_autoscale_st_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_msg3_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group2_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_ren_meth_st_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_f_config_msg4_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group1_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group6_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_display_list_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_separator1_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_config_sel_bt_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_config_msg1_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_config_msg2_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_config_color_msg_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group7_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_config_url_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_config_u_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_config_v_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_config_w_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_config_line_width_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group8_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_w_style_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_textfield2_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_textfield1_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_wind_alt_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group9_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group10_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_separator2_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_render_type_st_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_p_config_sel_bt_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_prod_config_msg1_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_prod_config_msg2_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group11_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group13_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_p_config_url_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_p_config_type_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_allow_before_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_allow_after_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_text_thresh_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_p_config_msg3_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group12_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group15_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_separator3_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_topo_url_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_land_use_url_tx_create(fields_pu_fields_pu_objects *, Xv_opaque);
extern Xv_opaque	fields_pu_fields_pu_group14_create(fields_pu_fields_pu_objects *, Xv_opaque);
#endif
