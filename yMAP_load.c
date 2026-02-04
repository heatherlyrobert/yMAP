/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2010 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might "    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



#define     YMAP_VALID     "°Ï´·<>|"
#define     YMAP_LIMITS    "<>|"
#define     YMAP_REAL      "°Ï´"


char        g_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                       small support                          ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
ymap_grid_set           (uchar a_axis, tyMAP *a_map, tGRID *a_grid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(map)----------------------------*/
   DEBUG_YMAP   yLOG_schar   (a_axis);
   DEBUG_YMAP   yLOG_spoint  (a_grid);
   --rce;  switch (a_axis) {
   case  YMAP_UNIV  :
      DEBUG_YMAP    yLOG_snote   ("store in b");
      DEBUG_YMAP    yLOG_spoint  (g_ugrid);
      if (g_ugrid != NULL)  ymap_grid_free ('-', a_axis);
      g_ugrid     = a_grid;
      a_map->grid = a_grid;
      DEBUG_YMAP    yLOG_spoint  (g_ugrid);
      break;
   case  YMAP_XAXIS  :
      DEBUG_YMAP    yLOG_snote   ("store in x");
      DEBUG_YMAP    yLOG_spoint  (g_xgrid);
      if (g_xgrid != NULL)  ymap_grid_free ('-', a_axis);
      g_xgrid     = a_grid;
      a_map->grid = a_grid;
      DEBUG_YMAP    yLOG_spoint  (g_xgrid);
      break;
   case  YMAP_YAXIS  :
      DEBUG_YMAP    yLOG_snote   ("store in y");
      DEBUG_YMAP    yLOG_spoint  (g_ygrid);
      if (g_ygrid != NULL)  ymap_grid_free ('-', a_axis);
      g_ygrid     = a_grid;
      a_map->grid = a_grid;
      DEBUG_YMAP    yLOG_spoint  (g_ygrid);
      break;
   case  YMAP_ZAXIS  :
      DEBUG_YMAP    yLOG_snote   ("store in z");
      DEBUG_YMAP    yLOG_spoint  (g_zgrid);
      if (g_zgrid != NULL)  ymap_grid_free ('-', a_axis);
      g_zgrid     = a_grid;
      a_map->grid = a_grid;
      DEBUG_YMAP    yLOG_spoint  (g_zgrid);
      break;
   case  YMAP_WHEN  :
      DEBUG_YMAP    yLOG_snote   ("store in w");
      DEBUG_YMAP    yLOG_spoint  (g_wgrid);
      if (g_wgrid != NULL)  ymap_grid_free ('-', a_axis);
      g_wgrid     = a_grid;
      a_map->grid = a_grid;
      DEBUG_YMAP    yLOG_spoint  (g_wgrid);
      break;
   default  :
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_grid_clear         (tGRID *a_grid, ushort a_len)
{
   int         i           =    0;
   if (a_grid == NULL)  return -1;
   for (i = 0; i < a_len; ++i) {
      a_grid [i].g_ref  = YMAP_EMPTY;
      a_grid [i].g_wide = 0;
      a_grid [i].g_used = YMAP_NADA;
      a_grid [i].g_unit = 0;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       small support                          ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
ymap_grid_free          (uchar a_full, uchar a_axis)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(map)----------------------------*/
   DEBUG_YMAP   yLOG_schar   (a_axis);
   switch (a_axis) {
   case YMAP_UNIV :
      DEBUG_YMAP    yLOG_snote   ("free b");
      DEBUG_YMAP    yLOG_spoint  (g_ugrid);
      if (a_full != 'I' && g_ugrid != NULL) {
         /*> printf ("freeing grid\n");                                               <*/
         DEBUG_YMAP   yLOG_snote   ("freeing");
         free (g_ugrid);
      }
      g_umap.grid = g_ugrid = NULL;
      DEBUG_YMAP    yLOG_spoint  (g_ugrid);
      break;
   case YMAP_XAXIS :
      DEBUG_YMAP    yLOG_snote   ("free x");
      DEBUG_YMAP    yLOG_spoint  (g_xgrid);
      if (a_full != 'I' && g_xgrid != NULL) {
         /*> printf ("freeing grid\n");                                               <*/
         DEBUG_YMAP   yLOG_snote   ("freeing");
         free (g_xgrid);
      }
      g_xmap.grid = g_xgrid = NULL;
      DEBUG_YMAP    yLOG_spoint  (g_xgrid);
      break;
   case YMAP_YAXIS :
      DEBUG_YMAP    yLOG_snote   ("free y");
      DEBUG_YMAP    yLOG_spoint  (g_ygrid);
      if (a_full != 'I' && g_ygrid != NULL) {
         /*> printf ("freeing grid\n");                                               <*/
         DEBUG_YMAP   yLOG_snote   ("freeing");
         free (g_ygrid);
      }
      g_ymap.grid = g_ygrid = NULL;
      DEBUG_YMAP    yLOG_spoint  (g_ygrid);
      break;
   case YMAP_ZAXIS :
      DEBUG_YMAP    yLOG_snote   ("free z");
      DEBUG_YMAP    yLOG_spoint  (g_zgrid);
      if (a_full != 'I' && g_zgrid != NULL) {
         /*> printf ("freeing grid\n");                                               <*/
         DEBUG_YMAP   yLOG_snote   ("freeing");
         free (g_zgrid);
      }
      g_zmap.grid = g_zgrid = NULL;
      DEBUG_YMAP    yLOG_spoint  (g_zgrid);
      break;
   case YMAP_WHEN :
      DEBUG_YMAP    yLOG_snote   ("free w");
      DEBUG_YMAP    yLOG_spoint  (g_wgrid);
      if (a_full != 'I' && g_wgrid != NULL) {
         /*> printf ("freeing grid\n");                                               <*/
         DEBUG_YMAP   yLOG_snote   ("freeing");
         free (g_wgrid);
      }
      g_wmap.grid = g_wgrid = NULL;
      DEBUG_YMAP    yLOG_spoint  (g_wgrid);
      break;
   default  :
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      clearing                                ----===*/
/*====================------------------------------------====================*/
static void  o___CLEAR___________o () { return; }

char
ymap__clear             (uchar a_full, uchar a_axis)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_full"    , a_full);
   --rce;  if (a_full == 0 || strchr ("Iy-", a_full) == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(identity)-----------------------*/
   DEBUG_YMAP   yLOG_note    ("self");
   if (a_full != '-') {
      x_map->axis  = a_axis;
      x_map->inc   = 1;
   }
   x_map->change = YMAP_SKIP;
   /*---(identity)-----------------------*/
   if (a_full == 'I') {
      DEBUG_YMAP   yLOG_note    ("grid initialize");
      x_map->glen  = 0;
      ymap_grid_free (a_full, a_axis);
   } else if (a_full == 'y') {
      DEBUG_YMAP   yLOG_note    ("grid removal");
      x_map->glen      = 0;
      ymap_grid_free (a_full, a_axis);
   } else {
      DEBUG_YMAP   yLOG_note    ("grid cleaning");
      ymap_grid_clear (x_grid, x_map->glen);
   }
   x_map->gused = 0;
   /*---(lefts)--------------------------*/
   DEBUG_YMAP   yLOG_note    ("mins");
   x_map->umin  = 0;
   x_map->gmin  = 0;
   x_map->gamin = 0;
   x_map->glmin = 0;
   x_map->gprev = 0;
   x_map->gpuse = 0;
   /*---(map)----------------------------*/
   DEBUG_YMAP   yLOG_note    ("map");
   if (a_full == 'I') {
      x_map->mlen     = 0;
      x_map->map      = NULL;
   } else {
      x_map->mlen     = 0;
      if (x_map->map  != NULL) {
         DEBUG_YMAP   yLOG_note    ("freeing map");
         /*> printf ("freeing map\n");                                                <*/
         free (x_map->map );
      }
      x_map->map      = NULL;
   }
   /*---(middles)------------------------*/
   DEBUG_YMAP   yLOG_note    ("mids");
   x_map->gmid  = 0;
   x_map->gavg  = 0;
   /*---(rights)-------------------------*/
   DEBUG_YMAP   yLOG_note    ("maxs");
   x_map->umax  = 0;
   x_map->gmax  = 0;
   x_map->gamax = 0;
   x_map->glmax = 0;
   x_map->gnext = 0;
   x_map->gnuse = 0;
   /*---(indexes)------------------------*/
   if (a_full == 'I') {
      DEBUG_YMAP   yLOG_note    ("screen");
      x_map->ubeg  = 0;
      x_map->ucur  = 0;
      x_map->uend  = 0;
      x_map->ulen  = 0;
      x_map->utend = 0;
   }
   if (a_full == 'I')  x_map->uavail = 0;
   /*---(grids)--------------------------*/
   if (a_full == 'I') {
      DEBUG_YMAP   yLOG_note    ("grid");
      x_map->gbeg  = 0;
      x_map->gcur  = 0;
      x_map->gend  = 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char  ymap_mapinit (uchar a_axis)  { return ymap__clear ('I', a_axis); }
char  ymap_factory (uchar a_axis)  { return ymap__clear ('y', a_axis); }
char  yMAP_clear   (uchar a_axis)  { return ymap__clear ('-', a_axis); }



/*====================------------------------------------====================*/
/*===----                      size setting                            ----===*/
/*====================------------------------------------====================*/
static void  o___SIZE____________o () { return; }

char
yMAP_size               (uchar a_axis, ushort a_len)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_tries     =    0;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   tGRID      *x_new       = NULL;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   DEBUG_YMAP   yLOG_value   ("pickmap"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(increment length)---------------*/
   ++a_len;  /* add sentinel */
   /*---(check)--------------------------*/
   DEBUG_YMAP   yLOG_point   ("x_map"     , x_map);
   DEBUG_YMAP   yLOG_point   ("x_grid"    , x_grid);
   if (x_grid != NULL && x_map->glen == a_len) {
      rc = yMAP_clear   (a_axis);
      DEBUG_YMAP   yLOG_note    ("already right length, just cleared");
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_YMAP   yLOG_note    ("new grid size");
   /*---(clear)--------------------------*/
   rc = ymap_factory (a_axis);
   DEBUG_YMAP   yLOG_value   ("factory"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_value   ("a_len"     , a_len);
   if (a_len == 0) {
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(allocate grid)------------------*/
   DEBUG_YMAP    yLOG_note    ("allocate");
   while (x_new == NULL && x_tries < 10)  {
      ++x_tries;
      x_new = (tGRID *) malloc (sizeof (tGRID) * a_len);
   }
   DEBUG_YMAP    yLOG_value   ("x_tries"   , x_tries);
   DEBUG_YMAP    yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear new grid)-----------------*/
   ymap_grid_clear (x_new, a_len);
   /*---(save back)----------------------*/
   ymap_grid_set   (a_axis, x_map, x_new);
   DEBUG_YMAP   yLOG_complex ("assign"    , "%c, b%-10p, x%-10p, y%-10p, z%-10p, t%-10p", a_axis, g_ugrid, g_xgrid, g_ygrid, g_zgrid, g_wgrid);
   x_map->glen    = a_len;
   /*---(show)---------------------------*/
   DEBUG_YMAP    yLOG_value   ("glen"      , x_map->glen);
   /*> for (i = 0; i < x_map->glen; ++i) {                                                                                  <* 
    *>    DEBUG_YMAP   yLOG_complex ("auditing"  , "%3d, %6d, %2d, %c", i, x_new [i].g_ref, x_new [i].g_wide, x_new [i].g_used);   <* 
    *> }                                                                                                                    <*/
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_allsize            (ushort u, ushort x, ushort y, ushort z, ushort w)
{
   char        rc          =    0;
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   if (rc >= 0)  rc = yMAP_size (YMAP_UNIV , u);
   if (rc >= 0)  rc = yMAP_size (YMAP_XAXIS, x);
   if (rc >= 0)  rc = yMAP_size (YMAP_YAXIS, y);
   if (rc >= 0)  rc = yMAP_size (YMAP_ZAXIS, z);
   if (rc >= 0)  rc = yMAP_size (YMAP_WHEN , w);
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                       adding entries                         ----===*/
/*====================------------------------------------====================*/
static void  o___ADDING__________o () { return; }

char
yMAP_entry              (uchar a_axis, ushort n, short a_ref, uchar a_wide, uchar a_used)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   DEBUG_YMAP   yLOG_value   ("pickmap"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_map"     , x_map);
   DEBUG_YMAP   yLOG_point   ("x_grid"    , x_grid);
   /*---(check)--------------------------*/
   DEBUG_YMAP   yLOG_value   ("n"         , n);
   DEBUG_YMAP   yLOG_value   ("glen"      , x_map->glen);
   --rce;  if (n >= x_map->glen - 1) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   if (a_ref  > -32000) x_grid [n].g_ref  = a_ref;
   if (a_wide != 255)   x_grid [n].g_wide = a_wide;
   if (a_used != 255) {
      DEBUG_YMAP   yLOG_complex ("a_used"    , "%3d/%c, %s", a_used, a_used, YMAP_VALID);
      /*---(translate)-------------------*/
      if (a_used == ' ')                                        a_used = YMAP_NADA;
      if (a_used == 'y')                                        a_used = YMAP_USED;
      if (a_used == 0 || strchr (YMAP_VALID, a_used) == NULL)   a_used = YMAP_NADA;
      /*---(update grid)-----------------*/
      x_grid [n].g_used = a_used;
      /*---(done)------------------------*/
   }
   DEBUG_YMAP   yLOG_complex ("change"    , "%3d, %6d, %3d, %c", n, x_grid [n].g_ref, x_grid [n].g_wide, x_grid [n].g_used);
   /*---(prepare update)-----------------*/
   ymap_change (x_map->axis, YMAP_POS);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

static uchar  s_axis = '-';
static ushort s_unit = 0;

char
yMAP_start              (uchar a_axis, ushort a_len)
{
   char        rc          =    0;
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_complex ("args"      , "%c %d", a_axis, a_len);
   rc = yMAP_size  (a_axis, a_len);
   if (rc >= 0) {
      s_axis = a_axis;
      s_unit = 0;
   }
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yMAP_append             (short a_ref, uchar a_wide, uchar a_used)
{
   char        rc          =    0;
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_complex ("args"      , "%4d %3d %c", a_ref, a_wide, a_used);
   rc = yMAP_entry (s_axis, s_unit, a_ref, a_wide, a_used);
   if (rc >= 0)  ++s_unit;
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yMAP_finish             (void)
{
   char        rc          =    0;
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   rc = ymap_update_large (s_axis);
   if (rc >= 0)  rc = ymap_update_small (s_axis);
   s_axis = '-';
   s_unit = 0;
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        calculating                           ----===*/
/*====================------------------------------------====================*/
static void  o___CALC____________o () { return; }

char
ymap__load_limits       (tyMAP *a_map, ushort a_umin, ushort a_umax)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         i           =    0;          /* grid index                     */
   int         x_used      =    0;
   int         x_sum       =    0;
   ushort      x_min, x_max;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_spoint  ( a_map);
   --rce;  if (a_map == NULL) {
      DEBUG_YMAP    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (a_map->grid);
   --rce;  if (a_map->grid == NULL) {
      DEBUG_YMAP    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(temp values)--------------------*/
   a_map->umin  = a_map->umax  = a_map->gmid  = a_map->gavg  = 0;
   a_map->glmin = 65001;
   a_map->glmax = 0;
   /*---(run grid)-----------------------*/
   DEBUG_YMAP    yLOG_sint    (a_map->glen);
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   for (i = 0; i < a_map->glen; ++i) {
      /*---(filter)----------------------*/
      DEBUG_YMAP    yLOG_sint    (i);
      if (a_map->grid [i].g_ref == YMAP_EMPTY)  break;
      /*---(accum units)-----------------*/
      x_len += a_map->grid [i].g_wide;
      /*---(full min/max)----------------*/
      if (i == 0) a_map->gmin  = i;
      if (x_len > 0)  a_map->umax  = x_len - 1;
      a_map->gmax  = i;
      /*---(absolute min/max)------------*/
      if (strchr (YMAP_LIMITS, a_map->grid [i].g_used) != NULL) {
         DEBUG_YMAP    yLOG_snote   ("limit");
         a_map->grid [i].g_used = YMAP_NADA;
      }
      /*---(local min/max)---------------*/
      if (strchr (YMAP_REAL, a_map->grid [i].g_used) != NULL) {
         if (a_map->glmin > 65000)  a_map->glmin = i;
         a_map->glmax = i;
         ++x_used;
         x_sum += i;
      }
      /*---(done)------------------------*/
   }
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   DEBUG_YMAP    yLOG_sint    (x_len);
   /*---(clean-up)-----------------------*/
   a_map->gused = x_used;
   if (x_used > 0)  a_map->gavg = x_sum / x_used;
   else             a_map->gavg = a_map->gcur;
   if (a_map->glmin > 65000)  a_map->glmin = a_map->gcur;
   if (a_map->glmax == 0 && a_map->grid [0].g_used == YMAP_NADA)  a_map->glmax = a_map->gcur;
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   /*---(absolute)-----------------------*/
   DEBUG_YMAP    yLOG_sint    (a_umin);
   DEBUG_YMAP    yLOG_sint    (a_umax);
   DEBUG_YMAP    yLOG_sint    (a_map->gamax);
   a_map->gamin = a_map->glmin;
   if (a_umin <= a_map->gmax && a_umin < a_map->glmin) {
      DEBUG_YMAP    yLOG_snote   ("gamin");
      a_map->gamin = a_umin;
      if (a_map->grid [a_umin].g_used == YMAP_NADA) a_map->grid [a_umin].g_used = YMAP_LOWER;
   }
   a_map->gamax = a_map->glmax;
   if (a_umax <= a_map->gmax && a_umax > a_map->glmax) {
      DEBUG_YMAP    yLOG_snote   ("gamax");
      a_map->gamax = a_umax;
      if (a_map->grid [a_umax].g_used == YMAP_NADA) a_map->grid [a_umax].g_used = YMAP_UPPER;
   }
   a_map->gmid = (a_umin + a_umax) / 2;
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap__load_ends_prep    (tyMAP *a_map, char a_dir, tGRID **r_grid, ushort *r_cur, char *r_inc, ushort **r_end, ushort **r_use)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =    0;
   /*---(header)-------------------------*/
   --rce;  if (a_map  == NULL)  return rce;
   --rce;  if (a_dir  == 0   )  return rce;
   --rce;  if (r_grid == NULL)  return rce;
   --rce;  if (r_end  == NULL)  return rce;
   --rce;  if (r_use  == NULL)  return rce;
   /*---(quick-out)----------------------*/
   if (a_map->gmax <= 0)                       return 0;   /* empty grid layout            */
   /*---(save grid)----------------------*/
   *r_grid = a_map->grid;
   --rce;  if (*r_grid == NULL) return rce;
   /*---(handle current)-----------------*/
   *r_cur  = a_map->gcur;
   if (a_dir == '<' && *r_cur <= 0)            return 0;   /* already hit bottom going down */
   if (a_dir == '>' && *r_cur >= a_map->gmax)  return 0;   /* already hit top going up      */
   /*---(handle saving pointers)---------*/
   switch (a_dir) {
   case '<'  : *r_inc = -1; *r_end = &(a_map->gprev); *r_use = &(a_map->gpuse); break;
   case '>'  : *r_inc =  1; *r_end = &(a_map->gnext); *r_use = &(a_map->gnuse); break;
   default   : return rce;                                                     break;
   }
   /*---(default)------------------------*/
   **r_end = **r_use = *r_cur;
   /*---(complete)-----------------------*/
   return 1;
}

char
ymap__load_ends         (tyMAP *a_map, char a_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =    0;
   char        rc          =    0;
   tGRID      *x_grid      = NULL;
   ushort      x_cur, i;
   ushort     *x_end, *x_use;
   uchar       c, n, t;
   char        x_inc;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ymap__load_ends_prep (a_map, a_dir, &x_grid, &x_cur, &x_inc, &x_end, &x_use);
   DEBUG_YMAP   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (rc == 0) {
      DEBUG_YMAP   yLOG_snote   ("nothing to do");
      DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   c = x_grid [x_cur        ].g_used;
   DEBUG_YMAP   yLOG_schar   (c);
   n = x_grid [x_cur + x_inc].g_used;
   DEBUG_YMAP   yLOG_schar   (n);
   /*---(target use)---------------------*/
   if      (c == YMAP_NADA)                    t = YMAP_USED;
   else if (c != YMAP_NADA && n == YMAP_NADA)  t = YMAP_USED;
   else                                        t = YMAP_NADA;
   DEBUG_YMAP   yLOG_schar   (t);
   DEBUG_YMAP   yLOG_sint    (*x_end);
   DEBUG_YMAP   yLOG_sint    (*x_use);
   /*---(walk)---------------------------*/
   for (i = x_cur + x_inc; i >= 0 && i <= a_map->gmax; i += x_inc) {
      /*---(filter)----------------------*/
      DEBUG_YMAP   yLOG_sint    (i);
      if (x_grid [i].g_ref == YMAP_EMPTY)  break;
      /*---(prepare)---------------------*/
      c = x_grid [i].g_used;
      DEBUG_YMAP   yLOG_schar   (c);
      /*---(used)------------------------*/
      if (*x_use == x_cur) {  /* not changed */
         if (strchr (YMAP_REAL, c) != NULL)  *x_use = i;
      }
      /*---(prev)------------------------*/
      if (*x_end == x_cur) {  /* not changed */
         switch (t) {
         case YMAP_NADA : if (c == YMAP_NADA)                 *x_end = i - x_inc;   break;
         case YMAP_USED : if (strchr (YMAP_REAL, c) != NULL)  *x_end = i;           break;
         }
      }
      /*---(done)------------------------*/
   }
   /*---(fix end)------------------------*/
   if (*x_end == x_cur) {
      if (a_dir == '<')  *x_end =  a_map->gmin;
      else               *x_end =  a_map->gmax;
   }
   /*---(save-back)----------------------*/
   DEBUG_YMAP   yLOG_sint    (*x_end);
   DEBUG_YMAP   yLOG_sint    (*x_use);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_update_large       (uchar a_axis)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   char        x_tries     =    0;
   int         x_len       =    0;
   int         i           =    0;          /* grid index                     */
   int         n           =    0;          /* map index                      */
   int         c           =    0;          /* width counter                  */
   ushort      x_min, x_max;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_map"     , x_map);
   --rce;  if (x_map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_grid"    , x_grid);
   --rce;  if (x_grid == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get absolutes)------------------*/
   rc = myMAP.e_sizer (a_axis, NULL, NULL, NULL, NULL, NULL, &x_min, &x_max);
   DEBUG_YMAP    yLOG_complex ("e_sizer"   , "%4dr, %4dm, %4dx", rc, x_min, x_max);
   /*---(run grid)-----------------------*/
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   rc = ymap__load_limits (x_map, x_min, x_max);
   DEBUG_YMAP    yLOG_value   ("limits"    , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   /*---(make length)--------------------*/
   if (x_grid [0].g_ref == YMAP_EMPTY)  x_len = 0;
   else                               x_len = x_map->umax + 1;
   DEBUG_YMAP    yLOG_value   ("x_len"     , x_len);
   /*---(free)-----------*/
   if (x_map->map  != NULL) {
      DEBUG_YMAP    yLOG_note    ("freeing map");
      free (x_map->map);
   }
   x_map->map   = NULL;
   x_map->mlen  = x_len;
   /*---(call off)-------*/
   --rce;  if (x_len <= 0) {
      DEBUG_YMAP    yLOG_note    ("empty grid, call off");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(alloc)----------*/
   DEBUG_YMAP    yLOG_note    ("allocating new map");
   x_tries = 0;
   while (x_map->map == NULL && x_tries < 10)  {
      ++x_tries;
      x_map->map = (short *) malloc (sizeof (short) * x_map->mlen);
   }
   DEBUG_YMAP    yLOG_value   ("x_tries"   , x_tries);
   DEBUG_YMAP    yLOG_point   ("map"       , x_map->map);
   --rce;  if (x_map->map == NULL) {
      DEBUG_YMAP    yLOG_note    ("FAILED");
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate map)-------------------*/
   for (i = 0; i < x_map->glen; ++i) {
      if (x_grid [i].g_ref == YMAP_EMPTY)  break;
      /*> printf ("LOOP %3d\n", i);                                                   <*/
      x_grid [i].g_unit = n;
      DEBUG_YMAP    yLOG_complex ("unit"      , "grid %2d, unit %4d", i, x_grid [i].g_unit);
      while (c < x_grid [i].g_wide) {
         /*> printf (" assign %3d into %3d %3d\n", i, n, c);                          <*/
         x_map->map [n] = i;
         ++n;  ++c;
      }
      c = 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_update_small       (uchar a_axis)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   ushort      n, a, b, c, e, x_min, x_max;
   ushort      x, y;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*> printf ("ymap...small    beg  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_map"     , x_map);
   --rce;  if (x_map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_grid"    , x_grid);
   --rce;  if (x_grid == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get absolutes)------------------*/
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   rc = myMAP.e_sizer (a_axis, &n, &a, &b, &c, &e, &x_min, &x_max);
   DEBUG_YMAP    yLOG_complex ("e_sizer"   , "%4dr, %4dn, %4da, %4db, %4dc, %4de, %4dm, %4dx", rc, n, a, b, c, e, x_min, x_max);
   /*---(load avail)---------------------*/
   x_map->uavail = a;
   /*---(DEBUGGING)----------------------*/
   yMAP_current (NULL, NULL, &x, &y, NULL);
   DEBUG_YMAP    yLOG_complex ("current"   , "%c, %4dx, %4dy", a_axis, x, y);
   /*---(run grid)-----------------------*/
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   rc = ymap__load_limits (x_map, x_min, x_max);
   DEBUG_YMAP    yLOG_value   ("limits"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> printf ("ymap...small    lims %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(update prev)--------------------*/
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   rc = ymap__load_ends   (x_map, '<');
   DEBUG_YMAP    yLOG_value   ("prev"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> printf ("ymap...small    end< %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(update next)--------------------*/
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   rc = ymap__load_ends   (x_map, '>');
   DEBUG_YMAP    yLOG_value   ("next"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> printf ("ymap...small    end> %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(DEBUGGING)----------------------*/
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   rc = myMAP.e_sizer (a_axis, &n, &a, &b, &c, &e, &x_min, &x_max);
   DEBUG_YMAP    yLOG_complex ("e_sizer"   , "%4dr, %4dn, %4db, %4dc, %4de, %4dm, %4dx", rc, n, b, c, e, x_min, x_max);
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   yMAP_current (NULL, NULL, &x, &y, NULL);
   DEBUG_YMAP    yLOG_complex ("current"   , "%c, %4dx, %4dy", a_axis, x, y);
   /*> printf ("ymap...small    839  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(finalize)-----------------------*/
   DEBUG_YMAP    yLOG_complex ("map coords", "%4db, %4dc, %4de", x_map->gbeg, x_map->gcur, x_map->gend);
   DEBUG_YMAP    yLOG_complex ("units"     , "%4db, %4dc, %4de", x_map->ubeg, x_map->ucur, x_map->uend);
   ymap_update_grid  (x_map);
   /*> printf ("ymap...small    grid %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   DEBUG_YMAP    yLOG_complex ("map coords", "%4db, %4dc, %4de", x_map->gbeg, x_map->gcur, x_map->gend);
   DEBUG_YMAP    yLOG_complex ("units"     , "%4db, %4dc, %4de", x_map->ubeg, x_map->ucur, x_map->uend);
   ymap_display      (x_map);
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   DEBUG_YMAP    yLOG_complex ("map coords", "%4db, %4dc, %4de", x_map->gbeg, x_map->gcur, x_map->gend);
   DEBUG_YMAP    yLOG_complex ("units"     , "%4db, %4dc, %4de", x_map->ubeg, x_map->ucur, x_map->uend);
   /*> printf ("ymap...small    disp %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(DEBUGGING)----------------------*/
   rc = myMAP.e_sizer (a_axis, &n, &a, &b, &c, &e, &x_min, &x_max);
   DEBUG_YMAP    yLOG_complex ("e_sizer"   , "%4dr, %4dn, %4db, %4dc, %4de, %4dm, %4dx", rc, n, b, c, e, x_min, x_max);
   yMAP_current (NULL, NULL, &x, &y, NULL);
   DEBUG_YMAP    yLOG_complex ("current"   , "%c, %4dx, %4dy", a_axis, x, y);
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   /*---(complete)-----------------------*/
   /*> printf ("ymap...small    end  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          searching                           ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

static ushort s_pos = 0;

char
yMAP_by_index           (uchar a_axis, uchar a_pos, ushort *r_pos, short *r_ref, uchar *r_wide, uchar *r_used)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   short       x_max       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_complex ("args"      , "%c, %d, %p, %p, %p", a_axis, a_pos, r_ref, r_wide, r_used);
   /*---(defaults)-----------------------*/
   if (r_pos  != NULL)  *r_pos  = 0;
   if (r_ref  != NULL)  *r_ref  = 0;
   if (r_wide != NULL)  *r_wide = 0;
   if (r_used != NULL)  *r_used = 0;
   /*---(get map)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   DEBUG_YMAP   yLOG_value   ("pick"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_note    ("axis not found/legal");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_map"     , x_map);
   --rce;  if (x_map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_grid"    , x_grid);
   --rce;  if (x_grid == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_max = x_map->gmax;
   /*---(trouble)------------------------*/
   --rce;  if (a_pos < 0 || a_pos > x_max) {
      DEBUG_YMAP   yLOG_note    ("position out of legal range");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   s_pos = a_pos;
   if (r_pos  != NULL)  *r_pos  = s_pos;
   if (r_ref  != NULL)  *r_ref  = x_grid [a_pos].g_ref;
   if (r_wide != NULL)  *r_wide = x_grid [a_pos].g_wide;
   if (r_used != NULL)  *r_used = x_grid [a_pos].g_used;
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yMAP_by_cursor          (uchar a_axis, uchar a_dir, ushort *r_pos, short *r_ref, uchar *r_wide, uchar *r_used)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   short       x_pos       =    0;
   short       x_max       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_complex ("args"      , "%c, %c, %p, %p, %p", a_axis, a_dir, r_ref, r_wide, r_used);
   /*---(defaults)-----------------------*/
   if (r_pos  != NULL)  *r_pos  = 0;
   if (r_ref  != NULL)  *r_ref  = 0;
   if (r_wide != NULL)  *r_wide = 0;
   if (r_used != NULL)  *r_used = 0;
   /*---(get map)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_note    ("axis not found/legal");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP    yLOG_char    ("axis"      , x_map->axis);
   /*---(defense)------------------------*/
   DEBUG_YMAP    yLOG_value   ("glen"      , x_map->glen);
   --rce;  if (x_map->glen <= 0) {
      DEBUG_YMAP   yLOG_note    ("no grid elements loaded");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_max = x_map->gmax;
   DEBUG_YMAP    yLOG_value   ("x_max"     , x_max);
   x_pos = s_pos;
   DEBUG_YMAP    yLOG_value   ("x_pos"     , x_pos);
   /*---(run grid)-----------------------*/
   --rce;  switch (a_dir) {
   case YDLST_HEAD :
      DEBUG_YMAP    yLOG_note    ("to head");
      x_pos = 0;
      break;
   case YDLST_PREV :
      DEBUG_YMAP    yLOG_note    ("go prev");
      --x_pos;
      break;
   case YDLST_CURR :
      DEBUG_YMAP    yLOG_note    ("stay at current");
      break;
   case YDLST_NEXT :
      DEBUG_YMAP    yLOG_note    ("go next");
      ++x_pos;
      break;
   case YDLST_TAIL :
      DEBUG_YMAP    yLOG_note    ("to tail");
      x_pos = x_max;
      break;
   default :
      DEBUG_YMAP   yLOG_note    ("direction not legal");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP    yLOG_value   ("x_pos"     , x_pos);
   /*---(trouble)------------------------*/
   --rce;  if (x_pos < 0 || x_pos > x_max) {
      DEBUG_YMAP   yLOG_note    ("position out of legal range, no bounce");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   s_pos = x_pos;
   if (r_pos  != NULL)  *r_pos  = s_pos;
   if (r_ref  != NULL)  *r_ref  = x_grid [x_pos].g_ref;
   if (r_wide != NULL)  *r_wide = x_grid [x_pos].g_wide;
   if (r_used != NULL)  *r_used = x_grid [x_pos].g_used;
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                    accessors and setters                     ----===*/
/*====================------------------------------------====================*/
static void  o___ACCESS__________o () { return; }

char
yMAP_axis_avail         (uchar a_axis, ushort a_avail)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, NULL);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(assign)-------------------------*/
   DEBUG_YMAP   yLOG_value   ("a_avail"   , a_avail);
   x_map->uavail = a_avail;
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_axis_force         (uchar a_axis, ushort a_beg, ushort a_cur, ushort a_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, &x_grid);
   DEBUG_YMAP   yLOG_value   ("pick"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_map"     , x_map);
   --rce;  if (x_map == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_grid"    , x_grid);
   --rce;  if (x_grid == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(beginning)----------------------*/
   DEBUG_YMAP   yLOG_value   ("a_beg"     , a_beg);
   if (a_beg > x_map->gmax) {
      a_beg = x_map->gmax;
      ++rc;
   }
   x_map->gbeg  = a_beg;
   x_map->ubeg  = x_grid [x_map->gbeg].g_unit;
   /*---(current)------------------------*/
   DEBUG_YMAP   yLOG_value   ("a_cur"     , a_cur);
   if (a_cur > x_map->gmax) {
      a_cur = x_map->gmax;
      ++rc;
   }
   x_map->gcur  = a_cur;
   x_map->ucur  = x_grid [x_map->gcur].g_unit;
   /*---(end)----------------------------*/
   DEBUG_YMAP   yLOG_value   ("a_end"     , a_end);
   if (a_end > x_map->gmax) {
      a_end = x_map->gmax;
      ++rc;
   }
   x_map->gend  = a_end;
   x_map->uend  = x_grid [x_map->gend].g_unit;
   /*---(rework display)-----------------*/
   ymap_display      (x_map);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yMAP_axis_grid          (uchar a_axis, ushort *a_beg, ushort *a_cur, ushort *a_end, uchar *a_extra)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, NULL);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(assign)-------------------------*/
   if (a_beg   != NULL)  *a_beg   = x_map->gbeg;
   if (a_cur   != NULL)  *a_cur   = x_map->gcur;
   if (a_end   != NULL)  *a_end   = x_map->gend;
   if (a_extra != NULL)  *a_extra = x_map->uavail - x_map->ulen;
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}


