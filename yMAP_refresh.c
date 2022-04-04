/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"



/*====================------------------------------------====================*/
/*===----                     refresh control                          ----===*/
/*====================------------------------------------====================*/
static void  o___CONTROL_________o () { return; }

/*
 *  help reduce mapping by specifying the depth of the next mapping process
 *
 */

char
ymap__change            (char *a_func, char a_axis, char a_level)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tyMAP      *x_map       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (a_func);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_axis"    , a_axis);
   rc = ymap_pick_map (a_axis, &x_map, NULL);
   DEBUG_YMAP   yLOG_value   ("pickmap"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP    yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("x_map"     , x_map);
   /*---(make change)--------------------*/
   DEBUG_YMAP    yLOG_value   ("a_level"   , a_level);
   DEBUG_YMAP    yLOG_value   ("before"    , x_map->change);
   switch (a_level) {
   case YMAP_FULL :
      if (x_map->change < YMAP_FULL)  x_map->change = YMAP_FULL;
      break;
   case YMAP_POS  :
      if (x_map->change < YMAP_POS)   x_map->change = YMAP_POS;
      break;
   case YMAP_SRC  :
      if (x_map->change < YMAP_SRC)   x_map->change = YMAP_SRC;
      break;
   default :
      DEBUG_YMAP    yLOG_note    ("unknown level");
      DEBUG_YMAP    yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_YMAP    yLOG_value   ("after"     , x_map->change);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (a_func);
   return 0;
}

char ymap_uchange (char a_level) { return ymap__change (__FUNCTION__, YMAP_UNIV , a_level); }
char ymap_xchange (char a_level) { return ymap__change (__FUNCTION__, YMAP_XAXIS, a_level); }
char ymap_ychange (char a_level) { return ymap__change (__FUNCTION__, YMAP_YAXIS, a_level); }
char ymap_zchange (char a_level) { return ymap__change (__FUNCTION__, YMAP_ZAXIS, a_level); }
char ymap_change  (char a_axis, char a_level) { return ymap__change (__FUNCTION__, a_axis, a_level); }



/*====================------------------------------------====================*/
/*===----                      realtime updates                        ----===*/
/*====================------------------------------------====================*/
static void  o___REALTIME________o () { return; }

/*
 *  help reduce the need for full map reloaads by updating specific data
 *
 */

char
ymap_used               (ushort x, ushort y, ushort z)
{
   char        rc          =    0;
   if (rc >= 0)  rc = yMAP_entry  (YMAP_XAXIS, x, YMAP_LEAVE, YMAP_CURR, 'Ï');
   if (rc >= 0)  ymap_xchange (YMAP_SRC);
   if (rc >= 0)  rc = yMAP_entry  (YMAP_YAXIS, y, YMAP_LEAVE, YMAP_CURR, 'Ï');
   if (rc >= 0)  ymap_ychange (YMAP_SRC);
   if (rc >= 0)  rc = yMAP_entry  (YMAP_ZAXIS, z, YMAP_LEAVE, YMAP_CURR, 'Ï');
   if (rc >= 0)  ymap_zchange (YMAP_SRC);
   return rc;
}

char
ymap_empty              (ushort x, ushort y, ushort z)
{
   char        rc          =    0;
   if (rc >= 0)  rc = yMAP_entry  (YMAP_XAXIS, x, YMAP_LEAVE, YMAP_CURR, '·');
   if (rc >= 0)  ymap_xchange (YMAP_SRC);
   if (rc >= 0)  rc = yMAP_entry  (YMAP_YAXIS, y, YMAP_LEAVE, YMAP_CURR, '·');
   if (rc >= 0)  ymap_ychange (YMAP_SRC);
   if (rc >= 0)  rc = yMAP_entry  (YMAP_ZAXIS, z, YMAP_LEAVE, YMAP_CURR, '·');
   if (rc >= 0)  ymap_zchange (YMAP_SRC);
   return rc;
}

char
ymap_wide               (ushort a_pos, uchar a_wide)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP    yLOG_value   ("a_pos"     , a_pos);
   DEBUG_YMAP    yLOG_value   ("gmax"      , g_xmap.gmax);
   /*---(defense)------------------------*/
   --rce;  if (a_pos > g_xmap.gmax) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update entry)-------------------*/
   DEBUG_YMAP    yLOG_value   ("a_wide"    , a_wide);
   rc = yMAP_entry (YMAP_XAXIS, a_pos, YMAP_LEAVE, a_wide, YMAP_CURR);
   DEBUG_YMAP    yLOG_value   ("entry"     , rc);
   /*---(update refresh)-----------------*/
   if (rc >= 0)   ymap_xchange (YMAP_POS);
   DEBUG_YMAP    yLOG_value   ("change"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}
