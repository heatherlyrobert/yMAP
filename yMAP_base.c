/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"




tMY         myMAP;


char    (*g_mapper)    (char  a_type);
char    (*g_locator)   (char *a_label, int *a_buf, int *a_x, int *a_y, int *a_z);
char*   (*g_addresser) (char *a_label, int  a_buf, int  a_x, int  a_y, int  a_z);



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
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_note    ("default globals");
   myMAP.orient = YMAP_OFFICE;
   g_mapper     = NULL;
   DEBUG_PROG   yLOG_note    ("map clearing");
   ymap_factory (&g_bmap, YMAP_BMAP);
   ymap_factory (&g_xmap, YMAP_XMAP);
   ymap_factory (&g_ymap, YMAP_YMAP);
   ymap_factory (&g_zmap, YMAP_ZMAP);
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
   g_mapper     = a_mapper;
   g_locator    = a_locator;
   g_addresser  = a_addresser;
   /*---(update status)------------------*/
   yMODE_conf_set   (MODE_MAP, '1');
   /*---(update)-------------------------*/
   if (g_mapper != NULL) {
      DEBUG_MAP   yLOG_snote   ("call host mapper");
      g_mapper (YMAP_INIT);
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_wrap              (void)
{
   return 0;
}




/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char           unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
ymap__unit_quiet         (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yMAP_unit" };
   ymap_init ();
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
   DEBUG_CMDS  yLOG_info     ("yMAP"     , yMAP_version   ());
   ymap_init ();
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
