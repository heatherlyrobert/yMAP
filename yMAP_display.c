/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"



/*====================------------------------------------====================*/
/*===----                     aligning inside grid                     ----===*/
/*====================------------------------------------====================*/
static void  o___ALIGN___________o () { return; }

char
ymap__align2left        (tyMAP *a_map, ushort *a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   ushort      x_curr      =    0;
   ushort      x_prev      =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_map      == NULL)         return rce;
   --rce;  if (a_map->map == NULL)         return rce;
   --rce;  if (a_pos      == NULL)         return rce;
   /*---(limits)-------------------------*/
   if (*a_pos < a_map->umin)   *a_pos = a_map->umin;
   if (*a_pos > a_map->umax)   *a_pos = a_map->umax;
   /*---(walk down)----------------------*/
   for (i = *a_pos; i > a_map->umin; --i) {
      if (i > 0)  x_prev       = a_map->map [i - 1];
      else        x_prev       = YMAP_MAX;
      x_curr       = a_map->map [i    ];
      if (x_curr != x_prev)   break;
   }
   /*---(save)---------------------------*/
   *a_pos = i;
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap__align2right       (tyMAP *a_map, ushort *a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   ushort      x_curr      =    0;
   ushort      x_next      =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_map      == NULL)         return rce;
   --rce;  if (a_map->map == NULL)         return rce;
   --rce;  if (a_pos      == NULL)         return rce;
   /*---(limits)-------------------------*/
   if (*a_pos < a_map->umin)   *a_pos = a_map->umin;
   if (*a_pos > a_map->umax)   *a_pos = a_map->umax;
   /*---(walk up)------------------------*/
   for (i = *a_pos; i < a_map->umax; ++i) {
      x_curr       = a_map->map [i    ];
      x_next       = a_map->map [i + 1];
      if (x_curr != x_next)   break;
   }
   /*---(save)---------------------------*/
   *a_pos = i;
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap__align2next        (tyMAP *a_map, ushort *a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   ushort      x_curr      =    0;
   ushort      x_prev      =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_map      == NULL)         return rce;
   --rce;  if (a_map->map == NULL)         return rce;
   --rce;  if (a_pos      == NULL)         return rce;
   /*---(limits)-------------------------*/
   if (*a_pos < a_map->umin)   *a_pos = a_map->umin;
   if (*a_pos > a_map->umax)   *a_pos = a_map->umax;
   /*---(walk up)------------------------*/
   for (i = *a_pos; i < a_map->umax; ++i) {
      if (i > 0)  x_prev       = a_map->map [i - 1];
      else        x_prev       = YMAP_MAX;
      x_curr       = a_map->map [i    ];
      if (x_curr != x_prev)   break;
   }
   /*---(save)---------------------------*/
   *a_pos = i;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     aligning inside screen                   ----===*/
/*====================------------------------------------====================*/
static void  o___SCREEN__________o () { return; }

