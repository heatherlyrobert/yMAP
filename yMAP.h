/*============================----beg-of-source---============================*/
#ifndef yMAP
#define yMAP yes



typedef  unsigned char        uchar;
typedef  unsigned short       ushort;


#define     LEN_HUGE       10000
#define     LEN_RECD        2000
#define     YMAP_EMPTY    -32000
#define     YMAP_LEAVE    -32000

#define     YMAP_NADA      '·';             /* nothing in location            */
#define     YMAP_USED      'Ï';             /* location used                  */
#define     YMAP_LIMIT     '|';             /* row/col limit across all       */


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

/*---(completely clean and populate)-----*/
#define     YMAP_INIT            'I'
/*---(changed focus of map)--------------*/
#define     YMAP_MAJOR           'M'
/*---(same focus, different pos)---------*/
#define     YMAP_MINOR           'n'
/*---(update as neccessary)--------------*/
#define     YMAP_UPDATE          'u'



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yMAP_version            (void);
char        yMAP_init               (void);
char        yMAP_config             (char a_orient, void *a_mapper, void *a_locator, void *a_addresser);
char        yMAP_wrap               (void);
char*       yMAP__unit              (char *a_question, char a_index);


char        yMAP_clear              (uchar a_axis);
char        yMAP_allsize            (ushort u, ushort x, ushort y, ushort z, ushort w);

char        yMAP_size               (uchar a_axis, ushort a_len);
char        yMAP_entry              (uchar a_axis, ushort n, short a_ref, uchar a_wide, uchar a_used);
char        yMAP_update             (uchar a_axis);
char        yMAP_refresh            (void);

char        yMAP_start              (uchar a_axis, ushort a_len);
char        yMAP_append             (short a_ref, uchar a_wide, uchar a_used);
char        yMAP_finish             (void);


char        yMAP_jump               (ushort u, ushort x, ushort y, ushort z);
char        yMAP_current            (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z);
char        yMAP_current_unit       (ushort *u, ushort *x, ushort *y, ushort *z);

char        yMAP_axis_avail         (uchar a_axis, ushort a_avail);
char        yMAP_axis_force         (uchar a_axis, ushort a_beg, ushort a_cur, ushort a_end);
char        yMAP_axis_grid          (uchar a_axis, ushort *a_beg, ushort *a_cur, ushort *a_end, uchar *a_extra);



/*===[[ yMAP_visual.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(cursor)---------------*/
char        yMAP_visu_range         (ushort *u, ushort *xb, ushort *xe, ushort *yb, ushort *ye, ushort *zb, ushort *ze);
char        yMAP_visu_first         (ushort *u, ushort *x, ushort *y, ushort *z);
char        yMAP_visu_next          (ushort *u, ushort *x, ushort *y, ushort *z);
/*---(cursor)---------------*/
char        yMAP_root               (ushort u, ushort x, ushort y, ushort z);
char        yMAP_visual             (ushort u, ushort x, ushort y, ushort z);
/*---(done)-----------------*/



/*===[[ yMAP_visual.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yMAP_current_status     (char a_size, short a_wide, char *a_list);
char        yMAP_xunit_status       (char a_size, short a_wide, char *a_list);
char        yMAP_yunit_status       (char a_size, short a_wide, char *a_list);
char        yMAP_xgrid_status       (char a_size, short a_wide, char *a_list);
char        yMAP_ygrid_status       (char a_size, short a_wide, char *a_list);
char        yMAP_visu_status        (char a_size, short a_wide, char *a_list);



#endif
/*============================----end-of-source---============================*/
