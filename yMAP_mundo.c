/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"






static char   *s_nada      = "";
static char   *s_nothing   = "´´´´´";


typedef struct cACTS  tACTS;
struct  cACTS{
   char        act;
   char        name         [LEN_LABEL];
   char        desc         [LEN_DESC];
};
static const tACTS s_acts [] = {
   /*---(univers changes)----------------*/
   { YMAP_VOLUME   , "volume"       , "change universe maximum size"    },
   { YMAP_TITLE    , "title"        , "change universe title/name"      },
   /*---(object changes)-----------------*/
   { YMAP_CREATE   , "create"       , "create object and attributes"    },
   { YMAP_BLANK    , "blank"        , "new/create object"               },
   { YMAP_DELETE   , "delete"       , "eliminate object"                },
   { YMAP_WIDTH    , "width"        , "change object/column width"      },
   { YMAP_HEIGHT   , "height"       , "change object/row height"        },
   { YMAP_DEPTH    , "depth"        , "change object depth"             },
   { YMAP_SHAPE    , "shape"        , "change object shape"             },
   { YMAP_COLOR    , "color"        , "change object coloration"        },
   { YMAP_SYNC     , "SYNC-UP"      , "undoing complex changes"         },
   /*---(content changes)----------------*/
   { YMAP_OVERWRITE, "overwrite"    , "change contents and formatting"  },
   { YMAP_CLEAR    , "clear"        , "clear object contents"           },
   { YMAP_SOURCE   , "source"       , "change content text"             },
   { YMAP_ALIGN    , "align"        , "change display alignment"        },
   { YMAP_FORMAT   , "format"       , "change display format"           },
   { YMAP_DECIMALS , "decimals"     , "change display decimal places"   },
   { YMAP_UNITS    , "units"        , "change display units of measure" },
   /*---(done)---------------------------*/
   { 0             , "end"          , "" },
};
static int    s_nact =    0;



