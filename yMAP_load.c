/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"



char
ymap__clear             (char a_full, tMAP *a_map, char a_which)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(identity)-----------------------*/
   DEBUG_MAP   yLOG_snote   ("self");
   if (a_full == 'y')  a_map->which = a_which;
   /*---(lefts)--------------------------*/
   DEBUG_MAP   yLOG_snote   ("mins");
   a_map->umin  = YMAP_EMPTY;
   a_map->gmin  = YMAP_EMPTY;
   a_map->gamin = YMAP_EMPTY;
   a_map->glmin = YMAP_EMPTY;
   a_map->gprev = YMAP_EMPTY;
   /*---(map)----------------------------*/
   DEBUG_MAP   yLOG_snote   ("map");
   for (i = 0; i < LEN_HUGE; ++i) {
      a_map->map [i] = YMAP_EMPTY;
   }
   /*---(rights)-------------------------*/
   DEBUG_MAP   yLOG_snote   ("maxs");
   a_map->umax  = YMAP_EMPTY;
   a_map->gmax  = YMAP_EMPTY;
   a_map->gamax = YMAP_EMPTY;
   a_map->glmax = YMAP_EMPTY;
   a_map->gnext = YMAP_EMPTY;
   /*---(indexes)------------------------*/
   DEBUG_MAP   yLOG_snote   ("screen");
   a_map->ubeg   = 0;
   a_map->ucur   = 0;
   a_map->uend   = 0;
   a_map->ulen   = 0;
   if (a_full == 'y')  a_map->uavail = 0;
   a_map->utend  = 0;
   /*---(grids)--------------------------*/
   DEBUG_MAP   yLOG_snote   ("grid");
   a_map->gbeg  = 0;
   a_map->gcur  = 0;
   a_map->gend  = 0;
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char  ymap_factory (tMAP *a_map, char a_which)  { return ymap__clear ('y', a_map, a_which); }
char  yMAP_clear   (tMAP *a_map)                { return ymap__clear ('-', a_map, '-'); }

char
ymap_load               (char a_style, tMAP *a_map)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   int         x_spot      =    0;
   /*---(clear)--------------------------*/
   yMAP_clear  (a_map);
   /*---(col/row setup)------------------*/
   if (a_style == 'f') {
      for (j =  0; j < 16; ++j)  a_map->map [x_spot++] = 1;
      for (j =  0; j <  7; ++j)  a_map->map [x_spot++] = 2;
      for (j =  0; j <  7; ++j)  a_map->map [x_spot++] = 3;
      for (j =  0; j <  2; ++j)  a_map->map [x_spot++] = 4;
      for (j =  0; j < 20; ++j)  a_map->map [x_spot++] = 5;
      for (j =  0; j <  6; ++j)  a_map->map [x_spot++] = 6;
      for (j =  0; j <  6; ++j)  a_map->map [x_spot++] = 7;
      for (j =  0; j <  2; ++j)  a_map->map [x_spot++] = 8;

   }
   else if (strchr ("uads", a_style) != NULL) {
      for (i = 0; i < 8; ++i) {
         switch (a_style) {
         case 'u' : /* uniform size grid       */
            for (j =  0; j <  8; ++j)  a_map->map [x_spot++] = i;
            break;
         case 'a' : /* ascending size grid     */
            for (j =  0; j <= i; ++j)  a_map->map [x_spot++] = i;
            break;
         case 'd' : /* descending size grid    */
            for (j =  0; j <= 7 - i; ++j)  a_map->map [x_spot++] = i;
            break;
         case 's' : /* small                   */
            for (j =  0; j <  3; ++j)  a_map->map [x_spot++] = i;
            break;
         }
      }
   } else if (a_style == '-') {  /* neg to pos grid        */
      for (i = -3; i <= 3; ++i) {
         for (j =  0; j <  8; ++j)  a_map->map [x_spot++] = i;
      }
   } else if (a_style == 'j') {   /* true grid the skips  */
      for (i = -120; i <= 300; i += 20) {
         a_map->map [x_spot++] = i;
      }
   } else if (a_style == 'w') {   /* get a big grid       */
      for (i = 0; i <= 40; ++i) {
         for (j =  0; j <  4; ++j)  a_map->map [x_spot++] = i;
      }
   } else if (a_style == '1') {
      for (i = 0; i <= 100; ++i)   a_map->map [x_spot++] = i;
   } else if (a_style == '0') {
      a_map->map [x_spot++] = 0;
   }
   /*---(unit min/max)-------------------*/
   a_map->umin  = 0;
   a_map->umax  = x_spot - 1;
   /*---(grid mins)----------------------*/
   a_map->gmin  = 0;
   a_map->gamin = 0;
   a_map->glmin = 0;
   a_map->gprev = 0;
   /*---(grid maxs)----------------------*/
   a_map->gnext = a_map->map [a_map->umax];
   a_map->glmax = a_map->map [a_map->umax];
   a_map->gamax = a_map->map [a_map->umax];
   a_map->gmax  = a_map->map [a_map->umax];
   /*---(final setup)--------------------*/
   switch (a_style) {
   case 'w' :
      a_map->ucur   = 44;
      a_map->ubeg   = 44;
      a_map->ulen   = 36;
      a_map->uend   = 79;
      a_map->uavail = 38;
      a_map->utend  = 81;
      break;
   case '1' :
      a_map->ucur   =  0;
      a_map->ubeg   =  0;
      a_map->ulen   = 30;
      a_map->uend   = 29;
      a_map->uavail = 30;
      a_map->utend  = 29;
      break;
   default  :
      a_map->ucur   = 0;
      a_map->ubeg   = 0;
      a_map->ulen   = x_spot;
      a_map->uend   = x_spot - 1;
      a_map->uavail = x_spot;
      a_map->utend  = x_spot - 1;
      break;
   }
   a_map->gbeg  = a_map->map [a_map->ubeg];
   a_map->gcur  = a_map->map [a_map->ucur];
   a_map->gend  = a_map->map [a_map->uend];
   /*> yvikeys__map_print  (a_map);                                                           <*/
   /*---(complete)-----------------------*/
   return 0;
}
