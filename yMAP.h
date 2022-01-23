/*============================----beg-of-source---============================*/
#ifndef yMAP
#define yMAP yes



typedef  unsigned char        uchar;
typedef  unsigned short       ushort;


#define     LEN_HUGE       10000
#define     LEN_RECD        2000
#define     YMAP_EMPTY    -32000
#define     YMAP_LEAVE    -32000
#define     YMAP_IGNORE    64000


#define     YMAP_NADA      (uchar) '·'              /* nothing in location            */
#define     YMAP_PLACE     (uchar) '´'              /* exists, but nominal            */
#define     YMAP_USED      (uchar) 'Ï'              /* location really used           */
#define     YMAP_LOWER     (uchar) '<'              /* lower row/col limit across all       */
#define     YMAP_UPPER     (uchar) '>'              /* upper row/col limit across all       */
#define     YMAP_BOTH      (uchar) '|'              /* both row/col limits across all       */
#define     YMAP_CURR      255

/*
 *  used
 *
 *   ----- unit  ··0 ··1 ··2 ··3 ··4 ··5 ··6 ··7 ··8 ··9 ·10 ·11 ·12 ·13 ·14 ·15
 *   short grid  ··1 ··2 ··3 ··4 ··5 ··6 ··7 ··8 ··9 ·10 ·11 ·12 ·13 ·14 ·15 ·16
 *   uchar wide    4   3   3   1   6   2   2   1   4   3   3   1   6   2   2   1
 *   uchar used    ·   ·   |   Ï   Ï   Ï   ·   Ï   Ï   ·   |   ·   ·   ·   ·   ·
 *
 *   map   00001112223444444556678888999aaabccccccddeef
 *   disp  ···+··+··++·····+·+·++···+··+··++·····+·+·++
 *
 *
 *
 */


#define     YMAP_UNIV            'u'
#define     YMAP_XAXIS           'x'
#define     YMAP_YAXIS           'y'
#define     YMAP_ZAXIS           'z'
#define     YMAP_WHEN            'w'




#define     YMAP_RIGHT           'r'
#define     YMAP_OFFICE          'o'



/*
 *    1) source/content change        must update ends only
 *    2) position change              must update display and ends
 *    3) full change                  must update map, display, and ends
 *
 *    if (NCOL != NCOL_SAVE)   full          map, display, and ends
 *    if (CCOL != CCOL_SAVE)   position      display and ends
 *    if (any size change)     size          display and ends
 *    else                                   ends
 *
 *    CHANGE UNIVERSE 
 *       universe            display and ends
 *       other axis          map, display, and ends
 *
 *    CHANGE NUMBER OF EMTRIES (mundo)...
 *       append and delete   map, display, and ends
 *
 *    CHANGE POSITION
 *       inside axis         display and ends
 *       other axis          map, display, and ends
 *
 *    CHANGE SIZE
 *       width/height        direct for each entry, plus display and ends
 *
 *    CHANGE CONTENT
 *       paste or clear      direct for each entry, plus display and ends
 *       source              direct for entry, ends
 *
 *
 *   add mundo for universe size changes
 *   add mundo for deletes (shrinking size)
 *   add mundo for insert/appends (growing size)
 *
 *
 *
 */

#define     YMAP_FULL            3
#define     YMAP_POS             2
#define     YMAP_SRC             1
#define     YMAP_SKIP            0

/*---(initialize)---------------------*/
#define     YMAP_INIT            'I'
/*---(universe)-----------------------*/
#define     YMAP_USRC            'u'
#define     YMAP_UPOS            'U'
#define     YMAP_UFUL            'û'
/*---(xaxis)--------------------------*/
#define     YMAP_XSRC            'x'
#define     YMAP_XPOS            'X'
#define     YMAP_XFUL            'õ'
/*---(yaxis)--------------------------*/
#define     YMAP_YSRC            'y'
#define     YMAP_YPOS            'Y'
#define     YMAP_YFUL            'ï'
/*---(done)---------------------------*/

