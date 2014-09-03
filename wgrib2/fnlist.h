/* headers for wgrib callable functions */

enum fntype {inv, output, inv_output, misc, setup};

struct function {const char *name; int (*fn)(); enum fntype type; int nargs; const char *desc; int sort;};

extern struct function functions[];

extern int nfunctions;

int f_0xSec(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_MM(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_N_ens(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_RT(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_S(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_Sec0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_Sec3(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_Sec4(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_Sec5(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_Sec6(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_Sec_len(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_T(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_V(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_VT(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_YY(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_aerosol_size(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_aerosol_wavelength(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_bitmap(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_center(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_checksum(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_code_table_0_0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_1_0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_1_1(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_1_2(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_1_3(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_1_4(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_1(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_11(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_15(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_2(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_20(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_21(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_6(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_7(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_3_8(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_1(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_10(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_11(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_11s(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_15(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_2(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_230(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_233(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_235(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_3(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_4(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_5a(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_5b(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_6(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_7(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_9(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_91(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_91b(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_5_0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_5_1(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_5_4(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_5_5(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_5_6(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_5_7(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_6_0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_ctl_ens(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_ctl_inv(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_cyclic(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_0_0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_domain(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_end_FT(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_end_ft(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_ens(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_ext_name(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_flag_table_3_10(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_flag_table_3_3(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_flag_table_3_4(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_flag_table_3_5(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_flag_table_3_9(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_ftime(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_full_name(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_gdt(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_get_byte(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_get_hex(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_get_ieee(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_get_int(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_get_int2(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_grid(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_grid_id(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_ij(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_ijlat(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_ilat(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_lev(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_lev0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_ll2i(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_ll2ij(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_lon(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_match_inv(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_max(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_min(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_misc(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_n(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_nl(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_nl_out(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_nlons(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_npts(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_nxny(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_packing(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_pds_fcst_time(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_print(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_prob(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_code_table_4_3(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_processid(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_proj4_ij2ll(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_proj4_ll2i(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_proj4_ll2ij(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_radius(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_range(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_s(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_scale(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_scaling(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_scan(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_spatial_proc(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_spectral(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_spectral_bands(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_start_FT(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_start_ft(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_stats(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_subcenter(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_t(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_table(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_unix_time(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_var(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_varX(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_vector_dir(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_verf(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_vt(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_wave_partition(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_inv_f77(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_s_out(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_big_endian(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_colon(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_config(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_count(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_end(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_fix_CFSv2_fcst(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_fix_ncep(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_gctpc(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_grid_changes(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_grid_def(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_h(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_header(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_help(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_if(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_if_n(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_if_rec(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_if_reg(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_ijundefine(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_import_bin(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_import_ieee(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_import_text(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_inv(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_limit(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_little_endian(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_new_grid_interpolation(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_new_grid_ipopt(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_new_grid_vectors(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_new_grid_winds(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_no_header(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_not_if(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_end(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_rpn(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_set_ave(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_bin_prec(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_byte(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_set_center(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_date(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_ens_num(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_set_ensm_derived_fcst(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_set_flag_table_3_3(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_flag_table_3_4(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_ftime(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_grib_max_bits(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_grib_type(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_hex(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_set_ieee(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_set_ijval(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_set_int(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_set_int2(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_set_ival(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_set_lev(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_metadata(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_pdt(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_radius(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_scaling(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_set_sec_size(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_set_ts_dates(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_set_var(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_submsg(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_sys(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_text_col(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_text_fmt(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_udf(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_udf_arg(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_undefine(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_undefine_val(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_v(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_v0(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_v(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_v2(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_v98(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_v99(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_version(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_AAIG(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_GRIB(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_ave(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_bin(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_cress_lola(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3, const char *arg4);
int f_csv(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_csv_nz(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_fcst_ave(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_fi(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_grib(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_grib_ieee(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_grib_out(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_grib_out_irr(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_ieee(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_ijbox(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3, const char *arg4);
int f_ijsmall_grib(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_irr_grid(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_lola(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3, const char *arg4);
int f_merge_fcst(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_mysql(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3, const char *arg4, const char *arg5);
int f_mysql_dump(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3, const char *arg4, const char *arg5, const char *arg6, const char *arg7);
int f_mysql_speed(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3, const char *arg4, const char *arg5, const char *arg6, const char *arg7);
int f_ncep_norm(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_ncep_uv(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_netcdf(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_new_grid(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3, const char *arg4);
int f_small_grib(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2, const char *arg3);
int f_spread(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_text(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_tosubmsg(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_wind_dir(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_wind_speed(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_append(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_crlf(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_d(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_eof_bin(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_eof_string(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_err_bin(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_err_string(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1, const char *arg2);
int f_fix_ncep_2(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_fix_ncep_3(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_fix_ncep_4(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_flush(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_for(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_for_n(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_g2clib(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_i(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_match(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_nc3(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_nc4(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_nc_grads(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_nc_nlev(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_nc_pack(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_nc_table(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_nc_time(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_ncpu(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_no_append(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_no_flush(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_no_nc_grads(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_no_nc_pack(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_no_nc_table(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_no_nc_time(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_not(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_one_line(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
int f_order(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_ext_name(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_set_regex(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local, const char *arg1);
int f_tigge(int mode, unsigned char **sec, float *data, unsigned int ndata, char *inv, void **local);
