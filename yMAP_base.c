/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"




tMY         myMAP;

tGRID       *g_ugrid;   /* universe/buffer  */
tGRID       *g_xgrid;   /* x-axis           */
tGRID       *g_ygrid;   /* y-axis           */
tGRID       *g_zgrid;   /* z-axis           */
tGRID       *g_wgrid;   /* when/time        */

tyMAP        g_umap;
tyMAP        g_xmap;
tyMAP        g_ymap;
tyMAP        g_zmap;
tyMAP        g_wmap;



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yMAP_ver [200] = "";

char*        /*--> return library versioning info --------[ leaf-- [ ------ ]-*/
yMAP_version            (void)
{
   char        t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yMAP_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yMAP_ver;
}



/*====================------------------------------------====================*/
/*===----                  shared support functions                    ----===*/
/*====================------------------------------------====================*/
static void  o___SHARED__________o () { return; }

char
ymap_pick_map           (uchar a_axis, tyMAP **r_map, tGRID **r_grid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(map)----------------------------*/
   DEBUG_YMAP   yLOG_schar   (a_axis);
   --rce;  switch (a_axis) {
   case YMAP_UNIV :
      x_map  = &g_umap;
      x_grid = g_ugrid;
      break;
   case YMAP_XAXIS :
      x_map  = &g_xmap;
      x_grid = g_xgrid;
      break;
   case YMAP_YAXIS :
      x_map  = &g_ymap;
      x_grid = g_ygrid;
      break;
   case YMAP_ZAXIS :
      x_map  = &g_zmap;
      x_grid = g_zgrid;
      break;
   case YMAP_WHEN :
      x_map  = &g_wmap;
      x_grid = g_wgrid;
      break;
   default  :
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_spoint  (x_map);
   DEBUG_YMAP   yLOG_spoint  (x_grid);
   /*---(save back)----------------------*/
   DEBUG_YMAP   yLOG_spoint  (r_map);
   if (r_map  != NULL)  *r_map  = x_map;
   DEBUG_YMAP   yLOG_spoint  (r_grid);
   if (r_grid != NULL)  *r_grid = x_grid;
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
yMAP_init              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (MODE_MAP)) {
      DEBUG_YMAP   yLOG_note    ("status is not ready for init");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> printf ("yMAP_init       beg  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(yVIHUB)-------------------------*/
   yVIHUB_from_yMAP (yMAP_refresh, yMAP_refresh_disponly, yMAP_refresh_full, yMAP_visu_islive, yMAP_range, yMAP_jump, yMAP_beg, yMAP_current, yMAP_locator, yMAP_addresser, yMAP_move_hmode);
   /*---(globals)------------------------*/
   DEBUG_YMAP   yLOG_note    ("default globals");
   myMAP.orient = YMAP_OFFICE;
   myMAP.e_locator    = NULL;
   myMAP.e_addresser  = NULL;
   myMAP.e_sizer      = NULL;
   myMAP.e_entry      = NULL;
   myMAP.e_placer     = NULL;
   myMAP.e_done       = NULL;
   /*---(clear)--------------------------*/
   DEBUG_YMAP   yLOG_note    ("map clearing");
   ymap_mapinit (YMAP_UNIV);
   ymap_mapinit (YMAP_XAXIS);
   ymap_mapinit (YMAP_YAXIS);
   ymap_mapinit (YMAP_ZAXIS);
   ymap_mapinit (YMAP_WHEN);
   g_ugrid;   /* universe/buffer  */
   g_xgrid;   /* x-axis           */
   g_ygrid;   /* y-axis           */
   g_zgrid;   /* z-axis           */
   g_wgrid;   /* when/time        */
   /*> printf ("yMAP_init       map  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   /*---(visual)-------------------------*/
   DEBUG_YMAP   yLOG_note    ("visual setup");
   ymap_visu_init ();
   DEBUG_YMAP   yLOG_note    ("register setup");
   ymap_mreg_init ();
   DEBUG_YMAP   yLOG_note    ("mundo setup");
   ymap_mundo_init ();
   DEBUG_YMAP   yLOG_note    ("universe setup");
   ymap_univ_init ();
   /*---(prepare external modes)---------*/
   yMODE_init_set   (XMOD_FORMAT , ymap_format_prepper, ymap_format_xmode);
   yMODE_init_set   (XMOD_UNITS  , NULL, ymap_units_xmode);
   rc = yVIHUB_yCMD_add (YVIHUB_M_FORMAT, "xwide"       , ""    , "sii"  , yMAP_multi_wide            , "change the width of columns"              );
   rc = yVIHUB_yCMD_add (YVIHUB_M_FORMAT, "xdef"        , ""    , "si"   , ymap_multi_wide_def        , "change current column widht to default"   );
   rc = yVIHUB_yCMD_add (YVIHUB_M_FORMAT, "xreset"      , ""    , "s"    , ymap_multi_wide_reset      , "reset width of call columns to default"   );
   rc = yVIHUB_yCMD_add (YVIHUB_M_FORMAT, "ytall"       , ""    , "sii"  , yMAP_multi_tall            , "change the height of rows"                );
   rc = yVIHUB_yCMD_add (YVIHUB_M_FORMAT, "ydef"        , ""    , "si"   , ymap_multi_tall_def        , "change current row height to default"     );
   rc = yVIHUB_yCMD_add (YVIHUB_M_FORMAT, "yreset"      , ""    , "s"    , ymap_multi_tall_reset      , "reset height of all rows to default"      );
   rc = yVIHUB_yCMD_add (YVIHUB_M_FORMAT, "zdeep"       , ""    , "sii"  , yMAP_multi_deep            , "change the thickness of levels"           );
   rc = yVIHUB_yCMD_add (YVIHUB_M_FORMAT, "zdef"        , ""    , "si"   , ymap_multi_deep_def        , "change current level thickness to default");
   rc = yVIHUB_yCMD_add (YVIHUB_M_FORMAT, "zreset"      , ""    , "s"    , ymap_multi_deep_reset      , "reset thickness of all levels to default" );
   /*---(update status)------------------*/
   yMODE_init_set   (MODE_MAP     , NULL, ymap_mode);
   yMODE_init_set   (MODE_GOD     , NULL, ymap_god_mode);
   /*> printf ("yMAP_init       end  %7du %7dx %7dy %7dz\n", g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);   <*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_init_after         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   rc = yVIHUB_yFILE_dump_add ("mundo"     , "mun", "inventory of undo/redo chain"  , ymap_mundo_dump);
   DEBUG_YMODE   yLOG_value   ("dump_add"  , rc);
   rc = yVIHUB_yFILE_dump_add ("maps"      , "map", "details of all axis maps"      , ymap_map_dump);
   DEBUG_YMODE   yLOG_value   ("dump_add"  , rc);
   rc = yVIHUB_yFILE_dump_add ("visuals"   , "vis", "current and saved visual selections", ymap_visu_dump);
   DEBUG_YMODE   yLOG_value   ("dump_add"  , rc);
   rc = yVIHUB_yVIEW_switch_add ('s', "visual"       , "vis"   , yMAP_visu_status       , "details of current visual selection"      );
   DEBUG_YMODE   yLOG_value   ("switch_add", rc);
   rc = yVIHUB_yVIEW_switch_add ('s', "current"      , "cur"   , yMAP_current_status    , "current map position"                     );
   DEBUG_YMODE   yLOG_value   ("switch_add", rc);
   yMODE_after_set  (MODE_MAP);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
yMAP_config_OLD         (char a_orient, void *a_umapper, void *a_xmapper, void *a_ymapper, void *a_zmapper, void *a_mapdone, void *a_locator, void *a_addresser)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (MODE_MAP)) {
      DEBUG_YMAP    yLOG_note    ("init must complete before config");
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   myMAP.orient       = a_orient;
   /*> myMAP.e_umapper    = a_umapper;                                                <* 
    *> myMAP.e_xmapper    = a_xmapper;                                                <* 
    *> myMAP.e_ymapper    = a_ymapper;                                                <* 
    *> myMAP.e_zmapper    = a_zmapper;                                                <* 
    *> myMAP.e_mapdone    = a_mapdone;                                                <* 
    *> myMAP.e_locator    = a_locator;                                                <* 
    *> myMAP.e_addresser  = a_addresser;                                              <*/
   /*---(update status)------------------*/
   yMODE_conf_set   (MODE_MAP, '1');
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_config             (char a_orient, void *a_locator, void *a_addresser, void *a_sizer, void *a_entry, void *a_placer, void *a_done)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (MODE_MAP)) {
      DEBUG_YMAP    yLOG_note    ("init must complete before config");
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   myMAP.orient       = a_orient;
   /*---(locator)------------------------*/
   DEBUG_YMAP   yLOG_point   ("locator"   , a_locator);
   --rce;  if (a_locator   == NULL) {
      DEBUG_YMAP    yLOG_note    ("installing false");
      myMAP.e_locator    = ymap_false_locator;
   } else {
      myMAP.e_locator    = a_locator;
   }
   /*---(addresser)----------------------*/
   DEBUG_YMAP   yLOG_point   ("addresser" , a_addresser);
   --rce;  if (a_addresser == NULL) {
      DEBUG_YMAP    yLOG_note    ("installing false");
      myMAP.e_addresser  = ymap_false_addresser;
   } else {
      myMAP.e_addresser  = a_addresser;
   }
   /*---(sizer)--------------------------*/
   DEBUG_YMAP   yLOG_point   ("sizer"     , a_sizer);
   --rce;  if (a_sizer     == NULL) {
      DEBUG_YMAP    yLOG_note    ("installing false");
      myMAP.e_sizer      = ymap_false_sizer;
   } else {
      myMAP.e_sizer      = a_sizer;
   }
   /*---(entry)--------------------------*/
   DEBUG_YMAP   yLOG_point   ("entry"     , a_entry);
   --rce;  if (a_entry     == NULL) {
      DEBUG_YMAP    yLOG_note    ("installing false");
      myMAP.e_entry      = ymap_false_entry;
   } else {
      myMAP.e_entry      = a_entry;
   }
   /*---(placer)-------------------------*/
   DEBUG_YMAP   yLOG_point   ("placer"    , a_placer);
   --rce;  if (a_placer    == NULL) {
      DEBUG_YMAP    yLOG_note    ("installing false");
      myMAP.e_placer     = ymap_false_placer;
   } else {
      myMAP.e_placer     = a_placer;
   }
   /*---(done)---------------------------*/
   DEBUG_YMAP   yLOG_point   ("done"      , a_done);
   --rce;  if (a_done      == NULL) {
      DEBUG_YMAP    yLOG_note    ("installing false");
      myMAP.e_done       = ymap_false_done;
   } else {
      myMAP.e_done       = a_done;
   }
   /*---(update status)------------------*/
   yMODE_conf_set   (MODE_MAP, '1');
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> turn label into coordinates --------[ ------ [gc.722.112.13]*/ /*-[01.0000.304.#]-*/ /*-[--.---.---.--]-*/
ymap__locator           (char a_strict, char *a_label, ushort *u, ushort *x, ushort *y, ushort *z)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =    0;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP yLOG_enter   (__FUNCTION__);
   /*---(check locator)------------------*/
   DEBUG_YMAP yLOG_point   ("e_locator"  , myMAP.e_locator);
   --rce;  if (myMAP.e_locator == NULL) {
      DEBUG_YMAP yLOG_exitr   (__FUNCTION__,rce);
      return rce;
   }
   /*---(call locator)-------------------*/
   rc = myMAP.e_locator (a_strict, a_label, u, x, y, z);
   DEBUG_YMAP   yLOG_value   ("locator"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP yLOG_exit    (__FUNCTION__);
   return rc;
}

char ymap_locator            (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z) { return ymap__locator ('-', a_label, u, x, y, z); }
char ymap_locator_strict     (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z) { return ymap__locator ('y', a_label, u, x, y, z); }

char yMAP_locator            (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z) { return ymap__locator ('-', a_label, u, x, y, z); }

char         /*-> turn coordinates into label --------[ ------ [gc.722.112.13]*/ /*-[01.0000.304.#]-*/ /*-[--.---.---.--]-*/
ymap__addresser         (char a_strict, char *a_label, ushort u, ushort x, ushort y, ushort z)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_label     [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("a_strict"  , a_strict);
   DEBUG_YMAP   yLOG_point   ("a_label"   , a_label);
   /*---(default)------------------------*/
   if (a_label != NULL)  strlcpy (a_label, "n/a", LEN_LABEL);
   /*---(check addresser)----------------*/
   DEBUG_YMAP   yLOG_point   ("addresser" , myMAP.e_addresser);
   --rce;  if (myMAP.e_addresser == NULL)  {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call locator)-------------------*/
   rc = myMAP.e_addresser (a_strict, x_label, u, x, y, z);
   DEBUG_YMAP   yLOG_value   ("addresser" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (a_label != NULL)  strlcpy (a_label, x_label, LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}

char ymap_addresser          (char *a_label, ushort u, ushort x, ushort y, ushort z) { return ymap__addresser ('-', a_label, u, x, y, z); }
char ymap_addresser_strict   (char *a_label, ushort u, ushort x, ushort y, ushort z) { return ymap__addresser ('y', a_label, u, x, y, z); }

char yMAP_addresser          (char *a_label, ushort u, ushort x, ushort y, ushort z) { return ymap__addresser ('-', a_label, u, x, y, z); }

char
ymap_valid              (ushort u, ushort x, ushort y, ushort z)
{
   char        rce         =  -10;
   --rce;  if (u < g_umap.gmin || u > g_umap.gmax)  return rce;
   --rce;  if (x < g_xmap.gmin || x > g_xmap.gmax)  return rce;
   --rce;  if (y < g_ymap.gmin || y > g_ymap.gmax)  return rce;
   --rce;  if (z < g_zmap.gmin || z > g_zmap.gmax)  return rce;
   return 0;
}

char
yMAP_beg                (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z)
{
   char        rce         =  -10;
   char        rc          =    0;
   --rce;  if (a_label != NULL) {
      rc = ymap_addresser (a_label, g_umap.gbeg, g_xmap.gbeg, g_ymap.gbeg, g_zmap.gbeg);
      if (rc < 0) return rce;
   }
   if (u  != NULL)  *u  = g_umap.gbeg;
   if (x  != NULL)  *x  = g_xmap.gbeg;
   if (y  != NULL)  *y  = g_ymap.gbeg;
   if (z  != NULL)  *z  = g_zmap.gbeg;
   return 0;
}

char
yMAP_current            (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z)
{
   char        rce         =  -10;
   char        rc          =    0;
   --rce;  if (a_label != NULL) {
      rc = ymap_addresser (a_label, g_umap.gcur, g_xmap.gcur, g_ymap.gcur, g_zmap.gcur);
      if (rc < 0) return rce;
   }
   if (u  != NULL)  *u  = g_umap.gcur;
   if (x  != NULL)  *x  = g_xmap.gcur;
   if (y  != NULL)  *y  = g_ymap.gcur;
   if (z  != NULL)  *z  = g_zmap.gcur;
   return 0;
}

char
yMAP_current_unit       (ushort *u, ushort *x, ushort *y, ushort *z)
{
   if (u  != NULL)  *u  = g_umap.ucur;
   if (x  != NULL)  *x  = g_xmap.ucur;
   if (y  != NULL)  *y  = g_ymap.ucur;
   if (z  != NULL)  *z  = g_zmap.ucur;
   return 0;
}

/*> char                                                                              <* 
 *> ymap_remap              (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YMAP   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(update)-------------------------+/                                       <* 
 *>    DEBUG_YMAP   yLOG_point   ("myMAP.e_mapper"  , myMAP.e_mapper);                <* 
 *>    if (myMAP.e_mapper != NULL) {                                                  <* 
 *>       DEBUG_YMAP   yLOG_note    ("calling source program mapper");                <* 
 *>       myMAP.e_mapper (YMAP_UPDATE);                                               <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

char
yMAP_refresh_universe   (void)
{
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(displays)-----------------------*/
   /*> ymap_display (&g_umap);                                                        <* 
    *> /+---(update)-------------------------+/                                       <* 
    *> DEBUG_YMAP   yLOG_point   ("myMAP.e_mapper"  , myMAP.e_mapper);                <* 
    *> if (myMAP.e_mapper != NULL) {                                                  <* 
    *>    DEBUG_YMAP   yLOG_note    ("calling source program mapper");                <* 
    *>    myMAP.e_mapper (YMAP_UNIVERSE);                                             <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_refresh_univdisp   (void)
{
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*> /+---(update)-------------------------+/                                       <* 
    *> DEBUG_YMAP   yLOG_point   ("myMAP.e_mapper"  , myMAP.e_mapper);                <* 
    *> if (myMAP.e_mapper != NULL) {                                                  <* 
    *>    DEBUG_YMAP   yLOG_note    ("calling source program mapper");                <* 
    *>    myMAP.e_mapper (YMAP_UNIVDISP);                                             <* 
    *> }                                                                              <* 
    *> /+---(displays)-----------------------+/                                       <* 
    *> yMAP_update (YMAP_UNIV);                                                       <*/
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_wrap               (void)
{
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   ymap_factory (YMAP_UNIV);
   ymap_factory (YMAP_XAXIS);
   ymap_factory (YMAP_YAXIS);
   ymap_factory (YMAP_ZAXIS);
   ymap_factory (YMAP_WHEN);
   ymap_mreg_purge (YSTR_IFULL);
   ymap_mundo_wrap ();
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

