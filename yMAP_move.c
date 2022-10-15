/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"



/*====================------------------------------------====================*/
/*===----                     movement translations                    ----===*/
/*====================------------------------------------====================*/
static void  o___TRANSLATE_______o () { return; }

char
ymap_office              (uchar a_axis, uchar *r_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_schar   (a_axis);
   --rce;  if (a_axis != YMAP_YAXIS) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_schar   (myMAP.orient);
   DEBUG_YMAP   yLOG_schar   (YMAP_OFFICE);
   --rce;  if (myMAP.orient != YMAP_OFFICE) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (r_minor);
   --rce;  if (r_minor == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_schar   (*r_minor);
   /*---(handle)-------------------------*/
   --rce;  switch (*r_minor) {
   case '_' :  *r_minor = '~';  break;
   case 'T' :  *r_minor = 'B';  break;
   case 't' :  *r_minor = 'b';  break;
   case 'K' :  *r_minor = 'J';  break;
   case 'k' :  *r_minor = 'j';  break;
   case 'j' :  *r_minor = 'k';  break;
   case 'J' :  *r_minor = 'K';  break;
   case 'b' :  *r_minor = 't';  break;
   case 'B' :  *r_minor = 'T';  break;
   case '~' :  *r_minor = '_';  break;
   case 'a' :  *r_minor = 'd';  break;
   case 'd' :  *r_minor = 'a';  break;
   case 'u' :  *r_minor = 'z';  break;
   case 'z' :  *r_minor = 'u';  break;
   case 'A' :  *r_minor = 'D';  break;
   case 'D' :  *r_minor = 'A';  break;
   case 'U' :  *r_minor = 'Z';  break;
   case 'Z' :  *r_minor = 'U';  break;
   default  :
               DEBUG_YMAP   yLOG_snote   ("not a recognized key");
               DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
               return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_corners            (uchar a_src, uchar a_axis, char *r_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_schar   (a_src);
   --rce;  if (a_src == 0 || strchr ("egz", a_src) == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (r_minor);
   --rce;  if (r_minor == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(ends)---------------------------*/
   if (a_src == 'e') {
      DEBUG_YMAP   yLOG_snote   ("ends");
      switch (a_axis) {
      case YMAP_XAXIS :
         DEBUG_YMAP   yLOG_snote   ("x-axis");
         switch (*r_minor) {
         case 'a'   : case 'A'   : *r_minor = 'S';  break;
         case 'u'   : case 'U'   : *r_minor = 'E';  break;
         case 'd'   : case 'D'   : *r_minor = 'S';  break;
         case 'z'   : case 'Z'   : *r_minor = 'E';  break;
         }
         DEBUG_YMAP   yLOG_schar   (*r_minor);
         break;
      case YMAP_YAXIS :
         DEBUG_YMAP   yLOG_snote   ("y-axis");
         switch (*r_minor) {
         case 'a'   : case 'A'   : *r_minor = 'T';  break;
         case 'u'   : case 'U'   : *r_minor = 'T';  break;
         case 'd'   : case 'D'   : *r_minor = 'B';  break;
         case 'z'   : case 'Z'   : *r_minor = 'B';  break;
         }
         DEBUG_YMAP   yLOG_schar   (*r_minor);
         break;
      default  :
         DEBUG_YMAP   yLOG_snote   ("unknown axis");
         DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
         break;
      }
   }
   /*---(goto/scroll)--------------------*/
   else if (a_src == 'g' || a_src == 'z') {
      DEBUG_YMAP   yLOG_snote   ("goto/scroll");
      switch (a_axis) {
      case YMAP_XAXIS :
         DEBUG_YMAP   yLOG_snote   ("x-axis");
         switch (*r_minor) {
         case 'a'   : *r_minor = 's';  break;
         case 'u'   : *r_minor = 'e';  break;
         case 'd'   : *r_minor = 's';  break;
         case 'z'   : *r_minor = 'e';  break;
         case '.'   : *r_minor = 'c';  break;
         case 'A'   : *r_minor = 'H';  break;
         case 'U'   : *r_minor = 'L';  break;
         case 'D'   : *r_minor = 'H';  break;
         case 'Z'   : *r_minor = 'L';  break;
         }
         DEBUG_YMAP   yLOG_schar   (*r_minor);
         break;
      case YMAP_YAXIS :
         DEBUG_YMAP   yLOG_snote   ("y-axis");
         switch (*r_minor) {
         case 'a'   : *r_minor = 't';  break;
         case 'u'   : *r_minor = 't';  break;
         case 'd'   : *r_minor = 'b';  break;
         case 'z'   : *r_minor = 'b';  break;
         case '.'   : *r_minor = 'm';  break;
         case 'A'   : *r_minor = 'K';  break;
         case 'U'   : *r_minor = 'K';  break;
         case 'D'   : *r_minor = 'J';  break;
         case 'Z'   : *r_minor = 'J';  break;
         }
         DEBUG_YMAP   yLOG_schar   (*r_minor);
         break;
      default  :
         DEBUG_YMAP   yLOG_snote   ("unknown axis");
         DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
         break;
      }
   }
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     shared functions                         ----===*/
/*====================------------------------------------====================*/
static void  o___SHARED__________o () { return; }

char
ymap_set_by_unit        (tyMAP *a_map, ushort a_pos)
{
   char        rce         =  -10;
   --rce;  if (a_map->grid == NULL)  return rce;
   a_map->ucur = a_pos;
   a_map->gcur = a_map->map [a_pos];
   return 0;
}

char
ymap_set_by_grid        (tyMAP *a_map, ushort b, ushort c, ushort e)        
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_spoint  (a_map);
   --rce;  if (a_map       == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (a_map->grid);
   --rce;  if (a_map->grid == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_sint    (a_map->gmax);
   --rce;  if (a_map->gmax == 0) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(beginning)----------------------*/
   DEBUG_YMAP   yLOG_sint    (b);
   --rce;  if (b != YMAP_IGNORE) {
      DEBUG_YMAP   yLOG_snote   ("set beg");
      if (b > a_map->gmax)  {
         DEBUG_YMAP   yLOG_snote   ("too high");
         b = a_map->gmax;
         ++rc;
         DEBUG_YMAP   yLOG_sint    (b);
      }
      a_map->gbeg = b;
      a_map->ubeg = a_map->grid [b].unit;
      DEBUG_YMAP   yLOG_sint    (a_map->ubeg);
   } else {
      DEBUG_YMAP   yLOG_snote   ("ignore beg");
   }
   /*---(current)------------------------*/
   DEBUG_YMAP   yLOG_sint    (c);
   --rce;  if (c != YMAP_IGNORE) {
      DEBUG_YMAP   yLOG_snote   ("set cur");
      if (c > a_map->gmax)  {
         DEBUG_YMAP   yLOG_snote   ("too high");
         c = a_map->gmax;
         ++rc;
         DEBUG_YMAP   yLOG_sint    (c);
      }
      a_map->gcur = c;
      a_map->ucur = a_map->grid [c].unit;
      DEBUG_YMAP   yLOG_sint    (a_map->ucur);
   } else {
      DEBUG_YMAP   yLOG_snote   ("ignore cur");
   }
   /*---(ending)-------------------------*/
   DEBUG_YMAP   yLOG_sint    (e);
   --rce;  if (e != YMAP_IGNORE) {
      DEBUG_YMAP   yLOG_snote   ("set end");
      if (e > a_map->gmax)  {
         DEBUG_YMAP   yLOG_snote   ("too high");
         e = a_map->gmax;
         ++rc;
         DEBUG_YMAP   yLOG_sint    (e);
      }
      a_map->gend = e;
      a_map->uend = a_map->grid [e].unit;
      DEBUG_YMAP   yLOG_sint    (a_map->uend);
   } else {
      DEBUG_YMAP   yLOG_snote   ("ignore end");
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                    find nearest grid                         ----===*/
/*====================------------------------------------====================*/
static void  o___NEARIST_________o () { return; }

char
ymap__grid_up           (tyMAP *a_map, short a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   ushort      x_beg       =    0;
   int         x_cur       = YMAP_EMPTY;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_spoint  (a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_sint    (a_count);
   --rce;  if (a_count <= 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(maxxed out)---------------------*/
   DEBUG_YMAP   yLOG_sint    (a_map->ucur);
   DEBUG_YMAP   yLOG_sint    (a_map->umax);
   --rce;  if (a_map->ucur >= a_map->umax) {
      DEBUG_YMAP   yLOG_note    ("already max");
      ymap_set_by_unit (a_map, a_map->umax);
      ymap_change (a_map->axis, YMAP_POS);
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(find)---------------------------*/
   x_beg  = a_map->ucur + 1;
   x_cur  = a_map->map [a_map->ucur];
   for (i = x_beg; i <= a_map->umax; ++i) {
      if (x_cur != a_map->map [i])  ++c;
      x_cur = a_map->map [i];
      if (c >= a_count)   break;
   }
   /*---(handle bounce)------------------*/
   --rce;  if (i > a_map->umax) {
      DEBUG_YMAP   yLOG_note    ("bounce");
      ymap_set_by_unit (a_map, a_map->umax);
      ymap_change (a_map->axis, YMAP_POS);
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   ymap_set_by_unit (a_map, i);
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   /*---(post-work)---------------------*/
   ymap_change (a_map->axis, YMAP_POS);
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap__grid_down         (tyMAP *a_map, short a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   ushort      x_beg       =    0;
   int         x_cur       = YMAP_EMPTY;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_spoint  (a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_sint    (a_count);
   --rce;  if (a_count >= 0) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(maxxed out)---------------------*/
   DEBUG_YMAP   yLOG_sint    (a_map->ucur);
   DEBUG_YMAP   yLOG_sint    (a_map->umin);
   --rce;  if (a_map->ucur <= a_map->umin) {
      DEBUG_YMAP   yLOG_snote   ("already min");
      ymap_set_by_unit (a_map, a_map->umin);
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      ymap_change (a_map->axis, YMAP_POS);
      return rce;
   }
   /*---(find)---------------------------*/
   x_beg  = a_map->ucur - 1;
   x_cur  = a_map->map [a_map->ucur];
   for (i = x_beg; i >= a_map->umin; --i) {
      if (x_cur != a_map->map [i])  --c;
      if (c <  a_count)  { ++i; break; }
      x_cur = a_map->map [i];
   }
   DEBUG_YMAP   yLOG_sint    (i);
   DEBUG_YMAP   yLOG_sint    (c);
   /*---(handle bounce)------------------*/
   --rce;  if (i < a_map->umin) {
      if (c != a_count) {
         DEBUG_YMAP   yLOG_snote   ("bounce");
         ymap_set_by_unit (a_map, a_map->umin);
         ymap_change (a_map->axis, YMAP_POS);
         DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      i = a_map->umin;
   }
   /*---(save back)----------------------*/
   ymap_set_by_unit (a_map, i);
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   /*---(post-work)---------------------*/
   ymap_change (a_map->axis, YMAP_POS);
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap__grid_at           (tyMAP *a_map, ushort a_unit, char a_limit)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   ushort      x_beg       =    0;
   int         x_cur       = YMAP_EMPTY;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_spoint  (a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(limits)-------------------------*/
   DEBUG_YMAP   yLOG_sint    (a_unit);
   if (a_limit == 'y') {
      DEBUG_YMAP   yLOG_snote   ("screen limited");
      if (a_unit < a_map->ubeg)  a_unit = a_map->ubeg;
      if (a_unit > a_map->uend)  a_unit = a_map->uend;
   } else {
      DEBUG_YMAP   yLOG_snote   ("unlimited");
   }
   if (a_unit < a_map->umin)  a_unit = a_map->umin;
   if (a_unit > a_map->umax)  a_unit = a_map->umax;
   DEBUG_YMAP   yLOG_sint    (a_unit);
   /*---(save back)----------------------*/
   ymap_set_by_unit (a_map, a_unit);
   DEBUG_YMAP   yLOG_sint    (a_map->ucur);
   DEBUG_YMAP   yLOG_sint    (a_map->gcur);
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   /*---(post-work)---------------------*/
   ymap_change (a_map->axis, YMAP_POS);
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap_grid_dest        (tyMAP *a_map, ushort a_grid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_spoint  (a_map);
   --rce;  if (a_map    == NULL) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (a_map->grid);
   --rce;  if (a_map->grid == NULL) {
      DEBUG_YMAP    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(limits)-------------------------*/
   DEBUG_YMAP   yLOG_sint    (a_grid);
   if (a_grid < a_map->gmin)    a_grid = a_map->gmin;
   if (a_grid > a_map->gmax)    a_grid = a_map->gmax;
   /*---(set current)--------------------*/
   ymap_set_by_unit (a_map, a_map->grid [a_grid].unit);
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   /*---(post-work)---------------------*/
   ymap_change (a_map->axis, YMAP_POS);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      general movements                       ----===*/
/*====================------------------------------------====================*/
static void  o___GENERAL_________o () { return; }

char
ymap_simple              (tyMAP *a_map, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_grid      =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_note    ("basic relative/absolute movements");
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("axis"      , a_map->axis);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   --rce;  if (a_minor == 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_XAXIS && !yKEYS_is_horz_simple (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_YAXIS && !yKEYS_is_vert_simple (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_ZAXIS && !yKEYS_is_deep_simple (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ymap_office (a_map->axis, &a_minor);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(handle)-------------------------*/
   --rce;  switch (a_minor) {
   case '0' : case '~' :
      rc = ymap__grid_at   (a_map, 0    , '-');
      break;
   case 'H' : case 'J' :
      rc = ymap__grid_down (a_map, -a_map->inc * 5);
      break;
   case 'h' : case 'j' :
      rc = ymap__grid_down (a_map, -a_map->inc);
      break;
   case 'l' : case 'k' :
      rc = ymap__grid_up   (a_map,  a_map->inc);
      break;
   case 'L' : case 'K' :
      rc = ymap__grid_up   (a_map,  a_map->inc * 5);
      break;
   case '$' : case '_' :
      rc = ymap__grid_at   (a_map, 65535, '-');
      break;
   case '|' : case '%' :
      /*> DEBUG_YMAP   yLOG_value   ("repeats"   , yKEYS_repeats     ());             <*/
      /*> DEBUG_YMAP   yLOG_value   ("original"  , yKEYS_repeat_orig ());             <*/
      x_grid = yKEYS_repeat_useall ();
      DEBUG_YMAP   yLOG_value   ("useall"    , x_grid);
      /*> DEBUG_YMAP   yLOG_value   ("repeats"   , yKEYS_repeats     ());             <*/
      rc = ymap_grid_dest (a_map, x_grid);
      break;
   default  :
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_value   ("result"    , rc);
   /*---(update)-------------------------*/
   ymap_change (a_map->axis, YMAP_POS);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}

char
ymap_goto               (tyMAP *a_map, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_beg       =    0;
   int         x_qtr       =    0;
   int         x_haf       =    0;
   int         x_ful       =    0;
   int         x_end       =    0;
   int         x_pos       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_note    ("goto fixed location on screen");
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("axis"      , a_map->axis);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   --rce;  if (a_minor == 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_XAXIS && !yKEYS_is_horz_goto   (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_YAXIS && !yKEYS_is_vert_goto   (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_ZAXIS && !yKEYS_is_deep_goto   (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ymap_corners ('g', a_map->axis, &a_minor);
   ymap_office  (a_map->axis, &a_minor);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(distances)----------------------*/
   x_beg  = a_map->ubeg;
   x_qtr  = (a_map->uavail / 4) - 1;
   x_haf  = (a_map->uavail / 2) - 1;
   x_ful  = a_map->uavail - 1;
   x_end  = a_map->uend;
   x_pos  = a_map->ucur - a_map->ubeg;
   DEBUG_YMAP   yLOG_complex ("spacing"   , "%4db, %4dq, %4dh, %4df, %4de, %4dp", x_beg, x_qtr, x_haf, x_ful, x_end, x_pos);
   DEBUG_YMAP   yLOG_complex ("before"    , "%4dg, %4du", a_map->gcur, a_map->ucur);
   /*---(handle)-------------------------*/
   --rce;  switch (a_minor) {
   case 'S' : case 'B' :
      rc = ymap__grid_at (a_map, x_beg - x_ful, '-');
      break;
   case 'H' : case 'J' :
      rc = ymap__grid_at (a_map, x_beg - x_haf, '-');
      break;
   case 's' : case 'b' :
      rc = ymap__grid_at (a_map, x_beg        , 'y');
      break;
   case 'h' : case 'j' :
      rc = ymap__grid_at (a_map, x_beg + x_qtr, 'y');
      break;
   case 'c' : case 'm' :
      rc = ymap__grid_at (a_map, x_beg + x_haf, 'y');
      break;
   case 'l' : case 'k' :
      rc = ymap__grid_at (a_map, x_end - x_qtr, 'y');
      break;
   case 'e' : case 't' :
      rc = ymap__grid_at (a_map, x_end        , 'y');
      break;
   case 'L' : case 'K' :
      rc = ymap__grid_at (a_map, x_end + x_haf, '-');
      break;
   case 'E' : case 'T' :
      rc = ymap__grid_at (a_map, x_end + x_ful, '-');
      break;
   default  :
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_value   ("result"    , rc);
   DEBUG_YMAP   yLOG_complex ("after"     , "%4dg, %4du", a_map->gcur, a_map->ucur);
   /*---(adjust)-------------------------*/
   if (strchr ("SHLE", a_minor) != NULL) {
      DEBUG_YMAP   yLOG_note    ("maintain relative position on page moves");
      ymap_display (a_map);  /* ¡¡ special case of early processing !! */
      ymap__grid_at (a_map, a_map->ubeg + x_pos, '-');
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}

char
ymap_scroll             (tyMAP *a_map, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_beg       =    0;
   int         x_qtr       =    0;
   int         x_haf       =    0;
   int         x_ful       =    0;
   int         x_end       =    0;
   int         x_pos       =    0;
   ushort      x_up        =    0;
   ushort      x_down      =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_note    ("goto fixed location on screen");
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("axis"      , a_map->axis);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   --rce;  if (a_minor == 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_XAXIS && !yKEYS_is_horz_scroll (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_YAXIS && !yKEYS_is_vert_scroll (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_ZAXIS && !yKEYS_is_deep_scroll (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ymap_office  (a_map->axis, &a_minor);
   ymap_corners ('z', a_map->axis, &a_minor);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(distances)----------------------*/
   x_beg  = a_map->ubeg;
   x_qtr  = (a_map->uavail / 4) - 2;
   x_haf  = (a_map->uavail / 2) - 2;
   x_ful  = a_map->uavail - 2;
   x_end  = a_map->uend - 2;
   /*---(handle)-------------------------*/
   --rce;  switch (a_minor) {
   case 's' : case 't' :
      x_pos = a_map->ucur;
      break;
   case 'h' : case 'k' :
      x_pos = a_map->ucur - x_qtr;
      break;
   case 'c' : case 'm' :
      x_pos = a_map->ucur - x_haf;
      break;
   case 'l' : case 'j' :
      x_pos = a_map->ucur - x_haf - x_qtr;
      break;
   case 'e' : case 'b' :
      x_pos = a_map->ucur - x_ful;
      break;
   default  :
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(limits)-------------------------*/
   if (x_pos < a_map->umin)  x_pos = a_map->umin;
   if (x_pos > a_map->umax)  x_pos = a_map->umax;
   DEBUG_YMAP   yLOG_value   ("x_pos"     , x_pos);
   /*---(find closest)-------------------*/
   x_up   = x_down = x_pos;
   ymap__align2left (a_map, &x_down);
   DEBUG_YMAP   yLOG_value   ("x_down"    , x_down);
   ymap__align2next (a_map, &x_up  );
   DEBUG_YMAP   yLOG_value   ("x_up"      , x_up);
   if ((x_pos - x_down) < (x_up - x_pos))  x_pos = x_down;
   else                                    x_pos = x_up;
   /*---(save back)----------------------*/
   a_map->ubeg = x_pos;
   DEBUG_YMAP   yLOG_value   ("ubeg"      , a_map->ubeg);
   /*---(update)-------------------------*/
   ymap_change (a_map->axis, YMAP_POS);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_ends               (tyMAP *a_map, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_grid      =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_note    ("goto the end of content");
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("axis"      , a_map->axis);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   --rce;  if (a_minor == 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_XAXIS && !yKEYS_is_horz_ends (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_YAXIS && !yKEYS_is_vert_ends (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_ZAXIS && !yKEYS_is_deep_ends (a_minor)) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ymap_office  (a_map->axis, &a_minor);
   ymap_corners ('e', a_map->axis, &a_minor);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(handle)-------------------------*/
   DEBUG_YMAP   yLOG_value   ("gmin"      , a_map->gmin);
   DEBUG_YMAP   yLOG_value   ("gamin"     , a_map->gamin);
   DEBUG_YMAP   yLOG_value   ("glmin"     , a_map->glmin);
   DEBUG_YMAP   yLOG_value   ("gprev"     , a_map->gprev);
   DEBUG_YMAP   yLOG_value   ("gnext"     , a_map->gnext);
   DEBUG_YMAP   yLOG_value   ("glmax"     , a_map->glmax);
   DEBUG_YMAP   yLOG_value   ("gamax"     , a_map->gamax);
   DEBUG_YMAP   yLOG_value   ("gmax"      , a_map->gmax);
   x_grid = a_map->gcur;
   switch (a_minor) {
   case 'S' : case 'B' : x_grid = a_map->gamin;     break;
   case 's' : case 'b' : x_grid = a_map->glmin;     break;
   case 'h' : case 'j' : x_grid = a_map->gprev;     break;
   case 'c' : case 'M' : x_grid = a_map->gavg;      break;
   case 'C' : case 'm' : x_grid = a_map->gmid;      break;
   case 'l' : case 'k' : x_grid = a_map->gnext;     break;
   case 'e' : case 't' : x_grid = a_map->glmax;     break;
   case 'E' : case 'T' : x_grid = a_map->gamax;     break;
   case 'x' : ymap_visu_locking ('x');  x_grid = a_map->gcur;  break;
   case 'y' : ymap_visu_locking ('y');  x_grid = a_map->gcur;  break;
   case '!' : ymap_visu_locking ('!');  x_grid = a_map->gcur;  break;
   case '*' : ymap_visu_locking ('*');  x_grid = a_map->gcur;  break;
   }
   /*---(limits)-------------------------*/
   if (x_grid < a_map->gmin)  x_grid = a_map->gmin;
   if (x_grid > a_map->gmax)  x_grid = a_map->gmax;
   /*---(outcome)------------------------*/
   DEBUG_YMAP   yLOG_value   ("x_grid"    , x_grid);
   ymap_set_by_grid (a_map, YMAP_IGNORE, x_grid, YMAP_IGNORE);
   /*---(update)-------------------------*/
   ymap_change (a_map->axis, YMAP_POS);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_jump               (ushort u, ushort x, ushort y, ushort z)
{
   char        rce         =  -10;
   char        rc          =    0;
   ushort      u_pos, x_pos, y_pos, z_pos;
   ushort      b, c, e;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(check)--------------------------*/
   rc = ymap_addresser_strict  (NULL, u, x, y, z);
   DEBUG_YMAP   yLOG_value   ("addresser" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(current position)---------------*/
   rc = yMAP_current  (NULL, &u_pos, &x_pos, &y_pos, &z_pos);
   DEBUG_YMAP   yLOG_value   ("addresser" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(change unverse, then remap)-----*/
   DEBUG_YMAP   yLOG_complex ("u"         , "%4d, %p", u, g_umap.grid);
   --rce;  if (u == u_pos) {
      DEBUG_YMAP   yLOG_note    ("jumping in the same universe");
   } else {
      DEBUG_YMAP   yLOG_note    ("changing universe, so all changed");
      ymap_univ_change (u);
      ymap_set_by_grid (&g_umap, YMAP_IGNORE, u, YMAP_IGNORE);
      yMAP_refresh ();  /* must update BEFORE moving in xyz */
   }
   /*---(xaxis/col)----------------------*/
   DEBUG_YMAP   yLOG_value   ("x"         , x);
   ymap_set_by_grid (&g_xmap, YMAP_IGNORE, x, YMAP_IGNORE);
   ymap_xchange (YMAP_POS);
   /*---(yaxis/row)----------------------*/
   DEBUG_YMAP   yLOG_value   ("y"         , y);
   ymap_set_by_grid (&g_ymap, YMAP_IGNORE, y, YMAP_IGNORE);
   ymap_ychange (YMAP_POS);
   /*---(xaxis/depth)--------------------*/
   DEBUG_YMAP   yLOG_value   ("z"         , z);
   ymap_set_by_grid (&g_zmap, YMAP_IGNORE, z, YMAP_IGNORE);
   ymap_zchange (YMAP_POS);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_grid               (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z)
{
   if (u     != NULL)  *u     = g_umap.gcur;
   if (x     != NULL)  *x     = g_xmap.gcur;
   if (y     != NULL)  *y     = g_ymap.gcur;
   if (z     != NULL)  *z     = g_zmap.gcur;
   return 0;
}

char
yMAP_cmd_loc            (char *a_text)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   ushort      b, x, y, z;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_point   ("a_text"    , a_text);
   --rce;  if (a_text == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_info    ("a_text"    , a_text);
   --rce;  if (a_text [0] != ':') {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_text);
   DEBUG_YMAP   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 3 || x_len > 7) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check address)------------------*/
   rc = ymap_locator_strict (a_text + 1, &b, &x, &y, &z);
   DEBUG_YMAP   yLOG_value   ("locator"   , rc);
   --rce;  if (rc >= 0) {
      DEBUG_YMAP   yLOG_complex ("position"  , "%3db, %3dx, %3dy, %3dz", b, x, y, z);
      rc = yMAP_jump (b, x, y, z);
      DEBUG_YMAP   yLOG_value   ("jump"      , rc);
      if (rc < 0) {
         DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     main axis drivers                        ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVERS_________o () { return; }

char
yMAP_move_hmode         (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("a_major"   , a_major);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(simple)-------------------------*/
   if (a_major == ' ') {
      DEBUG_YMAP   yLOG_note    ("checking for simple");
      if (yKEYS_is_horz_simple (a_minor)) {
         rc = ymap_simple   (&g_xmap, a_minor);
         if (yMODE_curr () == UMOD_WANDER && rc == 0)  rc = 1;
         ymap_xchange (YMAP_POS);
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return rc;
      }
      if (yKEYS_is_vert_simple (a_minor)) {
         rc = ymap_simple   (&g_ymap, a_minor);
         if (yMODE_curr () == UMOD_WANDER && rc == 0)  rc = 1;
         ymap_ychange (YMAP_POS);
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return rc;
      }
      if (yKEYS_is_deep_simple (a_minor)) {
         rc = ymap_simple   (&g_zmap, a_minor);
         if (yMODE_curr () == UMOD_WANDER && rc == 0)  rc = 1;
         ymap_ychange (YMAP_POS);
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return rc;
      }
   }
   /*---(goto)---------------------------*/
   else if (a_major == 'g') {
      DEBUG_YMAP   yLOG_note    ("checking for goto");
      if (a_minor == 'v') {
         ymap_visu_reselect ();
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return 1;
      }
      if (yKEYS_is_horz_goto   (a_minor)) {
         rc = ymap_goto     (&g_xmap, a_minor);
         ymap_xchange (YMAP_POS);
         ++c;
      }
      if (yKEYS_is_vert_goto   (a_minor)) {
         rc = ymap_goto     (&g_ymap, a_minor);
         ymap_ychange (YMAP_POS);
         ++c;
      }
      if (yKEYS_is_deep_goto   (a_minor)) {
         rc = ymap_goto     (&g_zmap, a_minor);
         ymap_zchange (YMAP_POS);
         ++c;
      }
      --rce;  if (c <= 0)  rc = rce;
      else if (yMODE_curr () == UMOD_WANDER)  rc = c;
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(scroll)-------------------------*/
   else if (a_major == 'z') {
      DEBUG_YMAP   yLOG_note    ("checking for scroll");
      if (yKEYS_is_horz_scroll (a_minor)) {
         rc = ymap_scroll   (&g_xmap, a_minor);
         ymap_xchange (YMAP_POS);
         ++c;
      }
      if (yKEYS_is_vert_scroll (a_minor)) {
         rc = ymap_scroll   (&g_ymap, a_minor);
         ymap_ychange (YMAP_POS);
         ++c;
      }
      if (yKEYS_is_deep_scroll (a_minor)) {
         rc = ymap_scroll   (&g_zmap, a_minor);
         ymap_zchange (YMAP_POS);
         ++c;
      }
      --rce;  if (c <= 0)  rc = rce;
      else if (yMODE_curr () == UMOD_WANDER)  rc = c;
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(ends)---------------------------*/
   else if (a_major == 'e') {
      DEBUG_YMAP   yLOG_note    ("checking for ends");
      if (yKEYS_is_horz_ends   (a_minor)) {
         rc = ymap_ends     (&g_xmap, a_minor);
         ymap_xchange (YMAP_POS);
         ++c;
      }
      if (yKEYS_is_vert_ends   (a_minor)) {
         rc = ymap_ends     (&g_ymap, a_minor);
         ymap_ychange (YMAP_POS);
         ++c;
      }
      if (yKEYS_is_deep_ends   (a_minor)) {
         rc = ymap_ends     (&g_zmap, a_minor);
         ymap_zchange (YMAP_POS);
         ++c;
      }
      --rce;  if (c <= 0)  rc = rce;
      else if (yMODE_curr () == UMOD_WANDER)  rc = c;
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}