/*---(completely clean and populate)-----*/
/*---(changed focus of map)--------------*/
#define     YMAP_MAJOR           'M'
/*---(same focus, different pos)---------*/
#define     YMAP_MINOR           'n'
/*---(update as neccessary)--------------*/
#define     YMAP_UPDATE          'i'
/*---(display only)----------------------*/


/*---(everything is new)-----------------*/
/*---(universe)--------------------------*/
#define     YMAP_UNIVERSE        'U'
#define     YMAP_UNIVDISP        'u'
/*---(xyz)-------------------------------*/
#define     YMAP_DISPONLY        'd'
/*---(done)------------------------------*/



/*---(univers changes)-----------*/
#define     YMAP_VOLUME       'V'
#define     YMAP_TITLE        'T'
/*---(object changes)------------*/
#define     YMAP_CREATE       'N'
#define     YMAP_BLANK        'B'
#define     YMAP_DELETE       'D'
#define     YMAP_WIDTH        'X'
#define     YMAP_WEXACT       (uchar) 'õ'
#define     YMAP_HEIGHT       'Y'
#define     YMAP_HEXACT       (uchar) 'î'
#define     YMAP_DEPTH        'Z'
#define     YMAP_DEXACT       (uchar) 'í'
#define     YMAP_SHAPE        'S'
#define     YMAP_COLOR        'C'
/*---(content changes)-----------*/
#define     YMAP_OVERWRITE    'o'
#define     YMAP_CLEAR        'x'
#define     YMAP_SOURCE       's'
#define     YMAP_ALIGN        'a'
#define     YMAP_FORMAT       'f'
#define     YMAP_DECIMALS     'd'
#define     YMAP_UNITS        'u'
/*---(validations)---------------*/
#define     YMAP_FORMATS      "afdu"
#define     YMAP_SIZES        "xyz"
/*---(modes)---------------------*/
#define     YMAP_NONE         '/'
#define     YMAP_BEG          '['
#define     YMAP_ADD          '+'
#define     YMAP_MODES        "/[+"
/*---(done)----------------------*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yMAP_version            (void);
char        yMAP_init               (void);
char        yMAP_config             (char a_orient, void *a_locator, void *a_addresser, void *a_sizer, void *a_entry, void *a_placer, void *a_done);
char        yMAP_wrap               (void);
char*       yMAP__unit              (char *a_question, char a_index);


char        yMAP_clear              (uchar a_axis);
char        yMAP_allsize            (ushort u, ushort x, ushort y, ushort z, ushort w);

char        yMAP_size               (uchar a_axis, ushort a_len);
char        yMAP_entry              (uchar a_axis, ushort n, short a_ref, uchar a_wide, uchar a_used);
/*---(process)--------------*/
char        yMAP_refresh            (void);
char        yMAP_refresh_full       (void);
char        yMAP_refresh_disponly   (void);
/*---(universe)-------------*/
char        yMAP_refresh_universe   (void);
char        yMAP_refresh_univdisp   (void);
/*---(done)-----------------*/

char        yMAP_start              (uchar a_axis, ushort a_len);
char        yMAP_append             (short a_ref, uchar a_wide, uchar a_used);
char        yMAP_finish             (void);
char        yMAP_by_index           (uchar a_axis, uchar a_pos, ushort *r_pos, short *r_ref, uchar *r_wide, uchar *r_used);
char        yMAP_by_cursor          (uchar a_axis, uchar a_dir, ushort *r_pos, short *r_ref, uchar *r_wide, uchar *r_used);

char        yMAP_cmd_loc            (char *a_cmd);
char        yMAP_jump               (ushort u, ushort x, ushort y, ushort z);
char        yMAP_beg                (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z);
char        yMAP_current            (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z);
char        yMAP_current_unit       (ushort *u, ushort *x, ushort *y, ushort *z);

char        yMAP_axis_avail         (uchar a_axis, ushort a_avail);
char        yMAP_axis_force         (uchar a_axis, ushort a_beg, ushort a_cur, ushort a_end);
char        yMAP_axis_grid          (uchar a_axis, ushort *a_beg, ushort *a_cur, ushort *a_end, uchar *a_extra);



