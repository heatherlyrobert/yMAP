/*============================----beg-of-source---============================*/
#ifndef yMAP_priv
#define yMAP_priv yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "vi-keys location management"
#define     P_PURPOSE   ""

#define     P_NAMESAKE  "theseus"
#define     P_HERITAGE  ""
#define     P_IMAGERY   "young, handsome, vigorous man armed only with sword and sandals"
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yMAP"
#define     P_FULLPATH  "/usr/local/lib64/libyMAP"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.0-, complete and tie yVIKEYS back into it"
#define     P_VERNUM    "2.0j"
#define     P_VERTXT    "all gyges mreg testing caught up with greater details to catch technical issues"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
#include    <math.h>              /* clibc  standard math library             */
#include    <time.h>              /* clibc  time related functions            */
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
/*---(custom vi-keys)--------------------*/
#include    <yKEYS.h>             /* heatherly vikeys key handling           */
#include    <yMODE.h>             /* heatherly vikeys mode tracking          */
#include    <yVIEW.h>             /* heatherly vikeys view management        */
#include    <yMACRO.h>            /* heatherly vikeys macro processing       */
#include    <ySRC.h>              /* heatherly vikeys source editing         */
#include    <yFILE.h>             /* heatherly vikeys content file handling  */
#include    <yMARK.h>             /* heatherly vikeys search and marking      */
#include    <yCMD.h>              /* heatherly vikeys command processing     */
/*---(custom other)----------------------*/
#include    <ySORT.h>        /* heatherly sorting library               */
#include    <yDLST_solo.h>        /* heatherly double-double-list             */
/*---(done)------------------------------*/



typedef  struct  cGRID    tGRID;
struct cGRID {
   short       ref;                    /* host name for grid item             */
   uchar       wide;                   /* width of grid                       */
   uchar       used;                   /* content classification              */
   ushort      unit;                   /* tie to map                          */
};
tGRID       *g_ugrid;   /* universe/buffer  */
tGRID       *g_xgrid;   /* x-axis           */
tGRID       *g_ygrid;   /* y-axis           */
tGRID       *g_zgrid;   /* z-axis           */
tGRID       *g_wgrid;   /* when/time        */

typedef  struct cyMAP  tyMAP;
struct cyMAP {
   /*---(identity)-------------*/
   uchar       axis;                        /* b, x, y, z, or t               */
   uchar       change;                      /* flag as content needs changing */
   uchar       inc;                         /* normal movement increment      */
   /*---(lefts)----------------*/
   ushort      umin;                        /* lowest map position            */
   ushort      gmin;                        /* global min, used or not        */
   ushort      gamin;                       /* min of all used space          */
   ushort      glmin;                       /* min for col/row                */
   ushort      gprev;                       /* prev change for "end"          */
   ushort      gpuse;                       /* prev change for "used"         */
   /*---(layout)---------------*/
   ushort      glen;                        /* length of grid                 */
   tGRID      *grid;                        /* pointer to grid                */
   ushort      mlen;                        /* length of map                  */
   ushort     *map;                         /* full unit map                  */
   ushort      gused;                       /* nunber of used grids           */
   /*---(middles)--------------*/
   ushort      gavg;                        /* average position in local      */
   ushort      gmid;                        /* average position of limits     */
   /*---(rights)---------------*/
   ushort      gnuse;                       /* next change for "used"         */
   ushort      gnext;                       /* next change for "end"          */
   ushort      glmax;                       /* max for col/row                */
   ushort      gamax;                       /* max of all used space          */
   ushort      gmax;                        /* global max, used or not        */
   ushort      umax;                        /* highest map position           */
   /*---(screen units)---------*/
   ushort      ubeg;                        /* beg abs pos shown on screen    */
   ushort      ucur;                        /* cur abs pos shown on screen    */
   ushort      uend;                        /* end abs pos shown on screen    */
   ushort      ulen;                        /* len shown on screen (end-beg+1)*/
   ushort      utend;                       /* theoretical end of screen      */
   ushort      uavail;                      /* full availible room on screen  */
   /*---(screen grids)---------*/
   short       gbeg;                        /* grid at start of screen        */
   short       gcur;                        /* current grid position          */
   short       gend;                        /* grid at end of screen          */
   /*---(done)-----------------*/
};
tyMAP        g_umap;
tyMAP        g_xmap;
tyMAP        g_ymap;
tyMAP        g_zmap;
tyMAP        g_wmap;



