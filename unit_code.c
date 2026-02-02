/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"
#include    "unit_code.h"



char       /*----: set up program urgents/debugging --------------------------*/
ymap__unit_quiet         (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yMAP_unit" };
   yMODE_init (MODE_MAP);
   yMODE_init_after ();
   yKEYS_unit_handlers ();
   yKEYS_init  ();
   yKEYS_init_after ();
   yMAP_init ();
   yMAP_init_after ();
   yMAP_config (YMAP_OFFICE, ymap__unit_locator, ymap__unit_addresser, ymap__unit_sizer, ymap__unit_entry, ymap__unit_placer, ymap__unit_done);
   ymap__unit_init ();
   ymap__unit_format_init ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ymap__unit_loud          (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yMAP_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("ystr"         , YURG_ON);
   yURG_by_name  ("yvihub"       , YURG_ON);
   yURG_by_name  ("ymode"        , YURG_ON);
   yURG_by_name  ("ykeys"        , YURG_ON);
   yURG_by_name  ("ymap"         , YURG_ON);
   yURG_by_name  ("regs"         , YURG_ON);
   yURG_by_name  ("hist"         , YURG_ON);
   DEBUG_YMAP  yLOG_info     ("yMAP"     , yMAP_version   ());
   yMODE_init (MODE_MAP);
   yMODE_init_after ();
   yKEYS_unit_handlers ();
   yKEYS_init  ();
   yKEYS_init_after ();
   yMAP_init ();
   yMAP_init_after ();
   yMAP_config (YMAP_OFFICE, ymap__unit_locator, ymap__unit_addresser, ymap__unit_sizer, ymap__unit_entry, ymap__unit_placer, ymap__unit_done);
   ymap__unit_init ();
   ymap__unit_format_init ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ymap__unit_end           (void)
{
   DEBUG_YMAP  yLOG_enter   (__FUNCTION__);
   yMAP_wrap   ();
   DEBUG_YMAP  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}



typedef  struct cMOCK  tMOCK;
static struct cMOCK {
   char        s;
   ushort      n, a, b, c, e;
} myu, myx, myy, myz, myw;



/*====================------------------------------------====================*/
/*===----                     sample data loads                        ----===*/
/*====================------------------------------------====================*/
static void  o___LOAD____________o () { return; }

/*
 *   f   flexible, gyges-like
 *   F   ... quad of f for wider testind
 *   +   ... f without unit limits
 *   u   uniform 8
 *   a   ascending 8
 *   d   decending 8
 *   s   small 8
 *   -   negative to positive
 *   w   wide with 30 grids
 *
 */

#define  MAX_UNITS          5
struct {
   uchar       style;
   uchar       uavail;
   uchar       ubeg;
   uchar       uend;
   uchar       utend;
} static s_units [MAX_UNITS] = {
   { 'w',  38,  44,  79,  81 },
   { 'f',  38,   0,  31,  37 },
   { 'F',  38,   0,  31,  37 },
   { 'r',  15,  10,  24,  24 },
   {  0 ,   0,   0,   0,   0 },
};

#define       MAX_LOADS      200
struct {
   uchar       style;
   short       ref;
   uchar       wide;
   uchar       used;
   uchar       twide;
   uchar       tused;
} static s_loads [MAX_LOADS] = {
   /*---(flex)---------------------------*/
   {  'f',    1,  16, 'Ï' },
   {  'f',    2,   7, 'Ï' },
   {  'f',    3,   7, 'Ï' },
   {  'f',    4,   2, '·' },
   {  'f',    5,  20, 'Ï' },
   {  'f',    6,   6, 'Ï' },
   {  'f',    7,   6, '·' },
   {  'f',    8,   2, '·' },
   /*---(flex+)--------------------------*/
   {  '+',    1,  16, 'Ï' },
   {  '+',    2,   7, 'Ï' },
   {  '+',    3,   7, 'Ï' },
   {  '+',    4,   2, '·' },
   {  '+',    5,  20, 'Ï' },
   {  '+',    6,   6, 'Ï' },
   {  '+',    7,   6, '·' },
   {  '+',    8,   2, '·' },
   /*---(FLEX)---------------------------*/
   {  'F',    1,  16, 'Ï' },
   {  'F',    2,   7, 'Ï' },
   {  'F',    3,   7, 'Ï' },
   {  'F',    4,   2, '·' },
   {  'F',    5,  20, 'Ï' },
   {  'F',    6,   6, 'Ï' },
   {  'F',    7,   6, '·' },
   {  'F',    8,   2, '·' },
   {  'F',    9,  16, 'Ï' },
   {  'F',   10,   7, 'Ï' },
   {  'F',   11,   7, 'Ï' },
   {  'F',   12,   2, '·' },
   {  'F',   13,  20, 'Ï' },
   {  'F',   14,   6, 'Ï' },
   {  'F',   15,   6, '·' },
   {  'F',   16,   2, '·' },
   {  'F',   17,  16, 'Ï' },
   {  'F',   18,   7, 'Ï' },
   {  'F',   19,   7, 'Ï' },
   {  'F',   20,   2, '·' },
   {  'F',   21,  20, 'Ï' },
   {  'F',   22,   6, 'Ï' },
   {  'F',   23,   6, '·' },
   {  'F',   24,   2, '·' },
   {  'F',   25,  16, 'Ï' },
   {  'F',   26,   7, 'Ï' },
   {  'F',   27,   7, 'Ï' },
   {  'F',   28,   2, '·' },
   {  'F',   29,  20, 'Ï' },
   {  'F',   30,   6, 'Ï' },
   {  'F',   31,   6, '·' },
   {  'F',   32,   2, '·' },
   /*---(uniform)------------------------*/
   {  'u',    0,   8, 'Ï' },
   {  'u',    1,   8, 'Ï' },
   {  'u',    2,   8, 'Ï' },
   {  'u',    3,   8, 'Ï' },
   {  'u',    4,   8, 'Ï' },
   {  'u',    5,   8, '·' },
   {  'u',    6,   8, '·' },
   {  'u',    7,   8, '·' },
   /*---(acsending)----------------------*/
   {  'a',    0,   1, 'Ï' },
   {  'a',    1,   2, '·' },
   {  'a',    2,   3, '·' },
   {  'a',    3,   4, '·' },
   {  'a',    4,   5, '·' },
   {  'a',    5,   6, '·' },
   {  'a',    6,   7, '·' },
   {  'a',    7,   8, 'Ï' },
   /*---(desending)----------------------*/
   {  'd',    0,   8, '·' },
   {  'd',    1,   7, '·' },
   {  'd',    2,   6, '·' },
   {  'd',    3,   5, 'Ï' },
   {  'd',    4,   4, 'Ï' },
   {  'd',    5,   3, '·' },
   {  'd',    6,   2, '·' },
   {  'd',    7,   1, '·' },
   /*---(desending)----------------------*/
   {  's',    0,   3, 'Ï' },
   {  's',    1,   3, 'Ï' },
   {  's',    2,   3, '·' },
   {  's',    3,   3, 'Ï' },
   {  's',    4,   3, 'Ï' },
   {  's',    5,   3, '·' },
   {  's',    6,   3, 'Ï' },
   {  's',    7,   3, 'Ï' },
   /*---(neg/pos)------------------------*/
   {  '-',   -3,   8, '·' },
   {  '-',   -2,   8, '·' },
   {  '-',   -1,   8, '·' },
   {  '-',    0,   8, '·' },
   {  '-',    1,   8, '·' },
   {  '-',    2,   8, '·' },
   {  '-',    3,   8, '·' },
   /*---(rows)---------------------------*/
   {  'r',    1,   1, '·' },
   {  'r',    2,   1, 'Ï' },
   {  'r',    3,   1, '·' },
   {  'r',    4,   1, 'Ï' },
   {  'r',    5,   1, 'Ï' },
   {  'r',    6,   1, 'Ï' },
   {  'r',    7,   1, 'Ï' },
   {  'r',    8,   1, 'Ï' },
   {  'r',    9,   1, 'Ï' },
   {  'r',   10,   1, 'Ï' },
   {  'r',   11,   1, 'Ï' },
   {  'r',   12,   1, 'Ï' },
   {  'r',   13,   1, 'Ï' },
   {  'r',   14,   1, 'Ï' },
   {  'r',   15,   1, 'Ï' },
   {  'r',   16,   1, 'Ï' },
   {  'r',   17,   1, 'Ï' },
   {  'r',   18,   1, 'Ï' },
   {  'r',   19,   1, '·' },
   {  'r',   20,   1, '·' },
   {  'r',   21,   1, '·' },
   {  'r',   22,   1, '·' },
   {  'r',   23,   1, '·' },
   {  'r',   24,   1, 'Ï' },
   {  'r',   25,   1, 'Ï' },
   {  'r',   26,   1, 'Ï' },
   {  'r',   27,   1, '·' },
   {  'r',   28,   1, '·' },
   {  'r',   29,   1, '·' },
   {  'r',   30,   1, '·' },
   {  'r',   31,   1, '·' },
   {  'r',   32,   1, '·' },
   {  'r',   33,   1, '·' },
   {  'r',   34,   1, 'Ï' },
   {  'r',   35,   1, 'Ï' },
   {  'r',   36,   1, 'Ï' },
   {  'r',   37,   1, '·' },
   {  'r',   38,   1, '·' },
   {  'r',   39,   1, '·' },
   {  'r',   40,   1, '·' },
   /*---(wide)---------------------------*/
   {  'w',    0,   4, '·' },
   {  'w',    1,   4, '·' },
   {  'w',    2,   4, 'Ï' },
   {  'w',    3,   4, '·' },
   {  'w',    4,   4, '·' },
   {  'w',    5,   4, '·' },
   {  'w',    6,   4, 'Ï' },
   {  'w',    7,   4, 'Ï' },
   {  'w',    8,   4, 'Ï' },
   {  'w',    9,   4, 'Ï' },
   {  'w',   10,   4, 'Ï' },
   {  'w',   11,   4, '·' },
   {  'w',   12,   4, 'Ï' },
   {  'w',   13,   4, 'Ï' },
   {  'w',   14,   4, '·' },
   {  'w',   15,   4, '·' },
   {  'w',   16,   4, '·' },
   {  'w',   17,   4, '·' },
   {  'w',   18,   4, '·' },
   {  'w',   19,   4, '·' },
   {  'w',   20,   4, 'Ï' },
   {  'w',   21,   4, '·' },
   {  'w',   22,   4, '·' },
   {  'w',   23,   4, 'Ï' },
   {  'w',   24,   4, 'Ï' },
   {  'w',   25,   4, 'Ï' },
   {  'w',   26,   4, '·' },
   {  'w',   27,   4, '·' },
   {  'w',   28,   4, '·' },
   {  'w',   29,   4, 'Ï' },
   /*---(wide)---------------------------*/
   {  '1',    0,   1, 'Ï' },
   /*---(done)---------------------------*/
   {   0 ,    0,   0,  0  },
};

char
ymap__unit_massive      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   int         c           =    0;
   tGRID      *x_grid      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(univers)------------------------*/
   DEBUG_YMAP   yLOG_note    ("universe");
   c = 40;
   rc = yMAP_size (YMAP_UNIV, c);
   rc = ymap_pick_map (YMAP_UNIV, NULL, &x_grid);
   DEBUG_YMAP   yLOG_note    ("load data");
   for (i = 0; i < c; ++i) {
      DEBUG_YMAP   yLOG_value   ("grid"     , i);
      x_grid [i].g_ref  = i;
      x_grid [i].g_wide = 1;
      x_grid [i].g_used = '·';
   }
   rc = ymap_update_large (YMAP_UNIV);
   rc = ymap_update_small (YMAP_UNIV);
   /*---(x/col)--------------------------*/
   DEBUG_YMAP   yLOG_note    ("xaxis");
   c = 500;
   rc = yMAP_size (YMAP_XAXIS, c);
   rc = ymap_pick_map (YMAP_XAXIS, NULL, &x_grid);
   DEBUG_YMAP   yLOG_note    ("load data");
   for (i = 0; i < c; ++i) {
      x_grid [i].g_ref  = i;
      x_grid [i].g_wide = 1;
      x_grid [i].g_used = '·';
   }
   rc = ymap_update_large (YMAP_XAXIS);
   rc = ymap_update_small (YMAP_XAXIS);
   /*---(y/row)--------------------------*/
   DEBUG_YMAP   yLOG_note    ("yaxis");
   c = 500;
   rc = yMAP_size (YMAP_YAXIS, c);
   rc = ymap_pick_map (YMAP_YAXIS, NULL, &x_grid);
   DEBUG_YMAP   yLOG_note    ("load data");
   for (i = 0; i < c; ++i) {
      x_grid [i].g_ref  = i;
      x_grid [i].g_wide = 1;
      x_grid [i].g_used = '·';
   }
   rc = ymap_update_large (YMAP_YAXIS);
   rc = ymap_update_small (YMAP_YAXIS);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__unit_load         (uchar a_axis, uchar a_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         k           =    0;
   int         n           =    0;
   int         m           =    0;
   int         w           =    0;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   int         x_loop      =    1;
   uchar       x_style     =  '-';
   tMOCK      *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(size)---------------------------*/
   rc = yMAP_size (a_axis, 200);
   DEBUG_YMAP   yLOG_value   ("size"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   DEBUG_YMAP   yLOG_value   ("pickmap"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_grid"    , x_grid);
   DEBUG_YMAP   yLOG_complex ("assign"    , "%c, b%-10p, x%-10p, y%-10p, z%-10p, t%-10p", a_axis, g_ugrid, g_xgrid, g_ygrid, g_zgrid, g_wgrid);
   --rce;  if (a_style == 0 || strchr ("fF+uadsr-w1", a_style) == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(show)---------------------------*/
   DEBUG_YMAP    yLOG_value   ("glen"      , x_map->glen);
   for (i = 0; i < x_map->glen; ++i) {
      DEBUG_YMAP   yLOG_complex ("auditing"  , "%3d, %6d, %2d, %c", i, x_grid [i].g_ref, x_grid [i].g_wide, x_grid [i].g_used);
   }
   /*---(load)---------------------------*/
   DEBUG_YMAP   yLOG_note    ("check loads");
   x_style = a_style;
   for (i = 0; i < MAX_LOADS; ++i) {
      if (s_loads [i].style == 0)        break;
      DEBUG_YMAP   yLOG_complex ("checking"  , "%2d, %2d, %c, %2d, %2d, %c", i, n, s_loads [i].style, s_loads [i].ref, s_loads [i].wide, s_loads [i].used);
      if (n >= x_map->glen)              break;
      if (s_loads [i].style != x_style)   continue;
      x_grid [n].g_ref  = s_loads [i].ref;
      x_grid [n].g_wide = s_loads [i].twide = s_loads [i].wide;
      x_grid [n].g_used = s_loads [i].tused = s_loads [i].used;
      DEBUG_YMAP   yLOG_note    ("YES");
      w += x_grid [n].g_wide;
      ++n;
   }
   ymap__load_limits (x_map, 2000, 2000);
   /*> printf ("ymap...full     load %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(show)---------------------------*/
   DEBUG_YMAP    yLOG_value   ("glen"      , x_map->glen);
   for (i = 0; i < x_map->glen; ++i) {
      DEBUG_YMAP   yLOG_complex ("auditing"  , "%3d, %6d, %2d, %c", i, x_grid [i].g_ref, x_grid [i].g_wide, x_grid [i].g_used);
   }
   /*---(unit min/max)-------------------*/
   x_map->umin   = 0;
   x_map->ubeg   = x_map->ucur   =  0;
   if (w > 0)  x_map->umax   = x_map->uend   = x_map->utend  = w - 1;
   else        x_map->umax   = x_map->uend   = x_map->utend  = 0;
   x_map->uavail = w;
   /*---(find defaults)------------------*/
   DEBUG_YMAP   yLOG_note    ("check units");
   x_style = a_style;
   for (i = 0; i < MAX_UNITS; ++i) {
      if (s_units [i].style == 0)        break;
      DEBUG_YMAP   yLOG_complex ("checking"  , "%2d, %c, %2d, %2d, %2d, %2d", i, s_units [i].style, s_units [i].ubeg, s_units [i].uend, s_units [i].utend, s_units [i].uavail);
      if (s_units [i].style != x_style)  continue;
      x_map->ubeg   = s_units [i].ubeg;
      x_map->ucur   = s_units [i].ubeg;
      x_map->uend   = s_units [i].uend;
      x_map->utend  = s_units [i].utend;
      x_map->uavail = s_units [i].uavail;
      DEBUG_YMAP   yLOG_note    ("FOUND");
      break;
   }
   x_map->ulen  = x_map->uend - x_map->ubeg + 1;
   DEBUG_YMAP   yLOG_value   ("ulen"      , x_map->ulen);
   /*> printf ("ymap...full     defs %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(unit test mock)-----------------*/
   switch (a_axis) {
   case 'u'  :  p = &myu;  break;
   case 'x'  :  p = &myx;  break;
   case 'y'  :  p = &myy;  break;
   case 'z'  :  p = &myz;  break;
   case 'w'  :  p = &myw;  break;
   }
   p->s  = a_style;
   p->a  = x_map->uavail;
   p->n  = x_map->gmax + 1;
   p->b  = x_map->gbeg;
   p->c  = x_map->gcur;
   p->e  = x_map->gend;
   DEBUG_YMAP   yLOG_complex ("LOADED"    , "%c, %3dn, %3da, %3db, %3dc, %3de", p->s, p->n, p->a, p->b, p->c, p->e);
   rc = 0;
   if (rc >= 0)  rc = ymap_update_large (a_axis);
   /*> printf ("ymap_update_large    %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   if (rc >= 0)  rc = ymap_update_small (a_axis);
   /*> printf ("ymap_update_small    %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   if (rc >= 0)  ymap_visu_update ();
   /*> printf ("ymap_visu_update     %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__unit_full         (uchar a_axis, uchar a_style)
{
   char        rc          =    0;
   tMOCK      *p           = NULL;
   tyMAP      *m           = NULL;
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   rc = ymap__unit_load (a_axis, a_style);
   /*> if (rc >= 0)  rc = ymap_update_large (a_axis);                                 <* 
    *> if (rc >= 0)  rc = ymap_update_small (a_axis);                                 <* 
    *> if (rc >= 0)  ymap_visu_update ();                                             <*/
   /*> switch (a_axis) {                                                              <* 
    *> case 'u'  :  p = &myu;  m = &g_umap;  break;                                   <* 
    *> case 'x'  :  p = &myx;  m = &g_xmap;  break;                                   <* 
    *> case 'y'  :  p = &myy;  m = &g_ymap;  break;                                   <* 
    *> case 'z'  :  p = &myz;  m = &g_zmap;  break;                                   <* 
    *> }                                                                              <* 
    *> p->s  = a_style;                                                               <* 
    *> p->a  = m->uavail;                                                             <* 
    *> p->n  = m->gmax + 1;                                                           <* 
    *> p->b  = m->gbeg;                                                               <* 
    *> p->c  = m->gcur;                                                               <* 
    *> p->e  = m->gend;                                                               <*/
   /*> DEBUG_YMAP   yLOG_complex ("LOADED"    , "%c, %3dn, %3da, %3db, %3dc, %3de", p->s, p->n, p->a, p->b, p->c, p->e);   <*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}

char*
ymap_print              (uchar a_axis)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char        x_spot      =    0;
   char        n           =    0;
   uchar       c           =    0;
   uchar       s           =    0;
   char        t           [LEN_TERSE] = "";
   tyMAP      *x_map       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   /*---(defense)------------------------*/
   rc = ymap_pick_map (a_axis, &x_map, NULL);
   DEBUG_YMAP   yLOG_point   ("x_map"     , x_map);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return "n/a";
   }
   --rce;  if (x_map->map == NULL) {
      sprintf (g_print, "%c åæ", x_map->axis);
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return g_print;
   }
   DEBUG_YMAP   yLOG_point   ("grid"      , x_map->grid);
   --rce;  if (x_map->grid == NULL) {
      sprintf (g_print, "%c åæ", x_map->axis);
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return g_print;
   }
   /*---(content)------------------------*/
   DEBUG_YMAP   yLOG_value   ("mlen"      , x_map->mlen);
   sprintf (g_print, "%c å", x_map->axis);
   s = x_map->map [0];
   for (i = 0; i <= x_map->mlen; ++i) {
      c = x_map->map [i];
      DEBUG_YMAP   yLOG_complex ("check"     , "%2di, s=%3d, c=%3d, %2dn, x_spot=%2d", i, s, c, n, x_spot);
      if (c != s || i == x_map->mlen) {
         if (n > 0) {
            sprintf (t, "%2d%c%-2d ", s, x_map->grid [s].g_used, n);
            ystrlcat (g_print, t, LEN_RECD);
            ++x_spot;
         }
         s = c;
         n = 1;
      } else ++n;
   }
   strcat (g_print, "æ");
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return g_print;
}

char*
ymap_print_grid         (uchar a_axis)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   char        t           [LEN_TERSE] = "";
   char        s           [LEN_TERSE] = "";
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   /*---(defense)------------------------*/
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   if (rc < 0)  return "n/a";
   /*---(content)------------------------*/
   sprintf (g_print, "%c å", x_map->axis);
   for (i = 0; i < x_map->glen; ++i) {
      if (x_grid [i].g_ref == YMAP_EMPTY)  break;
      sprintf (t, "%2d%c%-2d", x_grid [i].g_ref, x_grid [i].g_used, x_grid [i].g_wide);
      sprintf (s, "%s "  , t);
      strcat (g_print, s);
   }
   strcat (g_print, "æ");
   /*---(end)----------------------------*/
   return g_print;
}



/*====================------------------------------------====================*/
/*===----                   display testing support                    ----===*/
/*====================------------------------------------====================*/
static void  o___DISPLAY_________o () { return; }

char
ymap_display_show       (tyMAP *a_map, char *a_disp)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         n           =    0;
   int         c           =    0;
   int         x_beg       =    0;
   int         x_cur       =    0;
   char        s           [LEN_TERSE] = "";
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   if (a_disp == NULL)            return -1;
   strcpy (a_disp , "");
   if (a_map  == NULL)            return -2;
   if (a_map->map  == NULL)       return -3;
   /*---(main display)-------------------*/
   x_beg  = a_map->ubeg;
   x_cur  = a_map->map [a_map->ubeg];
   for (i = x_beg; i <= a_map->uend; ++i) {
      if (x_cur != a_map->map [i]) {
         ystrlpad ("+", t, '.', '>', c);
         ystrlcat (a_disp, t, LEN_RECD);
         ++n;
         c = 0;
      } else if (i == a_map->uend) {
         ++c;
         ystrlpad ("|", t, '.', '>', c);
         ystrlcat (a_disp, t, LEN_RECD);
      }
      x_cur = a_map->map [i];
      ++c;
   }
   /*---(extra at end)-------------------*/
   c     = a_map->utend - a_map->uend;
   if (c > 0) {
      ystrlpad ("", t, '-', '<', c);
      ystrlcat (a_disp, t, LEN_RECD);
   }
   /*---(left-over avail)----------------*/
   c     = (a_map->ubeg + a_map->uavail - 1) - a_map->utend;
   if (c > 0) {
      ystrlcpy (t, "///////////////////////////////////////", c + 1);
      ystrlcat (a_disp, t, LEN_RECD);
   }
   /*---(current position)---------------*/
   if (a_map->ucur >= a_map->ubeg && a_map->ucur <= a_map->utend) {
      a_disp [a_map->ucur - a_map->ubeg] = 'Ï';
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_display_map        (tyMAP *a_map, char *a_disp)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         n           =    0;
   int         c           =    0;
   ushort      x_cur       =    0;
   char        s           [LEN_TERSE] = "";
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   if (a_disp == NULL)            return -1;
   strcpy (a_disp , "");
   if (a_map  == NULL)            return -2;
   if (a_map->map  == NULL)       return -3;
   /*---(main display)-------------------*/
   x_cur  = a_map->map [a_map->ubeg];
   for (i = 0; i <= a_map->mlen; ++i) {
      if (x_cur != a_map->map [i] || i == a_map->mlen) {
         ystrlpad ("+", t, '.', '>', c);
         ystrlcat (a_disp, t, LEN_RECD);
         ++n;
         c = 0;
      }
      x_cur = a_map->map [i];
      ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_display_units      (tyMAP *a_map, char *a_disp)
{
   char        rc          =    0;
   int         i           =    0;
   int         l           =    0;
   rc = ymap_display_map  (a_map, a_disp);
   if (rc < 0)  return rc;
   l = strlen (YSTR_LOWUP);
   for (i = 0; i < a_map->glen; ++i) {
      if (a_map->grid [i].g_ref == YMAP_EMPTY)  break;
      a_disp [a_map->grid [i].g_unit] = YSTR_LOWUP [i % l];
   }
   return 0;
}




/*====================------------------------------------====================*/
/*===----                          drivers                             ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVERS_________o () { return; }


char
yMAP__unit_wander       (void)
{
   DEBUG_YMAP  yLOG_enter   (__FUNCTION__);
   yMAP_init ();
   yMAP_config (YMAP_OFFICE, ymap__unit_locator, ymap__unit_addresser, ymap__unit_sizer, ymap__unit_entry, ymap__unit_placer, ymap__unit_done);
   ymap__unit_init ();
   ymap__unit_format_init ();
   ymap__unit_massive ();
   DEBUG_YMAP  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         mock testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___MOCK____________o () { return; }

tMOCK*
ymap__unit_choose       (char a_axis)
{
   switch (a_axis) {
   case 'u' : return &myu;  break;
   case 'x' : return &myx;  break;
   case 'y' : return &myy;  break;
   case 'z' : return &myz;  break;
   case 'w' : return &myw;  break;
   }
   return NULL;
}

char
ymap__unit__one         (char a_axis)
{
   tMOCK      *p           = NULL;
   p = ymap__unit_choose (a_axis);
   if (p == NULL)  return -10;
   p->s  = '-';
   p->n  = p->b  = p->c  = p->e  = 0;
   return 0;
}

char
ymap__unit_init         (void)
{
   ymap__unit__one ('u');
   ymap__unit__one ('x');
   ymap__unit__one ('y');
   ymap__unit__one ('z');
   ymap__unit__one ('w');
   ymap__unit_presizer     (1000, 1000);
   return 0;
}

char
ymap__unit_map_general  (void)
{
   /*> printf ("ymap...general  beg  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   ymap__unit_full (YMAP_UNIV , 's');
   /*> printf ("   universe     aft  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   ymap__unit_full (YMAP_XAXIS, 'F');
   /*> printf ("   x-axis       aft  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   ymap__unit_full (YMAP_YAXIS, 'r');
   /*> printf ("   y-axis       aft  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   ymap__unit_full (YMAP_ZAXIS, '1');
   /*> printf ("   z-axis       aft  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*> printf ("ymap...general  end  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   return 0;
}

char
ymap__unit_map_bigger   (void)
{
   ymap__unit_full (YMAP_UNIV , 's');
   ymap__unit_full (YMAP_XAXIS, 'r');
   ymap__unit_full (YMAP_YAXIS, 'r');
   ymap__unit_full (YMAP_ZAXIS, '1');
   return 0;
}

char
ymap__unit_map_block    (void)
{
   ymap__unit_full (YMAP_UNIV , 'u');
   ymap__unit_full (YMAP_XAXIS, 'u');
   ymap__unit_full (YMAP_YAXIS, 'u');
   ymap__unit_full (YMAP_ZAXIS, 'u');
   return 0;
}

static ushort  s_amin = 0;
static ushort  s_amax = 0;

char
ymap__unit_presizer     (ushort a_min, ushort a_max)
{
   s_amin = a_min;
   s_amax = a_max;
   return 0;
}

char
ymap__unit_sizer        (char a_axis, ushort *n, ushort *a, ushort *b, ushort *c, ushort *e, ushort *m, ushort *x)
{
   char        rce         =  -10;
   tMOCK      *p           = NULL;
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   p = ymap__unit_choose (a_axis);
   DEBUG_YMAP   yLOG_spoint  (p);
   --rce;  if (p == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (n != NULL)  *n = p->n;
   if (a != NULL)  *a = p->a;
   if (b != NULL)  *b = p->b;
   if (c != NULL)  *c = p->c;
   if (e != NULL)  *e = p->e;
   if (m != NULL)  *m = s_amin;
   if (x != NULL)  *x = s_amax;
   DEBUG_YMAP   yLOG_schar   (p->s);
   DEBUG_YMAP   yLOG_sint    (p->n);
   DEBUG_YMAP   yLOG_sint    (p->b);
   DEBUG_YMAP   yLOG_sint    (p->c);
   DEBUG_YMAP   yLOG_sint    (p->e);
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap__unit_entry        (char a_axis, ushort a_pos, short *r_ref, uchar *r_wide, uchar *r_used)
{
   char        rce         =  -10;
   tMOCK      *p           = NULL;
   int         i           =    0;
   int         c           =    0;
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   p = ymap__unit_choose (a_axis);
   DEBUG_YMAP   yLOG_spoint  (p);
   --rce;  if (p == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   for (i = 0; i < MAX_LOADS; ++i) {
      if (s_loads [i].style == 0)        break;
      if (s_loads [i].style != p->s)  continue;
      if (c != a_pos) { ++c; continue; }
      DEBUG_YMAP   yLOG_sint    (i);
      DEBUG_YMAP   yLOG_sint    (s_loads [i].ref);
      DEBUG_YMAP   yLOG_sint    (s_loads [i].wide);
      DEBUG_YMAP   yLOG_sint    (s_loads [i].twide);
      DEBUG_YMAP   yLOG_schar   (s_loads [i].used);
      DEBUG_YMAP   yLOG_schar   (s_loads [i].tused);
      DEBUG_YMAP   yLOG_snote   ("found");
      if (r_ref  != NULL)  *r_ref  = s_loads [i].ref;
      if (r_wide != NULL)  *r_wide = s_loads [i].twide;
      if (r_used != NULL)  *r_used = s_loads [i].tused;
      DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char
ymap__unit_placer       (char a_axis, ushort b, ushort c, ushort e)
{
   char        rce         =  -10;
   tMOCK      *p           = NULL;
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   p = ymap__unit_choose (a_axis);
   DEBUG_YMAP   yLOG_spoint  (p);
   --rce;  if (p == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   p->b  = b;
   p->c  = c;
   p->e  = e;
   DEBUG_YMAP   yLOG_sint    (p->b);
   DEBUG_YMAP   yLOG_sint    (p->c);
   DEBUG_YMAP   yLOG_sint    (p->e);
   return 0;
}

char
ymap__unit_done         (void)
{
   return 0;
}

char
ymap__unit_locator      (char a_strict, char *a_label, ushort *u, ushort *x, ushort *y, ushort *z)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         u_pos, x_pos, y_pos, z_pos;
   /*---(default)------------------------*/
   if (u != NULL)  *u = 0;
   if (x != NULL)  *x = 0;
   if (y != NULL)  *y = 0;
   if (z != NULL)  *z = 0;
   /*---(parse label)--------------------*/
   rc = ystr2gyges (a_label, &u_pos, &x_pos, &y_pos, &z_pos, NULL, 0, YSTR_CHECK);
   --rce;  if (rc < 0) {
      if (a_label == NULL)                            return rce;
      if (strlen (a_label) != 2)                      return rce;
      u_pos = 0;
      x_pos = a_label [0];
      y_pos = a_label [1];
      z_pos = 0;
      if (strchr ("01234567", a_label [0]) == NULL)   return rce;
      if (strchr ("01234567", a_label [1]) == NULL)   return rce;
   }
   /*---(strict)-------------------------*/
   if (a_strict == 'y') {
      --rce;  if (u_pos > g_umap.gmax)  return rce;
      --rce;  if (x_pos > g_xmap.gmax)  return rce;
      --rce;  if (y_pos > g_ymap.gmax)  return rce;
      --rce;  if (z_pos > g_zmap.gmax)  return rce;
   }
   /*---(save-back)----------------------*/
   if (u != NULL)  *u = u_pos;
   if (x != NULL)  *x = x_pos;
   if (y != NULL)  *y = y_pos;
   if (z != NULL)  *z = z_pos;
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap__unit_addresser    (char a_strict, char *a_label, ushort u, ushort x, ushort y, ushort z)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_label     [LEN_LABEL] = "";
   /*---(default)------------------------*/
   if (a_label != NULL)  ystrlcpy (a_label, "", LEN_LABEL);
   /*---(strict)-------------------------*/
   if (a_strict == 'y') {
      --rce;  if (u > g_umap.gmax)  return rce;
      --rce;  if (x > g_xmap.gmax)  return rce;
      --rce;  if (y > g_ymap.gmax)  return rce;
      --rce;  if (z > g_zmap.gmax)  return rce;
   }
   /*---(get label)----------------------*/
   rc = ystr4gyges (u, x, y, 0, 0, x_label, YSTR_CHECK);
   --rce;  if (rc < 0)           return rce;
   /*---(save-back)----------------------*/
   if (a_label != NULL)  ystrlcpy (a_label, x_label, LEN_LABEL);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          formatter                           ----===*/
/*====================------------------------------------====================*/
static void  o___FORMAT__________o () { return; }

static struct {
   char        width;
   char        height;
   char        align;
   char        format;
   char        decs;
   char        units;
} s_grid [8][8];

char
ymap__unit_format_init  (void)
{
   int         x, y;
   for (y = 0; y < 8; ++y) {
      for (x = 0; x < 8; ++x) {
         s_grid [x][y].width  = 8;
         s_grid [x][y].height = 1;
         s_grid [x][y].align  = '?';
         s_grid [x][y].format = '?';
         s_grid [x][y].decs   = '0';
         s_grid [x][y].units  = '-';
      }
   }
   return 0;
}

char
ymap__unit_formatter    (uchar a_type, uchar a_abbr, ushort u, ushort x, ushort y, ushort z, uchar *r)
{
   char        x_prev      =    0;
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   DEBUG_YMAP   yLOG_schar   (a_type);
   DEBUG_YMAP   yLOG_schar   (a_abbr);
   DEBUG_YMAP   yLOG_spoint  (r);
   DEBUG_YMAP   yLOG_sint    (u);
   if (u != 0)  u = 0;
   DEBUG_YMAP   yLOG_sint    (x);
   if (x <  0)  x = 0;
   if (x >  5)  x = 5;
   DEBUG_YMAP   yLOG_sint    (y);
   if (y <  0)  y = 0;
   if (y >  5)  y = 5;
   if (r != NULL)  *r = 0;
   switch (a_type) {
   case YMAP_WIDTH    :
   case YMAP_WEXACT   :
      DEBUG_YMAP   yLOG_snote   ("width");
      x_prev = s_grid [x][y].width;
      switch (a_abbr) {
      case 'm'  :  a_abbr =  4;           break;
      case 'h'  :  a_abbr =  x_prev - 1;  break;
      case 'l'  :  a_abbr =  x_prev + 1;  break;
      case 'n'  :  a_abbr =  8;           break;
      default   :  break;
      }
      s_grid [x][y].width  = a_abbr;
      if (r != NULL) *r = a_abbr;
      DEBUG_YMAP   yLOG_sint    (x_prev);
      DEBUG_YMAP   yLOG_sint    (a_abbr);
      break;
   case YMAP_HEIGHT   :
   case YMAP_HEXACT   :
      DEBUG_YMAP   yLOG_snote   ("height");
      x_prev = s_grid [x][y].height;
      switch (a_abbr) {
      case 'J'  :  a_abbr =  1;           break;
      case 'j'  :  a_abbr =  x_prev - 1;  break;
      case 'k'  :  a_abbr =  x_prev + 1;  break;
      case 'K'  :  a_abbr =  4;           break;
      default   :  break;
      }
      s_grid [x][y].height = a_abbr;
      if (r != NULL) *r = a_abbr;
      DEBUG_YMAP   yLOG_sint    (x_prev);
      DEBUG_YMAP   yLOG_sint    (a_abbr);
      break;
   case YMAP_ALIGN    :
      DEBUG_YMAP   yLOG_snote   ("align");
      x_prev = s_grid [x][y].align;
      s_grid [x][y].align  = a_abbr;
      DEBUG_YMAP   yLOG_schar   (x_prev);
      break;
   case YMAP_FORMAT   :
      DEBUG_YMAP   yLOG_snote   ("format");
      x_prev = s_grid [x][y].format;
      s_grid [x][y].format = a_abbr;
      DEBUG_YMAP   yLOG_schar   (x_prev);
      break;
   case YMAP_DECIMALS :
      DEBUG_YMAP   yLOG_snote   ("decimals");
      x_prev = s_grid [x][y].decs;
      s_grid [x][y].decs   = a_abbr;
      DEBUG_YMAP   yLOG_schar   (x_prev);
      break;
   case YMAP_UNITS    :
      DEBUG_YMAP   yLOG_snote   ("units");
      x_prev = s_grid [x][y].units;
      s_grid [x][y].units  = a_abbr;
      DEBUG_YMAP   yLOG_schar   (x_prev);
      break;
   }
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return x_prev;
}

char*
ymap__unit_formatted    (ushort y)
{
   char        x           =    0;
   char        t           [LEN_LABEL] = "";
   if (y < 0 || y > 4)  return "n/a";
   sprintf (myMAP.g_print, "%dy", y);
   for (x = 0; x < 5; ++x) {
      sprintf (t, "    %dx %c%c·%c%c%c%c", x,
            s_grid [x][y].width + '0', s_grid [x][y].height + '0',
            s_grid [x][y].align, s_grid [x][y].format, 
            s_grid [x][y].decs, s_grid [x][y].units);
      ystrlcat (myMAP.g_print, t, LEN_RECD);
   }
   return myMAP.g_print;
}


/*====================------------------------------------====================*/
/*===----                        mreg testing                          ----===*/
/*====================------------------------------------====================*/
static void  o___MREG____________o () { return; }

typedef  struct cTHING  tTHING;
struct cTHING {
   int         x, y, z;
   char        l           [LEN_LABEL];
   tTHING     *n;
};
static tTHING  *s_things  [10][10];
static tTHING  *s_head    = NULL;
static tTHING  *s_tail    = NULL;
static int      s_nthing  =    0;
static int      s_nbase   =    0;
static int      s_nfree   =    0;

char
ymap__unit_purge        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   tTHING     *p           = NULL;
   tTHING     *n           = NULL;
   int         x, y;
   /*---(create)-------------------------*/
   p = s_head;
   /*---(wipe)---------------------------*/
   for (i = 0; i < s_nthing; ++i) {
      n = p->n;
      free (p);
      p = n;
   }
   s_nthing = 0;
   s_head   = NULL;
   s_tail   = NULL;
   /*---(clear matrix)-------------------*/
   for (x = 0; x < 10; ++x) {
      for (y = 0; y < 10; ++y) {
         s_things [x][y] = NULL;
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

tTHING*
ymap__unit_create      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tTHING     *p           = NULL;
   /*---(create)-------------------------*/
   p = (tTHING *) malloc (sizeof (tTHING));
   /*---(link)---------------------------*/
   p->n = NULL;
   if (s_head == NULL) {
      s_head   = s_tail   = p;
      s_nthing = 1;
   } else {
      s_tail->n = p;
      s_tail    = p;
      ++s_nthing;
   }
   /*---(complete)-----------------------*/
   return p;
}

char
ymap__unit_regkill     (void *a_thing)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   tTHING     *c           = NULL;
   tTHING     *p           = NULL;
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   DEBUG_REGS   yLOG_value   ("s_nthing"  , s_nthing);
   c  = s_head;
   p  = s_head;
   for (i = 0; i < s_nthing; ++i) {
      DEBUG_REGS   yLOG_value   ("pos"       , i);
      DEBUG_REGS   yLOG_info    ("label"     , c->l);
      /*---(not found)-------------------*/
      if (c != a_thing) {
         DEBUG_REGS   yLOG_note    ("wrong one, move to next");
         p = c;
         c = c->n;
         continue;
      }
      /*---(found)-----------------------*/
      if (s_nthing == 1) {
         DEBUG_REGS   yLOG_note    ("only one entry");
         s_head = s_tail = NULL;
      } else if (c == s_head) {
         DEBUG_REGS   yLOG_note    ("change head");
         s_head = c->n;
      } else if (c == s_tail) {
         DEBUG_REGS   yLOG_note    ("change tail");
         s_tail = p;
         p->n  = NULL;
      } else {
         DEBUG_REGS   yLOG_note    ("change middle");
         p->n  = c->n;
      }
      /*---(common)----------------------*/
      free (a_thing);
      --s_nthing;
      break;
   }
   DEBUG_REGS   yLOG_value   ("s_nthing"  , s_nthing);
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

tTHING*
ymap__unit_dup          (tTHING *p)
{
   /*---(locals)-----------+-----+-----+-*/
   tTHING     *q           = NULL;
   char        t           [LEN_LABEL];
   /*---(create)-------------------------*/
   q = ymap__unit_create ();
   /*---(copy contents)------------------*/
   q->x = p->x;
   q->y = p->y;
   q->z = 2;
   sprintf (t, "0%c%d", p->x + 'a', p->y + 1);
   ystrlcpy (q->l, t, LEN_LABEL);
   /*---(complete)-----------------------*/
   return q;
}

char
ymap__unit_hook         (tTHING *p, int x, int y)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_LABEL];
   /*---(check)--------------------------*/
   if (s_things [x][y] != NULL) {
      s_things [x][y] = NULL;
      ymap__unit_regkill (s_things [x][y]);
   }
   /*---(populate)-----------------------*/
   s_things [x][y] = p;
   p->x = x;
   p->y = y;
   p->z = 0;
   sprintf (t, "0%c%d", x + 'a', y + 1);
   ystrlcpy (p->l, t, LEN_LABEL);
   /*---(complete)-----------------------*/
   return 0;
}

char ymap__unit_mark    (tTHING *p) { p->z = 1; return 0; }

char
ymap__unit_base         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tTHING     *p           = NULL;
   /*---(purge)--------------------------*/
   /*> printf ("ymap...base     beg  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   ymap__unit_purge      ();
   /*---(3 secondary)--------------------*/
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 0, 5);
   ymap__unit_mark       (p);
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 3, 6);
   ymap__unit_mark       (p);
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 6, 7);
   ymap__unit_mark       (p);
   /*---(5 primary)----------------------*/
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 2, 0);
   ymap__unit_mark       (p);
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 0, 2);
   ymap__unit_mark       (p);
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 3, 2);
   ymap__unit_mark       (p);
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 6, 2);
   ymap__unit_mark       (p);
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 6, 4);
   ymap__unit_mark       (p);
   /*---(4 inner)------------------------*/
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 2, 1);
   ymap__unit_mark       (p);
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 2, 3);
   ymap__unit_mark       (p);
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 4, 1);
   ymap__unit_mark       (p);
   p = ymap__unit_create ();
   ymap__unit_hook       (p, 4, 3);
   ymap__unit_mark       (p);
   /*---(complete)-----------------------*/
   /*> printf ("ymap...base     end  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   return 0;
}

char*
ymap__unit_orig         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   tTHING     *p           = NULL;
   char        s           [LEN_RECD]  = "";
   char        t           [LEN_LABEL] = "";
   char        c           =    0;
   /*---(prepare)------------------------*/
   ystrlcpy (s, ",", LEN_RECD);
   s_nbase = 0;
   /*---(prepare)------------------------*/
   p = s_head;
   for (i = 0; i < s_nthing; ++i) {
      if (p->z == 1) {
         sprintf (t, "%s,", p->l);
         ystrlcat (s, t, LEN_RECD);
         ++s_nbase;
         ++c;
      }
      p = p->n;
   }
   /*---(finalize)-----------------------*/
   if (strcmp (s, ",") == 0)  ystrlcpy (s, "n/a", LEN_RECD);
   else                       ySORT_labels (s);
   sprintf (myMAP.g_print, "%-2d  %s", c, s);
   /*---(complete)-----------------------*/
   return myMAP.g_print;
}