/*===[[ yMAP_visual.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(cursor)---------------*/
char        yMAP_visu_range         (ushort *u, ushort *xb, ushort *xe, ushort *yb, ushort *ye, ushort *zb, ushort *ze, char *c);
char        yMAP_visu_first         (ushort *u, ushort *x, ushort *y, ushort *z);
char        yMAP_visu_next          (ushort *u, ushort *x, ushort *y, ushort *z);
/*---(cursor)---------------*/
char        yMAP_visu_islive        (void);
char        yMAP_root               (ushort u, ushort x, ushort y, ushort z);
char        yMAP_visual             (ushort u, ushort x, ushort y, ushort z);
/*---(done)-----------------*/



/*===[[ yMAP_rptg.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yMAP_current_status     (char a_size, short a_wide, char *a_list);
char        yMAP_xunit_status       (char a_size, short a_wide, char *a_list);
char        yMAP_yunit_status       (char a_size, short a_wide, char *a_list);
char        yMAP_xgrid_status       (char a_size, short a_wide, char *a_list);
char        yMAP_ygrid_status       (char a_size, short a_wide, char *a_list);
char        yMAP_visu_status        (char a_size, short a_wide, char *a_list);
char*       yMAP_mundo_detail       (int n);


/*===[[ yMAP_mreg.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yMAP_mreg_config        (void *a_clearer, void *a_copier, void *a_router, void *a_paster, void *a_finisher, void *a_regkill, void *a_exim);
char        yMAP_mreg_add           (void *a_thing, char *a_label);



/*===[[ yMAP_mundo.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        yMAP_mundo_config       (char a_len, void *a_mundo);
char        yMAP_mundo_purge        (void);
/*---(simple)---------------*/
char        yMAP_mundo_align        (char a_mode, char *a_label, char a_before, char a_after);
char        yMAP_mundo_format       (char a_mode, char *a_label, char a_before, char a_after);
char        yMAP_mundo_decimals     (char a_mode, char *a_label, char a_before, char a_after);
char        yMAP_mundo_units        (char a_mode, char *a_label, char a_before, char a_after);
/*---(number)---------------*/
char        yMAP_mundo_width        (char a_mode, char *a_label, char a_before, char a_after);
char        yMAP_mundo_height       (char a_mode, char *a_label, char a_before, char a_after);
char        yMAP_mundo_depth        (char a_mode, char *a_label, char a_before, char a_after);
/*---(string)---------------*/
char        yMAP_mundo_source       (char a_mode, char *a_label, char* a_before, char* a_after);
char        yMAP_mundo_volume       (char a_mode, char *a_label, char* a_before, char* a_after);
/*---(complex)--------------*/
char        yMAP_mundo_overwrite    (char a_mode, char *a_label, char* a_beforeF, char* a_before, char* a_afterF, char* a_after);
char        yMAP_mundo_clear        (char a_mode, char *a_label, char* a_beforeF, char* a_before, char *a_afterF);
char        yMAP_mundo_delete       (char a_mode, char *a_label, char* a_beforeF, char* a_before);
/*---(done)-----------------*/

char*       yMAP_univ_name          (char n);
char        yMAP_univ_config        (void *a_switcher);
char        yMAP_universe           (ushort a_pos, uchar a_used);
char        yMAP_switch             (ushort a_pos);

char        yMAP_multi_wide         (char *a_label, uchar a_size, uchar a_count);
char        yMAP_multi_tall         (char *a_label, uchar a_size, uchar a_count);
char        yMAP_multi_deep         (char *a_label, uchar a_size, uchar a_count);
char        yMAP_formatter          (void *a_formatter);


char        yMAP_inside             (short u, short x, short y, short z);
char        yMAP_move_hmode         (uchar a_major, uchar a_minor);
char        yMAP__unit_wander       (void);

#endif
/*============================----end-of-source---============================*/