#define     S_VISU_MAX     100
#define     VISU_NOT       '-'
#define     VISU_YES       'y'

typedef     struct cVISU    tVISU;
struct cVISU {
   /*---(flag)---------------------------*/
   uchar       abbr;
   char        active;
   char        modded;
   /*---(root)---------------------------*/
   ushort      u_all;
   ushort      x_root;
   ushort      y_root;
   ushort      z_root;
   /*---(begin)--------------------------*/
   ushort      x_beg;
   ushort      y_beg;
   ushort      z_beg;
   /*---(end)----------------------------*/
   ushort      x_end;
   ushort      y_end;
   ushort      z_end;
   /*---(labels)-------------------------*/
   char        b_label     [LEN_LABEL];
   char        e_label     [LEN_LABEL];
   /*---(special)------------------------*/
   char        x_lock;
   char        y_lock;
   char        z_lock;
   char        source;
   /*---(end)----------------------------*/
};


#define     YMAP_MAX       65000


typedef   struct cHIST  tHIST;
#define     MAX_HIST    100000
struct cHIST {
   uchar       mode;
   uchar       act;
   uchar      *label;
   uchar      *before;
   uchar      *after;
   tHIST      *h_prev;
   tHIST      *h_next;
};


typedef    struct    cMY    tMY;
struct cMY {
   /*---(universe)-------------*/
   char      (*e_switcher)   (char u);
   char       u_last;
   /*---(map)------------------*/
   char        orient;            /* normal (down = neg) office (down = pos)  */
   char      (*e_locator)    (char a_strict, char *a_label, ushort *u, ushort *x, ushort *y, ushort *z);
   char      (*e_addresser)  (char a_strict, char *a_label, ushort  u, ushort  x, ushort  y, ushort  z);
   char      (*e_sizer)      (char a_axis, ushort *n, ushort *a, ushort *b, ushort *c, ushort *e, ushort *m, ushort *x);
   char      (*e_entry)      (char a_axis, ushort a_pos, short *r_ref, uchar *r_wide, uchar *r_used);
   char      (*e_placer)     (char a_axis, ushort b, ushort c, ushort e);
   char      (*e_done)       (void);
   /*---(mreg)-----------------*/
   char      (*e_regkill)    (void *a_thing);
   void*     (*e_copier)     (char a_type, long a_stamp);
   char      (*e_clearer)    (char a_1st, ushort b, ushort x, ushort y, ushort z);
   char      (*e_paster)     (char a_regs, char a_1st, short a_uoff, short a_xoff, short a_yoff, short a_zoff, void *a_thing);
   char      (*e_finisher)   (char a_pros, char *a_target, char *a_labels, short uo, short xo, short yo, short zo);
   char      (*e_exim)       (char a_dir, char a_style);
   char        h_1st;
   /*---(mundo/hist)-----------*/
   uchar       h_active;               /* history is active y/-               */
   tHIST      *h_head;
   tHIST      *h_curr;
   tHIST      *h_tail;
   int         h_count;
   int         h_index;
   char        h_len;
   char      (*e_mundo)      (char a_dir, char a_act, char *a_label, char *a_format, char *a_content);
   /*---(other)----------------*/
   char      (*e_format)     (uchar a_type, uchar a_abbr, ushort u, ushort x, ushort y, ushort z, uchar *r);
   /*---(visual)---------------*/
   tVISU       v_visus     [S_VISU_MAX];
   char        v_nvisu;
   char        v_list      [S_VISU_MAX];
   tVISU      *v_curr;
   tVISU      *v_prev;
   uchar       v_ahead;                     /* first visual abbr in use       */
   uchar       v_acurr;                     /* current visual abbr in use     */
   uchar       v_atail;                     /* last visual abbr in use        */
   /*---(debugging)------------*/
   char        g_print     [LEN_RECD];      /* printable for testing          */
};
extern tMY         myMAP;


