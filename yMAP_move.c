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
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_schar   (a_axis);
   --rce;  if (a_axis != YMAP_YAXIS) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_schar   (myMAP.orient);
   DEBUG_MAP   yLOG_schar   (YMAP_OFFICE);
   --rce;  if (myMAP.orient != YMAP_OFFICE) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (r_minor);
   --rce;  if (r_minor == NULL) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_schar   (*r_minor);
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
   default  :
               DEBUG_MAP   yLOG_snote   ("not a recognized key");
               DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
               return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_corners            (uchar a_src, uchar a_axis, char *r_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_schar   (a_src);
   --rce;  if (a_src == 0 || strchr ("egz", a_src) == NULL) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (r_minor);
   --rce;  if (r_minor == NULL) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(ends)---------------------------*/
   if (a_src == 'e') {
      DEBUG_MAP   yLOG_snote   ("ends");
      switch (a_axis) {
      case YMAP_XAXIS :
         DEBUG_MAP   yLOG_snote   ("x-axis");
         switch (*r_minor) {
         case 'a'   : *r_minor = 'S';  break;
         case 'u'   : *r_minor = 'E';  break;
         case 'd'   : *r_minor = 'S';  break;
         case 'z'   : *r_minor = 'E';  break;
         }
         DEBUG_MAP   yLOG_schar   (*r_minor);
         break;
      case YMAP_YAXIS :
         DEBUG_MAP   yLOG_snote   ("y-axis");
         switch (*r_minor) {
         case 'a'   : *r_minor = 'T';  break;
         case 'u'   : *r_minor = 'T';  break;
         case 'd'   : *r_minor = 'B';  break;
         case 'z'   : *r_minor = 'B';  break;
         }
         DEBUG_MAP   yLOG_schar   (*r_minor);
         break;
      default  :
         DEBUG_MAP   yLOG_snote   ("unknown axis");
         DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
         break;
      }
   }
   /*---(goto/scroll)--------------------*/
   else if (a_src == 'g' || a_src == 'z') {
      DEBUG_MAP   yLOG_snote   ("goto/scroll");
      switch (a_axis) {
      case YMAP_XAXIS :
         DEBUG_MAP   yLOG_snote   ("x-axis");
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
         DEBUG_MAP   yLOG_schar   (*r_minor);
         break;
      case YMAP_YAXIS :
         DEBUG_MAP   yLOG_snote   ("y-axis");
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
         DEBUG_MAP   yLOG_schar   (*r_minor);
         break;
      default  :
         DEBUG_MAP   yLOG_snote   ("unknown axis");
         DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
         break;
      }
   }
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap__set_cur           (tyMAP *a_map, ushort a_pos)
{
   a_map->ucur = a_pos;
   a_map->gcur = a_map->map [a_map->ucur];
   ymap_update_ends (a_map);
   return 0;
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
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_spoint  (a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_sint    (a_count);
   --rce;  if (a_count <= 0) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(maxxed out)---------------------*/
   DEBUG_MAP   yLOG_sint    (a_map->ucur);
   DEBUG_MAP   yLOG_sint    (a_map->umax);
   --rce;  if (a_map->ucur >= a_map->umax) {
      DEBUG_MAP   yLOG_note    ("already max");
      a_map->ucur = a_map->umax;
      ymap_display (a_map);
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
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
      DEBUG_MAP   yLOG_note    ("bounce");
      a_map->ucur = a_map->umax;
      ymap_display (a_map);
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   a_map->ucur = i;
   ymap_display (a_map);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_spoint  (a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_sint    (a_count);
   --rce;  if (a_count >= 0) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(maxxed out)---------------------*/
   DEBUG_MAP   yLOG_sint    (a_map->ucur);
   DEBUG_MAP   yLOG_sint    (a_map->umin);
   --rce;  if (a_map->ucur <= a_map->umin) {
      DEBUG_MAP   yLOG_snote   ("already min");
      ymap__set_cur (a_map, a_map->umin);
      /*> a_map->ucur = a_map->umin;                                                  <* 
       *> a_map->gcur = a_map->grid.ref [a_map->map [a_map->ucur]];                   <*/
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
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
   DEBUG_MAP   yLOG_sint    (i);
   DEBUG_MAP   yLOG_sint    (c);
   /*---(handle bounce)------------------*/
   --rce;  if (i < a_map->umin) {
      if (c != a_count) {
         DEBUG_MAP   yLOG_snote   ("bounce");
         ymap__set_cur (a_map, a_map->umin);
         /*> a_map->ucur = a_map->umin;                                               <* 
          *> a_map->gcur = a_map->map [a_map->ucur];                                  <*/
         DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
         DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      i = a_map->umin;
   }
   /*---(save back)----------------------*/
   a_map->ucur = i;
   ymap_display (a_map);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_spoint  (a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(limits)-------------------------*/
   DEBUG_MAP   yLOG_sint    (a_unit);
   if (a_limit == 'y') {
      DEBUG_MAP   yLOG_snote   ("screen limited");
      if (a_unit < a_map->ubeg)  a_unit = a_map->ubeg;
      if (a_unit > a_map->uend)  a_unit = a_map->uend;
   } else {
      DEBUG_MAP   yLOG_snote   ("unlimited");
   }
   if (a_unit < a_map->umin)  a_unit = a_map->umin;
   if (a_unit > a_map->umax)  a_unit = a_map->umax;
   DEBUG_MAP   yLOG_sint    (a_unit);
   /*---(save back)----------------------*/
   a_map->ucur = a_unit;
   a_map->gcur = a_map->map [a_unit];
   ymap_display (a_map);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_grid_dest        (tyMAP *a_map, ushort a_grid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_spoint  (a_map);
   --rce;  if (a_map    == NULL) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (a_map->grid);
   --rce;  if (a_map->grid == NULL) {
      DEBUG_MAP    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(limits)-------------------------*/
   DEBUG_MAP   yLOG_sint    (a_grid);
   if (a_grid < a_map->gmin)    a_grid = a_map->gmin;
   if (a_grid > a_map->gmax)    a_grid = a_map->gmax;
   /*---(set current)--------------------*/
   a_map->gcur = a_grid;
   a_map->ucur = a_map->grid [a_grid].unit;
   ymap_display (a_map);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   DEBUG_MAP   yLOG_note    ("basic relative/absolute movements");
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_char    ("axis"      , a_map->axis);
   DEBUG_MAP   yLOG_char    ("a_minor"   , a_minor);
   --rce;  if (a_minor == 0) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_XAXIS && !yKEYS_is_horz_simple (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_YAXIS && !yKEYS_is_vert_simple (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_ZAXIS && !yKEYS_is_deep_simple (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ymap_office (a_map->axis, &a_minor);
   DEBUG_MAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(handle)-------------------------*/
   --rce;  switch (a_minor) {
   case '0' : case '~' : rc = ymap__grid_at   (a_map, 0    , '-');       break;
   case 'H' : case 'J' : rc = ymap__grid_down (a_map, -a_map->inc * 5);  break;
   case 'h' : case 'j' : rc = ymap__grid_down (a_map, -a_map->inc);      break;
   case 'l' : case 'k' : rc = ymap__grid_up   (a_map,  a_map->inc);      break;
   case 'L' : case 'K' : rc = ymap__grid_up   (a_map,  a_map->inc * 5);  break;
   case '$' : case '_' : rc = ymap__grid_at   (a_map, 65535, '-');       break;
   default  :
                         DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
                         return rce;
   }
   DEBUG_MAP   yLOG_value   ("result"    , rc);
   /*---(update)-------------------------*/
   ymap_display (a_map);
   ymap_visu_update ();
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rc);
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
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   DEBUG_MAP   yLOG_note    ("goto fixed location on screen");
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_char    ("axis"      , a_map->axis);
   DEBUG_MAP   yLOG_char    ("a_minor"   , a_minor);
   --rce;  if (a_minor == 0) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_XAXIS && !yKEYS_is_horz_goto   (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_YAXIS && !yKEYS_is_vert_goto   (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_ZAXIS && !yKEYS_is_deep_goto   (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ymap_corners ('g', a_map->axis, &a_minor);
   ymap_office  (a_map->axis, &a_minor);
   DEBUG_MAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(distances)----------------------*/
   x_beg  = a_map->ubeg;
   x_qtr  = (a_map->uavail / 4) - 1;
   x_haf  = (a_map->uavail / 2) - 1;
   x_ful  = a_map->uavail - 1;
   x_end  = a_map->uend;
   x_pos  = a_map->ucur - a_map->ubeg;
   /*---(handle)-------------------------*/
   /*> --rce;  switch (a_minor) {                                                      <* 
    *> case 'S' : case 'T' : rc = ymap__grid_at (a_map, x_beg - x_ful, '-');  break;   <* 
    *> case 'H' : case 'K' : rc = ymap__grid_at (a_map, x_beg - x_haf, '-');  break;   <* 
    *> case 's' : case 't' : rc = ymap__grid_at (a_map, x_beg        , 'y');  break;   <* 
    *> case 'h' : case 'k' : rc = ymap__grid_at (a_map, x_beg + x_qtr, 'y');  break;   <* 
    *> case 'c' : case 'm' : rc = ymap__grid_at (a_map, x_beg + x_haf, 'y');  break;   <* 
    *> case 'l' : case 'j' : rc = ymap__grid_at (a_map, x_end - x_qtr, 'y');  break;   <* 
    *> case 'e' : case 'b' : rc = ymap__grid_at (a_map, x_end        , 'y');  break;   <* 
    *> case 'L' : case 'J' : rc = ymap__grid_at (a_map, x_end + x_haf, '-');  break;   <* 
    *> case 'E' : case 'B' : rc = ymap__grid_at (a_map, x_end + x_ful, '-');  break;   <* 
    *> default  :                                                                      <* 
    *>                       DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);             <* 
    *>                       return rce;                                               <* 
    *> }                                                                               <*/
   --rce;  switch (a_minor) {
   case 'S' : case 'B' : rc = ymap__grid_at (a_map, x_beg - x_ful, '-');  break;
   case 'H' : case 'J' : rc = ymap__grid_at (a_map, x_beg - x_haf, '-');  break;
   case 's' : case 'b' : rc = ymap__grid_at (a_map, x_beg        , 'y');  break;
   case 'h' : case 'j' : rc = ymap__grid_at (a_map, x_beg + x_qtr, 'y');  break;
   case 'c' : case 'm' : rc = ymap__grid_at (a_map, x_beg + x_haf, 'y');  break;
   case 'l' : case 'k' : rc = ymap__grid_at (a_map, x_end - x_qtr, 'y');  break;
   case 'e' : case 't' : rc = ymap__grid_at (a_map, x_end        , 'y');  break;
   case 'L' : case 'K' : rc = ymap__grid_at (a_map, x_end + x_haf, '-');  break;
   case 'E' : case 'T' : rc = ymap__grid_at (a_map, x_end + x_ful, '-');  break;
   default  :
                         DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
                         return rce;
   }
   DEBUG_MAP   yLOG_value   ("result"    , rc);
   /*---(adjust)-------------------------*/
   if (strchr ("SHLE", a_minor) != NULL) {
      DEBUG_MAP   yLOG_note    ("maintain relative position on page moves");
      ymap__grid_at (a_map, a_map->ubeg + x_pos, '-');
   }
   ymap_visu_update ();
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rc);
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
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   DEBUG_MAP   yLOG_note    ("goto fixed location on screen");
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (a_map->map);
   --rce;  if (a_map->map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_char    ("axis"      , a_map->axis);
   DEBUG_MAP   yLOG_char    ("a_minor"   , a_minor);
   --rce;  if (a_minor == 0) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_XAXIS && !yKEYS_is_horz_scroll (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_YAXIS && !yKEYS_is_vert_scroll (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_ZAXIS && !yKEYS_is_deep_scroll (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ymap_office  (a_map->axis, &a_minor);
   ymap_corners ('z', a_map->axis, &a_minor);
   DEBUG_MAP   yLOG_char    ("a_minor"   , a_minor);
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
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(limits)-------------------------*/
   if (x_pos < a_map->umin)  x_pos = a_map->umin;
   if (x_pos > a_map->umax)  x_pos = a_map->umax;
   DEBUG_MAP   yLOG_value   ("x_pos"     , x_pos);
   /*---(find closest)-------------------*/
   x_up   = x_down = x_pos;
   ymap__align2left (a_map, &x_down);
   DEBUG_MAP   yLOG_value   ("x_down"    , x_down);
   ymap__align2next (a_map, &x_up  );
   DEBUG_MAP   yLOG_value   ("x_up"      , x_up);
   if ((x_pos - x_down) < (x_up - x_pos))  x_pos = x_down;
   else                                    x_pos = x_up;
   /*---(save back)----------------------*/
   a_map->ubeg = x_pos;
   DEBUG_MAP   yLOG_value   ("ubeg"      , a_map->ubeg);
   ymap_display (a_map);
   ymap_visu_update ();
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_ends               (tyMAP *a_map, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_grid      =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   DEBUG_MAP   yLOG_note    ("goto the end of content");
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_char    ("axis"      , a_map->axis);
   DEBUG_MAP   yLOG_char    ("a_minor"   , a_minor);
   --rce;  if (a_minor == 0) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_XAXIS && !yKEYS_is_horz_ends (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_YAXIS && !yKEYS_is_vert_ends (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->axis == YMAP_ZAXIS && !yKEYS_is_deep_ends (a_minor)) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ymap_office  (a_map->axis, &a_minor);
   ymap_corners ('e', a_map->axis, &a_minor);
   DEBUG_MAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(handle)-------------------------*/
   DEBUG_MAP   yLOG_value   ("gmin"      , a_map->gmin);
   DEBUG_MAP   yLOG_value   ("gamin"     , a_map->gamin);
   DEBUG_MAP   yLOG_value   ("glmin"     , a_map->glmin);
   DEBUG_MAP   yLOG_value   ("gprev"     , a_map->gprev);
   DEBUG_MAP   yLOG_value   ("gnext"     , a_map->gnext);
   DEBUG_MAP   yLOG_value   ("glmax"     , a_map->glmax);
   DEBUG_MAP   yLOG_value   ("gamax"     , a_map->gamax);
   DEBUG_MAP   yLOG_value   ("gmax"      , a_map->gmax);
   x_grid = a_map->gcur;
   switch (a_minor) {
   case 'S' : case 'T' : x_grid = a_map->gamin;     break;
   case 's' : case 't' : x_grid = a_map->glmin;     break;
   case 'h' : case 'k' : x_grid = a_map->gprev;     break;
   case 'c' : case 'm' : x_grid = a_map->gavg;      break;
   case 'C' : case 'M' : x_grid = a_map->gmid;      break;
   case 'l' : case 'j' : x_grid = a_map->gnext;     break;
   case 'e' : case 'b' : x_grid = a_map->glmax;     break;
   case 'E' : case 'B' : x_grid = a_map->gamax;     break;
   case 'x' : ymap_visu_locking ('x');              break;
   case 'y' : ymap_visu_locking ('y');              break;
   case '!' : ymap_visu_locking ('!');              break;
   case '*' : ymap_visu_locking ('*');              break;
   }
   /*---(limits)-------------------------*/
   if (x_grid < a_map->gmin)  x_grid = a_map->gmin;
   if (x_grid > a_map->gmax)  x_grid = a_map->gmax;
   /*---(outcome)------------------------*/
   DEBUG_MAP   yLOG_value   ("x_grid"    , x_grid);
   a_map->gcur = x_grid;
   a_map->ucur = a_map->grid [x_grid].unit;
   /*---(update)-------------------------*/
   ymap_display (a_map);
   ymap_visu_update ();
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_jump               (ushort u, ushort x, ushort y, ushort z)
{
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   /*---(check)--------------------------*/
   --rce;  if (ymap_valid  (u, x, y, z) < 0)  {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(change buffer, then remap)------*/
   DEBUG_MAP   yLOG_value   ("u"         , u);
   ymap_grid_dest (&g_umap, u);
   ymap_display   (&g_umap);
   ymap_remap     ();
   /*---(now change position)------------*/
   DEBUG_MAP   yLOG_value   ("x"         , x);
   ymap_grid_dest (&g_xmap, x);
   ymap_display   (&g_xmap);
   DEBUG_MAP   yLOG_value   ("y"         , y);
   ymap_grid_dest (&g_ymap, y);
   ymap_display   (&g_ymap);
   DEBUG_MAP   yLOG_value   ("z"         , z);
   ymap_grid_dest (&g_zmap, z);
   ymap_display   (&g_zmap);
   ymap_remap     ();
   /*---(update selection)---------------*/
   ymap_visu_update ();
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
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



/*====================------------------------------------====================*/
/*===----                     main axis drivers                        ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVERS_________o () { return; }

char
ymap_move_hmode         (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_char    ("a_major"   , a_major);
   DEBUG_USER   yLOG_char    ("a_minor"   , a_minor);
   /*---(multikey prefixes)--------------*/
   if (a_major == ' ') {
      DEBUG_USER   yLOG_note    ("checking for multikey prefix");
      if (ymap_visu_isdead () && yKEYS_is_multi_map  (a_minor)) {
         DEBUG_USER   yLOG_note    ("prefix of multimap keystring");
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return a_minor;
      }
      if (ymap_visu_islive () && yKEYS_is_multi_visu (a_minor)) {
         DEBUG_USER   yLOG_note    ("prefix of visual multimap keystring");
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return a_minor;
      }
   }
   /*---(simple)-------------------------*/
   if (a_major == ' ') {
      DEBUG_USER   yLOG_note    ("checking for simple");
      if (yKEYS_is_horz_simple (a_minor)) {
         rc = ymap_simple   (&g_xmap, a_minor);
         yMAP_refresh ();
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return rc;
      }
      if (yKEYS_is_vert_simple (a_minor)) {
         rc = ymap_simple   (&g_ymap, a_minor);
         yMAP_refresh ();
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return rc;
      }
      if (yKEYS_is_deep_simple (a_minor)) {
         rc = ymap_simple   (&g_zmap, a_minor);
         yMAP_refresh ();
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return rc;
      }
   }
   /*---(goto)---------------------------*/
   else if (a_major == 'g') {
      DEBUG_USER   yLOG_note    ("checking for goto");
      if (yKEYS_is_horz_goto   (a_minor)) {
         rc = ymap_goto     (&g_xmap, a_minor);
         ++c;
      }
      if (yKEYS_is_vert_goto   (a_minor)) {
         rc = ymap_goto     (&g_ymap, a_minor);
         ++c;
      }
      if (yKEYS_is_deep_goto   (a_minor)) {
         rc = ymap_goto     (&g_zmap, a_minor);
         ++c;
      }
      if (c > 0)  yMAP_refresh ();
      --rce;  if (c <= 0)  rc = rce;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(scroll)-------------------------*/
   else if (a_major == 'z') {
      DEBUG_USER   yLOG_note    ("checking for scroll");
      if (yKEYS_is_horz_scroll (a_minor)) {
         rc = ymap_scroll   (&g_xmap, a_minor);
         ++c;
      }
      if (yKEYS_is_vert_scroll (a_minor)) {
         rc = ymap_scroll   (&g_ymap, a_minor);
         ++c;
      }
      if (yKEYS_is_deep_scroll (a_minor)) {
         rc = ymap_scroll   (&g_zmap, a_minor);
         ++c;
      }
      if (c > 0)  yMAP_refresh ();
      --rce;  if (c <= 0)  rc = rce;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(ends)---------------------------*/
   else if (a_major == 'e') {
      DEBUG_USER   yLOG_note    ("checking for ends");
      if (yKEYS_is_horz_ends   (a_minor)) {
         rc = ymap_ends     (&g_xmap, a_minor);
         ++c;
      }
      if (yKEYS_is_vert_ends   (a_minor)) {
         rc = ymap_ends     (&g_ymap, a_minor);
         ++c;
      }
      if (yKEYS_is_deep_ends   (a_minor)) {
         rc = ymap_ends     (&g_zmap, a_minor);
         ++c;
      }
      if (c > 0)  yMAP_refresh ();
      --rce;  if (c <= 0)  rc = rce;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
   return 0;
}