char*
ymap__unit_regs                 (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   tTHING     *p           = NULL;
   char        s           [LEN_RECD]  = "";
   char        t           [LEN_LABEL] = "";
   char        c           =    0;
   /*---(prepare)------------------------*/
   ystrlcpy (s, ",", LEN_RECD);
   s_nfree = 0;
   /*---(prepare)------------------------*/
   p = s_head;
   for (i = 0; i < s_nthing; ++i) {
      if (p->z == 2) {
         sprintf (t, "%s,", p->l);
         ystrlcat (s, t, LEN_RECD);
         ++s_nfree;
         ++c;
      }
      p = p->n;
   }
   /*---(finalize)-----------------------*/
   if (strcmp (s, ",") == 0)  ystrlcpy (s, "n/a", LEN_RECD);
   else                       ySORT_labels (s);
   sprintf (myMAP.g_print, "%-2d  %s", c, s);
   /*---(complete)-----------------------*/
   return myMAP.g_print;
}

char*
ymap__unit_adds                 (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   tTHING     *p           = NULL;
   char        s           [LEN_RECD]  = "";
   char        t           [LEN_LABEL] = "";
   char        c           =    0;
   /*---(prepare)------------------------*/
   ystrlcpy (s, ",", LEN_RECD);
   /*---(walk)---------------------------*/
   p = s_head;
   for (i = 0; i < s_nthing; ++i) {
      if (p->z == 0) {
         sprintf (t, "%s,", p->l);
         ystrlcat (s, t, LEN_RECD);
         ++c;
      }
      p = p->n;
   }
   /*---(finalize)-----------------------*/
   if (strcmp (s, ",") == 0)  ystrlcpy (s, "n/a", LEN_RECD);
   else                       ySORT_labels (s);
   sprintf (myMAP.g_print, "%-2d  %s", c, s);
   /*---(complete)-----------------------*/
   return myMAP.g_print;
}