extern char        g_print     [LEN_RECD];






/*===[[ yMAP_base.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char*       yMAP_version            (void);
/*---(shared)---------------*/
char        ymap_pick_map           (uchar a_axis, tyMAP **r_map, tGRID **r_grid);
char        ymap_grid_set           (uchar a_axis, tyMAP *a_map, tGRID *a_grid);
char        ymap_grid_free          (uchar a_full, uchar a_axis);
char        ymap_grid_clear         (tGRID *a_grid, ushort a_len);
char        yMAP_init               (void);
char        ymap_locator            (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z);
char        ymap_locator_strict     (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z);
char        ymap_addresser          (char *a_label, ushort u, ushort x, ushort y, ushort z);
char        ymap_addresser_strict   (char *a_label, ushort u, ushort x, ushort y, ushort z);
char        ymap_valid              (ushort u, ushort x, ushort y, ushort z);
/*> char        ymap_remap              (void);                                       <*/
char        ymap_refresh            (void);
char        yMAP_wrap               (void);



/*===[[ yMAP_load.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        ymap__clear             (uchar a_full, uchar a_axis);
char        ymap_mapinit            (uchar a_axis);
char        ymap_factory            (uchar a_axis);
char        yMAP_clear              (uchar a_axis);
/*---(walking)--------------*/
char        ymap__load_limits       (tyMAP *a_map, ushort a_umin, ushort a_umax);
char        ymap__load_ends         (tyMAP *a_map, char a_dir);
char        ymap_update_large       (uchar a_axis);
char        ymap_update_small       (uchar a_axis);
/*---(done)-----------------*/



/*===[[ yMAP_mode.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ymap_mode               (uchar a_major, uchar a_minor);



/*===[[ yMAP_move.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(translate)------------*/
char        ymap_office             (uchar a_axis, uchar *r_minor);
char        ymap_corners            (uchar a_src, uchar a_axis, char *r_minor);
/*---(shared)---------------*/
char        ymap_set_by_unit        (tyMAP *a_map, ushort a_pos);
char        ymap_set_by_grid        (tyMAP *a_map, ushort b, ushort c, ushort e);
/*---(placement)------------*/
char        ymap__grid_up           (tyMAP *a_map, short a_count);
char        ymap__grid_down         (tyMAP *a_map, short a_count);
char        ymap__grid_at           (tyMAP *a_map, ushort a_unit, char a_limit);
/*---(general)--------------*/
char        ymap_simple             (tyMAP *a_map, uchar a_minor);
char        ymap_goto               (tyMAP *a_map, uchar a_minor);
char        ymap_scroll             (tyMAP *a_map, uchar a_minor);
char        ymap_ends               (tyMAP *a_map, uchar a_minor);
/*---(driver)---------------*/
char        yMAP_move_hmode         (uchar a_major, uchar a_minor);
/*---(done)-----------------*/



/*===[[ yMAP_display.c ]]=====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(align)----------------*/
char        ymap__align2left        (tyMAP *a_map, ushort *a_pos);
char        ymap__align2right       (tyMAP *a_map, ushort *a_pos);
char        ymap__align2next        (tyMAP *a_map, ushort *a_pos);
/*---(screen)---------------*/
char        ymap_update_grid        (tyMAP *a_map);
char        ymap__screen_small      (tyMAP *a_map);
char        ymap__screen_beg        (tyMAP *a_map);
char        ymap__screen_end        (tyMAP *a_map);
/*---(support)--------------*/
char        ymap_display            (tyMAP *a_map);
/*---(unittest)-------------*/
char        ymap_display_show       (tyMAP *a_map, char *a_disp);
char        ymap_display_map        (tyMAP *a_map, char *a_disp);
char        ymap_display_units      (tyMAP *a_map, char *a_disp);