/*====================------------------------------------====================*/
/*===----                   small support functions                    ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
ymap__mundo_valid_act   (char a_act)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   /*---(check actions)------------------*/
   if (a_act == 0)  return 0;
   for (i = 0; i < s_nact; ++i) {
      if (s_acts [i].act != a_act)  continue;
      return 1;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yMAP_mundo_make_add     (void)
{
   if (myMAP.h_tail != NULL)  myMAP.h_tail->mode = YMAP_ADD;
   return 0;
}

int yMAP_mundo_current      (void) { return myMAP.h_index; }

int yMAP_mundo_count        (void) { return myMAP.h_count; }



/*====================------------------------------------====================*/
/*===----                      memory allocation                       ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
ymap__mundo_new         (char a_mode, char a_act, char *a_label, tHIST **r_curr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tHIST      *x_new       = NULL;
   char        x_tries     =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (__FUNCTION__);
   DEBUG_HIST  yLOG_complex ("a_mode"    , "%c, %c, %s", a_mode, a_act, a_label);
   /*---(default)------------------------*/
   if (r_curr != NULL)  *r_curr = NULL;
   /*---(internal)-----------------------*/
   DEBUG_HIST  yLOG_char    ("active"    , myMAP.h_active);
   if (myMAP.h_active != 'y') {
      DEBUG_HIST  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (a_mode      == YMAP_NONE) {
      DEBUG_HIST  yLOG_note    ("history is not requested on this action");
      DEBUG_HIST  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   --rce;  if (a_mode == 0 || strchr (YMAP_MODES, a_mode) == NULL) {
      DEBUG_HIST  yLOG_note    ("a_mode not legal");
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (!ymap__mundo_valid_act (a_act)) {
      DEBUG_HIST  yLOG_note    ("a_act not legal");
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_label == NULL || a_label [0] == '\0') {
      DEBUG_HIST  yLOG_note    ("a_label is null/empty");
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prune future)-------------------*/
   rc = ymap__mundo_prune ('-');
   /*---(allocate)-----------------------*/
   DEBUG_HIST   yLOG_note    ("allocating");
   while (x_new == NULL && x_tries < 10)  {
      DEBUG_HIST   yLOG_value   ("x_tries"   , x_tries);
      ++x_tries;
      x_new = (tHIST *) malloc (sizeof (tHIST));
   }
   DEBUG_HIST   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_HIST   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_HIST   yLOG_note    ("FAILED");
      DEBUG_HIST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_HIST   yLOG_note    ("populate");
   x_new->mode    = a_mode;
   x_new->act     = a_act;
   x_new->label   = strdup (a_label);
   x_new->before  = s_nada;
   x_new->after   = s_nada;
   x_new->h_prev  = NULL;
   x_new->h_next  = NULL;
   /*---(tie to master list)-------------*/
   if (myMAP.h_head == NULL) {
      DEBUG_HIST   yLOG_note    ("nothing in list, make first");
      myMAP.h_head         = x_new;
   } else  {
      DEBUG_HIST   yLOG_note    ("append to list");
      myMAP.h_tail->h_next = x_new;
      x_new->h_prev  = myMAP.h_tail;
   }
   myMAP.h_tail        = x_new;
   /*---(update counts)------------------*/
   ++myMAP.h_count;
   DEBUG_HIST   yLOG_value   ("h_count"   , myMAP.h_count);
   /*---(update current)-----------------*/
   myMAP.h_curr   = myMAP.h_tail;
   myMAP.h_index  = myMAP.h_count - 1;
   DEBUG_HIST   yLOG_point   ("h_curr"    , myMAP.h_curr);
   DEBUG_HIST   yLOG_value   ("h_index"   , myMAP.h_index);
   /*---(save-back)----------------------*/
   if (r_curr != NULL)  *r_curr = x_new;
   /*---(complete)-----------------------*/
   DEBUG_HIST   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__mundo_free        (tHIST **r_curr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tHIST      *x_curr      = NULL;          /* simplifier only                */
   /*---(locals)-----------+-----+-----+-*/
   DEBUG_HIST   yLOG_senter  (__FUNCTION__);
   DEBUG_HIST   yLOG_spoint  (*r_curr);
   --rce;  if (*r_curr == NULL) {
      DEBUG_HIST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_HIST   yLOG_sint    (myMAP.h_count);
   x_curr = *r_curr;
   /*---(free content)-------------------*/
   if (x_curr->label  != s_nada)   free (x_curr->label);
   x_curr->label  = NULL;
   if (x_curr->before != s_nada)   free (x_curr->before);
   x_curr->before = NULL;
   if (x_curr->after  != s_nada)   free (x_curr->after);
   x_curr->after  = NULL;
   /*---(out of linked list)-------------*/
   if (x_curr->h_next != NULL)   x_curr->h_next->h_prev = x_curr->h_prev;
   else                          myMAP.h_tail           = x_curr->h_prev;
   if (x_curr->h_prev != NULL)   x_curr->h_prev->h_next = x_curr->h_next;
   else                          myMAP.h_head           = x_curr->h_next;
   --myMAP.h_count;
   DEBUG_HIST   yLOG_sint    (myMAP.h_count);
   /*---(clear links)--------------------*/
   x_curr->h_prev = NULL;
   x_curr->h_next = NULL;
   /*---(update current)-----------------*/
   if (myMAP.h_curr == x_curr) {
      myMAP.h_curr   = myMAP.h_tail;
      myMAP.h_index  = myMAP.h_count - 1;
   }
   /*---(free entry)---------------------*/
   free (x_curr);
   *r_curr = NULL;
   /*---(complete)-----------------------*/
   DEBUG_HIST   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char         /*-> clear out the history --------------[ leaf   [gz.530.011.00]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
ymap_mundo_init         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           = 0;
   /*---(header)-------------------------*/
   DEBUG_HIST   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (UMOD_MUNDO)) {
      DEBUG_HIST   yLOG_note    ("status is not ready for init");
      DEBUG_HIST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear vars)---------------------*/
   myMAP.h_head   = NULL;
   myMAP.h_tail   = NULL;
   myMAP.h_curr   = NULL;
   myMAP.h_count  =    0;
   myMAP.h_index  =   -1;
   myMAP.h_active =  'y';
   myMAP.h_len    =    5;
   myMAP.e_mundo  = NULL;
   /*---(check actions)------------------*/
   s_nact  = 0;
   for (i = 0; i < LEN_LABEL; ++i) {
      if (s_acts [i].act == 0)  break;
      ++s_nact;
   }
   yFILE_dump_add ("mundo"     , "mun", "inventory of undo/redo chain"  , ymap_mundo_dump);
   yFILE_dump_add ("maps"      , "map", "details of all axis maps"      , ymap_map_dump);
   /*---(update status)------------------*/
   yMODE_init_set   (UMOD_MUNDO, NULL, ymap_mode);
   DEBUG_HIST   yLOG_exit    (__FUNCTION__);
   /*---(complete)-----------------------*/
   return 0;
}

char
yMAP_mundo_config       (char a_len, void *a_mundo)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (UMOD_MUNDO)) {
      DEBUG_HIST   yLOG_note    ("init must complete before config");
      DEBUG_HIST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(format length)------------------*/
   DEBUG_HIST   yLOG_value   ("a_len"     , a_len);
   --rce;  if (a_len < 0 || a_len > 10) {
      DEBUG_HIST   yLOG_note    ("format lenght must be 0 to 10");
      DEBUG_HIST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   myMAP.h_len    = a_len;
   /*---(undo pointer)-------------------*/
   DEBUG_HIST   yLOG_point   ("a_mundo"   , a_mundo);
   --rce;  if (a_mundo == NULL) {
      DEBUG_HIST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   myMAP.e_mundo  = a_mundo;
   /*---(update status)------------------*/
   yMODE_conf_set   (UMOD_MUNDO, '1');
   /*---(complete)-----------------------*/
   DEBUG_HIST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_mundo_rollback     (void)
{
   ymap__mundo_by_cursor (YDLST_TAIL);
   ymap_mundo_undo ();
   if (myMAP.h_head != myMAP.h_curr)  ymap__mundo_by_cursor (YDLST_NEXT);
   ymap__mundo_prune ('-');
   return 0;
}

char
ymap__mundo_prune       (char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tHIST      *x_curr      = NULL;
   tHIST      *x_next      = NULL;
   tHIST      *x_stop      = NULL;
   DEBUG_HIST  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_HIST  yLOG_char    ("a_type"    , a_type);
   DEBUG_HIST  yLOG_point   ("h_curr"    , myMAP.h_curr);
   DEBUG_HIST  yLOG_point   ("h_tail"    , myMAP.h_tail);
   x_curr = myMAP.h_tail;
   if (a_type == '*')  x_stop = NULL;
   else                x_stop = myMAP.h_curr;
   DEBUG_HIST  yLOG_point   ("x_stop"    , x_stop);
   /*---(walk)---------------------------*/
   DEBUG_HIST  yLOG_point   ("x_curr"    , x_curr);
   while (x_curr != NULL && x_curr != x_stop) {
      x_next = x_curr->h_prev;
      ymap__mundo_free (&x_curr);
      x_curr = x_next;
      DEBUG_HIST  yLOG_point   ("x_curr"    , x_curr);
   }
   /*---(clean up)-----------------------*/
   if (a_type == '*') {
      myMAP.h_head  = NULL;
      myMAP.h_tail  = NULL;
      myMAP.h_curr  = NULL;
      myMAP.h_count = 0;
      myMAP.h_index = 0;
   } else {
      if (myMAP.h_curr != NULL) myMAP.h_curr->h_next = NULL;
      myMAP.h_tail = myMAP.h_curr;
   }
   /*---(complete)-----------------------*/
   DEBUG_HIST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char yMAP_mundo_purge        (void) { return ymap__mundo_prune ('*'); }

char
ymap_mundo_wrap         (void)
{
   ymap__mundo_prune ('*');
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       search/find entries                    ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char
ymap__mundo_by_cursor   (char a_move)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_HIST   yLOG_enter   (__FUNCTION__);
   DEBUG_HIST   yLOG_char    ("a_move"    , a_move);
   /*---(defenses)-----------------------*/
   DEBUG_HIST   yLOG_point   ("h_head"    , myMAP.h_head);
   --rce;  if (myMAP.h_head == NULL) {
      myMAP.h_curr  = NULL;
      myMAP.h_index = -1;
      DEBUG_HIST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_HIST   yLOG_point   ("myMAP.h_curr"    , myMAP.h_curr);
   --rce;  if (myMAP.h_curr == NULL && strchr ("<>", a_move) != NULL) {
      myMAP.h_index = -1;
      DEBUG_HIST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_HIST   yLOG_value   ("h_index"   , myMAP.h_index);
   /*---(handle move)--------------------*/
   DEBUG_HIST   yLOG_note    ("check special shortcuts");
   switch (a_move) {
   case YDLST_HEAD :
      myMAP.h_curr  = myMAP.h_head;
      myMAP.h_index = 0;
      break;
   case YDLST_PREV :
      myMAP.h_curr  = myMAP.h_curr->h_prev;
      --myMAP.h_index;
      break;
   case YDLST_NEXT :
      myMAP.h_curr  = myMAP.h_curr->h_next;
      ++myMAP.h_index;
      break;
   case YDLST_TAIL :
      myMAP.h_curr  = myMAP.h_tail;
      myMAP.h_index = myMAP.h_count - 1;
      break;
   }
   /*---(safeties)-----------------------*/
   DEBUG_HIST   yLOG_point   ("h_curr"    , myMAP.h_curr);
   --rce;  if (myMAP.h_curr == NULL) {
      myMAP.h_index = -1;
      DEBUG_HIST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(output)-------------------------*/
   DEBUG_HIST   yLOG_point   ("h_curr"    , myMAP.h_curr);
   DEBUG_HIST   yLOG_value   ("h_index"   , myMAP.h_index);
   /*---(complete)-----------------------*/
   DEBUG_HIST   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__mundo_by_index    (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tHIST      *x_curr      =    0;
   int         c           =    0;
   /*---(defense)---------------------*/
   --rce;  if (myMAP.h_head == NULL)  {
      myMAP.h_curr  = NULL;
      myMAP.h_index = -1;
      return rce;
   }
   /*---(walk entries)----------------*/
   x_curr = myMAP.h_head;
   while (x_curr != NULL) {
      if (n == c) break;
      ++c;
      x_curr = x_curr->h_next;
   }
   /*---(check for miss)-----------------*/
   --rce;  if (x_curr == NULL) {
      myMAP.h_curr  = NULL;
      myMAP.h_index = -1;
      return rce;
   }
   /*---(save current)-------------------*/
   myMAP.h_curr  = x_curr;
   myMAP.h_index = c;
   /*---(complete)-----------------------*/
   return 0;
}

char*
ymap_mundo_action   (char a_mode, char a_act)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   strcpy (myMAP.g_print, "n/a");
   for (i = 0; i < s_nact; ++i) {
      if (s_acts [i].act == 0)      break;
      if (s_acts [i].act != a_act)  continue;
      switch (a_mode) {
      case YMAP_BEG :
         strcpy (myMAP.g_print, s_acts [i].name);
         break;
      case YMAP_ADD :
         sprintf (myMAP.g_print, "´ %s", s_acts [i].name);
         break;
      }
      break;
   }
   return myMAP.g_print;
}


/*====================------------------------------------====================*/
/*===----                     simple character adds                    ----===*/
/*====================------------------------------------====================*/
static void  o___SIMPLE__________o () { return; }

char         /*-> record a cell change ---------------[ leaf   [gz.520.101.00]*/ /*-[01.0000.204.!]-*/ /*-[--.---.---.--]-*/
ymap__mundo_chars       (char *a_func, char a_mode, char a_act, char *a_label, char a_before, char a_after)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        s           [LEN_LABEL] = "";
   tHIST      *x_curr      = NULL;
   ushort      u, x, y, z;
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (a_func);
   DEBUG_HIST  yLOG_complex ("args"      , "%c, %c, %p, %c, %c", a_mode, a_act, a_label, a_before, a_after);
   /*---(early-defense)------------------*/
   --rce;  if (a_before != chrvisible (a_before)) {
      DEBUG_HIST  yLOG_note    ("a_before is non-visible char");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   --rce;  if (a_after  != chrvisible (a_after )) {
      DEBUG_HIST  yLOG_note    ("a_after is non-visible char");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(get location)-------------------*/
   DEBUG_HIST  yLOG_info    ("a_label"   , a_label);
   rc = ymap_locator_strict (a_label, &u, &x, &y, &z);
   DEBUG_HIST  yLOG_value   ("strict"    , rc);
   --rce;  if (rc  <  0) {
      DEBUG_HIST  yLOG_note    ("label not legal or in known space");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_HIST  yLOG_complex ("locator"   , "%4du, %4dx, %4dy, %4zx", u, x, y, z);
   /*---(mark changes)-------------------*/
   --rce;  switch (a_act) {
   case YMAP_ALIGN    :
   case YMAP_FORMAT   :
   case YMAP_DECIMALS :
   case YMAP_UNITS    :
      break;
   default :
      DEBUG_HIST  yLOG_note    ("action not known");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
      break;
   }
   /*---(late-defense)-------------------*/
   DEBUG_HIST  yLOG_char    ("active"    , myMAP.h_active);
   if (myMAP.h_active != 'y') {
      DEBUG_HIST  yLOG_exit    (a_func);
      return 0;
   }
   if (a_mode      == YMAP_NONE) {
      DEBUG_HIST  yLOG_note    ("history is not requested on this action");
      DEBUG_HIST  yLOG_exit    (a_func);
      return 0;
   }
   /*---(add record)---------------------*/
   rc = ymap__mundo_new (a_mode, a_act, a_label, &x_curr);
   DEBUG_HIST  yLOG_value   ("new"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_HIST  yLOG_note    ("creating a new mundo failed");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(add detail)------------------*/
   if (rc >= 0) {
      sprintf (s, "%c", a_before);
      x_curr->before = strdup  (s);
      sprintf (s, "%c", a_after );
      x_curr->after  = strdup  (s);
   }
   /*---(complete)--------------------*/
   DEBUG_HIST  yLOG_exitr   (a_func, rc);
   return rc;
}

char
yMAP_mundo_align        (char a_mode, char *a_label, char a_before, char a_after)
{
   return ymap__mundo_chars   (__FUNCTION__, a_mode, YMAP_ALIGN    , a_label, a_before, a_after);
}

char
yMAP_mundo_format       (char a_mode, char *a_label, char a_before, char a_after)
{
   return ymap__mundo_chars   (__FUNCTION__, a_mode, YMAP_FORMAT   , a_label, a_before, a_after);
}

char
yMAP_mundo_decimals     (char a_mode, char *a_label, char a_before, char a_after)
{
   return ymap__mundo_chars   (__FUNCTION__, a_mode, YMAP_DECIMALS , a_label, a_before, a_after);
}

char
yMAP_mundo_units        (char a_mode, char *a_label, char a_before, char a_after)
{
   return ymap__mundo_chars   (__FUNCTION__, a_mode, YMAP_UNITS    , a_label, a_before, a_after);
}



/*====================------------------------------------====================*/
/*===----                      simple integer adds                     ----===*/
/*====================------------------------------------====================*/
static void  o___NUMBER__________o () { return; }

char         /*-> record a cell change ---------------[ leaf   [gz.520.101.00]*/ /*-[01.0000.204.!]-*/ /*-[--.---.---.--]-*/
ymap__mundo_ints        (char *a_func, char a_mode, char a_act, char *a_label, char a_before, char a_after)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        s           [LEN_LABEL] = "";
   tHIST      *x_curr      = NULL;
   ushort      u, x, y, z;
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (a_func);
   DEBUG_HIST  yLOG_complex ("args"      , "%c, %c, %p, %3d, %3d", a_mode, a_act, a_label, a_before, a_after);
   /*---(early-defense)------------------*/
   --rce;  if (a_before <  0) {
      DEBUG_HIST  yLOG_note    ("a_before is negative");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   --rce;  if (a_after  <  0) {
      DEBUG_HIST  yLOG_note    ("a_after is negative");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(get position)-------------------*/
   DEBUG_HIST  yLOG_info    ("a_label"   , a_label);
   rc = ymap_locator_strict (a_label, &u, &x, &y, &z);
   DEBUG_HIST  yLOG_value   ("strict"    , rc);
   --rce;  if (rc  <  0) {
      DEBUG_HIST  yLOG_note    ("label not legal or in known space");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_HIST  yLOG_complex ("locator"   , "%4du, %4dx, %4dy, %4zx", u, x, y, z);
   /*---(mark changes)-------------------*/
   --rce;  switch (a_act) {
   case YMAP_WIDTH  :
      rc = ymap_wide (x, a_after);
      break;
   case YMAP_HEIGHT :
      rc = ymap_tall (y, a_after);
      break;
   case YMAP_DEPTH  :
      rc = ymap_deep (z, a_after);
      break;
   default :
      DEBUG_HIST  yLOG_note    ("action not known");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
      break;
   }
   DEBUG_HIST  yLOG_value   ("update"    , rc);
   /*---(late-defense)-------------------*/
   DEBUG_HIST  yLOG_char    ("active"    , myMAP.h_active);
   if (myMAP.h_active != 'y') {
      DEBUG_HIST  yLOG_exit    (a_func);
      return 0;
   }
   if (a_mode      == YMAP_NONE) {
      DEBUG_HIST  yLOG_note    ("history is not requested on this action");
      DEBUG_HIST  yLOG_exit    (a_func);
      return 0;
   }
   /*---(add record)---------------------*/
   rc = ymap__mundo_new (a_mode, a_act, a_label, &x_curr);
   DEBUG_HIST  yLOG_value   ("new"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_HIST  yLOG_note    ("creating a new mundo failed");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(add detail)------------------*/
   if (rc >= 0) {
      sprintf (s, "%d", a_before);
      x_curr->before = strdup  (s);
      sprintf (s, "%d", a_after );
      x_curr->after  = strdup  (s);
   }
   /*---(complete)--------------------*/
   DEBUG_HIST  yLOG_exitr   (a_func, rc);
   return rc;
}

char
yMAP_mundo_width        (char a_mode, char *a_label, char a_before, char a_after)
{
   return ymap__mundo_ints    (__FUNCTION__, a_mode, YMAP_WIDTH    , a_label, a_before, a_after);
}

char
yMAP_mundo_height       (char a_mode, char *a_label, char a_before, char a_after)
{
   return ymap__mundo_ints    (__FUNCTION__, a_mode, YMAP_HEIGHT   , a_label, a_before, a_after);
}

char
yMAP_mundo_depth        (char a_mode, char *a_label, char a_before, char a_after)
{
   return ymap__mundo_ints    (__FUNCTION__, a_mode, YMAP_DEPTH    , a_label, a_before, a_after);
}



/*====================------------------------------------====================*/
/*===----                   simple content adds                        ----===*/
/*====================------------------------------------====================*/
static void  o___STRING__________o () { return; }

char         /*-> record a cell change ---------------[ leaf   [gz.520.101.00]*/ /*-[01.0000.204.!]-*/ /*-[--.---.---.--]-*/
ymap__mundo_string      (char *a_func, char a_mode, char a_act, char *a_label, char *a_before, char *a_after)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *b           = NULL;
   char       *a           = NULL;
   tHIST      *x_curr      = NULL;
   ushort      u, x, y, z;
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (a_func);
   DEBUG_HIST  yLOG_complex ("args"      , "%c, %c, %p, %p, %p", a_mode, a_act, a_label, a_before, a_after);
   /*---(prepare)------------------------*/
   if (a_before == NULL)  b = s_nada;
   else                   b = a_before;
   if (a_after  == NULL)  a = s_nada;
   else                   a = a_after;
   /*---(get position)-------------------*/
   DEBUG_HIST  yLOG_info    ("a_label"   , a_label);
   if (strcmp (a_label, "n/a") != 0) {
      rc = ymap_locator_strict (a_label, &u, &x, &y, &z);
      DEBUG_HIST  yLOG_value   ("strict"    , rc);
      --rce;  if (rc  <  0) {
         DEBUG_HIST  yLOG_note    ("label not legal or in known space");
         DEBUG_HIST  yLOG_exitr   (a_func, rce);
         return rce;
      }
      DEBUG_HIST  yLOG_complex ("locator"   , "%4du, %4dx, %4dy, %4zx", u, x, y, z);
   }
   /*---(mark changes)-------------------*/
   --rce;  switch (a_act) {
   case YMAP_SOURCE :
      ymap_used (x, y, z);
      DEBUG_HIST  yLOG_value   ("update"    , rc);
      break;
   case YMAP_VOLUME :
   case YMAP_TITLE  :
   case YMAP_SYNC   :
      break;
      DEBUG_HIST  yLOG_note    ("action not known");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
      break;
   }
   /*---(defense)------------------------*/
   DEBUG_HIST  yLOG_char    ("active"    , myMAP.h_active);
   if (myMAP.h_active != 'y') {
      DEBUG_HIST  yLOG_exit    (a_func);
      return 0;
   }
   if (a_mode      == YMAP_NONE) {
      DEBUG_HIST  yLOG_note    ("history is not requested on this action");
      DEBUG_HIST  yLOG_exit    (a_func);
      return 0;
   }
   /*---(add record)---------------------*/
   rc = ymap__mundo_new (a_mode, a_act, a_label, &x_curr);
   DEBUG_HIST  yLOG_value   ("new"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_HIST  yLOG_note    ("creating a new mundo failed");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(add detail)------------------*/
   if (rc >= 0) {
      x_curr->before = strdup  (b);
      x_curr->after  = strdup  (a);
   }
   /*---(complete)--------------------*/
   DEBUG_HIST  yLOG_exitr   (a_func, rc);
   return rc;
}

char
yMAP_mundo_source       (char a_mode, char *a_label, char *a_before, char *a_after)
{
   char        rc          =    0;
   ushort      x, y, z;
   rc = ymap_locator_strict (a_label, NULL, &x, &y, &z);
   if (rc >= 0)  ymap_used (x, y, z);
   rc = ymap__mundo_string  (__FUNCTION__, a_mode, YMAP_SOURCE   , a_label, a_before, a_after);
   return rc;
}

char
yMAP_mundo_volume       (char a_mode, char *a_label, char *a_before, char *a_after)
{
   return ymap__mundo_string  (__FUNCTION__, a_mode, YMAP_VOLUME   , a_label, a_before, a_after);
}

char
yMAP_mundo_title        (char a_mode, char *a_label, char *a_before, char *a_after)
{
   return ymap__mundo_string  (__FUNCTION__, a_mode, YMAP_TITLE    , a_label, a_before, a_after);
}

char
yMAP_mundo_sync         (char a_mode, char *a_reqs, char *a_pros)
{
   return ymap__mundo_string  (__FUNCTION__, a_mode, YMAP_SYNC     , "n/a", a_reqs, a_pros);
}



/*====================------------------------------------====================*/
/*===----                   complex combo adds                         ----===*/
/*====================------------------------------------====================*/
static void  o___COMPLEX_________o () { return; }

char
ymap__mundo_concat      (char *a_format, char *a_content, char **a_final)
{
   /*---(locals)-----------+-----+-----+-*/
   char       *p           = NULL;
   char       *q           = NULL;
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (__FUNCTION__);
   /*---(format)----------------------*/
   DEBUG_HIST  yLOG_point   ("a_format"  , a_format);
   if (a_format == NULL)         p = s_nada;
   else {
      DEBUG_HIST  yLOG_info    ("a_format"  , a_format);
      p = a_format;
   }
   DEBUG_HIST  yLOG_complex ("format"    , "%-10.10s, %-10.10s, %10.10s", s_nothing, a_format, p);
   /*---(content)---------------------*/
   DEBUG_HIST  yLOG_point   ("a_content" , a_content);
   if      (a_content  == NULL)  q = s_nada;
   else {
      DEBUG_HIST  yLOG_info    ("a_content" , a_content);
      q = a_content;
   }
   /*---(concatenate)-----------------*/
   if (p == s_nada && q == s_nada)  *a_final = s_nada;
   else  {
      sprintf (t, "%-*.*s··%s", myMAP.h_len, myMAP.h_len, p, q);
      *a_final = strdup (t);
   }
   DEBUG_HIST  yLOG_complex ("before"    , "%-10.10s, %-10.10s, %10.10s", s_nada, a_content, *a_final);
   /*---(show)------------------------*/
   DEBUG_HIST  yLOG_info    ("*a_final"  , *a_final);
   /*---(complete)--------------------*/
   DEBUG_HIST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> record a cell change ---------------[ leaf   [gz.520.101.00]*/ /*-[01.0000.204.!]-*/ /*-[--.---.---.--]-*/
ymap__mundo_complex     (char *a_func, char a_mode, char a_act, char *a_label, char* a_beforeF, char* a_before, char* a_afterF, char* a_after)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tHIST      *x_curr      = NULL;
   char       *b           = NULL;
   char       *a           = NULL;
   ushort      u, x, y, z;
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (a_func);
   DEBUG_HIST  yLOG_complex ("args"      , "%c, %c, %p, %c, %c", a_mode, a_act, a_label, a_before, a_after);
   /*---(early-defense)------------------*/
   --rce;  if (a_beforeF == NULL || a_beforeF [0] == '\0') {
      DEBUG_HIST  yLOG_note    ("before format is null/empty");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   --rce;  if (a_afterF  == NULL || a_afterF  [0] == '\0') {
      if (a_act != YMAP_DELETE) {
         DEBUG_HIST  yLOG_note    ("after format is null/empty");
         DEBUG_HIST  yLOG_exitr   (a_func, rce);
         return rce;
      }
   }
   /*---(get position)-------------------*/
   DEBUG_HIST  yLOG_info    ("a_label"   , a_label);
   rc = ymap_locator_strict (a_label, &u, &x, &y, &z);
   DEBUG_HIST  yLOG_value   ("strict"    , rc);
   --rce;  if (rc  <  0) {
      DEBUG_HIST  yLOG_note    ("label not legal or in known space");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   DEBUG_HIST  yLOG_complex ("locator"   , "%4du, %4dx, %4dy, %4zx", u, x, y, z);
   /*---(mark changes)-------------------*/
   --rce;  switch (a_act) {
   case YMAP_CLEAR  :
      ymap_empty (x, y, z);
      DEBUG_HIST  yLOG_value   ("update"    , rc);
      break;
   case YMAP_OVERWRITE :
   case YMAP_DELETE    :
      break;
   default :
      DEBUG_HIST  yLOG_note    ("action not known");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
      break;
   }
   /*---(late-defense)-------------------*/
   DEBUG_HIST  yLOG_char    ("active"    , myMAP.h_active);
   if (myMAP.h_active != 'y') {
      DEBUG_HIST  yLOG_exit    (a_func);
      return 0;
   }
   if (a_mode      == YMAP_NONE) {
      DEBUG_HIST  yLOG_note    ("history is not requested on this action");
      DEBUG_HIST  yLOG_exit    (a_func);
      return 0;
   }
   /*---(concatinate)--------------------*/
   ymap__mundo_concat  (a_beforeF, a_before, &b);
   ymap__mundo_concat  (a_afterF , a_after , &a);
   /*---(add record)---------------------*/
   rc = ymap__mundo_new (a_mode, a_act, a_label, &x_curr);
   DEBUG_HIST  yLOG_value   ("new"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_HIST  yLOG_note    ("creating a new mundo failed");
      DEBUG_HIST  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(add detail)------------------*/
   if (rc >= 0) {
      x_curr->before = b;
      x_curr->after  = a;
   }
   /*---(complete)--------------------*/
   DEBUG_HIST  yLOG_exitr   (a_func, rc);
   return rc;
}

char
yMAP_mundo_overwrite    (char a_mode, char *a_label, char* a_beforeF, char* a_before, char* a_afterF, char* a_after)
{
   return ymap__mundo_complex (__FUNCTION__, a_mode, YMAP_OVERWRITE, a_label, a_beforeF, a_before, a_afterF, a_after);
}

char
yMAP_mundo_clear        (char a_mode, char *a_label, char* a_beforeF, char* a_before, char *a_afterF)
{
   return ymap__mundo_complex (__FUNCTION__, a_mode, YMAP_CLEAR    , a_label, a_beforeF, a_before, a_afterF, "");
}

char
yMAP_mundo_delete       (char a_mode, char *a_label, char* a_beforeF, char* a_before)
{
   return ymap__mundo_complex (__FUNCTION__, a_mode, YMAP_DELETE   , a_label, a_beforeF, a_before, NULL, NULL);
}



/*====================------------------------------------====================*/
/*===----                       undo functions                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNDO____________o () { return; }

char
ymap__mundo_parse       (char a_act, char *a_field, char *a_format, char *a_content)
{
   /*---(locals)-----------+-----+-----+-*/
   int         l           =    0;
   char        x_len       =    0;
   char        x_off       =    0;
   /*---(defaults)-----------------------*/
   if (a_format  != NULL)  strlcpy (a_format , "", LEN_LABEL);
   if (a_content != NULL)  strlcpy (a_content, "", LEN_RECD);
   /*---(quick-out)----------------------*/
   if (a_field == NULL)  return 0;
   x_len = myMAP.h_len;
   /*---(handle simples)-----------------*/
   if (strchr ("oxD", a_act) == NULL) {
      strlcpy (a_content, a_field, LEN_RECD);
      return 0;
   }
   /*---(format)-------------------------*/
   l = strlen (a_field);
   if (a_format != NULL) {
      sprintf (a_format, "%-.*s··········", x_len, a_field);
      a_format [x_len] = '\0';
   }
   /*---(content)------------------------*/
   x_off = x_len + 2;
   if (l > x_off) {
      if (a_content != NULL)  sprintf (a_content, "%s", a_field + x_off);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> take a change away -----------------[ leaf   [gc.J76.043.IA]*/ /*-[03.0000.113.!]-*/ /*-[--.---.---.--]-*/
ymap__mundo_undo_one    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_format    [LEN_LABEL] = "";
   char        x_content   [LEN_RECD]  = "";
   int         l           =    0;
   ushort      u, x, y, z;
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (__FUNCTION__);
   /*---(identify location)--------------*/
   DEBUG_HIST  yLOG_info    ("label"     , myMAP.h_curr->label);
   if (strcmp (myMAP.h_curr->label, "n/a") != 0) {
      /*---(parse location)--------------*/
      rc = ymap_locator (myMAP.h_curr->label, &u, &x, &y, &z);
      DEBUG_HIST  yLOG_value   ("locator"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_HIST  yLOG_complex ("jump to"   , "%4du, %4dx, %4dy, %4dz", u, x, y, z);
      /*---(get to right location)-------*/
      rc = yMAP_jump  (u, x, y, z);
      DEBUG_HIST  yLOG_value   ("jump"        , rc);
      --rce;  if (rc < 0) {
         DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(parse data)---------------------*/
   ymap__mundo_parse (myMAP.h_curr->act, myMAP.h_curr->before, x_format, x_content);
   /*---(handle request)-----------------*/
   DEBUG_HIST  yLOG_point   ("e_mundo"     , myMAP.e_mundo);
   --rce;  if (myMAP.e_mundo == NULL) {
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = myMAP.e_mundo ('<', myMAP.h_curr->act, myMAP.h_curr->label, x_format, x_content);
   DEBUG_HIST  yLOG_value   ("undo"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_HIST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> take a change away -----------------[ leaf   [gc.J76.043.IA]*/ /*-[03.0000.113.!]-*/ /*-[--.---.---.--]-*/
ymap_mundo_undo         (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_mode      =  '-';
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_HIST  yLOG_value   ("h_count"     , myMAP.h_count);
   --rce;  if (myMAP.h_count <  0) {
      DEBUG_HIST  yLOG_note    ("no history to undo");
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_HIST  yLOG_point   ("h_curr"      , myMAP.h_curr);
   --rce;  if (myMAP.h_curr == NULL) {
      DEBUG_HIST  yLOG_note    ("current is not set");
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_HIST  yLOG_value   ("h_index"     , myMAP.h_index);
   --rce;  if (myMAP.h_index <  0) {
      DEBUG_HIST  yLOG_note    ("current is already at beginning");
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   myMAP.h_active = '-';
   DEBUG_HIST  yLOG_char    ("h_active"    , myMAP.h_active);
   /*> HIST_debug ();                                                                 <*/
   /*---(process)------------------------*/
   while (rc == 0) {
      /*---(save mode)-------------------*/
      x_mode = myMAP.h_curr->mode;
      DEBUG_HIST  yLOG_char    ("curr mode" , x_mode);
      /*---(process current)-------------*/
      rc = ymap__mundo_undo_one ();
      if (rc <  0) {
         DEBUG_HIST  yLOG_note    ("error in undo processing");
         myMAP.h_active = 'y';
         DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(update position)-------------*/
      rc = ymap__mundo_by_cursor (YDLST_PREV);
      /*---(check for breakpoint)--------*/
      if (x_mode == YMAP_BEG) {
         DEBUG_HIST  yLOG_note    ("hit start of undo chain, done");
         break;
      }
      /*---(next)------------------------*/
   }
   /*---(reset)--------------------------*/
   DEBUG_HIST  yLOG_char    ("h_active"    , myMAP.h_active);
   myMAP.h_active = 'y';
   /*---(complete)-----------------------*/
   DEBUG_HIST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> add a change back ------------------[ leaf   [gc.J76.043.IA]*/ /*-[03.0000.113.!]-*/ /*-[--.---.---.--]-*/
ymap__mundo_redo_one    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_format    [LEN_LABEL] = "";
   char        x_content   [LEN_RECD]  = "";
   int         l           =    0;
   ushort      u, x, y, z;
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (__FUNCTION__);
   /*---(identify location)--------------*/
   DEBUG_HIST  yLOG_info    ("label"     , myMAP.h_curr->label);
   if (strcmp (myMAP.h_curr->label, "n/a") != 0) {
      /*---(parse location)--------------*/
      rc = ymap_locator (myMAP.h_curr->label, &u, &x, &y, &z);
      DEBUG_HIST  yLOG_value   ("locator"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_HIST  yLOG_complex ("jump to"   , "%4du, %4dx, %4dy, %4dz", u, x, y, z);
      /*---(get to right location)-------*/
      rc = yMAP_jump  (u, x, y, z);
      DEBUG_HIST  yLOG_value   ("jump"        , rc);
      --rce;  if (rc < 0) {
         DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(parse data)---------------------*/
   ymap__mundo_parse (myMAP.h_curr->act, myMAP.h_curr->after, x_format, x_content);
   /*---(handle request)-----------------*/
   DEBUG_HIST  yLOG_point   ("e_mundo"     , myMAP.e_mundo);
   --rce;  if (myMAP.e_mundo == NULL) {
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = myMAP.e_mundo ('>', myMAP.h_curr->act, myMAP.h_curr->label, x_format, x_content);
   DEBUG_HIST  yLOG_value   ("undo"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_HIST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> take a change away -----------------[ leaf   [gc.J76.043.IA]*/ /*-[03.0000.113.!]-*/ /*-[--.---.---.--]-*/
ymap_mundo_redo        (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_mode      =  '-';
   /*---(header)-------------------------*/
   DEBUG_HIST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_HIST  yLOG_value   ("h_count"     , myMAP.h_count);
   --rce;  if (myMAP.h_count <  0) {
      DEBUG_HIST  yLOG_note    ("no history to undo");
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_HIST  yLOG_value   ("h_index"     , myMAP.h_index);
   --rce;  if (myMAP.h_index >= myMAP.h_count - 1) {
      DEBUG_HIST  yLOG_note    ("current is already at maximum");
      DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   myMAP.h_active = '-';
   if      (myMAP.h_curr  == NULL)  ymap__mundo_by_cursor (YDLST_HEAD);
   else if (myMAP.h_index == -1)    ymap__mundo_by_cursor (YDLST_HEAD);
   else                             ymap__mundo_by_cursor (YDLST_NEXT);
   /*---(process)------------------------*/
   while (rc == 0) {
      /*---(process current)-------------*/
      rc = ymap__mundo_redo_one ();
      if (rc <  0) {
         DEBUG_HIST  yLOG_note    ("error in redo processing");
         DEBUG_HIST  yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(update position)-------------*/
      DEBUG_HIST  yLOG_value   ("h_index"     , myMAP.h_index);
      if (myMAP.h_curr == NULL) {
         DEBUG_HIST  yLOG_note    ("hit end of of history, done");
         ymap__mundo_by_cursor (YDLST_TAIL);
         myMAP.h_index = myMAP.h_count - 1;
         break;
      }
      /*---(check for breakpoint)--------*/
      if (myMAP.h_curr->h_next == NULL || myMAP.h_curr->h_next->mode == YMAP_BEG) {
         DEBUG_HIST  yLOG_note    ("hit end of undo chain, done");
         break;
      }
      /*---(next)------------------------*/
      rc = ymap__mundo_by_cursor (YDLST_NEXT);
   }
   /*---(reset)--------------------------*/
   myMAP.h_active = 'y';
   /*---(complete)-----------------------*/
   DEBUG_HIST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       mode helper                            ----===*/
/*====================------------------------------------====================*/
static void  o___MODE____________o () { return; }

char
ymap_mundo_hmode        (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =   -1;
   /*---(quick out)----------------------*/
   if (a_major != G_KEY_SPACE)  return 0;
   /*---(header)-------------------------*/
   DEBUG_HIST   yLOG_enter   (__FUNCTION__);
   /*---(macros modes)-------------------*/
   switch (a_minor) {
   case 'u'      :
      DEBUG_HIST   yLOG_note    ("undo reqested");
      ymap_mundo_undo ();
      DEBUG_HIST   yLOG_exit    (__FUNCTION__);
      return 1;
      break;
   case 'U'      :
      DEBUG_HIST   yLOG_note    ("redo reqested");
      ymap_mundo_redo ();
      DEBUG_HIST   yLOG_exit    (__FUNCTION__);
      return 1;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_HIST   yLOG_exit    (__FUNCTION__);
   return 0;
}





