/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"

/*
 *  must update selections on grid changes (add col, row, ...).  HOW?
 *
 *  do i wish read and write of visual ranges?
 *
 *
 *
 */



tVISU       s_visus     [S_VISU_MAX];
char        s_nvisu     =   0;
char        S_VISU_LIST [S_VISU_MAX];
tVISU      *s_curr      = NULL;
tVISU      *s_prev      = NULL;



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void  o___UTILITY_________o () { return; }

char 
ymap_visu_valid         (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_senter  (__FUNCTION__);
   /*---(check)--------------------------*/
   DEBUG_MAP    yLOG_snote   ("check");
   rc = strlchr (S_VISU_LIST, a_abbr, S_VISU_MAX);
   DEBUG_MAP    yLOG_sint    (rc);
   --rce;  if (a_abbr == 0 || rc < 0) {
      DEBUG_MAP    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_visu_index         (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_senter  (__FUNCTION__);
   /*---(check)--------------------------*/
   DEBUG_MAP    yLOG_snote   ("check");
   n  = strchr (S_VISU_LIST, a_abbr) - S_VISU_LIST;
   DEBUG_MAP    yLOG_sint    (n);
   --rce;  if (a_abbr == 0 || n  < 0) {
      DEBUG_MAP    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_sexit   (__FUNCTION__);
   return n;
}



/*====================------------------------------------====================*/
/*===----                        small helpers                         ----===*/
/*====================------------------------------------====================*/
static void  o___HELPERS_________o () { return; }

char
ymap__visu_wipe         (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =    0;
   tVISU      *x_visu      = NULL;
   /*---(check)--------------------------*/
   n = ymap_visu_index (a_abbr);
   --rce;  if (n < 0) return n;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_senter  (__FUNCTION__);
   DEBUG_MAP    yLOG_schar   (a_abbr);
   DEBUG_MAP    yLOG_sint    (n);
   /*---(pointer)------------------------*/
   x_visu = s_visus + n;
   DEBUG_MAP    yLOG_spoint  (x_visu);
   /*---(mark self)----------------------*/
   if (strchr ("'>", a_abbr) != NULL)   x_visu->abbr   = a_abbr;
   /*---(active)-------------------------*/
   DEBUG_MAP    yLOG_snote   ("inactive");
   x_visu->active = VISU_NOT;
   x_visu->modded = '-';
   /*---(buf)----------------------------*/
   DEBUG_MAP    yLOG_snote   ("buf");
   x_visu->u_all  = 0;
   /*---(x_pos)--------------------------*/
   DEBUG_MAP    yLOG_snote   ("x");
   x_visu->x_root = 0;
   x_visu->x_beg  = 0;
   x_visu->x_end  = 0;
   /*---(y_pos)--------------------------*/
   DEBUG_MAP    yLOG_snote   ("y");
   x_visu->y_root = 0;
   x_visu->y_beg  = 0;
   x_visu->y_end  = 0;
   /*---(z_pos)--------------------------*/
   DEBUG_MAP    yLOG_snote   ("z");
   x_visu->z_root = 0;
   x_visu->z_beg  = 0;
   x_visu->z_end  = 0;
   /*---(labels)-------------------------*/
   DEBUG_MAP    yLOG_snote   ("labels");
   strlcpy (x_visu->b_label, ""   , LEN_LABEL);
   strlcpy (x_visu->e_label, ""   , LEN_LABEL);
   /*---(locks)--------------------------*/
   DEBUG_MAP    yLOG_snote   ("locks");
   x_visu->x_lock = '-';
   x_visu->y_lock = '-';
   x_visu->z_lock = '-';
   x_visu->source = '-';
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap__visu_copy         (uchar a_dst, uchar a_src)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =    0;
   tVISU      *x_src       = NULL;
   tVISU      *x_dst       = NULL;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(destination)--------------------*/
   DEBUG_MAP    yLOG_char    ("a_dst"     , a_dst);
   n = ymap_visu_index (a_dst);
   DEBUG_MAP    yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_dst  = s_visus + n;
   DEBUG_MAP    yLOG_point   ("x_dst"     , x_dst);
   /*---(source)-------------------------*/
   DEBUG_MAP    yLOG_char    ("a_src"     , a_src);
   n = ymap_visu_index (a_src);
   DEBUG_MAP    yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_src  = s_visus + n;
   DEBUG_MAP    yLOG_point   ("x_src"     , x_src);
   /*---(mark self)----------------------*/
   if (strchr ("'<?", a_dst) != NULL) {
      if (strchr ("'<?", a_src) != NULL) {
         DEBUG_MAP    yLOG_note    ("copying between '<?");
         x_dst->abbr   = x_src->abbr;
         x_dst->modded = x_src->modded;
      } else {
         DEBUG_MAP    yLOG_note    ("copying from saved to '<?");
         x_dst->abbr   = a_src;
         x_dst->modded = '-';
      }
   }
   /*---(active)-------------------------*/
   DEBUG_MAP    yLOG_note    ("active");
   x_dst->active = x_src->active;
   /*---(buf)----------------------------*/
   DEBUG_MAP    yLOG_note    ("buf");
   x_dst->u_all  = x_src->u_all;
   /*---(x_pos)--------------------------*/
   DEBUG_MAP    yLOG_note    ("x");
   x_dst->x_root = x_src->x_beg;  /* always override root with beg  */
   x_dst->x_beg  = x_src->x_beg;
   x_dst->x_end  = x_src->x_end;
   /*---(y_pos)--------------------------*/
   DEBUG_MAP    yLOG_note    ("y");
   x_dst->y_root = x_src->y_beg;  /* always override root with beg  */
   x_dst->y_beg  = x_src->y_beg;
   x_dst->y_end  = x_src->y_end;
   /*---(z_pos)--------------------------*/
   DEBUG_MAP    yLOG_note    ("z");
   x_dst->z_root = x_src->z_beg;  /* always override root with beg  */
   x_dst->z_beg  = x_src->z_beg;
   x_dst->z_end  = x_src->z_end;
   /*---(labels)-------------------------*/
   DEBUG_MAP    yLOG_note    ("labels");
   strlcpy (x_dst->b_label, x_src->b_label, LEN_LABEL);
   strlcpy (x_dst->e_label, x_src->e_label, LEN_LABEL);
   /*---(locks)--------------------------*/
   DEBUG_MAP    yLOG_note    ("locks");
   x_dst->x_lock = x_src->x_lock;
   x_dst->y_lock = x_src->y_lock;
   x_dst->z_lock = x_src->z_lock;
   x_dst->source = x_src->source;
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char  /*-> adjust the visual selection --------[ ------ [ge.760.324.D2]*/ /*-[01.0000.015.X]-*/ /*-[--.---.---.--]-*/
ymap_visu_update          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   ushort      u, x, y, z;
   /*---(prepare)------------------------*/
   rc = yMAP_current         (NULL, &u, &x, &y, &z);
   --rce;  if (rc < 0) {
      return rce;
   }
   /*---(not-live)-----------------------*/
   DEBUG_MAP    yLOG_senter  (__FUNCTION__);
   if (s_curr->active == VISU_NOT) {
      DEBUG_MAP    yLOG_snote   ("inactive visual");
      s_curr->abbr    = '-';
      s_curr->modded  = '-';
      s_curr->u_all   = u;
      s_curr->x_root  = s_curr->x_beg   = s_curr->x_end   = x;
      s_curr->y_root  = s_curr->y_beg   = s_curr->y_end   = y;
      s_curr->z_root  = s_curr->z_beg   = s_curr->z_end   = z;
      ymap_addresser (s_curr->b_label, u, x, y, z);
      --rce;  if (rc < 0) {
         return rce;
      }
      strlcpy  (s_curr->e_label, s_curr->b_label, LEN_LABEL);
      return 0;
   }
   /*---(before real updates)------------*/
   --rce;  if (u != s_curr->u_all) {
      return rce;
   }
   /*---(x)------------------------------*/
   if (s_curr->x_lock != 'y') {
      DEBUG_MAP    yLOG_snote   ("update x");
      if (x < s_curr->x_root) {
         s_curr->x_beg  = x;
         s_curr->x_end  = s_curr->x_root;
      } else {
         s_curr->x_beg  = s_curr->x_root;
         s_curr->x_end  = x;
      }
   }
   /*---(y)------------------------------*/
   if (s_curr->y_lock != 'y') {
      DEBUG_MAP    yLOG_snote   ("update y");
      if (y < s_curr->y_root) {
         s_curr->y_beg  = y;
         s_curr->y_end  = s_curr->y_root;
      } else {
         s_curr->y_beg  = s_curr->y_root;
         s_curr->y_end  = y;
      }
   }
   DEBUG_MAP    yLOG_sexit   (__FUNCTION__);
   /*---(set labels)---------------------*/
   rc = ymap_addresser (s_curr->b_label, s_curr->u_all, s_curr->x_beg, s_curr->y_beg, s_curr->z_beg);
   --rce;  if (rc < 0) {
      return rce;
   }
   rc = ymap_addresser (s_curr->e_label, s_curr->u_all, s_curr->x_end, s_curr->y_end, s_curr->z_end);
   --rce;  if (rc < 0) {
      return rce;
   }
   /*---(mark modded)--------------------*/
   s_curr->modded = '+';
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     check and setters                        ----===*/
/*====================------------------------------------====================*/
static void  o___QUICK___________o () { return; }

char ymap_visu_getlive    (void) { return s_curr->active; }
char ymap_visu_islive     (void) { if (s_curr->active == VISU_YES)  return 1; return 0; }
char ymap_visu_isdead     (void) { if (s_curr->active == VISU_NOT)  return 1; return 0; }
char ymap_visu_makelive   (void) { s_curr->active = VISU_YES; return 0; }



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char         /*-> remove marks -----------------------[ ------ [gz.642.141.12]*/ /*-[01.0000.033.3]-*/ /*-[--.---.---.--]-*/
ymap_visu_purge         (char a_scope)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           = 0;
   char        x_abbr      = 0;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_char    ("a_scope"   , a_scope);
   --rce;  switch (a_scope) {
   case YSTR_ILOWER  : case YSTR_IUPPER  : case YSTR_INUMBER :
   case YSTR_IGREEK  : case YSTR_IFULL   :
      break;
   default :
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   DEBUG_MAP    yLOG_value   ("nvisu"     , s_nvisu);
   for (i = 0; i < s_nvisu; ++i) {
      x_abbr = S_VISU_LIST [i];
      if (a_scope == YSTR_IUPPER  && strchr (YSTR_UPPER , x_abbr) == NULL)  continue;
      if (a_scope == YSTR_ILOWER  && strchr (YSTR_LOWER , x_abbr) == NULL)  continue;
      if (a_scope == YSTR_INUMBER && strchr (YSTR_NUMBER, x_abbr) == NULL)  continue;
      if (a_scope == YSTR_IGREEK  && strchr (YSTR_GREEK , x_abbr) == NULL)  continue;
      ymap__visu_wipe  (x_abbr);
   }
   /*---(globals)------------------------*/
   DEBUG_MAP    yLOG_note    ("initialize globals");
   myMAP.v_head  = '-';
   myMAP.v_curr  = '-';
   myMAP.v_tail  = '-';
   /*> yvikeys_visu__range ();                                                        <*/
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_visu_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (UMOD_VISUAL)) {
      DEBUG_PROG   yLOG_note    ("status is not ready for init");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(visu abbrev list)---------------*/
   strlcpy (S_VISU_LIST, "'"        , S_VISU_MAX);
   strlcat (S_VISU_LIST, "<"        , S_VISU_MAX);
   strlcat (S_VISU_LIST, YSTR_LOWER , S_VISU_MAX);
   strlcat (S_VISU_LIST, YSTR_UPPER , S_VISU_MAX);
   strlcat (S_VISU_LIST, YSTR_NUMBER, S_VISU_MAX);
   strlcat (S_VISU_LIST, YSTR_GREEK , S_VISU_MAX);
   strlcat (S_VISU_LIST, "?"        , S_VISU_MAX);
   DEBUG_PROG   yLOG_info    ("LIST"      , S_VISU_LIST);
   s_nvisu  = strlen (S_VISU_LIST);
   DEBUG_MAP    yLOG_value   ("nvisu"     , s_nvisu);
   /*---(set pointers)-------------------*/
   s_curr = s_visus + 0;
   s_prev = s_visus + 1;
   /*---(clear)--------------------------*/
   ymap_visu_purge  (YSTR_IFULL);
   s_curr->abbr   = s_prev->abbr   = '-';
   /*> yVIKEYS_view_optionX (YVIKEYS_STATUS, "visual" , yvikeys_visu_status , "details of visual selection"                );   <*/
   /*---(update status)------------------*/
   yMODE_init_set   (UMOD_VISUAL, NULL, ymap_visu_umode);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       visual setting                         ----===*/
/*====================------------------------------------====================*/
static void  o___SETTING_________o () { return; }

char       /*-> clear the selection ----------------[ ------ [gz.742.001.13]*/ /*-[01.0000.743.A]-*/ /*-[--.---.---.--]-*/
ymap_visu_clear             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x, y;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(set prev)-----------------------*/
   /*> yvikeys_visu__set ('\'');                                                      <*/
   /*---(backup)-------------------------*/
   s_curr->abbr   = '-';
   s_curr->active = VISU_NOT;
   s_curr->x_lock = '-';
   s_curr->y_lock = '-';
   s_curr->z_lock = '-';
   s_curr->modded = '-';
   ymap_visu_update ();
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_visu_exact         (ushort u, ushort xb, ushort xe, ushort yb, ushort ye, ushort zb, ushort ze)
{  /*---(design notes)--------------------------------------------------------*/
   /* if the two ends of the range are legal, this function will change the   */
   /* current selection to the boundaries passed as arguments.                */
   /*---(locals)-----------+-----------+-*//*---------------------------------*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_beg       [LEN_LABEL];
   char        x_end       [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   DEBUG_MAP    yLOG_complex ("args"      , "%3db,  %4d to %4dx,  %4d to %4dy,  %4d to %4dz", u, xb, xe, yb, ye, zb, ze);
   /*---(prepare)------------------------*/
   DEBUG_MAP    yLOG_note    ("clear existing ranges");
   rc = ymap_visu_clear ();
   /*---(check limits)-------------------*/
   --rce;  if (ymap_valid  (u, xb, yb, zb) < 0)  {
      DEBUG_MAP    yLOG_note    ("beginning not legal/mapped");
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (ymap_valid  (u, xe, ye, ze) < 0)  {
      DEBUG_MAP    yLOG_note    ("ending not legal/mapped");
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set labels)---------------------*/
   rc = ymap_addresser (x_beg, u, xb, yb, zb);
   DEBUG_MAP    yLOG_value   ("beg label" , rc);
   --rce;  if (rc < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ymap_addresser (x_end, u, xe, ye, ze);
   DEBUG_MAP    yLOG_value   ("end label" , rc);
   --rce;  if (rc < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set range)----------------------*/
   DEBUG_MAP    yLOG_note    ("set range live");
   s_curr->active  = VISU_YES;
   /*---(locations)----------------------*/
   DEBUG_MAP    yLOG_note    ("set range coordinates");
   s_curr->u_all  = u;
   s_curr->x_root = s_curr->x_beg  = xb;
   s_curr->x_end  = xe;
   s_curr->y_root = s_curr->y_beg  = yb;
   s_curr->y_end  = ye;
   s_curr->z_root = s_curr->z_beg  = zb;
   s_curr->z_end  = ze;
   strlcpy (s_curr->b_label, x_beg, LEN_LABEL);
   strlcpy (s_curr->e_label, x_end, LEN_LABEL);
   /*---(jump to the end)----------------*/
   yMAP_jump (u, xe, ye, ze);
   s_curr->abbr   = '-';
   s_curr->modded = '+';
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_visu_reverse       (void)
{
   if (s_curr->active == VISU_NOT)  return 0;
   /*---(if x locked)--------------------*/
   if (s_curr->x_lock == 'y') {
      if (s_curr->y_root == s_curr->y_beg) {
         s_curr->y_root = s_curr->y_end;
         yMAP_jump (s_curr->u_all, s_curr->x_root, s_curr->y_beg, s_curr->z_beg);
      }
      else  {
         s_curr->y_root = s_curr->y_beg;
         yMAP_jump (s_curr->u_all, s_curr->x_root, s_curr->y_end, s_curr->z_beg);
      }
      return 0;
   }
   /*---(if y locked)--------------------*/
   if (s_curr->y_lock == 'y') {
      if (s_curr->x_root == s_curr->x_beg) {
         s_curr->x_root = s_curr->x_end;
         yMAP_jump (s_curr->u_all, s_curr->x_beg, s_curr->y_root, s_curr->z_beg);
      }
      else  {
         s_curr->x_root = s_curr->x_beg;
         yMAP_jump (s_curr->u_all, s_curr->x_end, s_curr->y_root, s_curr->z_beg);
      }
      return 0;
   }
   /*---(root at beg)--------------------*/
   if (s_curr->x_root == s_curr->x_beg && s_curr->y_root == s_curr->y_beg) {
      s_curr->x_root = s_curr->x_end;
      s_curr->y_root = s_curr->y_end;
      yMAP_jump (s_curr->u_all, s_curr->x_beg, s_curr->y_beg, s_curr->z_beg);
      return 0;
   }
   /*---(root at end)--------------------*/
   s_curr->x_root = s_curr->x_beg;
   s_curr->y_root = s_curr->y_beg;
   yMAP_jump (s_curr->u_all, s_curr->x_end, s_curr->y_end, s_curr->z_beg);
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap_visu_locking       (char a_type)
{
   char        rce         =  -10;
   char        rc          =    0;
   if (s_curr->active == VISU_NOT)  return 0;
   switch (a_type) {
   case 'y'  :
      if (s_curr->y_lock == 'y') {
         DEBUG_USER   yLOG_note    ("unlock y full y_axis selection");
         s_curr->y_lock = '-';
         if (s_curr->y_root <= g_ymap.gcur) {
            s_curr->y_beg  = s_curr->y_root;
            s_curr->y_end  = g_ymap.gcur;
         } else {
            s_curr->y_end  = s_curr->y_root;
            s_curr->y_beg  = g_ymap.gcur;
         }
      } else {
         DEBUG_USER   yLOG_note    ("lock y for full y_axis selection");
         s_curr->y_lock = 'y';
         s_curr->y_beg  = g_ymap.gmin;
         s_curr->y_end  = g_ymap.gmax;
      }
      break;
   case 'x'  :
      if (s_curr->x_lock == 'y') {
         DEBUG_USER   yLOG_note    ("unlock x full x-axis selection");
         s_curr->x_lock = '-';
         if (s_curr->x_root <= g_xmap.gcur) {
            s_curr->x_beg  = s_curr->x_root;
            s_curr->x_end  = g_xmap.gcur;
         } else {
            s_curr->x_end  = s_curr->x_root;
            s_curr->x_beg  = g_xmap.gcur;
         }
      } else {
         DEBUG_USER   yLOG_note    ("lock x for full x-axis selection");
         s_curr->x_lock = 'y';
         s_curr->x_beg  = g_xmap.gmin;
         s_curr->x_end  = g_xmap.gmax;
      }
      break;
   case '!'  :
      DEBUG_USER   yLOG_note    ("! for screen selection");
      s_curr->y_lock = '-';
      s_curr->y_root = g_ymap.gbeg;
      s_curr->y_beg  = g_ymap.gbeg;
      s_curr->y_end  = g_ymap.gend;
      s_curr->x_lock = '-';
      s_curr->x_root = g_xmap.gbeg;
      s_curr->x_beg  = g_xmap.gbeg;
      s_curr->x_end  = g_xmap.gend;
      yMAP_jump (s_curr->u_all, s_curr->x_end, s_curr->y_end, s_curr->z_end);
      break;
   case '*'  :
      DEBUG_USER   yLOG_note    ("* for all on current z selection");
      s_curr->y_lock = 'y';
      s_curr->y_beg  = g_ymap.gmin;
      s_curr->y_end  = g_ymap.gmax;
      s_curr->x_lock = 'y';
      s_curr->x_beg  = g_xmap.gmin;
      s_curr->x_end  = g_xmap.gmax;
      break;
   default   :
      DEBUG_USER   yLOG_note    ("option not understood");
      return -1;
   }
   /*---(update selection)---------------*/
   ymap_visu_update ();
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       visual history                         ----===*/
/*====================------------------------------------====================*/
static void  o___HISTORY_________o () { return; }

char         /*-> tbd --------------------------------[ leaf   [gz.640.021.20]*/ /*-[01.0000.044.!]-*/ /*-[--.---.---.--]-*/
ymap__visu_range        (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_senter  (__FUNCTION__);
   /*---(find next)----------------------*/
   myMAP.v_head = '-';
   for (i = 2; i < s_nvisu - 2; ++i) {
      if (s_visus [i].active == VISU_NOT) continue;
      myMAP.v_head = S_VISU_LIST [i];
      DEBUG_MAP    yLOG_schar   (myMAP.v_head);
      DEBUG_MAP    yLOG_snote   ("HEAD");
      break;
   }
   /*---(find last)----------------------*/
   myMAP.v_tail = '-';
   for (i = s_nvisu - 2; i >  1; --i) {
      if (s_visus [i].active == VISU_NOT) continue;
      myMAP.v_tail = S_VISU_LIST [i];
      DEBUG_MAP    yLOG_schar   (myMAP.v_tail);
      DEBUG_MAP    yLOG_snote   ("TAIL");
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [ge.732.043.21]*/ /*-[01.0000.014.!]-*/ /*-[--.---.---.--]-*/
ymap__visu_prev      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        x_abbr      =  '-';
   int         x_index     =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(check mark)---------------------*/
   DEBUG_MAP    yLOG_char    ("visu_curr" , myMAP.v_curr);
   x_index = ymap_visu_index (myMAP.v_curr);
   DEBUG_MAP    yLOG_value   ("x_index"   , x_index);
   --rce;  if (x_index < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find previous)------------------*/
   DEBUG_MAP    yLOG_note    ("search for previous mark");
   for (i = x_index - 1; i > 1; --i) {
      if (s_visus [i].active == VISU_NOT )  continue;
      DEBUG_MAP    yLOG_value   ("found"     , i);
      x_abbr = S_VISU_LIST [i];
      DEBUG_MAP    yLOG_char    ("x_abbr"    , x_abbr);
      DEBUG_MAP    yLOG_exit    (__FUNCTION__);
      return x_abbr;
   }
   DEBUG_MAP    yLOG_note    ("not found");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char         /*-> tbd --------------------------------[ ------ [ge.842.053.21]*/ /*-[01.0000.014.!]-*/ /*-[--.---.---.--]-*/
ymap__visu_next         (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        x_abbr      =  '-';
   int         x_index     =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(check mark)---------------------*/
   DEBUG_MAP    yLOG_char    ("visu_curr" , myMAP.v_curr);
   x_index = ymap_visu_index (myMAP.v_curr);
   DEBUG_MAP    yLOG_value   ("x_index"   , x_index);
   --rce;  if (x_index < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find next)----------------------*/
   DEBUG_MAP    yLOG_note    ("search for next mark");
   for (i = x_index + 1; i < s_nvisu - 2; ++i) {
      if (s_visus [i].active == VISU_NOT )  continue;
      DEBUG_MAP    yLOG_value   ("found"     , i);
      x_abbr = S_VISU_LIST [i];
      DEBUG_MAP    yLOG_char    ("x_abbr"    , x_abbr);
      myMAP.v_curr    = x_abbr;
      DEBUG_MAP    yLOG_exit    (__FUNCTION__);
      return x_abbr;
   }
   DEBUG_MAP    yLOG_note    ("not found");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char         /*-> tbd --------------------------------[ ------ [ge.A52.153.55]*/ /*-[01.0000.033.8]-*/ /*-[--.---.---.--]-*/
ymap__visu_unset        (uchar a_abbr)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(save)---------------------------*/
   DEBUG_MAP    yLOG_char    ("a_abbr"    , a_abbr);
   rc = ymap__visu_wipe (a_abbr);
   DEBUG_MAP    yLOG_value   ("wipe"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update range)-------------------*/
   ymap__visu_range ();
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__visu_save         (uchar a_abbr)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   DEBUG_MAP    yLOG_char    ("a_abbr"    , a_abbr);
   /*---(check mark)---------------------*/
   DEBUG_MAP    yLOG_char    ("active"    , s_curr->active);
   if (s_curr->active != VISU_YES) {
      DEBUG_MAP    yLOG_exit    (__FUNCTION__);
      return 0;
   }
   n = ymap_visu_index (a_abbr);
   DEBUG_MAP    yLOG_value   ("index"     , n);
   --rce;  if (n < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy)---------------------------*/
   rc = ymap__visu_copy (a_abbr, '\'');
   DEBUG_MAP    yLOG_value   ("copy"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update current)-----------------*/
   DEBUG_MAP    yLOG_note    ("update current");
   myMAP.v_curr    = a_abbr;
   s_curr->abbr   = a_abbr;
   s_curr->modded = '-';
   /*---(update range)-------------------*/
   DEBUG_MAP    yLOG_note    ("update the range");
   ymap__visu_range ();
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [ge.A52.153.55]*/ /*-[01.0000.033.8]-*/ /*-[--.---.---.--]-*/
ymap__visu_return    (uchar a_abbr)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   char        x_preserve  =  '-';
   tVISU       x_temp;
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MAP    yLOG_char    ("a_abbr"    , a_abbr);
   --rce;  if (a_abbr == '\'') {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(look for sequences)-------------*/
   DEBUG_MAP    yLOG_note    ("check special shortcuts");
   switch (a_abbr) {
   case YDLST_HEAD  : a_abbr = myMAP.v_head;          break;
   case YDLST_PREV  : a_abbr = ymap__visu_prev ();   break;
   case YDLST_LUSED : a_abbr = '<';                  break;
   case YDLST_NEXT  : a_abbr = ymap__visu_next ();   break;
   case YDLST_TAIL  : a_abbr = myMAP.v_tail;          break;
   }
   /*---(check mark)---------------------*/
   n = ymap_visu_index (a_abbr);
   DEBUG_MAP    yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (s_visus [n].active != VISU_YES) {
      DEBUG_MAP    yLOG_note    ("nothing saved under this reference");
      DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(if swapping curr/prev)----------*/
   --rce;  if (a_abbr == '<') {
      DEBUG_MAP    yLOG_note    ("return to previous");
      if (s_prev->active == VISU_NOT) {
         DEBUG_MAP    yLOG_note    ("no active previous selection");
         DEBUG_MAP    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = ymap__visu_copy ('?' , '\'');
      rc = ymap__visu_copy ('\'', '<');
      rc = ymap__visu_copy ('<' , '?');
      x_preserve = s_curr->modded;
      yMAP_jump (s_curr->u_all, s_curr->x_end, s_curr->y_end, s_curr->z_end);
      s_curr->modded = x_preserve;
      myMAP.v_curr    = s_curr->abbr;
      DEBUG_MAP    yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(back-up current)----------------*/
   if (s_curr->active == VISU_YES) {
      x_preserve = s_curr->modded;
      rc = ymap__visu_copy ('<', '\'');
      s_prev->modded = x_preserve;
   }
   /*---(return saved)-------------------*/
   rc = ymap__visu_copy ('\'', a_abbr);
   yMAP_jump (s_curr->u_all, s_curr->x_end, s_curr->y_end, s_curr->z_end);
   s_curr->modded = '-';
   myMAP.v_curr    = s_curr->abbr;
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       visual ranges                          ----===*/
/*====================------------------------------------====================*/
static void  o___CURSOR__________o () { return; }

/*
 * always reads across then down
 *
 */

static char       s_valid = '-';
static ushort     s_u = 0;
static ushort     s_x = 0;
static ushort     s_y = 0;
static ushort     s_z = 0;

char
yMAP_visu_range         (ushort *u, ushort *xb, ushort *xe, ushort *yb, ushort *ye, ushort *zb, ushort *ze)
{
   if (u  != NULL) *u  = s_curr->u_all;
   if (xb != NULL) *xb = s_curr->x_beg;
   if (xe != NULL) *xe = s_curr->x_end;
   if (yb != NULL) *yb = s_curr->y_beg;
   if (ye != NULL) *ye = s_curr->y_end;
   return 0;
}

char
yMAP_visu_first         (ushort *u, ushort *x, ushort *y, ushort *z)
{
   s_u = s_curr->u_all;
   s_x = s_curr->x_beg;
   s_y = s_curr->y_beg;
   if (u != NULL) *u = s_u;
   if (x != NULL) *x = s_x;
   if (y != NULL) *y = s_y;
   if (z != NULL) *z = s_z;
   s_valid = 'y';
   return 0;
}

char
yMAP_visu_next          (ushort *u, ushort *x, ushort *y, ushort *z)
{
   char        rce         =  -10;
   if (s_valid == 'y') {
      ++s_x;
      if (s_x > s_curr->x_end) {
         s_x = s_curr->x_beg;
         ++s_y;
         if (s_y > s_curr->y_end) {
            s_valid = '-';
         }
      }
   }
   --rce;  if (s_valid != 'y') {
      if (u != NULL) *u = s_u = 0;
      if (x != NULL) *x = s_x = 0;
      if (y != NULL) *y = s_y = 0;
      if (z != NULL) *z = s_z = 0;
      return rce;
   } else {
      if (u != NULL) *u = s_u;
      if (x != NULL) *x = s_x;
      if (y != NULL) *y = s_y;
      if (z != NULL) *z = s_z;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       visual status                          ----===*/
/*====================------------------------------------====================*/
static void  o___STATUS__________o () { return; }

char
yMAP_root               (ushort u, ushort x, ushort y, ushort z)
{
   if (s_curr->active == VISU_NOT)  return 0;
   if (u != s_curr->u_all )  return 0;
   if (x != s_curr->x_root)  return 0;
   if (y != s_curr->y_root)  return 0;
   if (z != s_curr->z_root)  return 0;
   return 1;
}

char
yMAP_visual             (ushort u, ushort x, ushort y, ushort z)
{
   if (s_curr->active == VISU_NOT)  return 0;
   if (u != s_curr->u_all)   return 0;
   if (x <  s_curr->x_beg)   return 0;
   if (x >  s_curr->x_end)   return 0;
   if (y <  s_curr->y_beg)   return 0;
   if (y >  s_curr->y_end)   return 0;
   if (z <  s_curr->z_beg)   return 0;
   if (z >  s_curr->z_end)   return 0;
   return 1;
}



/*====================------------------------------------====================*/
/*===----                       visual mode                            ----===*/
/*====================------------------------------------====================*/
static void  o___MODE____________o () { return; }

char
ymap_visu_hmode         (uchar a_major, uchar a_minor)
{
   char        rc          =    0;
   switch (a_minor) {
   case 'v'      :
      DEBUG_USER   yLOG_note    ("start/reverse visual selection");
      if (ymap_visu_islive ())   ymap_visu_reverse  ();
      else                       ymap_visu_makelive ();
      rc = G_KEY_SPACE;
      break;
   case 'M'      : case 'V'      :
      DEBUG_USER   yLOG_note    ("entering visual selection history sub-mode");
      rc = yMODE_enter  (UMOD_VISUAL);
      if (rc >= 0)  rc = a_minor;
      break;
   }
   return rc;
}

char         /*-> process keys for marks -------------[ leaf   [ge.UD8.24#.JA]*/ /*-[03.0000.102.E]-*/ /*-[--.---.---.--]-*/
ymap_visu_umode         (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   char       *x_majors    = "VM";
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_char    ("a_major"   , a_major);
   DEBUG_USER   yLOG_char    ("a_minor"   , chrvisible (a_minor));
   /*> myVIKEYS.info_win = '-';                                                       <*/
   /*---(defenses)-----------------------*/
   DEBUG_USER   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (UMOD_VISUAL )) {
      DEBUG_USER   yLOG_note    ("not the correct mode");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(exit mode)----------------------*/
   if (a_minor == G_KEY_ESCAPE) {
      DEBUG_USER   yLOG_note    ("escape means leave");
      yMODE_exit ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return  0;
   }
   /*---(major check)--------------------*/
   DEBUG_USER   yLOG_info    ("x_majors"  , x_majors);
   --rce;  if (strchr (x_majors, a_major) == NULL) {
      DEBUG_USER   yLOG_note    ("major not valid");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(common quick, any major)--------*/
   /*> --rce;  if (strchr("!", a_minor) != NULL) {                                    <* 
    *>    switch (a_minor) {                                                          <* 
    *>    case '!' :                                                                  <* 
    *>       DEBUG_USER   yLOG_note    ("use visual status bar");                     <* 
    *>       yVIKEYS_cmds_direct (":status visual");                                  <* 
    *>       break;                                                                   <* 
    *>    }                                                                           <* 
    *>    yMODE_exit ();                                                              <* 
    *>    DEBUG_USER   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return  0;                                                                  <* 
    *> }                                                                              <*/
   /*---(common complex)-----------------*/
   /*> --rce;  if (a_minor == '?') {                                                  <* 
    *>    DEBUG_USER   yLOG_note    ("show mark info window");                        <* 
    *>    myVIKEYS.info_win = 'y';                                                    <* 
    *>    return a_major;                                                             <* 
    *> }                                                                              <*/
   /*---(check for setting)--------------*/
   --rce;  if (a_major == 'M') {
      DEBUG_USER   yLOG_note    ("handle visual selection saving (M)");
      rc = ymap__visu_save (a_minor);
      DEBUG_USER   yLOG_value   ("rc"        , rc);
      if (rc < 0) {
         yMODE_exit ();
         DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yMODE_exit ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check for returning)------------*/
   --rce;  if (a_major == 'V') {
      DEBUG_USER   yLOG_note    ("handle visual selection return (V)");
      rc = ymap__visu_return (a_minor);
      DEBUG_USER   yLOG_value   ("rc"        , rc);
      if (rc < 0)  {
         yMODE_exit ();
         DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yMODE_exit ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(failure)------------------------*/
   --rce;
   yMODE_exit ();
   DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

