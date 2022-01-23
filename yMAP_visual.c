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
   DEBUG_YMAP    yLOG_senter  (__FUNCTION__);
   /*---(check)--------------------------*/
   DEBUG_YMAP    yLOG_snote   ("check");
   rc = strlchr (myMAP.v_list, a_abbr, S_VISU_MAX);
   DEBUG_YMAP    yLOG_sint    (rc);
   --rce;  if (a_abbr == 0 || rc < 0) {
      DEBUG_YMAP    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ymap_visu_index         (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMAP    yLOG_senter  (__FUNCTION__);
   /*---(check)--------------------------*/
   DEBUG_YMAP    yLOG_snote   ("check");
   n  = strchr (myMAP.v_list, a_abbr) - myMAP.v_list;
   DEBUG_YMAP    yLOG_sint    (n);
   --rce;  if (a_abbr == 0 || n  < 0) {
      DEBUG_YMAP    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YMAP    yLOG_senter  (__FUNCTION__);
   DEBUG_YMAP    yLOG_schar   (a_abbr);
   DEBUG_YMAP    yLOG_sint    (n);
   /*---(pointer)------------------------*/
   x_visu = myMAP.v_visus + n;
   DEBUG_YMAP    yLOG_spoint  (x_visu);
   /*---(mark self)----------------------*/
   if (a_abbr != '\'' && a_abbr != ';')  x_visu->abbr   = a_abbr;
   /*> if (strchr ("'>", a_abbr) != NULL)   x_visu->abbr   = a_abbr;                  <*/
   /*---(active)-------------------------*/
   DEBUG_YMAP    yLOG_snote   ("inactive");
   x_visu->active = VISU_NOT;
   x_visu->modded = '-';
   /*---(buf)----------------------------*/
   DEBUG_YMAP    yLOG_snote   ("buf");
   x_visu->u_all  = 0;
   /*---(x_pos)--------------------------*/
   DEBUG_YMAP    yLOG_snote   ("x");
   x_visu->x_root = 0;
   x_visu->x_beg  = 0;
   x_visu->x_end  = 0;
   /*---(y_pos)--------------------------*/
   DEBUG_YMAP    yLOG_snote   ("y");
   x_visu->y_root = 0;
   x_visu->y_beg  = 0;
   x_visu->y_end  = 0;
   /*---(z_pos)--------------------------*/
   DEBUG_YMAP    yLOG_snote   ("z");
   x_visu->z_root = 0;
   x_visu->z_beg  = 0;
   x_visu->z_end  = 0;
   /*---(labels)-------------------------*/
   DEBUG_YMAP    yLOG_snote   ("labels");
   strlcpy (x_visu->b_label, ""   , LEN_LABEL);
   strlcpy (x_visu->e_label, ""   , LEN_LABEL);
   /*---(locks)--------------------------*/
   DEBUG_YMAP    yLOG_snote   ("locks");
   x_visu->x_lock = '-';
   x_visu->y_lock = '-';
   x_visu->z_lock = '-';
   x_visu->source = '-';
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   /*---(destination)--------------------*/
   DEBUG_YMAP    yLOG_char    ("a_dst"     , a_dst);
   n = ymap_visu_index (a_dst);
   DEBUG_YMAP    yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_dst  = myMAP.v_visus + n;
   DEBUG_YMAP    yLOG_point   ("x_dst"     , x_dst);
   /*---(source)-------------------------*/
   DEBUG_YMAP    yLOG_char    ("a_src"     , a_src);
   n = ymap_visu_index (a_src);
   DEBUG_YMAP    yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_src  = myMAP.v_visus + n;
   DEBUG_YMAP    yLOG_point   ("x_src"     , x_src);
   /*---(mark self)----------------------*/
   if (strchr ("';?", a_dst) != NULL) {
      if (strchr ("';?", a_src) != NULL) {
         DEBUG_YMAP    yLOG_note    ("copying between ';?");
         x_dst->abbr   = x_src->abbr;
         x_dst->modded = x_src->modded;
      } else {
         DEBUG_YMAP    yLOG_note    ("copying from saved to ';?");
         x_dst->abbr   = a_src;
         x_dst->modded = '-';
      }
   }
   /*---(active)-------------------------*/
   DEBUG_YMAP    yLOG_note    ("active");
   x_dst->active = x_src->active;
   /*---(buf)----------------------------*/
   DEBUG_YMAP    yLOG_note    ("buf");
   x_dst->u_all  = x_src->u_all;
   /*---(x_pos)--------------------------*/
   DEBUG_YMAP    yLOG_note    ("x");
   x_dst->x_root = x_src->x_beg;  /* always override root with beg  */
   x_dst->x_beg  = x_src->x_beg;
   x_dst->x_end  = x_src->x_end;
   /*---(y_pos)--------------------------*/
   DEBUG_YMAP    yLOG_note    ("y");
   x_dst->y_root = x_src->y_beg;  /* always override root with beg  */
   x_dst->y_beg  = x_src->y_beg;
   x_dst->y_end  = x_src->y_end;
   /*---(z_pos)--------------------------*/
   DEBUG_YMAP    yLOG_note    ("z");
   x_dst->z_root = x_src->z_beg;  /* always override root with beg  */
   x_dst->z_beg  = x_src->z_beg;
   x_dst->z_end  = x_src->z_end;
   /*---(labels)-------------------------*/
   DEBUG_YMAP    yLOG_note    ("labels");
   strlcpy (x_dst->b_label, x_src->b_label, LEN_LABEL);
   strlcpy (x_dst->e_label, x_src->e_label, LEN_LABEL);
   /*---(locks)--------------------------*/
   DEBUG_YMAP    yLOG_note    ("locks");
   x_dst->x_lock = x_src->x_lock;
   x_dst->y_lock = x_src->y_lock;
   x_dst->z_lock = x_src->z_lock;
   x_dst->source = x_src->source;
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char  /*-> adjust the visual selection --------[ ------ [ge.760.324.D2]*/ /*-[01.0000.015.X]-*/ /*-[--.---.---.--]-*/
ymap_visu_update          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   ushort      u, x, y, z;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yMAP_current         (NULL, &u, &x, &y, &z);
   DEBUG_YMAP   yLOG_value   ("current"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_complex ("current"   , "%2du, %4dx, %4dy, %4dz", u, x, y, z);
   DEBUG_YMAP   yLOG_point   ("v_vurr"    , myMAP.v_curr);
   --rce;  if (myMAP.v_curr == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(not-live)-----------------------*/
   DEBUG_YMAP   yLOG_char    ("active"    , myMAP.v_curr->active);
   if (myMAP.v_curr->active == VISU_NOT) {
      DEBUG_YMAP    yLOG_note    ("inactive visual");
      myMAP.v_curr->abbr    = '-';
      myMAP.v_curr->modded  = '-';
      myMAP.v_curr->u_all   = u;
      myMAP.v_curr->x_root  = myMAP.v_curr->x_beg   = myMAP.v_curr->x_end   = x;
      myMAP.v_curr->y_root  = myMAP.v_curr->y_beg   = myMAP.v_curr->y_end   = y;
      myMAP.v_curr->z_root  = myMAP.v_curr->z_beg   = myMAP.v_curr->z_end   = z;
      DEBUG_YMAP    yLOG_note    ("beginning label");
      ymap_addresser (myMAP.v_curr->b_label, u, x, y, z);
      --rce;  if (rc < 0) {
         DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YMAP    yLOG_note    ("ending label");
      strlcpy  (myMAP.v_curr->e_label, myMAP.v_curr->b_label, LEN_LABEL);
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(before real updates)------------*/
   --rce;  if (u != myMAP.v_curr->u_all) {
      DEBUG_YMAP    yLOG_note    ("switched universes");
      ymap_visu_clear ();
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(x)------------------------------*/
   if (myMAP.v_curr->x_lock != 'y') {
      DEBUG_YMAP    yLOG_note    ("update x");
      if (x < myMAP.v_curr->x_root) {
         if (myMAP.v_curr->x_beg != x)  myMAP.v_curr->modded = '+';
         myMAP.v_curr->x_beg  = x;
         myMAP.v_curr->x_end  = myMAP.v_curr->x_root;
      } else {
         if (myMAP.v_curr->x_end != x)  myMAP.v_curr->modded = '+';
         myMAP.v_curr->x_beg  = myMAP.v_curr->x_root;
         myMAP.v_curr->x_end  = x;
      }
   }
   /*---(y)------------------------------*/
   if (myMAP.v_curr->y_lock != 'y') {
      DEBUG_YMAP    yLOG_note    ("update y");
      if (y < myMAP.v_curr->y_root) {
         if (myMAP.v_curr->y_beg != y)  myMAP.v_curr->modded = '+';
         myMAP.v_curr->y_beg  = y;
         myMAP.v_curr->y_end  = myMAP.v_curr->y_root;
      } else {
         if (myMAP.v_curr->y_end != y)  myMAP.v_curr->modded = '+';
         myMAP.v_curr->y_beg  = myMAP.v_curr->y_root;
         myMAP.v_curr->y_end  = y;
      }
   }
   /*---(set labels)---------------------*/
   DEBUG_YMAP    yLOG_note    ("beginning label");
   rc = ymap_addresser (myMAP.v_curr->b_label, myMAP.v_curr->u_all, myMAP.v_curr->x_beg, myMAP.v_curr->y_beg, myMAP.v_curr->z_beg);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP    yLOG_note    ("ending label");
   rc = ymap_addresser (myMAP.v_curr->e_label, myMAP.v_curr->u_all, myMAP.v_curr->x_end, myMAP.v_curr->y_end, myMAP.v_curr->z_end);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     check and setters                        ----===*/
/*====================------------------------------------====================*/
static void  o___QUICK___________o () { return; }

char
ymap_visu_getlive       (void)
{
   if (myMAP.v_curr == NULL)  return VISU_NOT;
   return myMAP.v_curr->active;
}

char
yMAP_visu_islive        (void)
{
   if (myMAP.v_curr == NULL)  return 0;
   if (myMAP.v_curr->active == VISU_YES)  return 1;
   return 0;
}

char
ymap_visu_isdead        (void)
{
   if (myMAP.v_curr == NULL)  return 1;
   if (myMAP.v_curr->active == VISU_NOT)  return 1;
   return 0;
}

char
ymap_visu_makelive      (void)
{
   if (myMAP.v_curr == NULL)  return -10;
   myMAP.v_curr->active = VISU_YES;
   return 0;
}



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
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_scope"   , a_scope);
   --rce;  switch (a_scope) {
   case YSTR_ILOWER  : case YSTR_IUPPER  : case YSTR_INUMBER :
   case YSTR_IGREEK  : case YSTR_IFULL   :
      break;
   default :
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   DEBUG_YMAP    yLOG_value   ("nvisu"     , myMAP.v_nvisu);
   for (i = 0; i < myMAP.v_nvisu; ++i) {
      x_abbr = myMAP.v_list [i];
      if (a_scope == YSTR_IUPPER  && strchr (YSTR_UPPER , x_abbr) == NULL)  continue;
      if (a_scope == YSTR_ILOWER  && strchr (YSTR_LOWER , x_abbr) == NULL)  continue;
      if (a_scope == YSTR_INUMBER && strchr (YSTR_NUMBER, x_abbr) == NULL)  continue;
      if (a_scope == YSTR_IGREEK  && strchr (YSTR_GREEK , x_abbr) == NULL)  continue;
      ymap__visu_wipe  (x_abbr);
   }
   /*---(globals)------------------------*/
   DEBUG_YMAP    yLOG_note    ("initialize globals");
   myMAP.v_ahead  = '-';
   myMAP.v_acurr  = '-';
   myMAP.v_atail  = '-';
   ymap__visu_range ();
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_visu_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (UMOD_VISUAL)) {
      DEBUG_YMAP   yLOG_note    ("status is not ready for init");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(visu abbrev list)---------------*/
   strlcpy (myMAP.v_list, "'"        , S_VISU_MAX);
   strlcat (myMAP.v_list, ";"        , S_VISU_MAX);
   strlcat (myMAP.v_list, YSTR_LOWER , S_VISU_MAX);
   strlcat (myMAP.v_list, YSTR_UPPER , S_VISU_MAX);
   strlcat (myMAP.v_list, YSTR_NUMBER, S_VISU_MAX);
   strlcat (myMAP.v_list, YSTR_GREEK , S_VISU_MAX);
   strlcat (myMAP.v_list, "?,"       , S_VISU_MAX);
   DEBUG_YMAP   yLOG_info    ("LIST"      , myMAP.v_list);
   myMAP.v_nvisu  = strlen (myMAP.v_list);
   DEBUG_YMAP    yLOG_value   ("nvisu"     , myMAP.v_nvisu);
   /*---(set pointers)-------------------*/
   myMAP.v_curr = myMAP.v_visus + 0;
   DEBUG_YMAP    yLOG_point   ("v_curr"    , myMAP.v_curr);
   myMAP.v_prev = myMAP.v_visus + 1;
   DEBUG_YMAP    yLOG_point   ("v_prev"    , myMAP.v_prev);
   /*---(clear)--------------------------*/
   ymap_visu_purge  (YSTR_IFULL);
   myMAP.v_curr->abbr   = myMAP.v_prev->abbr   = '-';
   /*> yVIKEYS_view_optionX (YVIKEYS_STATUS, "visual" , yvikeys_visu_status , "details of visual selection"                );   <*/
   yFILE_dump_add ("visuals"   , "vis", "current and saved visual selections", ymap_visu_dump);
   /*---(update status)------------------*/
   yMODE_init_set   (UMOD_VISUAL, NULL, ymap_visu_umode);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   /*---(set prev)-----------------------*/
   ymap__visu_save (',');
   /*---(backup)-------------------------*/
   myMAP.v_curr->abbr   = '-';
   myMAP.v_curr->active = VISU_NOT;
   myMAP.v_curr->x_lock = '-';
   myMAP.v_curr->y_lock = '-';
   myMAP.v_curr->z_lock = '-';
   myMAP.v_curr->modded = '-';
   yMAP_jump (myMAP.v_curr->u_all, myMAP.v_curr->x_root, myMAP.v_curr->y_root, myMAP.v_curr->z_root);
   ymap_visu_update ();
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_visu_exact         (ushort u, ushort xb, ushort xe, ushort yb, ushort ye, ushort zb, ushort ze, char c)
{  /*---(design notes)--------------------------------------------------------*/
   /* if the two ends of the range are legal, this function will change the   */
   /* current selection to the boundaries passed as arguments.                */
   /*---(locals)-----------+-----------+-*//*---------------------------------*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_beg       [LEN_LABEL];
   char        x_end       [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP    yLOG_complex ("args"      , "%3db,  %4d to %4dx,  %4d to %4dy,  %4d to %4dz", u, xb, xe, yb, ye, zb, ze);
   /*---(prepare)------------------------*/
   DEBUG_YMAP    yLOG_note    ("clear existing ranges");
   rc = ymap_visu_clear ();
   /*---(check limits)-------------------*/
   rc = ymap_addresser_strict  (x_beg, u, xb, yb, zb);
   DEBUG_YMAP    yLOG_value   ("beg label" , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YMAP    yLOG_note    ("beginning not legal/mapped");
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP    yLOG_info    ("beg label" , x_beg);
   rc = ymap_addresser_strict  (x_end, u, xe, ye, ze);
   DEBUG_YMAP    yLOG_value   ("end label" , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YMAP    yLOG_note    ("ending not legal/mapped");
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP    yLOG_info    ("end label" , x_end);
   /*---(jump to the end)----------------*/
   myMAP.v_curr->active  = VISU_NOT;
   if (c == 'b') {
      yMAP_jump (u, xb, yb, zb);
      myMAP.v_curr->x_root = xe;
      myMAP.v_curr->y_root = ye;
      myMAP.v_curr->z_root = ze;
   } else {
      yMAP_jump (u, xe, ye, ze);
      myMAP.v_curr->x_root = xb;
      myMAP.v_curr->y_root = yb;
      myMAP.v_curr->z_root = zb;
   }
   /*---(locations)----------------------*/
   DEBUG_YMAP    yLOG_note    ("set range coordinates");
   myMAP.v_curr->u_all  = u;
   myMAP.v_curr->x_beg  = xb;
   myMAP.v_curr->x_end  = xe;
   myMAP.v_curr->y_beg  = yb;
   myMAP.v_curr->y_end  = ye;
   myMAP.v_curr->z_beg  = zb;
   myMAP.v_curr->z_end  = ze;
   strlcpy (myMAP.v_curr->b_label, x_beg, LEN_LABEL);
   strlcpy (myMAP.v_curr->e_label, x_end, LEN_LABEL);
   /*---(last settings)------------------*/
   myMAP.v_curr->active  = VISU_YES;
   myMAP.v_curr->abbr   = '-';
   myMAP.v_curr->modded = '+';
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_visu_reverse       (void)
{
   if (myMAP.v_curr->active == VISU_NOT)  return 0;
   /*---(if x locked)--------------------*/
   if (myMAP.v_curr->x_lock == 'y') {
      if (myMAP.v_curr->y_root == myMAP.v_curr->y_beg) {
         myMAP.v_curr->y_root = myMAP.v_curr->y_end;
         yMAP_jump (myMAP.v_curr->u_all, myMAP.v_curr->x_root, myMAP.v_curr->y_beg, myMAP.v_curr->z_beg);
      }
      else  {
         myMAP.v_curr->y_root = myMAP.v_curr->y_beg;
         yMAP_jump (myMAP.v_curr->u_all, myMAP.v_curr->x_root, myMAP.v_curr->y_end, myMAP.v_curr->z_beg);
      }
      return 0;
   }
   /*---(if y locked)--------------------*/
   if (myMAP.v_curr->y_lock == 'y') {
      if (myMAP.v_curr->x_root == myMAP.v_curr->x_beg) {
         myMAP.v_curr->x_root = myMAP.v_curr->x_end;
         yMAP_jump (myMAP.v_curr->u_all, myMAP.v_curr->x_beg, myMAP.v_curr->y_root, myMAP.v_curr->z_beg);
      }
      else  {
         myMAP.v_curr->x_root = myMAP.v_curr->x_beg;
         yMAP_jump (myMAP.v_curr->u_all, myMAP.v_curr->x_end, myMAP.v_curr->y_root, myMAP.v_curr->z_beg);
      }
      return 0;
   }
   /*---(root at beg)--------------------*/
   if (myMAP.v_curr->x_root == myMAP.v_curr->x_beg && myMAP.v_curr->y_root == myMAP.v_curr->y_beg) {
      myMAP.v_curr->x_root = myMAP.v_curr->x_end;
      myMAP.v_curr->y_root = myMAP.v_curr->y_end;
      yMAP_jump (myMAP.v_curr->u_all, myMAP.v_curr->x_beg, myMAP.v_curr->y_beg, myMAP.v_curr->z_beg);
      return 0;
   }
   /*---(root at end)--------------------*/
   myMAP.v_curr->x_root = myMAP.v_curr->x_beg;
   myMAP.v_curr->y_root = myMAP.v_curr->y_beg;
   yMAP_jump (myMAP.v_curr->u_all, myMAP.v_curr->x_end, myMAP.v_curr->y_end, myMAP.v_curr->z_beg);
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap_visu_locking       (char a_type)
{
   char        rce         =  -10;
   char        rc          =    0;
   ushort      eu, ex, ey, ez;
   if (myMAP.v_curr->active == VISU_NOT)  return 0;
   switch (a_type) {
   case 'y'  :
      if (myMAP.v_curr->y_lock == 'y') {
         DEBUG_YMAP   yLOG_note    ("unlock y full y_axis selection");
         myMAP.v_curr->y_lock = '-';
         if (myMAP.v_curr->y_root <= g_ymap.gcur) {
            myMAP.v_curr->y_beg  = myMAP.v_curr->y_root;
            myMAP.v_curr->y_end  = g_ymap.gcur;
         } else {
            myMAP.v_curr->y_end  = myMAP.v_curr->y_root;
            myMAP.v_curr->y_beg  = g_ymap.gcur;
         }
      } else {
         DEBUG_YMAP   yLOG_note    ("lock y for full y_axis selection");
         myMAP.v_curr->y_lock = 'y';
         myMAP.v_curr->y_beg  = g_ymap.gmin;
         myMAP.v_curr->y_end  = g_ymap.gmax;
      }
      break;
   case 'x'  :
      if (myMAP.v_curr->x_lock == 'y') {
         DEBUG_YMAP   yLOG_note    ("unlock x full x-axis selection");
         myMAP.v_curr->x_lock = '-';
         if (myMAP.v_curr->x_root <= g_xmap.gcur) {
            myMAP.v_curr->x_beg  = myMAP.v_curr->x_root;
            myMAP.v_curr->x_end  = g_xmap.gcur;
         } else {
            myMAP.v_curr->x_end  = myMAP.v_curr->x_root;
            myMAP.v_curr->x_beg  = g_xmap.gcur;
         }
      } else {
         DEBUG_YMAP   yLOG_note    ("lock x for full x-axis selection");
         myMAP.v_curr->x_lock = 'y';
         myMAP.v_curr->x_beg  = g_xmap.gmin;
         myMAP.v_curr->x_end  = g_xmap.gmax;
      }
      break;
   case '!'  :
      DEBUG_YMAP   yLOG_note    ("! for screen selection");
      /*> ymap_visu_exact (g_zmap.gcur, g_xmap.gbeg, g_xmap.gend, g_ymap.gbeg, g_ymap.gend, 0, 0);   <*/
      DEBUG_YMAP    yLOG_complex ("x-curr"    , "%3db, %3dc, %3de", g_xmap.gbeg, g_xmap.gcur, g_xmap.gend);
      DEBUG_YMAP    yLOG_complex ("x-visu"    , "%3db, %3dr, %3de", myMAP.v_curr->x_beg, myMAP.v_curr->x_root, myMAP.v_curr->x_end);
      DEBUG_YMAP    yLOG_complex ("y-curr"    , "%3db, %3dc, %3de", g_ymap.gbeg, g_ymap.gcur, g_ymap.gend);
      DEBUG_YMAP    yLOG_complex ("y-visu"    , "%3db, %3dr, %3de", myMAP.v_curr->y_beg, myMAP.v_curr->y_root, myMAP.v_curr->y_end);
      ymap_visu_clear    ();
      eu = g_umap.gcur;
      ex = g_xmap.gend;
      ey = g_ymap.gend;
      ez = g_zmap.gend;
      yMAP_jump (g_umap.gcur, g_xmap.gbeg, g_ymap.gbeg, g_zmap.gbeg);
      ymap_visu_update   ();
      ymap_visu_makelive ();
      yMAP_jump (eu, ex, ey, ez);
      /*> myMAP.v_curr->x_lock = myMAP.v_curr->y_lock = '-';                          <*/
      /*> myMAP.v_curr->x_beg  = myMAP.v_curr->x_root = g_xmap.gbeg;                  <* 
       *> myMAP.v_curr->y_beg  = myMAP.v_curr->y_root = g_ymap.gbeg;                  <* 
       *> myMAP.v_curr->x_end  = g_xmap.gcur    = g_xmap.gend;                        <* 
       *> myMAP.v_curr->y_end  = g_ymap.gcur    = g_ymap.gend;                        <*/
      DEBUG_YMAP    yLOG_complex ("x-curr"    , "%3db, %3dc, %3de", g_xmap.gbeg, g_xmap.gcur, g_xmap.gend);
      DEBUG_YMAP    yLOG_complex ("x-visu"    , "%3db, %3dr, %3de", myMAP.v_curr->x_beg, myMAP.v_curr->x_root, myMAP.v_curr->x_end);
      DEBUG_YMAP    yLOG_complex ("y-curr"    , "%3db, %3dc, %3de", g_ymap.gbeg, g_ymap.gcur, g_ymap.gend);
      DEBUG_YMAP    yLOG_complex ("y-visu"    , "%3db, %3dr, %3de", myMAP.v_curr->y_beg, myMAP.v_curr->y_root, myMAP.v_curr->y_end);
      break;
   case '*'  :
      DEBUG_YMAP   yLOG_note    ("* for all on current z selection");
      myMAP.v_curr->y_lock = 'y';
      myMAP.v_curr->y_beg  = g_ymap.gmin;
      myMAP.v_curr->y_end  = g_ymap.gmax;
      myMAP.v_curr->x_lock = 'y';
      myMAP.v_curr->x_beg  = g_xmap.gmin;
      myMAP.v_curr->x_end  = g_xmap.gmax;
      yMAP_jump (myMAP.v_curr->u_all, myMAP.v_curr->x_end, myMAP.v_curr->y_end, myMAP.v_curr->z_end);
      break;
   default   :
      DEBUG_YMAP   yLOG_note    ("option not understood");
      return -1;
   }
   /*---(update selection)---------------*/
   myMAP.v_curr->modded = '+';
   ymap_visu_update ();
   DEBUG_YMAP    yLOG_complex ("x-curr"    , "%3db, %3dc, %3de", g_xmap.gbeg, g_xmap.gcur, g_xmap.gend);
   DEBUG_YMAP    yLOG_complex ("x-visu"    , "%3db, %3dr, %3de", myMAP.v_curr->x_beg, myMAP.v_curr->x_root, myMAP.v_curr->x_end);
   DEBUG_YMAP    yLOG_complex ("y-curr"    , "%3db, %3dc, %3de", g_ymap.gbeg, g_ymap.gcur, g_ymap.gend);
   DEBUG_YMAP    yLOG_complex ("y-visu"    , "%3db, %3dr, %3de", myMAP.v_curr->y_beg, myMAP.v_curr->y_root, myMAP.v_curr->y_end);
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
   DEBUG_YMAP    yLOG_senter  (__FUNCTION__);
   /*---(find next)----------------------*/
   myMAP.v_ahead = '-';
   for (i = 2; i < myMAP.v_nvisu - 3; ++i) {
      if (myMAP.v_visus [i].active == VISU_NOT) continue;
      myMAP.v_ahead = myMAP.v_list [i];
      DEBUG_YMAP    yLOG_schar   (myMAP.v_ahead);
      DEBUG_YMAP    yLOG_snote   ("HEAD");
      break;
   }
   /*---(find last)----------------------*/
   myMAP.v_atail = '-';
   for (i = myMAP.v_nvisu - 3; i >  1; --i) {
      if (myMAP.v_visus [i].active == VISU_NOT) continue;
      myMAP.v_atail = myMAP.v_list [i];
      DEBUG_YMAP    yLOG_schar   (myMAP.v_atail);
      DEBUG_YMAP    yLOG_snote   ("TAIL");
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   /*---(check mark)---------------------*/
   DEBUG_YMAP    yLOG_char    ("visu_curr" , myMAP.v_acurr);
   x_index = ymap_visu_index (myMAP.v_acurr);
   DEBUG_YMAP    yLOG_value   ("x_index"   , x_index);
   --rce;  if (x_index < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find previous)------------------*/
   DEBUG_YMAP    yLOG_note    ("search for previous mark");
   for (i = x_index - 1; i > 1; --i) {
      if (myMAP.v_visus [i].active == VISU_NOT )  continue;
      DEBUG_YMAP    yLOG_value   ("found"     , i);
      x_abbr = myMAP.v_list [i];
      DEBUG_YMAP    yLOG_char    ("x_abbr"    , x_abbr);
      DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
      return x_abbr;
   }
   DEBUG_YMAP    yLOG_note    ("not found");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
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
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   /*---(check mark)---------------------*/
   DEBUG_YMAP    yLOG_char    ("visu_curr" , myMAP.v_acurr);
   x_index = ymap_visu_index (myMAP.v_acurr);
   DEBUG_YMAP    yLOG_value   ("x_index"   , x_index);
   --rce;  if (x_index < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find next)----------------------*/
   DEBUG_YMAP    yLOG_note    ("search for next mark");
   for (i = x_index + 1; i < myMAP.v_nvisu - 2; ++i) {
      if (myMAP.v_visus [i].active == VISU_NOT )  continue;
      DEBUG_YMAP    yLOG_value   ("found"     , i);
      x_abbr         = myMAP.v_list [i];
      DEBUG_YMAP    yLOG_char    ("x_abbr"    , x_abbr);
      myMAP.v_acurr  = x_abbr;
      DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
      return x_abbr;
   }
   DEBUG_YMAP    yLOG_note    ("not found");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
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
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   /*---(save)---------------------------*/
   DEBUG_YMAP    yLOG_char    ("a_abbr"    , a_abbr);
   rc = ymap__visu_wipe (a_abbr);
   DEBUG_YMAP    yLOG_value   ("wipe"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update range)-------------------*/
   ymap__visu_range ();
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
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
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP    yLOG_char    ("a_abbr"    , a_abbr);
   /*---(check mark)---------------------*/
   DEBUG_YMAP    yLOG_char    ("active"    , myMAP.v_curr->active);
   if (myMAP.v_curr->active != VISU_YES) {
      DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
      return 0;
   }
   n = ymap_visu_index (a_abbr);
   DEBUG_YMAP    yLOG_value   ("index"     , n);
   --rce;  if (n < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy)---------------------------*/
   rc = ymap__visu_copy (a_abbr, '\'');
   DEBUG_YMAP    yLOG_value   ("copy"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update current)-----------------*/
   DEBUG_YMAP    yLOG_note    ("update current");
   myMAP.v_acurr        = a_abbr;
   myMAP.v_curr->abbr   = a_abbr;
   myMAP.v_curr->modded = '-';
   /*---(update range)-------------------*/
   DEBUG_YMAP    yLOG_note    ("update the range");
   ymap__visu_range ();
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
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
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP    yLOG_char    ("a_abbr"    , a_abbr);
   --rce;  if (a_abbr == '\'') {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(look for sequences)-------------*/
   DEBUG_YMAP    yLOG_note    ("check special shortcuts");
   switch (a_abbr) {
   case YDLST_HEAD  : a_abbr = myMAP.v_ahead;        break;
   case YDLST_PREV  : a_abbr = ymap__visu_prev ();   break;
   case YDLST_NEXT  : a_abbr = ymap__visu_next ();   break;
   case YDLST_TAIL  : a_abbr = myMAP.v_atail;        break;
   }
   /*---(check mark)---------------------*/
   n = ymap_visu_index (a_abbr);
   DEBUG_YMAP    yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (myMAP.v_visus [n].active != VISU_YES) {
      DEBUG_YMAP    yLOG_note    ("nothing saved under this reference");
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(if swapping curr/prev)----------*/
   --rce;  if (a_abbr == ';') {
      DEBUG_YMAP    yLOG_note    ("return to previous");
      if (myMAP.v_prev->active == VISU_NOT) {
         DEBUG_YMAP    yLOG_note    ("no active previous selection");
         DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_preserve = myMAP.v_prev->modded;
      rc = ymap__visu_copy ('?' , '\'');
      yMAP_jump (myMAP.v_prev->u_all, myMAP.v_prev->x_end, myMAP.v_prev->y_end, myMAP.v_prev->z_end);
      rc = ymap__visu_copy ('\'', ';');
      ymap_visu_update ();
      rc = ymap__visu_copy (';' , '?');
      myMAP.v_curr->modded = x_preserve;
      myMAP.v_acurr   = myMAP.v_curr->abbr;
      DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(back-up current)----------------*/
   if (myMAP.v_curr->active == VISU_YES) {
      x_preserve = myMAP.v_curr->modded;
      rc = ymap__visu_copy (';', '\'');
      myMAP.v_prev->modded = x_preserve;
   }
   /*---(return saved)-------------------*/
   yMAP_jump (myMAP.v_visus [n].u_all, myMAP.v_visus [n].x_end, myMAP.v_visus [n].y_end, myMAP.v_visus [n].z_end);
   rc = ymap__visu_copy ('\'', a_abbr);
   ymap_visu_update ();
   myMAP.v_acurr   = myMAP.v_curr->abbr;
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char ymap_visu_reselect      (void) { return ymap__visu_return (','); }



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
yMAP_visu_range         (ushort *u, ushort *xb, ushort *xe, ushort *yb, ushort *ye, ushort *zb, ushort *ze, char *c)
{
   if (u  != NULL) *u  = myMAP.v_curr->u_all;
   if (xb != NULL) *xb = myMAP.v_curr->x_beg;
   if (xe != NULL) *xe = myMAP.v_curr->x_end;
   if (yb != NULL) *yb = myMAP.v_curr->y_beg;
   if (ye != NULL) *ye = myMAP.v_curr->y_end;
   if (zb != NULL) *zb = myMAP.v_curr->z_beg;
   if (ze != NULL) *ze = myMAP.v_curr->z_end;
   if (c  != NULL) *c  = (myMAP.v_curr->x_beg == myMAP.v_curr->x_root) ? 'e' : 'b';
   return 0;
}

char
yMAP_visu_first         (ushort *u, ushort *x, ushort *y, ushort *z)
{
   s_u = myMAP.v_curr->u_all;
   s_x = myMAP.v_curr->x_beg;
   s_y = myMAP.v_curr->y_beg;
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
      if (s_x > myMAP.v_curr->x_end) {
         s_x = myMAP.v_curr->x_beg;
         ++s_y;
         if (s_y > myMAP.v_curr->y_end) {
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
   if (myMAP.v_curr->active == VISU_NOT)  return 0;
   if (u != myMAP.v_curr->u_all )  return 0;
   if (x != myMAP.v_curr->x_root)  return 0;
   if (y != myMAP.v_curr->y_root)  return 0;
   if (z != myMAP.v_curr->z_root)  return 0;
   return 1;
}

char
yMAP_visual             (ushort u, ushort x, ushort y, ushort z)
{
   if (myMAP.v_curr->active == VISU_NOT)  return 0;
   if (u != myMAP.v_curr->u_all)   return 0;
   if (x <  myMAP.v_curr->x_beg)   return 0;
   if (x >  myMAP.v_curr->x_end)   return 0;
   if (y <  myMAP.v_curr->y_beg)   return 0;
   if (y >  myMAP.v_curr->y_end)   return 0;
   if (z <  myMAP.v_curr->z_beg)   return 0;
   if (z >  myMAP.v_curr->z_end)   return 0;
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
      DEBUG_YMAP   yLOG_note    ("start/reverse visual selection");
      if (yMAP_visu_islive ())   ymap_visu_reverse  ();
      else                       ymap_visu_makelive ();
      myMAP.v_curr->modded = '+';
      rc = G_KEY_SPACE;
      break;
   case 'M'      : case 'V'      :
      DEBUG_YMAP   yLOG_note    ("entering visual selection history sub-mode");
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
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("a_major"   , a_major);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , chrvisible (a_minor));
   /*> myVIKEYS.info_win = '-';                                                       <*/
   /*---(defenses)-----------------------*/
   DEBUG_YMAP   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (UMOD_VISUAL )) {
      DEBUG_YMAP   yLOG_note    ("not the correct mode");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(exit mode)----------------------*/
   if (a_minor == G_KEY_ESCAPE) {
      DEBUG_YMAP   yLOG_note    ("escape means leave");
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return  0;
   }
   /*---(major check)--------------------*/
   DEBUG_YMAP   yLOG_info    ("x_majors"  , x_majors);
   --rce;  if (strchr (x_majors, a_major) == NULL) {
      DEBUG_YMAP   yLOG_note    ("major not valid");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_minor == '!') {
      DEBUG_YMAP   yLOG_note    ("request visual status line");
      yCMD_direct (":status visual");
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(common quick, any major)--------*/
   /*> --rce;  if (strchr("!", a_minor) != NULL) {                                    <* 
    *>    switch (a_minor) {                                                          <* 
    *>    case '!' :                                                                  <* 
    *>       DEBUG_YMAP   yLOG_note    ("use visual status bar");                     <* 
    *>       yVIKEYS_cmds_direct (":status visual");                                  <* 
    *>       break;                                                                   <* 
    *>    }                                                                           <* 
    *>    yMODE_exit ();                                                              <* 
    *>    DEBUG_YMAP   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return  0;                                                                  <* 
    *> }                                                                              <*/
   /*---(common complex)-----------------*/
   /*> --rce;  if (a_minor == '?') {                                                  <* 
    *>    DEBUG_YMAP   yLOG_note    ("show mark info window");                        <* 
    *>    myVIKEYS.info_win = 'y';                                                    <* 
    *>    return a_major;                                                             <* 
    *> }                                                                              <*/
   /*---(check for setting)--------------*/
   --rce;  if (a_major == 'M') {
      DEBUG_YMAP   yLOG_note    ("handle visual selection saving (M)");
      rc = ymap__visu_save (a_minor);
      DEBUG_YMAP   yLOG_value   ("rc"        , rc);
      if (rc < 0) {
         yMODE_exit ();
         DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check for returning)------------*/
   --rce;  if (a_major == 'V') {
      DEBUG_YMAP   yLOG_note    ("handle visual selection return (V)");
      rc = ymap__visu_return (a_minor);
      DEBUG_YMAP   yLOG_value   ("rc"        , rc);
      if (rc < 0)  {
         yMODE_exit ();
         DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(failure)------------------------*/
   --rce;
   yMODE_exit ();
   DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}