/*===[[ yMAP_visual.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(utility)--------------*/
char        ymap_visu_valid         (uchar a_abbr);
char        ymap_visu_index         (uchar a_abbr);
/*---(helpers)--------------*/
char        ymap__visu_wipe         (uchar a_abbr);
char        ymap__visu_copy         (uchar a_dst, uchar a_src);
char        ymap_visu_update        (void);
/*---(program)--------------*/
char        ymap_visu_purge         (char a_scope);
char        ymap_visu_init          (void);
/*---(quick)----------------*/
char        ymap_visu_getlive       (void);
char        yMAP_visu_islive        (void);
char        ymap_visu_isdead        (void);
char        ymap_visu_makelive      (void);
/*---(setting)--------------*/
char        ymap__visu_range        (void);
char        ymap_visu_clear         (void);
char        ymap_visu_exact         (ushort u, ushort xb, ushort xe, ushort yb, ushort ye, ushort zb, ushort ze, char c);
char        ymap_visu_reverse       (void);
char        ymap_visu_locking       (char a_type);
/*---(history)--------------*/
char        ymap__visu_save         (uchar a_abbr);
char        ymap__visu_return       (uchar a_abbr);
char        ymap_visu_reselect      (void);
/*---(cursor)---------------*/
char        yMAP_visu_range         (ushort *u, ushort *xb, ushort *xe, ushort *yb, ushort *ye, ushort *zb, ushort *ze, char *c);
char        yMAP_visu_first         (ushort *u, ushort *x, ushort *y, ushort *z);
char        yMAP_visu_next          (ushort *u, ushort *x, ushort *y, ushort *z);
/*---(status)---------------*/
char        yMAP_root               (ushort u, ushort x, ushort y, ushort z);
char        yMAP_visual             (ushort u, ushort x, ushort y, ushort z);
char        ymap_visu_dump          (FILE *f);
/*---(umode)----------------*/
char        ymap_visu_hmode         (uchar a_major, uchar a_minor);
char        ymap_visu_umode         (uchar a_major, uchar a_minor);
/*---(done)-----------------*/



/*===[[ yMAP_test.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(load)-----------------*/
char        ymap__unit_massive      (void);
char        ymap__unit_load         (uchar a_axis, uchar a_style);
char        ymap__unit_full         (uchar a_axis, uchar a_style);
char*       ymap_print              (uchar a_axis);
char*       ymap_print_grid         (uchar a_axis);
/*---(driver)---------------*/
char        ymap__unit_quiet        (void);
char        ymap__unit_loud         (void);
char        ymap__unit_end          (void);
/*---(mock)-----------------*/
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
/*---(format)---------------*/
char        ymap__unit_format_init  (void);
char        ymap__unit_formatter    (uchar a_type, uchar a_abbr, ushort u, ushort x, ushort y, ushort z, uchar *r);
char*       ymap__unit_formatted    (ushort y);
/*---(mreg)-----------------*/
char        ymap__unit_base         (void);
char        ymap__unit_config       (void);
char*       ymap__unit_orig         (void);
char*       ymap__unit_reqs         (void);
char*       ymap__unit_adds         (void);
char*       ymap__unit_mreg         (void);
/*---(mundo)----------------*/
char        ymap__unit_mundo        (char a_dir, char a, char *l, char *f, char *c);
/*---(accessor)-------------*/
char*       yMAP__unit              (char *a_question, char a_index);
/*---(done)-----------------*/