char
ymap_tall               (ushort a_pos, uchar a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP    yLOG_value   ("a_pos"     , a_pos);
   DEBUG_YMAP    yLOG_value   ("gmax"      , g_ymap.gmax);
   /*---(defense)------------------------*/
   --rce;  if (a_pos > g_ymap.gmax) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update entry)-------------------*/
   DEBUG_YMAP    yLOG_value   ("a_tall"    , a_tall);
   rc = yMAP_entry (YMAP_YAXIS, a_pos, YMAP_LEAVE, a_tall, YMAP_CURR);
   DEBUG_YMAP    yLOG_value   ("entry"     , rc);
   /*---(update refresh)-----------------*/
   if (rc >= 0) ymap_ychange (YMAP_POS);
   DEBUG_YMAP    yLOG_value   ("change"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}

char
ymap_deep               (ushort a_pos, uchar a_deep)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP    yLOG_value   ("a_pos"     , a_pos);
   DEBUG_YMAP    yLOG_value   ("gmax"      , g_zmap.gmax);
   /*---(defense)------------------------*/
   --rce;  if (a_pos > g_zmap.gmax) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update entry)-------------------*/
   DEBUG_YMAP    yLOG_value   ("a_deep"    , a_deep);
   rc = yMAP_entry (YMAP_ZAXIS, a_pos, YMAP_LEAVE, a_deep, YMAP_CURR);
   DEBUG_YMAP    yLOG_value   ("entry"     , rc);
   /*---(update refresh)-----------------*/
   if (rc >= 0) ymap_zchange (YMAP_POS);
   DEBUG_YMAP    yLOG_value   ("change"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                     mapping driver                           ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVER__________o () { return; }

static ushort u_last   = YMAP_EMPTY;
static ushort x_last   = YMAP_EMPTY;
static ushort y_last   = YMAP_EMPTY;
static ushort z_last   = YMAP_EMPTY;

char
ymap__refresh_analyze   (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   ushort      b, c, e;
   /*---(header)-------------------------*/
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   /*---(universes)----------------------*/
   rc = yMAP_axis_grid (YMAP_UNIV , &b, &c, &e, NULL);
   if (u_last == YMAP_EMPTY) {
      DEBUG_YMAP    yLOG_complex ("UNIV"      , "%4d, ····l, %4db, %4dc, %4de", rc, b, c, e);
   } else {
      DEBUG_YMAP    yLOG_complex ("UNIV"      , "%4d, %4dl, %4db, %4dc, %4de", rc, u_last, b, c, e);
   }
   if (c == u_last) {
      DEBUG_YMAP    yLOG_note    ("univ/tab did not change, do not remap");
   } else {
      DEBUG_YMAP    yLOG_note    ("univ/tab change, remap");
      ymap_uchange (YMAP_POS);
      ymap_xchange (YMAP_FULL);   /* opposite axis */
      ymap_ychange (YMAP_FULL);   /* opposite axis */
      ymap_zchange (YMAP_FULL);   /* opposite axis */
   }
   u_last = c;
   /*---(columns)------------------------*/
   rc = yMAP_axis_grid (YMAP_XAXIS, &b, &c, &e, NULL);
   if (x_last == YMAP_EMPTY) {
      DEBUG_YMAP    yLOG_complex ("COLS"      , "%4d, ····l, %4db, %4dc, %4de", rc, b, c, e);
   } else {
      DEBUG_YMAP    yLOG_complex ("COLS"      , "%4d, %4dl, %4db, %4dc, %4de", rc, x_last, b, c, e);
   }
   if (c == x_last) {
      DEBUG_YMAP    yLOG_note    ("xpos/col did not change, do not remap");
   } else {
      DEBUG_YMAP    yLOG_note    ("xpos/col change, remap");
      ymap_xchange (YMAP_POS);
      ymap_ychange (YMAP_FULL);   /* opposite axis */
      ymap_zchange (YMAP_FULL);   /* opposite axis */
   }
   x_last = c;
   /*---(rows)---------------------------*/
   rc = yMAP_axis_grid (YMAP_YAXIS, &b, &c, &e, NULL);
   if (y_last == YMAP_EMPTY) {
      DEBUG_YMAP    yLOG_complex ("ROWS"      , "%4d, ····l, %4db, %4dc, %4de", rc, b, c, e);
   } else  {
      DEBUG_YMAP    yLOG_complex ("ROWS"      , "%4d, %4dl, %4db, %4dc, %4de", rc, y_last, b, c, e);
   }
   if (c == y_last) {
      DEBUG_YMAP    yLOG_note    ("ypos/row did not change, do not remap");
   } else {
      DEBUG_YMAP    yLOG_note    ("ypos/row change, remap");
      ymap_xchange (YMAP_FULL);   /* opposite axis */
      ymap_ychange (YMAP_POS);
      ymap_zchange (YMAP_FULL);   /* opposite axis */
   }
   y_last = c;
   /*---(rows)---------------------------*/
   rc = yMAP_axis_grid (YMAP_ZAXIS, &b, &c, &e, NULL);
   if (y_last == YMAP_EMPTY) {
      DEBUG_YMAP    yLOG_complex ("DEEP"      , "%4d, ····l, %4db, %4dc, %4de", rc, b, c, e);
   } else {
      DEBUG_YMAP    yLOG_complex ("DEEP"      , "%4d, %4dl, %4db, %4dc, %4de", rc, z_last, b, c, e);
   }
   if (c == z_last) {
      DEBUG_YMAP    yLOG_note    ("zpos/deep did not change, do not remap");
   } else {
      DEBUG_YMAP    yLOG_note    ("zpos/deep change, remap");
      ymap_xchange (YMAP_FULL);   /* opposite axis */
      ymap_ychange (YMAP_FULL);   /* opposite axis */
      ymap_zchange (YMAP_POS);
   }
   z_last = c;
   /*---(ocmplete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__refresh           (char *a_name, char a_axis, tyMAP *a_map)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   short       x_ref       =    0;
   uchar       x_wide      =    0;
   uchar       x_used      =    0;
   ushort      x_max       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_note    (a_name);
   switch (a_map->change) {
   case YMAP_FULL :  /* call external mapper */
      /*---(get sizes)----------------------*/
      DEBUG_YMAP   yLOG_point   ("e_sizer"   , myMAP.e_sizer);
      if (myMAP.e_sizer == NULL) {
         DEBUG_YMAP   yLOG_note    ("without e_sizer, nothing to do");
         DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = myMAP.e_sizer (a_axis, &x_max, NULL, NULL, NULL, NULL, NULL, NULL);
      DEBUG_YMAP   yLOG_value   ("e_sizer"   , rc);
      --rce;  if (rc < 0) {
         DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YMAP   yLOG_value   ("x_max"     , x_max);
      --rce;  if (x_max <= 0) {
         DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = yMAP_start (a_axis, x_max);
      for (i = 0; i < x_max; ++i) {
         rc = myMAP.e_entry (a_axis, i, &x_ref, &x_wide, &x_used);
         DEBUG_YMAP   yLOG_value   ("e_entry"   , rc);
         if (rc < 0)  break;
         rc = yMAP_append (x_ref, x_wide, x_used);
         DEBUG_YMAP   yLOG_value   ("append"    , rc);
         if (rc < 0)  break;
      }
      rc = yMAP_finish ();
   case YMAP_POS  :  /* process map and make display */
      DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
      rc = ymap_update_large (a_axis);
      DEBUG_YMAP   yLOG_value   ("update"    , rc);
      DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   case YMAP_SRC  :  /* handle local ends */
      rc = ymap_update_small (a_axis);
      DEBUG_YMAP   yLOG_value   ("ends"      , rc);
      DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
      if (a_map->grid != NULL) {
         rc = myMAP.e_placer (a_axis, a_map->gbeg, a_map->gcur, a_map->gend);
         DEBUG_YMAP   yLOG_value   ("placer"    , rc);
      } else {
         DEBUG_YMAP   yLOG_note    ("grid is null, skipping placer");
      }
      DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_refresh            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (MODE_MAP)) {
      DEBUG_YMAP   yLOG_note    ("can not execute until operational");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(look for combinations)----------*/
   DEBUG_YMAP    yLOG_complex ("change bef", "%du, %dx, %dy, %dz", g_umap.change, g_xmap.change, g_ymap.change, g_zmap.change);
   ymap__refresh_analyze ();
   DEBUG_YMAP    yLOG_complex ("change aft", "%du, %dx, %dy, %dz", g_umap.change, g_xmap.change, g_ymap.change, g_zmap.change);
   /*---(refresh axis)-------------------*/
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   ymap__refresh ("universe"  , YMAP_UNIV , &g_umap);
   DEBUG_YMAP   yLOG_complex ("CUR"       ,  "%4du, %4dg", g_umap.ucur, g_umap.gcur);
   ymap__refresh ("xaxis"     , YMAP_XAXIS, &g_xmap);
   ymap__refresh ("yaxis"     , YMAP_YAXIS, &g_ymap);
   ymap__refresh ("zaxis"     , YMAP_ZAXIS, &g_zmap);
   /*---(reset)--------------------------*/
   g_umap.change = YMAP_SKIP;
   g_xmap.change = YMAP_SKIP;
   g_ymap.change = YMAP_SKIP;
   g_zmap.change = YMAP_SKIP;
   /*---(update selection)---------------*/
   ymap_visu_update ();
   /*---(finalize)-----------------------*/
   DEBUG_YMAP   yLOG_point   ("e_done"    , myMAP.e_done);
   if (myMAP.e_done != NULL)  rc = myMAP.e_done ();
   DEBUG_YMAP   yLOG_value   ("e_done"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_refresh_disponly   (void)
{
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(displays)-----------------------*/
   g_xmap.change = YMAP_POS;
   g_ymap.change = YMAP_POS;
   yMAP_refresh ();
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_refresh_full       (void)
{
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   g_umap.change = YMAP_FULL;
   g_xmap.change = YMAP_FULL;
   g_ymap.change = YMAP_FULL;
   g_zmap.change = YMAP_FULL;
   yMAP_refresh ();
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}