char*
ymap__unit_mreg         (void)
{
   int    x, y;
   ystrlcpy (myMAP.g_print, "", LEN_RECD);
   for (y = 0; y < 8; ++y) {
      if (y > 0)  ystrlcat (myMAP.g_print, "  ", LEN_RECD);
      for (x = 0; x < 10; ++x) {
         if      (s_things [x][y] == NULL) {
            if (yMAP_visual (0, x, y, 0))    ystrlcat (myMAP.g_print, "`", LEN_RECD);
            else                             ystrlcat (myMAP.g_print, "·", LEN_RECD);
         }
         else if (s_things [x][y]->z == 1)   ystrlcat (myMAP.g_print, "Ï", LEN_RECD);
         else if (s_things [x][y]->z == 0)   ystrlcat (myMAP.g_print, "+", LEN_RECD);
         else                                ystrlcat (myMAP.g_print, "·", LEN_RECD);
      }
   }
   return myMAP.g_print;
}

char
ymap__unit_copier       (char a_type, long a_stamp)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   tTHING     *x_thing     = NULL;
   tTHING     *x_new       = NULL;
   ushort      b           =    0;
   ushort      x           =    0;
   ushort      y           =    0;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   rc = yMAP_visu_first (&b, &x, &y, NULL);
   while (rc >= 0) {
      x_thing = s_things [x][y];
      if (x_thing != NULL) {
         rc = yMAP_visual (b, x, y, 0);
         if (rc == 1) {
            x_new = ymap__unit_dup (x_thing);
            yMAP_mreg_add (x_new, x_new->l, "", "");
         }
      }
      rc = yMAP_visu_next  (&b, &x, &y, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__unit_clearer      (char a_1st, int b, int x, int y, int z)
{
   tTHING     *x_thing     = NULL;
   if (s_things [x][y] == NULL)  return 0;
   myMAP.e_regkill (s_things [x][y]);
   s_things [x][y] = NULL;
   return 0;
}

char
ymap__unit_paster       (char a_regs, char a_pros, char a_intg, char a_1st, int a_boff, int a_xoff, int a_yoff, int a_zoff, void *a_thing)
{
   tTHING     *x_thing;
   int         x, y;
   x_thing = ymap__unit_dup (a_thing);
   x = x_thing->x + a_xoff;
   y = x_thing->y + a_yoff;
   ymap__unit_hook (x_thing, x, y);
   return 0;
}

char
ymap__unit_config       (void)
{
   char        rc          =    0;
   rc = yMAP_mreg_config (ymap__unit_clearer, ymap__unit_copier, ymap__unit_paster, NULL, ymap__unit_regkill, NULL);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___MUNDO___________o () { return; }

static int    s_undos = 0;
static int    s_redos = 0;
static char   s_mundo [LEN_RECD] = "··n ··u ··r  §  · · ········ ··åæ       ··åæ";

char
ymap__unit_mundo_save   (char d, char a, char *l, char *f, char *c)
{
   char        s           [LEN_HUND]  = "";
   char        t           [LEN_HUND]  = "";
   if (d == '<')  ++s_undos;
   if (d == '>')  ++s_redos;
   sprintf (s, "%2då%-.6sæ", strlen (f), f);
   sprintf (t, "%2då%sæ", strlen (c), c);
   sprintf (s_mundo, "%2dn %2du %2dr  §  %c %c %-8.8s %-10.10s %s",
         myMAP.h_count, s_undos, s_redos,
         d, a, l, s, t);
   return 0;
}

char
ymap__unit_mundo        (char d, char a, char *l, char *f, char *c)
{
   return ymap__unit_mundo_save (d, a, l, f, c);
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACCESSOR________o () { return; }

char           unit_answer [LEN_FULL];

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yMAP__unit              (char *a_question, char a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   char        n           =    0;
   ushort      u, x, y, z;
   char        t           [LEN_RECD]  = "";
   char        s           [LEN_LABEL] = "";
   /*---(preprare)-----------------------*/
   ystrlcpy  (unit_answer, "MAP unit         : question not understood", LEN_FULL);
   /*---(dependency list)----------------*/
   if      (strcmp (a_question, "pos"            )   == 0) {
      rc = ymap_pick_map (a_index, &x_map, NULL);
      if (rc < 0)  snprintf (unit_answer, LEN_FULL, "MAP pos      (·) : L  ·i  §  U    ·a    ·b    ·c    ·e    ·t    ·l    ·x  §  G    ·b    ·c    ·e");
      else         snprintf (unit_answer, LEN_FULL, "MAP pos      (%c) : L %2di  §  U %4da %4db %4dc %4de %4dt %4dl %4dx  §  G %4db %4dc %4de",
            x_map->axis, x_map->inc,
            x_map->uavail, x_map->ubeg, x_map->ucur, x_map->uend, x_map->utend, x_map->ulen, x_map->umax,
            x_map->gbeg, x_map->gcur, x_map->gend);
   }
   else if (strcmp (a_question, "grid"           )   == 0) {
      rc = ymap_pick_map (a_index, &x_map, NULL);
      if (rc < 0)  snprintf (unit_answer, LEN_FULL, "MAP grid     (·) :    ·g    ·a    ·l §    ·p    ·u §    ·b    ·c    ·e §    ·u    ·n §    ·l    ·a    ·g");
      else         snprintf (unit_answer, LEN_FULL, "MAP grid     (%c) : %4dg %4da %4dl § %4dp %4du § %4db %4dc %4de § %4du %4dn § %4dl %4da %4dg",
            x_map->axis,
            x_map->gmin , x_map->gamin, x_map->glmin, x_map->gprev, x_map->gpuse,
            x_map->gbeg , x_map->gcur , x_map->gend ,
            x_map->gnuse, x_map->gnext, x_map->glmax, x_map->gamax, x_map->gmax );
   }
   else if (strcmp (a_question, "current"        )   == 0) {
      yMAP_current (t, &u, &x, &y, &z);
      snprintf (unit_answer, LEN_FULL, "MAP current      : %-12.12s  %4du %4dx %4dy %4dz", t, u, x, y, z);
   }
   else if (strcmp (a_question, "display"        )   == 0) {
      rc = ymap_pick_map (a_index, &x_map, NULL);
      if (rc < 0)  snprintf (unit_answer, LEN_FULL, "MAP disp     (·) : åæ");
      else {
         ymap_display_show (x_map, g_print);
         snprintf (unit_answer, LEN_FULL, "MAP disp     (%c) : %3då%sæ", x_map->axis, strlen (g_print), g_print);
      }
   }
   else if (strcmp (a_question, "map"            )   == 0) {
      rc = ymap_pick_map (a_index, &x_map, NULL);
      if (rc < 0)  snprintf (unit_answer, LEN_FULL, "MAP map      (·) : åæ");
      else {
         ymap_display_map  (x_map, g_print);
         snprintf (unit_answer, LEN_FULL, "MAP mapish   (%c) : %3då%sæ", x_map->axis, strlen (g_print), g_print);
      }
   }
   else if (strcmp (a_question, "units"          )   == 0) {
      rc = ymap_pick_map (a_index, &x_map, NULL);
      if (rc < 0)  snprintf (unit_answer, LEN_FULL, "MAP units    (·) : åæ");
      else {
         ymap_display_units (x_map, g_print);
         snprintf (unit_answer, LEN_FULL, "MAP units    (%c) : %3då%sæ", x_map->axis, strlen (g_print), g_print);
      }
   }
   else if (strcmp (a_question, "range"          )   == 0) {
   }
   else if (strcmp (a_question, "mundo"          )   == 0) {
      sprintf (unit_answer, "MAP mundo exec   : %s", s_mundo);
   }
   else if (strcmp (a_question, "refresh"        )   == 0) {
      sprintf (unit_answer, "MAP refresh      : univ %d, xaxis %d, yaxis %d, zaxis %d", g_umap.change, g_xmap.change, g_ymap.change, g_zmap.change);
   }
   else if (strcmp (a_question, "mreg_list"      )   == 0) {
         snprintf (unit_answer, LEN_FULL, "MAP mreg list    : %s", ymap_mreg_list   (a_index));
   }
   else if (strcmp (a_question, "mreg_detail"    )   == 0) {
         snprintf (unit_answer, LEN_FULL, "MAP mreg detail  : %s", ymap_mreg_detail (a_index));
   }
   else if (strcmp (a_question, "visual"         )   == 0) {
      n = ymap_visu_index (a_index);
      if (n < 0) snprintf (unit_answer, LEN_FULL, "MAP visual (- -) : - - - §  ·u § -    ·b    ·e    ·r § -    ·b    ·e    ·r § b=         e=         §");
      else {
         ymap_visu_line (myMAP.v_visus + n, '+', 0, t);
         if      (a_index == '\'')  sprintf (s, "visu.cur (%c)", myMAP.v_visus [n].abbr);
         else if (a_index == ';')   sprintf (s, "visu.prv (%c)", myMAP.v_visus [n].abbr);
         else                       sprintf (s, "visual   (%c)", a_index);
         snprintf (unit_answer, LEN_FULL, "MAP %s : %s", s, t + 10);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