/*===[[ yMAP_mreg.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(support)--------------*/
char        ymap__mreg_valid        (char a_abbr);
char        ymap__mreg_by_abbr      (char a_abbr);
/*---(memory)---------------*/
char        ymap__mreg_new          (char a_abbr, void *a_item, char *a_label, char *a_reqs, char *a_pros);
char        ymap__mreg_wipe         (char a_abbr, char a_scope);
char        ymap_mreg_wipe_curr     (void);
char        ymap__mreg_set          (char a_abbr);
char        ymap__mreg_reset        (void);
char        ymap_mreg_curr          (void);
/*---(program)--------------*/
char        ymap_mreg_purge         (char a_scope);
char        ymap_mreg_init          (void);
char        yMAP_mreg_config        (void *a_clearer, void *a_copier, void *a_paster, void *a_finisher, void *a_regkill, void *a_exim);
char        ymap_mreg_wrap          (void);
/*---(attach)---------------*/
char        yMAP_mreg_add           (void *a_thing, char *a_label, char *a_reqs, char *a_pros);
char        ymap_mreg_save          (void);
char*       ymap_mreg_list          (char a_abbr);
char*       ymap_mreg_detail        (char a_abbr);
/*---(actions)--------------*/
char        ymap_mreg_clear         (void);
char        ymap_mreg_clear_combo   (void);
char        ymap__mreg_paste        (char *a_type);
char        ymap_mreg_paste         (char *a_type);
char        ymap_mreg_paste_combo   (char *a_type);
char        ymap_mreg_visual        (void);
/*---(mode)-----------------*/
char        yMAP_mreg_hmode         (uchar a_major, uchar a_minor);
char        ymap_mreg_smode         (uchar a_major, uchar a_minor);
/*---(done)-----------------*/



/*===[[ yMAP_mreg.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(memory)---------------*/
char        ymap__mundo_new         (char a_mode, char a_type, char *a_label, tHIST **r_curr);
char        ymap__mundo_free        (tHIST **r_curr);
/*---(program)--------------*/
char        ymap_mundo_init         (void);
char        ymap__mundo_prune       (char a_type);
char        ymap_mundo_wrap         (void);
/*---(search)---------------*/
char        ymap__mundo_by_cursor   (char a_move);
char        ymap__mundo_by_index    (int n);
char*       ymap_mundo_action       (char a_mode, char a_act);
/*---(undo/redo)------------*/
char        ymap__mundo_parse       (char a_act, char *a_field, char *a_format, char *a_content);
char        ymap_mundo_undo         (void);
char        ymap_mundo_redo         (void);
/*---(mode)-----------------*/
char        ymap_mundo_hmode        (uchar a_major, uchar a_minor);
/*---(done)-----------------*/



/*===[[ yMAP_rptg.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ymap_mundo_dump         (FILE *f);
char        ymap_map_dump           (FILE *f);



/*===[[ yMAP_univ.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ymap_univ_init          (void);
char        ymap_univ_current       (void);
char        ymap_univ_umode         (uchar a_major, uchar a_minor);



/*===[[ yMAP_refresh.c ]]=====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(control)--------------*/
char        ymap__change            (char *a_func, char a_axis, char a_level);
char        ymap_uchange            (char a_level);
char        ymap_xchange            (char a_level);
char        ymap_ychange            (char a_level);
char        ymap_zchange            (char a_level);
char        ymap_change             (char a_axis, char a_level);
/*---(realtime)-------------*/
char        ymap_used               (ushort x, ushort y, ushort z);
char        ymap_empty              (ushort x, ushort y, ushort z);
char        ymap_wide               (ushort a_pos, uchar a_wide);
char        ymap_tall               (ushort a_pos, uchar a_tall);
char        ymap_deep               (ushort a_pos, uchar a_deep);
/*---(done)-----------------*/



/*===[[ yMAP_format.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ymap__format_abbr       (char a_abbr);
char        ymap__format_units      (char a_abbr);
char        ymap__multisize         (char *a_label, uchar a_type, uchar a_size, uchar a_count);
char        ymap_multi_wide_def     (char *a_label, uchar a_count);
char        ymap_multi_wide_reset   (char *a_label);
char        ymap_multi_tall_def     (char *a_label, uchar a_count);
char        ymap_multi_tall_reset   (char *a_label);
char        ymap_multi_deep_def     (char *a_label, uchar a_count);
char        ymap_multi_deep_reset   (char *a_label);
char        ymap_format_prepper     (void);
char        ymap_format_xmode       (uchar a_major, uchar a_minor);
char        ymap_units_xmode        (uchar a_major, uchar a_minor);


#endif
