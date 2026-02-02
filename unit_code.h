



/*===[[ unit_code.c ]]========================================================*/
/*········´ ´·············endcaps·´ ´·········································*/
char        ymap__unit_quiet        (void);
char        ymap__unit_loud         (void);
char        ymap__unit_end          (void);
/*········´ ´················load·´ ´·········································*/
char        ymap__unit_massive      (void);
char        ymap__unit_load         (uchar a_axis, uchar a_style);
char        ymap__unit_full         (uchar a_axis, uchar a_style);
char*       ymap_print              (uchar a_axis);
char*       ymap_print_grid         (uchar a_axis);
/*········´ ´················mock·´ ´·········································*/
char        ymap__unit_map_general  (void);
char        ymap__unit_map_bigger   (void);
char        ymap__unit_map_block    (void);
char        ymap__unit_locator      (char a_strict, char *a_label, ushort *u, ushort *x, ushort *y, ushort *z);
char        ymap__unit_addresser    (char a_strict, char *a_label, ushort u, ushort x, ushort y, ushort z);
char        ymap__unit_init         (void);
char        ymap__unit_presizer     (ushort a_min, ushort a_max);
char        ymap__unit_sizer        (char a_axis, ushort *n, ushort *a, ushort *b, ushort *c, ushort *e, ushort *m, ushort *x);
char        ymap__unit_entry        (char a_axis, ushort a_pos, short *r_ref, uchar *r_wide, uchar *r_used);
char        ymap__unit_placer       (char a_axis, ushort b, ushort c, ushort e);
char        ymap__unit_done         (void);
char        ymap__unit_mapper       (char a_type);
/*········´ ´··············format·´ ´·········································*/
char        ymap__unit_format_init  (void);
char        ymap__unit_formatter    (uchar a_type, uchar a_abbr, ushort u, ushort x, ushort y, ushort z, uchar *r);
char*       ymap__unit_formatted    (ushort y);
/*········´ ´················mreg·´ ´·········································*/
char        ymap__unit_base         (void);
char        ymap__unit_config       (void);
char*       ymap__unit_orig         (void);
char*       ymap__unit_reqs         (void);
char*       ymap__unit_adds         (void);
char*       ymap__unit_mreg         (void);
/*········´ ´···············mundo·´ ´·········································*/
char        ymap__unit_mundo        (char a_dir, char a, char *l, char *f, char *c);
/*········´ ´············accessor·´ ´·········································*/
char*       yMAP__unit              (char *a_question, char a_index);
/*········´ ´················DONE·´ ´·········································*/

