/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"




tMY         myMAP;



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
   DEBUG_MAP   yLOG_senter  (__FUNCTION__);
   /*---(map)----------------------------*/
   DEBUG_MAP   yLOG_schar   (a_axis);
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
      DEBUG_MAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP   yLOG_spoint  (x_map);
   DEBUG_MAP   yLOG_spoint  (x_grid);
   /*---(save back)----------------------*/
   DEBUG_MAP   yLOG_spoint  (r_map);
   if (r_map  != NULL)  *r_map  = x_map;
   DEBUG_MAP   yLOG_spoint  (r_grid);
   if (r_grid != NULL)  *r_grid = x_grid;
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_sexit   (__FUNCTION__);
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
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (MODE_MAP)) {
      DEBUG_PROG   yLOG_note    ("status is not ready for init");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   DEBUG_PROG   yLOG_note    ("default globals");
   myMAP.orient = YMAP_OFFICE;
   myMAP.e_mapper     = NULL;
   myMAP.e_locator    = NULL;
   myMAP.e_addresser  = NULL;
   /*---(clear)--------------------------*/
   DEBUG_PROG   yLOG_note    ("map clearing");
   ymap_mapinit (YMAP_UNIV);
   ymap_mapinit (YMAP_XAXIS);
   ymap_mapinit (YMAP_YAXIS);
   ymap_mapinit (YMAP_ZAXIS);
   ymap_mapinit (YMAP_WHEN);
   /*---(visual)-------------------------*/
   DEBUG_PROG   yLOG_note    ("visual setup");
   ymap_visu_init ();
   DEBUG_PROG   yLOG_note    ("register setup");
   ymap_mreg_init ();
   DEBUG_PROG   yLOG_note    ("mundo setup");
   ymap_mundo_init ();
   /*---(update status)------------------*/
   yMODE_init_set   (MODE_MAP, NULL, ymap_mode);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_config             (char a_orient, void *a_mapper, void *a_locator, void *a_addresser)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (MODE_MAP)) {
      DEBUG_MAP    yLOG_note    ("init must complete before config");
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   myMAP.orient = a_orient;
   myMAP.e_mapper     = a_mapper;
   myMAP.e_locator    = a_locator;
   myMAP.e_addresser  = a_addresser;
   /*---(update status)------------------*/
   yMODE_conf_set   (MODE_MAP, '1');
   /*---(update)-------------------------*/
   if (myMAP.e_mapper != NULL) {
      DEBUG_MAP   yLOG_snote   ("call host mapper");
      myMAP.e_mapper (YMAP_INIT);
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> turn label into coordinates --------[ ------ [gc.722.112.13]*/ /*-[01.0000.304.#]-*/ /*-[--.---.---.--]-*/
ymap_locator            (char *a_label, ushort *u, ushort *x, ushort *y, ushort *z)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =    0;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP_M yLOG_enter   (__FUNCTION__);
   /*---(check locator)------------------*/
   DEBUG_MAP_M yLOG_point   ("myMAP.e_locator"  , myMAP.e_locator);
   --rce;  if (myMAP.e_locator == NULL) {
      DEBUG_MAP_M yLOG_exitr   (__FUNCTION__,rce);
      return rce;
   }
   /*---(display input)------------------*/
   DEBUG_MAP_M yLOG_point   ("a_label"   , a_label);
   if (a_label != NULL)  DEBUG_MAP_M yLOG_info    ("a_label"   , a_label);
   /*---(call locator)-------------------*/
   rc = myMAP.e_locator (a_label, u, x, y, z);
   DEBUG_MAP   yLOG_value   ("locator"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_MAP_M yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(display output)-----------------*/
   if (u != NULL)  DEBUG_MAP_M yLOG_value   ("*u", *u);
   if (x != NULL)  DEBUG_MAP_M yLOG_value   ("*x", *x);
   if (y != NULL)  DEBUG_MAP_M yLOG_value   ("*y", *y);
   if (z != NULL)  DEBUG_MAP_M yLOG_value   ("*z", *z);
   /*---(complete)-----------------------*/
   DEBUG_MAP_M yLOG_exit    (__FUNCTION__);
   return rc;
}

char         /*-> turn coordinates into label --------[ ------ [gc.722.112.13]*/ /*-[01.0000.304.#]-*/ /*-[--.---.---.--]-*/
ymap_addresser          (char *a_label, ushort u, ushort x, ushort y, ushort z)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   /*---(check addresser)----------------*/
   DEBUG_MAP   yLOG_point   ("addresser" , myMAP.e_addresser);
   --rce;  if (myMAP.e_addresser == NULL)  {
      strlcpy (a_label, "-", LEN_LABEL);
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(display input)------------------*/
   DEBUG_MAP   yLOG_point   ("a_label"   , a_label);
   DEBUG_MAP   yLOG_value   ("u"         , u);
   DEBUG_MAP   yLOG_value   ("x"         , x);
   DEBUG_MAP   yLOG_value   ("y"         , y);
   DEBUG_MAP   yLOG_value   ("z"         , z);
   /*---(call locator)-------------------*/
   rc = myMAP.e_addresser (a_label, u, x, y, z);
   DEBUG_MAP   yLOG_value   ("addresser" , rc);
   --rce;  if (rc < 0) {
      DEBUG_MAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(display output)-----------------*/
   if (a_label != NULL)  DEBUG_MAP   yLOG_info    ("a_label"   , a_label);
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
   return rc;
}

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

char
ymap_remap              (void)
{
   /*---(header)-------------------------*/
   DEBUG_MAP   yLOG_enter   (__FUNCTION__);
   /*---(update)-------------------------*/
   DEBUG_MAP   yLOG_point   ("myMAP.e_mapper"  , myMAP.e_mapper);
   if (myMAP.e_mapper != NULL) {
      DEBUG_MAP   yLOG_note    ("calling source program mapper");
      myMAP.e_mapper (YMAP_UPDATE);
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_refresh            (void)
{
   /*---(update)-------------------------*/
   ymap_remap ();
   /*---(refresh position)---------------*/
   yMAP_update (YMAP_UNIV);
   yMAP_update (YMAP_XAXIS);
   yMAP_update (YMAP_YAXIS);
   /*> yMAP_update (YMAP_ZAXIS);                                                      <*/
   /*> yvikeys__map_vert (' ', '©');                                                  <* 
    *> yvikeys__map_horz (' ', '©');                                                  <*/
   /*> clear     ();                                                                  <*/
   /*---(complete)-----------------------*/
   return 0;
}

char
yMAP_wrap               (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   ymap_mreg_purge (YSTR_IFULL);
   ymap_mundo_wrap ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

