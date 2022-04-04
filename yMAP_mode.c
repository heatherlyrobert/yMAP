/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"

char
ymap__biggies           (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =   -1;
   int         c           =    0;
   int         i           =    0;
   uchar       x_ch        = '\0';
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   switch (a_minor) {
   case G_KEY_ESCAPE :
      DEBUG_YMAP   yLOG_note    ("escape to clear selection");
      ymap_visu_clear    ();
      yKEYS_repeat_reset ();
      break;
   case G_KEY_SPACE  :
      DEBUG_YMAP   yLOG_note    ("space, nothing to do");
      break;
   case  '\0'        :
      DEBUG_YMAP   yLOG_note    ("null, nothing to do");
      break;
   default           :
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
ymap__multibeg          (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(multikey prefixes)--------------*/
   if (a_major == ' ') {
      DEBUG_YMAP   yLOG_note    ("checking for multikey prefix");
      DEBUG_YMAP   yLOG_value   ("multi"     , yKEYS_is_multi_map  (a_minor));
      DEBUG_YMAP   yLOG_value   ("isdead"    , ymap_visu_isdead ());
      if (ymap_visu_isdead () && yKEYS_is_multi_map  (a_minor)) {
         DEBUG_YMAP   yLOG_note    ("prefix of multimap keystring");
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return a_minor;
      }
      DEBUG_YMAP   yLOG_value   ("islive"    , yMAP_visu_islive ());
      DEBUG_YMAP   yLOG_value   ("multi"     , yKEYS_is_multi_visu (a_minor));
      if (yMAP_visu_islive () && yKEYS_is_multi_visu (a_minor)) {
         DEBUG_YMAP   yLOG_note    ("prefix of visual multimap keystring");
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return a_minor;
      }
      DEBUG_YMAP   yLOG_note    ("done checking");
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       big combinations                       ----===*/
/*====================------------------------------------====================*/
static void  o___COMBO___________o () { return; }

#define    ACT_CLEAR       'x'
#define    ACT_DELMOV      'd'
#define    ACT_DELCPY      'D'
#define    ACT_APPMOV      'a'
#define    ACT_APPCPY      'A'

#define    ACT_DELETES     "Dd"
#define    ACT_APPENDS     "Aa"

#define    OBJ_COLBEF      'X'
#define    OBJ_COLAFT      'x'
#define    OBJ_ROWBEF      'Y'
#define    OBJ_ROWAFT      'y'
#define    OBJ_DEPBEF      'Z'
#define    OBJ_DEPAFT      'z'

static  ushort  s_b, s_z;                          /* shared coordinates      */
static  ushort  s_xbs, s_xes, s_ybs, s_yes;        /* starting selection      */
static  ushort  s_xbc, s_xec, s_ybc, s_yec;        /* selection for copy      */
static  ushort  s_xp , s_yp;                       /* top/left for paste      */
static  ushort  s_xl , s_yl;                       /* starting selection size */
static  ushort  s_top, s_lef;                      /* screen top/left         */
static  char    s_nopaste;                         /* can not fill over       */

char
ymap__combo_prep        (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(get current)--------------------*/
   rc = yMAP_visu_range  (&s_b, &s_xbs, &s_xes, &s_ybs, &s_yes, &s_z, NULL, NULL);
   DEBUG_MAP    yLOG_complex ("src loc"   , "%3d, %2db, %3dxb %4dyb, %3dxe %4dye", rc, s_b, s_xbs, s_ybs, s_xes, s_yes);
   /*---(update for line cases)----------*/
   switch (a_minor) {
   case OBJ_COLAFT : case OBJ_COLBEF :
      s_ybs = g_ymap.gmin;
      s_yes = g_ymap.gmax;
      ymap_visu_exact  (s_b, s_xbs, s_xes, s_ybs, s_yes, s_z, s_z, 'e');
      DEBUG_MAP    yLOG_complex ("src update", "%3d, %2db, %3dxb %4dyb, %3dxe %4dye", rc, s_b, s_xbs, s_ybs, s_xes, s_yes);
      break;
   case OBJ_ROWAFT : case OBJ_ROWBEF :
      s_xbs = g_xmap.gmin;
      s_xes = g_xmap.gmax;
      ymap_visu_exact  (s_b, s_xbs, s_xes, s_ybs, s_yes, s_z, s_z, 'e');
      DEBUG_MAP    yLOG_complex ("src update", "%3d, %2db, %3dxb %4dyb, %3dxe %4dye", rc, s_b, s_xbs, s_ybs, s_xes, s_yes);
      break;
   case OBJ_DEPAFT : case OBJ_DEPBEF :
      break;
   }
   /*---(selection size)-----------------*/
   s_xl   = (s_xes - s_xbs) + 1;
   s_yl   = (s_yes - s_ybs) + 1;
   DEBUG_MAP    yLOG_complex ("dims"      , "          %3dxl %4dyl", s_xl, s_yl);
   /*---(clear)--------------------------*/
   if (strchr (ACT_DELETES, a_major) != NULL)  rc = ymap_mreg_clear ();
   rc = ymap_visu_clear ();
   /*---(save top/left)------------------*/
   s_lef  = g_xmap.ubeg;
   s_top  = g_ymap.ubeg;
   /*---(copy loc default)---------------*/
   s_xbc  = s_xbs;
   s_ybc  = s_ybs;
   s_xec  = s_xes;
   s_yec  = s_yes;
   DEBUG_MAP    yLOG_complex ("copy loc"  , "          %3dxb %4dyb, %3dxe %4dye", s_xbc, s_ybc, s_xec, s_yec);
   /*---(paste loc default)--------------*/
   s_nopaste = '-';
   s_xp   = s_xbs;
   s_yp   = s_ybs;
   DEBUG_MAP    yLOG_complex ("paste loc" , "          %3dxp %4dyp", s_xp, s_yp);
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__combo_wrap        (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_method    [LEN_LABEL] = "append";
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(defense on boundaries)----------*/
   if (s_xp  <  0          )  s_xp  = 0;
   if (s_xp  >= g_xmap.gmax)  s_xp  = g_xmap.gmax;
   if (s_xbc <  0          )  s_xbc = 0;
   if (s_xbc >= g_xmap.gmax)  s_xbc = g_xmap.gmax;
   if (s_xec <  0          )  s_xec = 0;
   if (s_xec >= g_xmap.gmax)  s_xec = g_xmap.gmax;
   if (s_yp  <  0          )  s_yp  = 0;
   if (s_yp  >= g_ymap.gmax)  s_yp  = g_ymap.gmax;
   if (s_ybc <  0          )  s_ybc = 0;
   if (s_ybc >= g_ymap.gmax)  s_ybc = g_ymap.gmax;
   if (s_yec <  0          )  s_yec = 0;
   if (s_yec >= g_ymap.gmax)  s_yec = g_ymap.gmax;
   /*---(copy/clear)---------------------*/
   DEBUG_MAP    yLOG_complex ("copy loc"  , "          %3dxb %4dyb, %3dxe %4dye", s_xbc, s_ybc, s_xec, s_yec);
   rc = ymap_visu_exact  (s_b, s_xbc, s_xec, s_ybc, s_yec, s_z, s_z, 'e');
   DEBUG_MAP    yLOG_complex ("paste loc" , "          %3dxp %4dyp", s_xp, s_yp);
   switch (a_major) {
   case ACT_CLEAR  :
      DEBUG_MAP    yLOG_note ("ACT_CLEAR");
      /*> case 'c' :                                                                     <*/
      /*---(clear)-------------*/
      rc = ymap_mreg_clear ();
      rc = ymap_visu_clear ();
      break;
   case ACT_DELCPY :
      strlcpy (x_method, "normal", LEN_LABEL);
   case ACT_DELMOV :
      DEBUG_MAP    yLOG_note ("ACT_DELCPY/ACT_DELMOV");
      /*> case 'y' :                                                                     <*/
      /*---(copy)--------------*/
      rc = ymap_mreg_save  ();
      rc = ymap_mreg_clear_combo ();
      rc = ymap_visu_clear ();
      /*---(paste)-------------*/
      if (s_nopaste == '-') {
         rc = yMAP_jump (s_b, s_xp, s_yp, s_z);
         rc = ymap_mreg_paste_combo (x_method);
      }
      break;
   case ACT_APPCPY :
      strlcpy (x_method, "normal", LEN_LABEL);
   case ACT_APPMOV :
      DEBUG_MAP    yLOG_note ("ACT_APPCPY/ACT_APPMOV");
      /*> case '-' :                                                                     <*/
      /*---(copy)--------------*/
      rc = ymap_mreg_save  ();
      rc = ymap_mreg_clear ();
      rc = ymap_visu_clear ();
      /*---(paste)-------------*/
      rc = yMAP_jump (s_b, s_xp, s_yp, s_z);
      rc = ymap_mreg_paste_combo (x_method);
      break;
   }
   /*---(move to final pos)--------------*/
   g_xmap.ubeg = s_lef;
   g_ymap.ubeg = s_top;
   rc = yMAP_jump (s_b, s_xbs, s_ybs, s_z);
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> complex delete action --------------[ ------ [gz.430.031.02]*/ /*-[01.0000.213.!]-*/ /*-[--.---.---.--]-*/
ymap__combo_clear       (char a_major, char a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   char        x_len       =    0;
   char        x_pos       =    0;
   char        x_minors    [LEN_LABEL]  = "lhxX··jkyY··iozZ·.";
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP    yLOG_char    ("visu live" , yMAP_visu_islive ());
   --rce;  if (yMAP_visu_islive ()) {
      DEBUG_MAP    yLOG_note    ("function only handles non-selected deletes/clearing");
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP    yLOG_char    ("a_major"   , chrvisible (a_major));
   --rce;  if (a_major != ACT_CLEAR) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP    yLOG_char    ("a_minor"   , chrvisible (a_minor));
   DEBUG_MAP    yLOG_info    ("valid"     , x_minors);
   --rce;  if (a_minor == 0 || strchr (x_minors, a_minor) == NULL) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get and clear)------------------*/
   rc = ymap__combo_prep    (a_major, a_minor);
   /*---(clear)--------------------------*/
   rc = ymap__combo_wrap    (a_major, a_minor);
   /*---(move after)---------------------*/
   switch (a_minor) {
   case 'l' : case OBJ_COLAFT :  rc = yMAP_move_hmode (G_KEY_SPACE, 'l');   break;
   case 'h' : case OBJ_COLBEF :  rc = yMAP_move_hmode (G_KEY_SPACE, 'h');   break;
   case 'j' : case OBJ_ROWAFT :  rc = yMAP_move_hmode (G_KEY_SPACE, 'j');   break;
   case 'k' : case OBJ_ROWBEF :  rc = yMAP_move_hmode (G_KEY_SPACE, 'k');   break;
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> complex delete action --------------[ ------ [gz.430.031.02]*/ /*-[01.0000.213.!]-*/ /*-[--.---.---.--]-*/
ymap__combo_delete      (char a_major, char a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   char        x_pos       =    0;
   char        x_minors    [LEN_LABEL]  = "lhxX·jkyY·iozZ";
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP    yLOG_char    ("visu live" , yMAP_visu_islive ());
   DEBUG_MAP    yLOG_char    ("a_major"   , chrvisible (a_major));
   --rce;  if (a_major == 0 || strchr (ACT_DELETES, a_major) == NULL) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP    yLOG_char    ("a_minor"   , chrvisible (a_minor));
   DEBUG_MAP    yLOG_info    ("valid"     , x_minors);
   --rce;  if (a_minor == 0 || strchr (x_minors, a_minor) == NULL) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get and clear)------------------*/
   rc = ymap__combo_prep    (a_major, a_minor);
   /*---(horizontal)---------------------*/
   switch (a_minor) {
   case 'l' : case OBJ_COLAFT :
      DEBUG_MAP    yLOG_note    ("horizontal RIGHT 'l' and 'x' handling");
      s_xbc = s_xes + 1;
      s_xec = g_xmap.gmax;
      if (s_xbc > s_xec)  s_nopaste = 'y';
      break;
   case 'h' : case OBJ_COLBEF :
      DEBUG_MAP    yLOG_note    ("horizontal LEFT 'h' and 'X' handling");
      s_xbc = g_xmap.gmin;
      s_xec = s_xbs - 1;
      if (s_xbc > s_xec)  s_nopaste = 'y';
      s_xp  = s_xes - (s_xec - s_xbc);
      break;
   }
   /*---(vertical)-----------------------*/
   switch (a_minor) {
   case 'j' : case OBJ_ROWAFT :
      DEBUG_MAP    yLOG_note    ("vertical DOWN 'j' and 'y' handling");
      s_ybc = s_yes + 1;
      s_yec = g_ymap.gmax;
      s_yp  = s_ybs;
      if (s_ybc > s_yec)  s_nopaste = 'y';
      break;
   case 'k' : case OBJ_ROWBEF :
      DEBUG_MAP    yLOG_note    ("vertical UP 'k' and 'Y' handling");
      s_yec = s_ybs - 1;
      s_ybc = g_ymap.gmin;
      s_yp  = s_ybc + s_yl;
      if (s_ybc > s_yec)  s_nopaste = 'y';
      break;
   }
   /*---(paste/move)---------------------*/
   DEBUG_MAP    yLOG_complex ("copy loc"  , "          %3dxb %4dyb, %3dxe %4dye", s_xbc, s_ybc, s_xec, s_yec);
   DEBUG_MAP    yLOG_complex ("paste loc" , "          %3dxp %4dyp", s_xp, s_yp);
   rc = ymap__combo_wrap    (a_major, a_minor);
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> complex append action --------------[ ------ [gz.430.031.02]*/ /*-[01.0000.213.!]-*/ /*-[--.---.---.--]-*/
ymap__combo_append      (char a_major, char a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   char        x_pos       =    0;
   char        x_minors    [LEN_LABEL]  = "lhxX·jkyY·iozZ";
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP    yLOG_char    ("visu live" , yMAP_visu_islive ());
   DEBUG_MAP    yLOG_char    ("a_major"   , chrvisible (a_major));
   --rce;  if (a_major == 0 || strchr (ACT_APPENDS, a_major) == NULL) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MAP    yLOG_char    ("a_minor"   , chrvisible (a_minor));
   DEBUG_MAP    yLOG_info    ("valid"     , x_minors);
   --rce;  if (a_minor == 0 || strchr (x_minors, a_minor) == NULL) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get and clear)------------------*/
   rc = ymap__combo_prep    (a_major, a_minor);
   /*---(horizontal)---------------------*/
   switch (a_minor) {
   case 'l' : case OBJ_COLAFT :  /* insert to right, and full column version         */
      s_xbc = s_xbs + 1;
      s_xec = g_xmap.gmax - s_xl + 1;
      s_xp  = s_xbs + s_xl + 1;
      ++s_xbs;
      if (a_minor == 'l')  break;
      s_yp  = s_ybc = g_ymap.gmin;
      s_yec = g_ymap.gmax;
      break;
   case 'h' : case OBJ_COLBEF :  /* insert to left, and full column version          */
      s_xbc = s_xbs;
      s_xec = g_xmap.gmax - s_xl;
      s_xp  = s_xbs + s_xl;
      if (a_minor == 'h')  break;
      s_yp  = s_ybc = g_ymap.gmin;
      s_yec = g_ymap.gmax;
      break;
   }
   /*---(vertical)-----------------------*/
   switch (a_minor) {
   case 'j' : case OBJ_ROWAFT :  /* insert below, and full column version            */
      s_ybc = s_ybs + 1;
      s_yec = g_ymap.gmax - s_yl + 1;
      s_yp  = s_ybs + s_yl + 1;
      ++s_ybs;
      if (a_minor == 'j')  break;
      s_xp  = s_xbc = g_xmap.gmin;
      s_xec = g_xmap.gmax;
      break;
   case 'k' : case OBJ_ROWBEF :  /* insert above, and full column version            */
      s_ybc = s_ybs;
      s_yec = g_ymap.gmax - s_yl;
      s_yp  = s_ybs + s_yl;
      if (a_minor == 'k')  break;
      s_xp  = s_xbc = g_xmap.gmin;
      s_xec = g_xmap.gmax;
      break;
   }
   /*---(zoom)---------------------------*/
   /*---(paste/move)---------------------*/
   rc = ymap__combo_wrap    (a_major, a_minor);
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__multilike         (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   ushort      u, x, y, z;
   /*---(quick out)----------------------*/
   if (a_major != G_KEY_SPACE)  return 0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(non-visual)---------------------*/
   if (ymap_visu_isdead ()) {
      switch (a_minor) {
      case 'X' :
         rc = ymap_mreg_clear ();
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return 1;
         break;
      }
   }
   /*---(visual)-------------------------*/
   else {
      rc = yMAP_visu_range  (&u, &x, NULL, &y, NULL, &z, NULL, NULL);
      DEBUG_MAP    yLOG_complex ("top-left"  , "%4dr, %3du, %3dx, %3dy, %3dz", rc, u, x, y, z);
      switch (a_minor) {
      case 'x' :
         rc = ymap_mreg_clear ();
         rc = ymap_visu_clear ();
         rc = yMAP_jump (u, x, y, z);
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return 1;
         break;
      }
   }
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__multiend          (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(pastes)-------------------------*/
   if (a_major == 'p') {
      yKEYS_repeat_reset ();
      switch (a_minor) {
      case '_' :  rc = ymap_mreg_visual ();            break;
      case '#' :  rc = ymap_mreg_paste  ("clear");     break;
      case 'x' :  rc = ymap_mreg_paste  ("clear");     break;
      case 'n' :  rc = ymap_mreg_paste  ("normal");    break;
      case 'r' :  rc = ymap_mreg_paste  ("replace");   break;
      case 'd' :  rc = ymap_mreg_paste  ("duplicate"); break;
      case 'm' :  rc = ymap_mreg_paste  ("move");      break;
      case 'f' :  rc = ymap_mreg_paste  ("force");     break;
      }
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(deletes)------------------------*/
   if (tolower (a_major) == 'd') {
      yKEYS_repeat_reset ();
      rc = ymap__combo_delete     (a_major, a_minor);
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(clears)-------------------------*/
   if (a_major == 'x') {
      yKEYS_repeat_reset ();
      rc = ymap__combo_clear      (a_major, a_minor);
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(appends)------------------------*/
   if (tolower (a_major) == 'a') {
      yKEYS_repeat_reset ();
      rc = ymap__combo_append     (a_major, a_minor);
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__submodes          (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       t           [LEN_TERSE] = "";
   /*---(quick out)----------------------*/
   if (a_major != G_KEY_SPACE)  return 0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(any time)-----------------------*/
   switch (a_minor) {
   case 'G'      :
      DEBUG_YMAP   yLOG_note    ("entering god mode");
      yMODE_enter  (MODE_GOD);
      rc = 0;
      break;
   case ':'      :
      DEBUG_YMAP   yLOG_note    ("entering command mode");
      ySRC_start (":");
      rc = 'A';
      break;
   case '/'      :
      DEBUG_YMAP   yLOG_note    ("entering search mode");
      ySRC_start ("/");
      rc = ' ';
      break;
   case ';'      :
      DEBUG_YMAP   yLOG_note    ("entering hint sub-mode");
      ySRC_start (";");
      rc = ' ';
      break;
   case '\\'     :
      DEBUG_YMAP   yLOG_note    ("entering menu sub-mode");
      yMODE_enter  (SMOD_MENUS);
      rc = a_minor;
      break;
   case ','      :
      DEBUG_YMAP   yLOG_note    ("entering universe sub-mode");
      yMODE_enter  (UMOD_UNIVERSE);
      rc = a_minor;
      break;
   case '"'      :
      DEBUG_YMAP   yLOG_note    ("entering mapreg sub-mode");
      yMODE_enter  (SMOD_MREG);
      rc = a_minor;
      break;
   case 'E'      :
      DEBUG_YMAP   yLOG_note    ("entering error sub-mode");
      yMODE_enter  (SMOD_ERROR);
      rc = a_minor;
      break;
   case 'F'      : case 'f'      :
      DEBUG_YMAP   yLOG_note    ("entering format external-mode");
      yMODE_enter  (XMOD_FORMAT);
      rc = a_minor;
      break;
   }
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(non-selection)------------------*/
   if (ymap_visu_isdead ()) {
      switch (a_minor) {
      case  G_KEY_RETURN :      /* edit existing cell               */
         DEBUG_YMAP   yLOG_note    ("edit existing map location");
         ySRC_start ("¦");
         rc = ' ';
         break;
      case  's'  :              /* replace cell entirely            */
         DEBUG_YMAP   yLOG_note    ("replace existing map location");
         ySRC_start ("");
         rc = ' ';
         break;
      case  '='  : case  '#'  : /* replace cell with formula        */
         DEBUG_YMAP   yLOG_note    ("replace existing map location with formula");
         sprintf (t, "%c", a_minor);
         ySRC_start (t);
         rc = ' ';
         break;
      case  '+'  : case  '-'  : /* replace cell with a number       */
         DEBUG_YMAP   yLOG_note    ("replace existing map location with number");
         sprintf (t, "%c", a_minor);
         ySRC_start (t);
         rc = ' ';
         break;
      }
   }
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(visual selection)---------------*/
   if (yMAP_visu_islive ()) {
      switch (a_minor) {
      case  '+'  : case  '-'  : /* import and export sub-mode       */
         DEBUG_YMAP   yLOG_note    ("import/export map registers");
         /*> yMODE_enter (SMOD_MREG);                                                 <* 
          *> rc = yvikeys_mreg_smode  ('"', a_minor);                                 <*/
         break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}


/*> char                                                                              <* 
 *> yvikeys__map_mode_chg   (char a_minor)                                            <* 
 *> {                                                                                 <* 
 *>    char        rc          =   -1;                                                <* 
 *>    char        t           [5];                                                   <* 
 *>    /+---(common modes)----------------+/                                          <* 
 *>    DEBUG_YMAP   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    DEBUG_YMAP   yLOG_char    ("change"    , a_minor);                             <* 
 *>    /+---(selecting and marking)-------+/                                          <* 
 *>    switch (a_minor) {                                                             <* 
 *>    case 'v'      :                                                                <* 
 *>       if (yvikeys_visu_islive ())   yvikeys_visu_reverse  ();                     <* 
 *>       else                          yvikeys_visu_makelive ();                     <* 
 *>       rc = 0;                                                                     <* 
 *>       break;                                                                      <* 
 *>    case 'M'      : case 'V'      :                                                <* 
 *>       DEBUG_YMAP   yLOG_note    ("entering visual selection history sub-mode");   <* 
 *>       rc = yMODE_enter  (UMOD_VISUAL  );                                          <* 
 *>       if (rc >= 0)  rc = a_minor;                                                 <* 
 *>       break;                                                                      <* 
 *>    case 'm'      : case '\''     :                                                <* 
 *>       DEBUG_YMAP   yLOG_note    ("entering location mark sub-mode");              <* 
 *>       rc = yMODE_enter  (UMOD_MARK    );                                          <* 
 *>       if (rc >= 0)  rc = a_minor;                                                 <* 
 *>       break;                                                                      <* 
 *>    }                                                                              <* 
 *>    if (rc >= 0) {                                                                 <* 
 *>       DEBUG_YMAP   yLOG_value   ("rc"        , rc);                               <* 
 *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                   <* 
 *>       return rc;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(import/export)---------------+/                                          <* 
 *>    if (yvikeys_visu_islive () && strchr ("+-"   , a_minor) != NULL) {             <* 
 *>       yMODE_enter (SMOD_MREG);                                                    <* 
 *>       rc = yvikeys_mreg_smode  ('"', a_minor);                                    <* 
 *>    }                                                                              <* 
 *>    if (rc >= 0) {                                                                 <* 
 *>       DEBUG_YMAP   yLOG_value   ("rc"        , rc);                               <* 
 *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                   <* 
 *>       return rc;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);                                  <* 
 *>    return rc;                                                                     <* 
 *> }                                                                                 <*/

char
ymap_mode               (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_grid      =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("a_major"   , a_major);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , chrvisible (a_minor));
   DEBUG_YMAP   yLOG_value   ("a_minor"   , a_minor);
   /*---(defenses)-----------------------*/
   DEBUG_YMAP   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (MODE_MAP    )) {
      DEBUG_YMAP   yLOG_note    ("not the correct mode");
      yMODE_exit  ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(universal)----------------------*/
   rc = ymap__biggies    (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("biggies"   , rc);
   if (rc != 0) {
      if (rc > 0)  rc = 0;
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(repeat)-------------------------*/
   if (yKEYS_is_repeater (a_minor)) {
      DEBUG_YMAP   yLOG_note    ("repeating");
      yMODE_enter  (PMOD_REPEAT);
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return a_minor;
   }
   /*---(multikey)-----------------------*/
   rc = ymap__multibeg   (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("multibeg"  , rc);
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   rc = ymap__multilike  (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("multiend"  , rc);
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   rc = ymap__multiend   (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("multiend"  , rc);
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(sub-modes)----------------------*/
   rc = ymap__submodes  (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("submodes"  , rc);
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(moves)--------------------------*/
   rc = yMAP_move_hmode (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("moves"     , rc);
   if (rc != 0) {  /* also for failed goto, scroll, or end multikeys */
      if (a_minor == 'v')  rc = 0;
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(visual)-------------------------*/
   rc = ymap_visu_hmode (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("visu"      , rc);
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(registers)----------------------*/
   rc = yMAP_mreg_hmode  (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("mreg"      , rc);
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return 0;
   }
   /*---(macros)-------------------------*/
   rc = yMACRO_hmode  (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("macros"    , rc);
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(mundo)--------------------------*/
   rc = ymap_mundo_hmode  (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("mundo"     , rc);
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return 0;
   }
   /*---(search)-------------------------*/
   rc = yMARK_find_hmode  (a_major, a_minor);
   DEBUG_YMAP   yLOG_value   ("srch"      , rc);
   if (rc != 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rc);
      return 0;
   }
   /*---(single key)---------------------*/
   DEBUG_YMAP   yLOG_note    ("review single keys");
   /*> --rce;                                                                         <* 
    *> if (a_major == ' ') {                                                          <* 
    *>    DEBUG_YMAP   yLOG_note    ("no or empty major");                            <* 
    *>    /+---(speed)-----------------------+/                                       <* 
    *>    if (a_minor == '\t' || a_minor == 9) {                                      <* 
    *>       DEBUG_YMAP   yLOG_note    ("MAP MODE BLITZ");                            <* 
    *>       yvikeys_loop_blitz ();                                                   <* 
    *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return 0;                                                                <* 
    *>    } else if (a_minor == '\b' || a_minor == 127) {                             <* 
    *>       DEBUG_YMAP   yLOG_note    ("MAP MODE UNBLITZ");                          <* 
    *>       yvikeys_loop_unblitz ();                                                 <* 
    *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return 0;                                                                <* 
    *>    }                                                                           <* 
    *>    /+---(repeat)----------------------+/                                       <* 
    *>    if (strchr (g_repeat, a_minor) != 0) {                                      <* 
    *>       DEBUG_YMAP   yLOG_note    ("repeating");                                 <* 
    *>       yMODE_enter  (PMOD_REPEAT);                                              <* 
    *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return a_minor;                                                          <* 
    *>    }                                                                           <* 
    *>    /+---(multikey prefixes)-----------+/                                       <* 
    *>    if (yvikeys_visu_isdead () && strchr (g_multimap , a_minor) != 0) {         <* 
    *>       DEBUG_YMAP   yLOG_note    ("prefix of multimap keystring");              <* 
    *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return a_minor;                                                          <* 
    *>    }                                                                           <* 
    *>    if (yvikeys_visu_islive () && strchr (g_multivisu, a_minor) != 0) {         <* 
    *>       DEBUG_YMAP   yLOG_note    ("prefix of visual multimap keystring");       <* 
    *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return a_minor;                                                          <* 
    *>    }                                                                           <* 
    *>    /+---(grouping)--------------------+/                                       <* 
    *>    if (a_minor == '(') {                                                       <* 
    *>       DEBUG_YMAP   yLOG_note    ("begin group");                               <* 
    *>       yKEYS_group_beg ();                                                      <* 
    *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return 0;                                                                <* 
    *>    }                                                                           <* 
    *>    if (a_minor == ')') {                                                       <* 
    *>       DEBUG_YMAP   yLOG_note    ("end group");                                 <* 
    *>       yKEYS_group_end ();                                                      <* 
    *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return 0;                                                                <* 
    *>    }                                                                           <* 
    *>    /+---(funky moves)-----------------+/                                       <* 
    *>    if (a_minor == ':') {                                                       <* 
    *>       x_grid = yKEYS_repeat_useall ();                                         <* 
    *>       if (x_grid > 0) {                                                        <* 
    *>          rc = yvikeys__map_move   (x_grid, &g_ymap);                           <* 
    *>          yvikeys__screen (&g_ymap);                                            <* 
    *>          yvikeys_map_reposition  ();                                           <* 
    *>          DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                             <* 
    *>          return rc;;                                                           <* 
    *>       }                                                                        <* 
    *>       /+ non-repeat fall thru  +/                                              <* 
    *>    }                                                                           <* 
    *>    if (a_minor == '|') {                                                       <* 
    *>       rc = yvikeys__map_move   (yKEYS_repeat_useall (), &g_xmap);              <* 
    *>       yvikeys__screen (&g_xmap);                                               <* 
    *>       yvikeys_map_reposition  ();                                              <* 
    *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return rc;                                                               <* 
    *>    }                                                                           <* 
    *>    if (a_minor == '%') {                                                       <* 
    *>       rc = yvikeys__map_move   (yKEYS_repeat_useall (), &g_ymap);              <* 
    *>       yvikeys__screen (&g_ymap);                                               <* 
    *>       yvikeys_map_reposition  ();                                              <* 
    *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return rc;                                                               <* 
   *>    }                                                                           <* 
      *>    /+---(mode changes)----------------+/                                       <* 
      *>    if (strchr (s_map_modes, a_minor) != 0) {                                   <* 
         *>       DEBUG_YMAP   yLOG_note    ("mode changes");                              <* 
            *>       rc = yvikeys__map_mode_chg (a_minor);                                    <* 
            *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
            *>       return rc;                                                               <* 
            *>    }                                                                           <* 
            *>    if (strchr ("yYpPx", a_minor) != 0) {                                       <* 
               *>       DEBUG_YMAP   yLOG_note    ("switch to a map register mode");             <* 
                  *>       yMODE_enter (SMOD_MREG);                                                 <* 
                  *>       rc = yvikeys_mreg_smode  (G_KEY_SPACE, a_minor);                         <* 
                  *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
                  *>       return rc;                                                               <* 
                  *>    }                                                                           <* 
                  *>    /+---(normal)----------------------+/                                       <* 
                  *>    if (strchr (g_hsimple, a_minor) != 0) {                                     <* 
                     *>       rc = yvikeys__map_horz   (a_major, a_minor);                             <* 
                        *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
                        *>       return rc;                                                               <* 
                        *>    }                                                                           <* 
                        *>    if (strchr (g_vsimple, a_minor) != 0) {                                     <* 
                           *>       rc = yvikeys__map_vert   (a_major, a_minor);                             <* 
                              *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
                              *>       return rc;                                                               <* 
                              *>    }                                                                           <* 
                              *>    if (strchr (g_search, a_minor) != 0) {                                      <* 
                                 *>       rc = yvikeys_srch_by_cursor (a_minor, NULL);                             <* 
                                    *>       if (rc >= 0) {                                                           <* 
                                       *>          yvikeys__screen (&g_xmap);                                            <* 
                                          *>          yvikeys__screen (&g_ymap);                                            <* 
                                          *>          yvikeys__screen (&g_zmap);                                            <* 
                                          *>          yvikeys_map_reposition  ();                                           <* 
                                          *>       }                                                                        <* 
                                          *>       DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                <* 
                                          *>       if (rc > 0)  rc = -1;                                                    <* 
                                          *>       return rc;                                                               <* 
                                          *>    }                                                                           <* 
                                          *>    DEBUG_YMAP   yLOG_note    ("no matches found");                             <* 
                                          *> }                                                                              <*/
                                          /*---(complete)------------------------------*/
                                          DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return rc;
}


