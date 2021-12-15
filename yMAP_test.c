/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"



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
   { 'r',  15,  10,  24,  24 },
   {  0 ,   0,   0,   0,   0 },
};

#define       MAX_LOADS      200
struct {
   uchar       style;
   short       ref;
   uchar       wide;
   uchar       used;
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
   {  'r',   41,   1, '·' },
   {  'r',   42,   1, '·' },
   {  'r',   43,   1, '·' },
   {  'r',   44,   1, 'Ï' },
   {  'r',   45,   1, 'Ï' },
   {  'r',   46,   1, 'Ï' },
   {  'r',   47,   1, '·' },
   {  'r',   48,   1, '·' },
   {  'r',   49,   1, '·' },
   {  'r',   50,   1, '·' },
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
   {  '1',    0,   0, 'Ï' },
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
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   /*---(univers)------------------------*/
   DEBUG_MAP   yLOG_note    ("universe");
   c = 40;
   rc = yMAP_size (YMAP_UNIV, c);
   rc = ymap_pick_map (YMAP_UNIV, NULL, &x_grid);
   DEBUG_MAP   yLOG_note    ("load data");
   for (i = 0; i < c; ++i) {
      DEBUG_MAP   yLOG_value   ("grid"     , i);
      x_grid [i].ref  = i;
      x_grid [i].wide = 1;
      x_grid [i].used = '·';
   }
   rc = yMAP_update     (YMAP_UNIV);
   /*---(x/col)--------------------------*/
   DEBUG_MAP   yLOG_note    ("xaxis");
   c = 500;
   rc = yMAP_size (YMAP_XAXIS, c);
   rc = ymap_pick_map (YMAP_XAXIS, NULL, &x_grid);
   DEBUG_MAP   yLOG_note    ("load data");
   for (i = 0; i < c; ++i) {
      x_grid [i].ref  = i;
      x_grid [i].wide = 1;
      x_grid [i].used = '·';
   }
   rc = yMAP_update     (YMAP_XAXIS);
   /*---(y/row)--------------------------*/
   DEBUG_MAP   yLOG_note    ("yaxis");
   c = 500;
   rc = yMAP_size (YMAP_YAXIS, c);
   rc = ymap_pick_map (YMAP_YAXIS, NULL, &x_grid);
   DEBUG_MAP   yLOG_note    ("load data");
   for (i = 0; i < c; ++i) {
      x_grid [i].ref  = i;
      x_grid [i].wide = 1;
      x_grid [i].used = '·';
   }
   rc = yMAP_update     (YMAP_YAXIS);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
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
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   /*---(size)---------------------------*/
   rc = yMAP_size (a_axis, 200);
   DEBUG_MAP   yLOG_value   ("size"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   DEBUG_MAP   yLOG_value   ("pickmap"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_point   ("x_grid"    , x_grid);
   DEBUG_MAP   yLOG_complex ("assign"    , "%c, b%-10p, x%-10p, y%-10p, z%-10p, t%-10p", a_axis, g_ugrid, g_xgrid, g_ygrid, g_zgrid, g_wgrid);
   --rce;  if (a_style == 0 || strchr ("fF+uadsr-w", a_style) == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(show)---------------------------*/
   DEBUG_MAP    yLOG_value   ("glen"      , x_map->glen);
   for (i = 0; i < x_map->glen; ++i) {
      DEBUG_MAP   yLOG_complex ("auditing"  , "%3d, %6d, %2d, %c", i, x_grid [i].ref, x_grid [i].wide, x_grid [i].used);
   }
   /*---(load)---------------------------*/
   DEBUG_MAP   yLOG_note    ("check loads");
   x_style = a_style;
   if (a_style == 'F')  { x_style = 'f';  x_loop = 4; }
   if (a_style == '+')  { x_style = 'f'; }
   for (k = 0; k < x_loop; ++k) {
      for (i = 0; i < MAX_LOADS; ++i) {
         if (s_loads [i].style == 0)        break;
         DEBUG_MAP   yLOG_complex ("checking"  , "%2d, %2d, %c, %2d, %2d, %c", i, n, s_loads [i].style, s_loads [i].ref, s_loads [i].wide, s_loads [i].used);
         if (n >= x_map->glen)              break;
         if (s_loads [i].style != x_style)   continue;
         x_grid [n].ref  = s_loads [i].ref   + (k * m);
         x_grid [n].wide = s_loads [i].wide;
         x_grid [n].used = s_loads [i].used;
         DEBUG_MAP   yLOG_note    ("LOADED");
         w += x_grid [n].wide;
         ++n;
      }
      if (k == 0)  m = n;
   }
   /*---(show)---------------------------*/
   DEBUG_MAP    yLOG_value   ("glen"      , x_map->glen);
   for (i = 0; i < x_map->glen; ++i) {
      DEBUG_MAP   yLOG_complex ("auditing"  , "%3d, %6d, %2d, %c", i, x_grid [i].ref, x_grid [i].wide, x_grid [i].used);
   }
   /*---(unit min/max)-------------------*/
   x_map->umin   = 0;
   x_map->ubeg   = x_map->ucur   =  0;
   x_map->umax   = x_map->uend   = x_map->utend  = w - 1;
   x_map->uavail = w;
   /*---(find defaults)------------------*/
   DEBUG_MAP   yLOG_note    ("check units");
   x_style = a_style;
   if (a_style == 'F')  { x_style = 'f'; }
   for (i = 0; i < MAX_UNITS; ++i) {
      if (s_units [i].style == 0)        break;
      DEBUG_MAP   yLOG_complex ("checking"  , "%2d, %c, %2d, %2d, %2d, %2d", i, s_units [i].style, s_units [i].ubeg, s_units [i].uend, s_units [i].utend, s_units [i].uavail);
      if (s_units [i].style != x_style)  continue;
      x_map->ubeg   = s_units [i].ubeg;
      x_map->ucur   = s_units [i].ubeg;
      x_map->uend   = s_units [i].uend;
      x_map->utend  = s_units [i].utend;
      x_map->uavail = s_units [i].uavail;
      DEBUG_MAP   yLOG_note    ("FOUND");
      break;
   }
   x_map->ulen  = x_map->uend - x_map->ubeg + 1;
   DEBUG_MAP   yLOG_value   ("ulen"      , x_map->ulen);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__unit_full         (uchar a_axis, uchar a_style)
{
   char        rc          =    0;
   rc = ymap__unit_load (a_axis, a_style);
   if (rc >= 0)  rc = yMAP_update     (a_axis);
   ymap_visu_update ();
   return rc;
}

char*
ymap_print              (uchar a_axis)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   char        x_spot      =    0;
   char        n           =    0;
   uchar       c           =    0;
   uchar       s           =    0;
   char        t           [LEN_TERSE] = "";
   tyMAP      *x_map       = NULL;
   /*---(defense)------------------------*/
   rc = ymap_pick_map (a_axis, &x_map, NULL);
   if (rc < 0)  return "n/a";
   if (x_map->map == NULL) {
      sprintf (g_print, "%c åæ", x_map->axis);
      return g_print;
   }
   /*---(content)------------------------*/
   sprintf (g_print, "%c å", x_map->axis);
   s = x_map->map [0];
   for (i = 0; i <= x_map->mlen; ++i) {
      c = x_map->map [i];
      if (c == YMAP_MAX)  break;
      if (c != s) {
         if (n > 0) {
            sprintf (t, "%2d%c%-2d ", s, x_map->grid [s].used, n);
            strlcat (g_print, t, LEN_RECD);
            ++x_spot;
         }
         s = c;
         n = 1;
      } else ++n;
   }
   strcat (g_print, "æ");
   /*---(end)----------------------------*/
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
      if (x_grid [i].ref == YMAP_EMPTY)  break;
      sprintf (t, "%2d%c%-2d", x_grid [i].ref, x_grid [i].used, x_grid [i].wide);
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
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
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
         strlpad ("+", t, '.', '>', c);
         strlcat (a_disp, t, LEN_RECD);
         ++n;
         c = 0;
      } else if (i == a_map->uend) {
         ++c;
         strlpad ("|", t, '.', '>', c);
         strlcat (a_disp, t, LEN_RECD);
      }
      x_cur = a_map->map [i];
      ++c;
   }
   /*---(extra at end)-------------------*/
   c     = a_map->utend - a_map->uend;
   if (c > 0) {
      strlpad ("", t, '-', '<', c);
      strlcat (a_disp, t, LEN_RECD);
   }
   /*---(left-over avail)----------------*/
   c     = (a_map->ubeg + a_map->uavail - 1) - a_map->utend;
   if (c > 0) {
      strlcpy (t, "///////////////////////////////////////", c + 1);
      strlcat (a_disp, t, LEN_RECD);
   }
   /*---(current position)---------------*/
   if (a_map->ucur >= a_map->ubeg && a_map->ucur <= a_map->utend) {
      a_disp [a_map->ucur - a_map->ubeg] = 'Ï';
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   if (a_disp == NULL)            return -1;
   strcpy (a_disp , "");
   if (a_map  == NULL)            return -2;
   if (a_map->map  == NULL)       return -3;
   /*---(main display)-------------------*/
   x_cur  = a_map->map [a_map->ubeg];
   for (i = 0; i <= a_map->mlen; ++i) {
      if (x_cur != a_map->map [i] || i == a_map->mlen) {
         strlpad ("+", t, '.', '>', c);
         strlcat (a_disp, t, LEN_RECD);
         ++n;
         c = 0;
      }
      x_cur = a_map->map [i];
      ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_display_units      (tyMAP *a_map, char *a_disp)
{
   char        rc          =    0;
   int         i           =    0;
   rc = ymap_display_map  (a_map, a_disp);
   if (rc < 0)  return rc;
   for (i = 0; i < a_map->glen; ++i) {
      if (a_map->grid [i].ref == YMAP_EMPTY)  break;
      a_disp [a_map->grid [i].unit] = YSTR_LOWUP [i];
   }
   return 0;
}




/*====================------------------------------------====================*/
/*===----                          drivers                             ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVERS_________o () { return; }

char       /*----: set up program urgents/debugging --------------------------*/
ymap__unit_quiet         (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yMAP_unit" };
   yMODE_init (MODE_MAP);
   yMODE_handler_setup ();
   yMACRO_global_init ();
   yMAP_init ();
   yMAP_config (YMAP_OFFICE, ymap__unit_mapper, ymap__unit_locator, ymap__unit_addresser);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ymap__unit_loud          (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yMAP_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("edit"         , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   yURG_name  ("ymode"        , YURG_ON);
   yURG_name  ("mode"         , YURG_ON);
   yURG_name  ("cmds"         , YURG_ON);
   yURG_name  ("map"          , YURG_ON);
   yURG_name  ("keys"         , YURG_ON);
   yURG_name  ("regs"         , YURG_ON);
   DEBUG_CMDS  yLOG_info     ("yMAP"     , yMAP_version   ());
   yMODE_init (MODE_MAP);
   yMODE_handler_setup ();
   yMACRO_global_init ();
   yMAP_init ();
   yMAP_config (YMAP_OFFICE, ymap__unit_mapper, ymap__unit_locator, ymap__unit_addresser);
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ymap__unit_end           (void)
{
   DEBUG_CMDS  yLOG_enter   (__FUNCTION__);
   yMAP_wrap   ();
   DEBUG_CMDS  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         mock testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___MOCK____________o () { return; }

char
ymap__unit_map_general  (void)
{
   ymap__unit_full (YMAP_UNIV , 's');
   ymap__unit_full (YMAP_XAXIS, 'F');
   ymap__unit_full (YMAP_YAXIS, 'r');
   ymap__unit_full (YMAP_ZAXIS, '1');
   return 0;
}

char
ymap__unit_mapper       (char a_type)
{
   return 0;
}

char
ymap__unit_locator      (char *a_label, ushort *b, ushort *x, ushort *y, ushort *z)
{
   if (z != NULL)  *z = 0;
   return str2gyges (a_label, b, x, y, NULL, NULL, 0, YSTR_CHECK);
}

char 
ymap__unit_addresser    (char *a_label, ushort b, ushort x, ushort y, ushort z)
{
   return str4gyges (b, x, y, 0, 0, a_label, YSTR_CHECK);
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
   sprintf (t, "%d%d", p->y, p->x);
   strlcpy (q->l, t, LEN_LABEL);
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
   sprintf (t, "%d%d", y, x);
   strlcpy (p->l, t, LEN_LABEL);
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
   strlcpy (s, ",", LEN_RECD);
   s_nbase = 0;
   /*---(prepare)------------------------*/
   p = s_head;
   for (i = 0; i < s_nthing; ++i) {
      if (p->z == 1) {
         sprintf (t, "%s,", p->l);
         strlcat (s, t, LEN_RECD);
         ++s_nbase;
         ++c;
      }
      p = p->n;
   }
   /*---(finalize)-----------------------*/
   if (strcmp (s, ",") == 0)  strlcpy (s, "n/a", LEN_RECD);
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
   strlcpy (s, ",", LEN_RECD);
   s_nfree = 0;
   /*---(prepare)------------------------*/
   p = s_head;
   for (i = 0; i < s_nthing; ++i) {
      if (p->z == 2) {
         sprintf (t, "%s,", p->l);
         strlcat (s, t, LEN_RECD);
         ++s_nfree;
         ++c;
      }
      p = p->n;
   }
   /*---(finalize)-----------------------*/
   if (strcmp (s, ",") == 0)  strlcpy (s, "n/a", LEN_RECD);
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
   strlcpy (s, ",", LEN_RECD);
   /*---(walk)---------------------------*/
   p = s_head;
   for (i = 0; i < s_nthing; ++i) {
      if (p->z == 0) {
         sprintf (t, "%s,", p->l);
         strlcat (s, t, LEN_RECD);
         ++c;
      }
      p = p->n;
   }
   /*---(finalize)-----------------------*/
   if (strcmp (s, ",") == 0)  strlcpy (s, "n/a", LEN_RECD);
   sprintf (myMAP.g_print, "%-2d  %s", c, s);
   /*---(complete)-----------------------*/
   return myMAP.g_print;
}

char*
ymap__unit_mreg         (void)
{
   int    x, y;
   strlcpy (myMAP.g_print, "", LEN_RECD);
   for (y = 0; y < 8; ++y) {
      if (y > 0)  strlcat (myMAP.g_print, "  ", LEN_RECD);
      for (x = 0; x < 10; ++x) {
         if      (s_things [x][y] == NULL) {
            if (yMAP_visual (0, x, y, 0))    strlcat (myMAP.g_print, "`", LEN_RECD);
            else                             strlcat (myMAP.g_print, "·", LEN_RECD);
         }
         else if (s_things [x][y]->z == 1)   strlcat (myMAP.g_print, "Ï", LEN_RECD);
         else if (s_things [x][y]->z == 0)   strlcat (myMAP.g_print, "+", LEN_RECD);
         else                                strlcat (myMAP.g_print, "·", LEN_RECD);
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
            yMAP_mreg_add (x_new, x_new->l);
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
   rc = yMAP_mreg_config (ymap__unit_clearer, ymap__unit_copier, NULL, ymap__unit_paster, NULL, ymap__unit_regkill, NULL);
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
   char        t           [LEN_LABEL] = "";
   char        s           [LEN_LABEL] = "";
   /*---(preprare)-----------------------*/
   strlcpy  (unit_answer, "MAP unit         : question not understood", LEN_FULL);
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
      if (rc < 0)  snprintf (unit_answer, LEN_FULL, "MAP grid     (·) :    ·g    ·a    ·l §    ·p §    ·b    ·c    ·e §    ·n §    ·l    ·a    ·g");
      else         snprintf (unit_answer, LEN_FULL, "MAP grid     (%c) : %4dg %4da %4dl § %4dp § %4db %4dc %4de § %4dn § %4dl %4da %4dg",
            x_map->axis,
            x_map->gmin , x_map->gamin, x_map->glmin, x_map->gprev,
            x_map->gbeg , x_map->gcur , x_map->gend ,
            x_map->gnext, x_map->glmax, x_map->gamax, x_map->gmax );
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
   else if (strcmp (a_question, "visual"         )   == 0) {
      n = ymap_visu_index (a_index);
      if (n < 0) snprintf (unit_answer, LEN_FULL, "MAP visual (- -) : - - - §  ·u § -    ·b    ·e    ·r § -    ·b    ·e    ·r § b=         e=         §");
      else {
         if      (a_index == '\'')  sprintf (s, "visu.cur (%c)", s_visus [n].abbr);
         else if (a_index == '<')   sprintf (s, "visu.prv (%c)", s_visus [n].abbr);
         else                       sprintf (s, "visual   (%c)", a_index);
         sprintf (t, "%dx%d", s_visus [n].x_end -  s_visus [n].x_beg + 1, s_visus [n].y_end -  s_visus [n].y_beg + 1);
         snprintf (unit_answer, LEN_FULL, "MAP %s : %c %c %c § %2du § %c %4db %4de %4dr § %c %4db %4de %4dr § b=%-6.6s e=%-6.6s %s",
               s, s_visus [n].active, s_visus [n].source, s_visus [n].modded, s_visus [n].u_all,
               s_visus [n].x_lock , s_visus [n].x_beg  , s_visus [n].x_end  , s_visus [n].x_root ,
               s_visus [n].y_lock , s_visus [n].y_beg  , s_visus [n].y_end  , s_visus [n].y_root ,
               s_visus [n].b_label, s_visus [n].e_label, t);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*> char*        /+-> tbd --------------------------------[ leaf   [gs.520.202.40]+/ /+-[01.0000.00#.#]-+/ /+-[--.---.---.--]-+/                                                                                                                                                                     <* 
 *> yvikeys_visu__unit      (char *a_question, char a_which)                                                                                                                                                                                                                                         <* 
 *> {                                                                                                                                                                                                                                                                                                <* 
 *>    int         n           =    0;                                                                                                                                                                                                                                                               <* 
 *>    /+---(preprare)-----------------------+/                                                                                                                                                                                                                                                      <* 
 *>    strlcpy  (yVIKEYS__unit_answer, "VISU unit        : question not understood", LEN_FULL);                                                                                                                                                                                                      <* 
 *>    /+---(simple)-------------------------+/                                                                                                                                                                                                                                                      <* 
 *>    if      (strcmp (a_question, "selection"      )   == 0) {                                                                                                                                                                                                                                     <* 
 *>       snprintf (yVIKEYS__unit_answer, LEN_FULL, "VISU selection   : %c  %3db,  %4d to %4dx,  %4d to %4dy,  %4dz", yvikeys_visu_getlive (), s_visu.b_all, s_visu.x_beg, s_visu.x_end, s_visu.y_beg, s_visu.y_end, s_visu.z_all);                                                                  <* 
 *>       return yVIKEYS__unit_answer;                                                                                                                                                                                                                                                               <* 
 *>    }                                                                                                                                                                                                                                                                                             <* 
 *>    else if (strcmp (a_question, "range"          )   == 0) {                                                                                                                                                                                                                                     <* 
 *>       snprintf (yVIKEYS__unit_answer, LEN_FULL, "VISU range       : %c to %c,  %c", s_visu_head, s_visu_tail, s_visu_curr);                                                                                                                                                                      <* 
 *>       return yVIKEYS__unit_answer;                                                                                                                                                                                                                                                               <* 
 *>    }                                                                                                                                                                                                                                                                                             <* 
 *>    else if (strcmp (a_question, "cursor"         )   == 0) {                                                                                                                                                                                                                                     <* 
 *>       snprintf (yVIKEYS__unit_answer, LEN_FULL, "VISU cursor      : %c  %3db,  %4dx,  %4dy,  %4dz", yvikeys_visu_getlive (), s_visu.b_all, s_visu.x_beg, s_visu.y_beg, s_visu.z_all);                                                                                                            <* 
 *>    }                                                                                                                                                                                                                                                                                             <* 
 *>    /+---(complex)------------------------+/                                                                                                                                                                                                                                                      <* 
 *>    n = yvikeys_visu__index (a_which);                                                                                                                                                                                                                                                            <* 
 *>    if (n < 0) {                                                                                                                                                                                                                                                                                  <* 
 *>       strlcpy  (yVIKEYS__unit_answer, "VISU unit        : not a valid range name", LEN_FULL);                                                                                                                                                                                                    <* 
 *>       return yVIKEYS__unit_answer;                                                                                                                                                                                                                                                               <* 
 *>    }                                                                                                                                                                                                                                                                                             <* 
 *>    /+---(dependency list)----------------+/                                                                                                                                                                                                                                                      <* 
 *>    if      (strcmp (a_question, "saved"          )   == 0) {                                                                                                                                                                                                                                     <* 
 *>       snprintf (yVIKEYS__unit_answer, LEN_FULL, "VISU saved   (%c) : %c  %3db,  %4d to %4dx,  %4d to %4dy,  %4dz", a_which, s_visu_info [n].active, s_visu_info [n].b_all, s_visu_info [n].x_beg, s_visu_info [n].x_end, s_visu_info [n].y_beg, s_visu_info [n].y_end, s_visu_info [n].z_all);   <* 
 *>    }                                                                                                                                                                                                                                                                                             <* 
 *>    else if (strcmp (a_question, "labels"         )   == 0) {                                                                                                                                                                                                                                     <* 
 *>       snprintf (yVIKEYS__unit_answer, LEN_FULL, "VISU labels  (%c) : %c    beg=%-12.12s, end=%s", a_which, s_visu_info [n].active, s_visu_info [n].b_label, s_visu_info [n].e_label);                                                                                                            <* 
 *>    }                                                                                                                                                                                                                                                                                             <* 
 *>    /+---(complete)-----------------------+/                                                                                                                                                                                                                                                      <* 
 *>    return yVIKEYS__unit_answer;                                                                                                                                                                                                                                                                  <* 
 *> }                                                                                                                                                                                                                                                                                                <*/