char
ymap_update_ends        (tyMAP *a_map)
{  /*---(design notes)-------------------*/
   /*
    *   forward
    *      '·'       then do to next 'Ï'
    *      'Ï' '·'   then go to next 'Ï'
    *
    *
    *
    */
   int         i        =    0;
   uchar       c        =  '·';
   uchar       n        =  '·';
   uchar       t        =  '·';
   /*---(previous)-----------------------*/
   a_map->gprev = 0;
   if (a_map->gcur > 0) {
      c = a_map->grid [a_map->gcur    ].used;
      n = a_map->grid [a_map->gcur - 1].used;
      if      (c == G_CHAR_SPACE)                         t = G_CHAR_HUGEDOT;
      else if (c == G_CHAR_HUGEDOT && n == G_CHAR_SPACE)  t = G_CHAR_HUGEDOT;
      else                                                t = G_CHAR_SPACE;
      for (i = a_map->gcur - 1; i >= 0; --i) {
         if (a_map->grid [i].ref == YMAP_EMPTY)  break;
         c = a_map->grid [i].used;
         if (t ==  G_CHAR_SPACE)  a_map->gprev = i + 1;
         else                     a_map->gprev = i;
         if (c == t)  break;
      }
   }
   /*---(next)---------------------------*/
   a_map->gnext = a_map->gmax;
   if (a_map->gcur < a_map->gmax) {
      c = a_map->grid [a_map->gcur    ].used;
      n = a_map->grid [a_map->gcur + 1].used;
      if      (c == G_CHAR_SPACE)                         t = G_CHAR_HUGEDOT;
      else if (c == G_CHAR_HUGEDOT && n == G_CHAR_SPACE)  t = G_CHAR_HUGEDOT;
      else                                                t = G_CHAR_SPACE;
      for (i = a_map->gcur + 1; i < a_map->glen; ++i) {
         if (a_map->grid [i].ref == YMAP_EMPTY)  break;
         c = a_map->grid [i].used;
         if (t ==  G_CHAR_SPACE)  a_map->gnext = i - 1;
         else                     a_map->gnext = i;
         if (c == t)  break;
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap_update_grid        (tyMAP *a_map)
{
   a_map->ulen  = a_map->uend - a_map->ubeg + 1;
   a_map->gbeg = a_map->map [a_map->ubeg];
   a_map->gcur = a_map->map [a_map->ucur];
   a_map->gend = a_map->map [a_map->uend];
   ymap_update_ends (a_map);
   return 0;
}

char
ymap_no_display         (tyMAP *a_map)
{
   a_map->ubeg = a_map->uend = a_map->ulen = a_map->utend = 0;
   return 0;
}

char
ymap__screen_small      (tyMAP *a_map)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_spoint  (a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_value   ("uavail"    , a_map->uavail);
   --rce;  if (a_map->uavail <= 0) {
      ymap_no_display (a_map);
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->umax >= a_map->uavail) {
      DEBUG_MAP   yLOG_note    ("not a small format!!!");
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(limits)-------------------------*/
   if (a_map->ucur  > YMAP_MAX)    { a_map->ucur = a_map->umin; rc = 1; }
   if (a_map->ucur  < a_map->umin) { a_map->ucur = a_map->umin; rc = 2; }
   if (a_map->ucur  > a_map->umax) { a_map->ucur = a_map->umax; rc = 3; }
   DEBUG_MAP   yLOG_value   ("limits"    , rc);
   /*---(updates)------------------------*/
   a_map->ubeg   = a_map->umin;
   a_map->uend   = a_map->umax;
   a_map->utend  = a_map->umax;
   ymap_update_grid (a_map);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rc);
   return rc;
}

char         /*-> arrange screen from beg position ---[ ------ [gc.D44.233.C7]*/ /*-[02.0000.111.R]-*/ /*-[--.---.---.--]-*/
ymap__screen_beg        (tyMAP *a_map)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   ushort      x_curr      =    0;
   ushort      x_next      =    0;
   int         x_tend      =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_value   ("uavail"    , a_map->uavail);
   --rce;  if (a_map->uavail <= 0) {
      ymap_no_display (a_map);
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->umax <  a_map->uavail) {
      DEBUG_MAP   yLOG_note    ("must use small format!!!");
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(limits)-------------------------*/
   if (a_map->ubeg  > YMAP_MAX)    { a_map->ubeg = a_map->umin; rc = 1; }
   if (a_map->ubeg  < a_map->umin) { a_map->ubeg = a_map->umin; rc = 2; }
   if (a_map->ubeg  > a_map->umax) { a_map->ubeg = a_map->umax; rc = 3; }
   DEBUG_MAP   yLOG_value   ("limits"    , rc);
   /*---(align beg with grid)------------*/
   ymap__align2left  (a_map, &(a_map->ubeg));
   DEBUG_MAP   yLOG_value   ("ubeg"      , a_map->ubeg);
   /*---(calculate end)------------------*/
   x_tend = a_map->ubeg + a_map->uavail - 1;
   DEBUG_MAP   yLOG_value   ("x_tend"    , x_tend);
   DEBUG_MAP   yLOG_value   ("umax"      , a_map->umax);
   /*---(can not fill screen)------------*/
   if (x_tend > a_map->umax) {
      DEBUG_MAP   yLOG_note    ("can not fill screen from here");
      a_map->ubeg = a_map->umax - a_map->uavail + 1;
      DEBUG_MAP   yLOG_value   ("farthest"  , a_map->ubeg);
      ymap__align2next (a_map, &(a_map->ubeg));
      DEBUG_MAP   yLOG_value   ("fixed"     , a_map->ubeg);
      x_tend = a_map->umax;
      DEBUG_MAP   yLOG_value   ("x_tend"    , x_tend);
   }
   a_map->utend  = x_tend;
   /*---(find end of last full grid)-----*/
   for (i = a_map->utend; i >= a_map->umin; --i) {
      a_map->uend   = i;
      x_curr       = a_map->map [i    ];
      x_next       = a_map->map [i + 1];
      if (x_curr != x_next)   break;
   }
   DEBUG_MAP   yLOG_value   ("ubeg"       , a_map->ubeg);
   DEBUG_MAP   yLOG_value   ("uend"       , a_map->uend);
   DEBUG_MAP   yLOG_value   ("ucur"       , a_map->ucur);
   /*---(trouble with cur)---------------*/
   while (a_map->ucur > a_map->uend) {
      DEBUG_MAP   yLOG_note    ("gotta reword");
      ++(a_map->ubeg);
      ymap__align2next (a_map, &(a_map->ubeg));
      DEBUG_MAP   yLOG_value   ("ubeg"       , a_map->ubeg);
      x_tend = a_map->ubeg + a_map->uavail - 1;
      a_map->utend  = x_tend;
      for (i = a_map->utend; i >= a_map->umin; --i) {
         a_map->uend   = i;
         x_curr       = a_map->map [i    ];
         x_next       = a_map->map [i + 1];
         if (x_curr != x_next)   break;
      }
      DEBUG_MAP   yLOG_value   ("uend"       , a_map->uend);
   }
   /*---(updates)------------------------*/
   ymap_update_grid (a_map);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}

char
ymap__screen_end        (tyMAP *a_map)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_value   ("uavail"    , a_map->uavail);
   --rce;  if (a_map->uavail <= 0) {
      ymap_no_display (a_map);
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->umax <  a_map->uavail) {
      DEBUG_MAP   yLOG_note    ("must use small format!!!");
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(limits)-------------------------*/
   if (a_map->utend > YMAP_MAX)    { a_map->utend = a_map->umin; rc = 1; }
   if (a_map->utend < a_map->umin) { a_map->utend = a_map->umin; rc = 2; }
   if (a_map->utend > a_map->umax) { a_map->utend = a_map->umax; rc = 3; }
   DEBUG_MAP   yLOG_value   ("limits"    , rc);
   /*---(align beg with grid)------------*/
   ymap__align2right (a_map, &(a_map->utend));
   DEBUG_MAP   yLOG_value   ("utend"     , a_map->utend);
   /*---(run the final)------------------*/
   if (a_map->utend <= a_map->uavail)  a_map->ubeg = 0;
   else                                a_map->ubeg = a_map->utend - a_map->uavail + 1;
   DEBUG_MAP   yLOG_value   ("farthest"  , a_map->ubeg);
   ymap__align2next (a_map, &(a_map->ubeg));
   DEBUG_MAP   yLOG_value   ("fixed"     , a_map->ubeg);
   /*---(handle normally)----------------*/
   rc = ymap__screen_beg (a_map);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                   unit testing support                       ----===*/
/*====================------------------------------------====================*/
static void  o___DISPLAY_________o () { return; }

char
ymap_display            (tyMAP *a_map)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP   yLOG_point   ("a_map"     , a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_map->map == NULL) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(screen fits all)----------------*/
   if (a_map->umax - a_map->umin <  a_map->uavail) {
      DEBUG_MAP   yLOG_note    ("small format, all content fits");
      rc = ymap__screen_small  (a_map);
   }
   /*---(from beginning)-----------------*/
   else if (a_map->ucur < a_map->ubeg) {
      DEBUG_MAP   yLOG_note    ("map from beginning");
      a_map->ubeg  = a_map->ucur;
      rc = ymap__screen_beg (a_map);
   }
   /*---(from ending)--------------------*/
   else if (a_map->ucur > a_map->uend) {
      DEBUG_MAP   yLOG_note    ("map from ending");
      a_map->utend = a_map->ucur;
      rc = ymap__screen_end (a_map);
   }
   /*---(just a refresh)-----------------*/
   else {
      DEBUG_MAP   yLOG_note    ("just a refresh");
      rc = ymap__screen_beg (a_map);
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
   return rc;
}


