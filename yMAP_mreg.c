/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"


/*===[[ OVERVIEW ]]==========================================================*/

/*  map-registers are a series of temporary spaces which are used to aid
 *  movement of objects/items from one map location to another using the
 *  yank/copy, delete/cut, and put/paste commands.
 */



/*
 *   map registers manages a series of temporary registers which are used to
 *   aid movement of cells from one spreadsheet location to another using the
 *   yank, delete, and put commands.  in order to support scripting, batch
 *   operations, and power/technical users; a large number of registers will
 *   be created to complicated operations and scripts can be facilitated.
 *
 *   since registers are vital to all applications that allow any form of
 *   editing or modification, a consistent interface will allow users to
 *   quickly become efficient and effective in each tool.  also, consistency
 *   will allow deeper tool usage as training will easily translate across
 *   applications.
 *
 *   gyges registers will be based on the usage and capabilities of vi/vim, but
 *   as mentioned above, generalized to be useful in a broad range of
 *   applications.  the resulting consistent command set is called the vi-keys
 *   mini-language.  because of this desired consistency, though, i will have to
 *   manage a series of broad applicability versus power/depth trade-offs which
 *   will result in better transportability, but perhaps a slightly sub-optimal
 *   feature set for a spreadsheet.
 *
 *   vi/vim has a huge number of registers, many of which are special purpose.
 *   we will focus on delivering the following fifty-five registers to be used
 *   for (y)ank, (d)elete, and (p)ut.
 *      -      default, unnamed register
 *      a-z    named registers, accessable only within this spreadsheet
 *      A-Z    named registers, accessable to all spreadsheet instances
 *      +      window manager clipboard as delimited, 7bit-safe, ascii text
 *      0      working area                  
 *
 *   gyges registers are meant to support power users, scripting, and robust
 *   batch usage.  for everyday they are way overbuilt ;)
 *
 *
 */






#define     S_REG_MAX   100
#define     LEN_BUF    1000


typedef  struct  cITEM  tITEM;
struct cITEM {
   void       *data;
   char       *routes;
   tITEM      *b_next;
   tITEM      *b_prev;
};


typedef  struct  cREG   tREG;
struct cREG {
   /*---(#1, ORIGIN TAB)-----------------*/
   /*   stores the tab number of the original selection so that cell          */
   /*   references can be properly adjusted when placed back into a tab.      */
   char        u_all;
   char        z_all;
   /*---(#2, MINIMUM REACH)--------------*/
   /*   stores the column and row of the furthest upper-left cell reference   */
   /*   within a formula of a register cell (for error-checking).             */
   short       x_min;
   short       y_min;
   /*---(#3, MINIMUM BOUND)--------------*/
   /*   stores the column and row of the upper-left corner of the selection   */
   /*   used to source the cells for the register.                            */
   short       x_beg;
   short       y_beg;
   /*---(#4, MAXIMUM BOUND)--------------*/
   /*   stores the column and row of the lower-right corner of the selection  */
   /*   used to source the cells for the register.                            */
   short       x_end;
   short       y_end;
   /*---(#5, MAXIMUM REACH)--------------*/
   /*   stores the column and row of the furthest lower-right cell reference  */
   /*   within a formula of a register cell (for error-checking).             */
   short       x_max;
   short       y_max;
   /*---(#6, CELLS)----------------------*/
   /*   stores the an array of cells within the register in the order that    */
   /*   they need to be placed back into a tab to correctly calculate.        */
   tITEM      *hbuf;                             /* head of items             */
   tITEM      *tbuf;                             /* tail of items             */
   short       nbuf;                             /* total items               */
   char       *labels;                           /* label list (debugging)    */
   /*---(#7, SPECIAL)--------------------*/
   /*   the type flag indicates whether non-selection formula cells with      */
   /*   references into the selection should be adjusted when pasted.         */
   char        type;
   /*---(end)----------------------------*/
};
static      tREG        s_regs       [S_REG_MAX];
static      char        S_REG_LIST   [S_REG_MAX];
static      int         s_nreg       =    0;
static      char        s_creg       =  '"';
static      char       *s_stubby     = "n/a";

#define     S_REG_EMPTY     '-'
#define     S_REG_ACTIVE    'y'

/* destroy a copy held in a register --------------------------*/
/*> static char    (*s_regkill)    (void *a_thing);                                   <*/
/* get a copy and put it into a register ----------------------*/
/*> static void*   (*s_copier)     (char a_type, long a_stamp);                       <*/
/* clear an area in the host application ----------------------*/
/*> static char    (*s_clearer)    (char a_1st, int b, int x, int y, int z);          <*/
/* update links in host application ---------------------------*/
/*> static char    (*s_router)     (void *a_thing, char *a_list);                     <*/
/* integrate something into the host application --------------*/
/*> static char    (*s_paster)     (char a_regs, char a_pros, char a_intg, char a_1st, int a_boff, int a_xoff, int a_yoff, int a_zoff, void *a_thing, char *a_list);   <*/
/* update links in host application ---------------------------*/
/*> static char    (*s_finisher)   (int a_boff, int a_xoff, int a_yoff, int a_zoff, void *a_thing);   <*/
/* data export and import -------------------------------------*/
/*> static char    (*s_exim)       (char a_dir, char a_style);                        <*/



#define   MAX_PASTING           500
typedef  struct cPASTING tPASTING;
struct cPASTING {
   char        abbr;
   char        ref         [LEN_LABEL];
   char        name        [LEN_LABEL];
   char        primary;
   char        clear;       /* merge, clear, ... */
   char        reqs;        /* none, relative, inner, both (rel/inner), every  */
   char        pros;        /* none, relative, all, split */
   char        intg;        /* tbd */
   char        desc        [LEN_DESC ];
};
static const tPASTING   s_pasting [MAX_PASTING] = {
   /*-a- --ref-- ---name-------- -pr-    --c- --r- --p- --i- ---desc--- */
   { '-', "----", ""            , '-',    '-', '-', '-', '-',    "tbd" },
   /*-01/04--*/
   { '-', "-nN-", ""            , '-',    '-', 'n', 'N', '-',    "tbd" },
   { '-', "-nR-", ""            , '-',    '-', 'n', 'R', '-',    "tbd" },
   { '-', "-nA-", ""            , '-',    '-', 'n', 'A', '-',    "tbd" },
   { '-', "-nS-", ""            , '-',    '-', 'n', 'S', '-',    "tbd" },
   /*-05/08--*/
   { 'n', "-rN-", "normal"      , 'y',    '-', 'r', 'N', '-',    "tbd" },
   { '-', "-rR-", ""            , '-',    '-', 'r', 'R', '-',    "tbd" },
   { '-', "-rA-", ""            , '-',    '-', 'r', 'A', '-',    "tbd" },
   { '-', "-rS-", ""            , '-',    '-', 'r', 'S', '-',    "tbd" },
   /*-09/12--*/
   { '-', "-iN-", ""            , '-',    '-', 'i', 'N', '-',    "tbd" },
   { '-', "-iR-", ""            , '-',    '-', 'i', 'R', '-',    "tbd" },
   { '-', "-iA-", ""            , '-',    '-', 'i', 'A', '-',    "tbd" },
   { '-', "-iS-", ""            , '-',    '-', 'i', 'S', '-',    "tbd" },
   /*-13/16--*/
   { '-', "-bN-", ""            , '-',    '-', 'b', 'N', '-',    "tbd" },
   { '-', "-bR-", ""            , '-',    '-', 'b', 'R', '-',    "tbd" },
   { '-', "-bA-", ""            , '-',    '-', 'b', 'A', '-',    "tbd" },
   { '-', "-bS-", ""            , '-',    '-', 'b', 'S', '-',    "tbd" },
   /*-17/20--*/
   { '-', "-eN-", ""            , '-',    '-', 'e', 'N', '-',    "tbd" },
   { '-', "-eR-", ""            , '-',    '-', 'e', 'R', '-',    "tbd" },
   { '-', "-eA-", ""            , '-',    '-', 'e', 'A', '-',    "tbd" },
   { '-', "-eS-", ""            , '-',    '-', 'e', 'S', '-',    "tbd" },
   /*---------*/
   { '#', "y---", "clear"       , 'y',    'y', '-', '-', '-',    "tbd" },
   /*-21/24--*/
   { '-', "ynN-", ""            , '-',    'y', 'n', 'N', '-',    "tbd" },
   { '-', "ynR-", ""            , '-',    'y', 'n', 'R', '-',    "tbd" },
   { '-', "ynA-", ""            , '-',    'y', 'n', 'A', '-',    "tbd" },
   { '-', "ynS-", ""            , '-',    'y', 'n', 'S', '-',    "tbd" },
   /*-25/28--*/
   { 'r', "yrN-", "replace"     , 'y',    'y', 'r', 'N', '-',    "tbd" },
   { '-', "yrR-", ""            , '-',    'y', 'r', 'R', '-',    "tbd" },
   { '-', "yrA-", ""            , '-',    'y', 'r', 'A', '-',    "tbd" },
   { '-', "yrS-", ""            , '-',    'y', 'r', 'S', '-',    "tbd" },
   /*-29/32--*/
   { 'd', "yiN-", "duplicate"   , 'y',    'y', 'i', 'N', '-',    "tbd" },
   { '-', "yiR-", ""            , '-',    'y', 'i', 'R', '-',    "tbd" },
   { '-', "yiA-", "append"      , '-',    'y', 'i', 'A', '-',    "tbd" },
   { '-', "yiS-", ""            , '-',    'y', 'i', 'S', '-',    "tbd" },
   /*-33/36--*/
   { 'c', "ybN-", "combo"       , 'y',    'y', 'b', 'N', '-',    "tbd" },
   { 'm', "ybR-", "move"        , 'y',    'y', 'b', 'R', '-',    "tbd" },
   { 'f', "ybA-", "force"       , 'y',    'y', 'b', 'A', '-',    "tbd" },
   { '-', "ybS-", ""            , '-',    'y', 'b', 'S', '-',    "tbd" },
   /*-37/40--*/
   { '-', "yeN-", ""            , '-',    'y', 'e', 'N', '-',    "tbd" },
   { '-', "yeR-", ""            , '-',    'y', 'e', 'R', '-',    "tbd" },
   { '-', "yeA-", ""            , '-',    'y', 'e', 'A', '-',    "tbd" },
   { '-', "yeS-", ""            , '-',    'y', 'e', 'S', '-',    "tbd" },
   /*---------*/
};



/*====================------------------------------------====================*/
/*===----                        support functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char 
ymap__mreg_valid        (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_HIST   yLOG_senter  (__FUNCTION__);
   /*---(check)--------------------------*/
   DEBUG_HIST   yLOG_snote   ("check");
   rc = strlchr (S_REG_LIST, a_abbr, S_REG_MAX);
   DEBUG_HIST   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_HIST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_HIST   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char 
ymap__mreg_by_abbr      (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_HIST   yLOG_senter  (__FUNCTION__);
   /*---(check)--------------------------*/
   DEBUG_HIST   yLOG_snote   ("check");
   n  = strlchr (S_REG_LIST, a_abbr, S_REG_MAX);
   DEBUG_HIST   yLOG_sint    (n);
   --rce;  if (n  < 0) {
      DEBUG_HIST   yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   /*---(complete)-----------------------*/
   DEBUG_HIST   yLOG_sexit   (__FUNCTION__);
   return n;
}

char
ymap__mreg_reset                (void)
{
   /*---(reset register)-----------------*/
   s_creg = '"';
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap__mreg_set                  (char a_abbr)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   int         x_reg       = 0;
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MREG)) {
      DEBUG_REGS   yLOG_note    ("can not execute until operational");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(reset)--------------------------*/
   ymap__mreg_reset ();
   /*---(get register number)------------*/
   x_reg  = ymap__mreg_by_abbr  (a_abbr);
   DEBUG_REGS   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_creg = a_abbr;
   /*---(complete)-----------------------*/
   return 0;
}

char ymap_mreg_curr     (void) { return s_creg; }

char         /*-> indicate whether cell is in a reg --[ leaf   [ge.430.419.80]*/ /*-[00.0000.209.#]-*/ /*-[--.---.---.--]-*/
yMAP_inside             (short u, short x, short y, short z)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_reg       = 0;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   /*---(get register number)------------*/
   x_reg  = ymap__mreg_by_abbr  (s_creg);
   DEBUG_REGS   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   --rce;  if (s_regs [x_reg].type != S_REG_ACTIVE) {
      DEBUG_REGS   yLOG_note    ("register inactive");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(misses)-------------------------*/
   if (u != s_regs [x_reg].u_all) {
      DEBUG_REGS   yLOG_note    ("u failed");
      DEBUG_REGS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (x <  s_regs [x_reg].x_beg || x >  s_regs [x_reg].x_end) {
      DEBUG_REGS   yLOG_note    ("x failed");
      DEBUG_REGS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (y <  s_regs [x_reg].y_beg || y >  s_regs [x_reg].y_end) {
      DEBUG_REGS   yLOG_note    ("y failed");
      DEBUG_REGS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (z != s_regs [x_reg].z_all) {
      DEBUG_REGS   yLOG_note    ("z failed");
      DEBUG_REGS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(complete------------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 1;
}


/*====================------------------------------------====================*/
/*===----                      memory allocation                       ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
ymap__mreg_new          (char a_abbr, void *a_item, char *a_label)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_reg       =    0;
   tITEM      *x_new       = NULL;
   char        x_tries     =    0;
   int         x_len       =    0;
   tITEM      *x_curr      = NULL;
   char        t           [LEN_LABEL]  = "";
   char        x_labels    [LEN_RECD]   = "";
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_REGS   yLOG_char    ("a_abbr"    , a_abbr);
   x_reg  = ymap__mreg_by_abbr  (a_abbr);
   DEBUG_REGS   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_CMDS   yLOG_point   ("a_item"    , a_item);
   --rce;  if (a_item == NULL) {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL && x_tries < 10)  {
      ++x_tries;
      x_new = (tITEM *) malloc (sizeof (tITEM));
   }
   DEBUG_CMDS   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_CMDS   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_CMDS   yLOG_note    ("FAILED");
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_CMDS   yLOG_note    ("populate");
   x_new->data     = a_item;
   x_new->b_next   = NULL;
   x_new->b_prev   = NULL;
   x_new->routes   = NULL;
   /*---(tie to master list)-------------*/
   if (s_regs [x_reg].hbuf == NULL) {
      DEBUG_CMDS   yLOG_note    ("nothing in master list, make first");
      s_regs [x_reg].hbuf = x_new;
   } else  {
      DEBUG_CMDS   yLOG_note    ("append to master list");
      s_regs [x_reg].tbuf->b_next = x_new;
      x_new->b_prev  = s_regs [x_reg].tbuf;
   }
   s_regs [x_reg].tbuf = x_new;
   /*---(labels)-------------------------*/
   if (s_regs [x_reg].labels != s_stubby)  {
      strlcpy (x_labels, s_regs [x_reg].labels, LEN_RECD);
      free (s_regs [x_reg].labels);
      if (a_label != NULL)  sprintf (t, "%s,", a_label);
      else                  sprintf (t, "%s,", "?");
   } else {
      if (a_label != NULL)  sprintf (t, ",%s,", a_label);
      else                  sprintf (t, ",%s,", "?");
   }
   strlcat (x_labels, t, LEN_RECD);
   s_regs [x_reg].labels = strdup (x_labels);
   /*---(list)---------------------------*/
   x_curr = s_regs [x_reg].hbuf;
   while  (x_curr != NULL) {
      DEBUG_CMDS   yLOG_complex ("item"      , "%-10p, %-10p, %-10p, %-10p", x_curr, x_curr->data, x_curr->b_prev, x_curr->b_next);
      x_curr = x_curr->b_next;
   }
   /*---(update counts)------------------*/
   ++s_regs [x_reg].nbuf;
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 0;
}


char         /*-> clear out a register ---------------[ ------ [ge.B63.253.32]*/ /*-[03.0000.043.3]-*/ /*-[--.---.---.--]-*/
ymap__mreg_wipe         (char a_abbr, char a_scope)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   int         x_reg       = 0;
   int         i           = 0;
   char        rc          = 0;
   tITEM      *x_curr      = NULL;
   tITEM      *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   DEBUG_REGS   yLOG_char    ("a_abbr"    , a_abbr);
   DEBUG_REGS   yLOG_char    ("a_scope"   , a_scope);
   /*---(get register number)------------*/
   x_reg  = ymap__mreg_by_abbr (a_abbr);
   DEBUG_REGS   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_REGS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(boundaries)---------------------*/
   DEBUG_REGS   yLOG_note    ("reset all values to zero");
   s_regs [x_reg].u_all  = 0;
   s_regs [x_reg].x_min  = s_regs [x_reg].y_min  = 0;
   s_regs [x_reg].x_beg  = s_regs [x_reg].y_beg  = 0;
   s_regs [x_reg].x_end  = s_regs [x_reg].y_end  = 0;
   s_regs [x_reg].x_max  = s_regs [x_reg].y_max  = 0;
   s_regs [x_reg].z_all  = 0;
   s_regs [x_reg].type   = S_REG_EMPTY;
   /*---(cells)--------------------------*/
   DEBUG_REGS   yLOG_note    ("clear all register positions");
   --rce;
   x_curr = s_regs [x_reg].tbuf;
   while (x_curr != NULL) {
      x_next = x_curr->b_prev;
      if (myMAP.e_regkill != NULL && a_scope != YSTR_INIT && x_curr->data != NULL) {
         rc = myMAP.e_regkill (x_curr->data);
         if (rc < 0) {
            DEBUG_REGS   yLOG_note    ("found a bad register position");
            DEBUG_REGS   yLOG_value   ("posid"     , i);
            DEBUG_REGS   yLOG_exit    (__FUNCTION__);
            return rce;
         }
      }
      x_curr->data   = NULL;
      x_curr->b_next = NULL;
      x_curr->b_prev = NULL;
      if (x_curr->routes != NULL)  free (x_curr->routes);
      free (x_curr);
      x_curr = x_next;
   }
   s_regs [x_reg].hbuf = NULL;
   s_regs [x_reg].tbuf = NULL;
   s_regs [x_reg].nbuf = 0;
   /*---(labels)-------------------------*/
   if (a_scope != YSTR_INIT && s_regs [x_reg].labels != s_stubby)
      free (s_regs [x_reg].labels);
   s_regs [x_reg].labels = s_stubby;
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char         /*-> clear out all buffers --------------[ ------ [gz.421.121.01]*/ /*-[01.0000.013.!]-*/ /*-[--.---.---.--]-*/
ymap_mreg_purge         (char a_scope)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        x_abbr      =  '-';
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_char    ("a_scope"   , a_scope);
   --rce;  switch (a_scope) {
   case YSTR_ILOWER  : case YSTR_IUPPER  : case YSTR_INUMBER :
   case YSTR_IGREEK  : case YSTR_IFULL   : case YSTR_INIT    :
      break;
   default :
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   s_creg = '"';
   DEBUG_SCRP   yLOG_value   ("s_nreg"    , s_nreg);
   for (i = 0; i < s_nreg; ++i) {
      x_abbr = S_REG_LIST [i];
      if (a_scope == YSTR_IUPPER  && strchr (YSTR_UPPER , x_abbr) == NULL)  continue;
      if (a_scope == YSTR_ILOWER  && strchr (YSTR_LOWER , x_abbr) == NULL)  continue;
      if (a_scope == YSTR_INUMBER && strchr (YSTR_NUMBER, x_abbr) == NULL)  continue;
      if (a_scope == YSTR_IGREEK  && strchr (YSTR_GREEK , x_abbr) == NULL)  continue;
      ymap__mreg_wipe (x_abbr, a_scope);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> clear all selections ---------------[ shoot  [gz.311.001.02]*/ /*-[00.0000.102.1]-*/ /*-[--.---.---.--]-*/
ymap_mreg_init                  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (SMOD_MREG)) {
      DEBUG_PROG   yLOG_note    ("status is not ready for init");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(macro abbrev list)--------------*/
   strlcpy (S_REG_LIST, "\""       , S_REG_MAX);
   strlcat (S_REG_LIST, YSTR_LOWER , S_REG_MAX);
   strlcat (S_REG_LIST, YSTR_UPPER , S_REG_MAX);
   strlcat (S_REG_LIST, YSTR_NUMBER, S_REG_MAX);
   strlcat (S_REG_LIST, YSTR_GREEK , S_REG_MAX);
   strlcat (S_REG_LIST, "-+"       , S_REG_MAX);
   s_nreg   = strlen (S_REG_LIST);
   /*---(registers)----------------------*/
   ymap_mreg_purge    (YSTR_INIT);
   myMAP.e_copier   = NULL;
   myMAP.e_clearer  = NULL;
   myMAP.e_router   = NULL;
   myMAP.e_paster   = NULL;
   myMAP.e_finisher = NULL;
   myMAP.e_regkill  = NULL;
   myMAP.e_exim     = NULL;
   /*---(update status)------------------*/
   yMODE_init_set   (SMOD_MREG, NULL, ymap_mreg_smode);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> clear all selections ---------------[ shoot  [gz.311.001.02]*/ /*-[00.0000.102.1]-*/ /*-[--.---.---.--]-*/
ymap_mreg_wrap          (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(registers)----------------------*/
   ymap_mreg_purge    (YSTR_INIT);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_mreg_config        (void *a_clearer, void *a_copier, void *a_router, void *a_paster, void *a_finisher, void *a_regkill, void *a_exim)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_REGS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (SMOD_MREG)) {
      DEBUG_REGS   yLOG_note    ("init must complete before config");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   DEBUG_REGS  yLOG_point   ("a_clearer" , a_clearer);
   myMAP.e_clearer    = a_clearer;
   DEBUG_REGS  yLOG_point   ("a_copier"  , a_copier);
   myMAP.e_copier     = a_copier;
   DEBUG_REGS  yLOG_point   ("a_router"  , a_router);
   myMAP.e_router     = a_router;
   DEBUG_REGS  yLOG_point   ("a_paster"  , a_paster);
   myMAP.e_paster     = a_paster;
   DEBUG_REGS  yLOG_point   ("a_finisher", a_finisher);
   myMAP.e_finisher   = a_finisher;
   DEBUG_REGS  yLOG_point   ("a_regkill" , a_regkill);
   myMAP.e_regkill    = a_regkill;
   DEBUG_REGS  yLOG_point   ("a_exim"    , a_exim);
   myMAP.e_exim       = a_exim;
   /*---(update status)------------------*/
   yMODE_conf_set   (SMOD_MREG, '1');
   /*---(complete)-----------------------*/
   DEBUG_REGS  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           attaching                          ----===*/
/*====================------------------------------------====================*/
static void  o___ATTACH__________o () { return; }

static char    s_saving   = '-';

char         /*-> attach a cell to a buffer ----------[ ------ [fe.870.378.72]*/ /*-[00.0000.025.7]-*/ /*-[--.---.---.--]-*/
yMAP_mreg_add           (void *a_thing, char *a_label)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          =   0;
   int         x_reg       =   0;
   char        t           [LEN_LABEL]  = "";
   char        x_labels    [LEN_RECD]   = "";
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_REGS   yLOG_char    ("s_saving"  , s_saving);
   --rce;  if (s_saving != 'y') {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_REGS   yLOG_char    ("s_creg"    , s_creg);
   /*---(attach)-------------------------*/
   rc = ymap__mreg_new (s_creg, a_thing, a_label);
   --rce;  if (rc < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(counters)-----------------------*/
   DEBUG_REGS   yLOG_value   ("nbuf"      , s_regs [x_reg].nbuf);
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_mreg_save          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_reg       =    0;
   int         x_nbuf      =    0;
   long        x_stamp     =    0;
   ushort      u, xb, xe, yb, ye, z;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MREG)) {
      DEBUG_REGS   yLOG_note    ("can not execute until operational");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check copier)-------------------*/
   DEBUG_REGS   yLOG_point   ("e_copier"  , myMAP.e_copier);
   --rce;  if (myMAP.e_copier == NULL) {
      DEBUG_REGS   yLOG_note    ("copier must be set to operate");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(identify register)--------------*/
   DEBUG_REGS   yLOG_char    ("s_creg"    , s_creg);
   x_reg  = ymap__mreg_by_abbr  (s_creg);
   DEBUG_REGS   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(wipe register)------------------*/
   rc = ymap__mreg_wipe  (s_creg, '-');
   DEBUG_REGS   yLOG_value   ("wipe rc"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(save selection)-----------------*/
   rc = yMAP_visu_range (&u, &xb, &xe, &yb, &ye, &z, NULL);
   DEBUG_REGS   yLOG_value   ("visu rc"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   s_regs [x_reg].u_all   = u;
   s_regs [x_reg].x_beg   = s_regs [x_reg].x_min   = xb;
   s_regs [x_reg].x_end   = s_regs [x_reg].x_max   = xe;
   s_regs [x_reg].y_beg   = s_regs [x_reg].y_min   = yb;
   s_regs [x_reg].y_end   = s_regs [x_reg].y_max   = ye;
   s_regs [x_reg].z_all   = z;
   /*---(call save)----------------------*/
   x_stamp  = rand ();
   s_saving = 'y';
   s_regs [x_reg].type = S_REG_ACTIVE;
   rc = myMAP.e_copier ('c', x_stamp);
   s_saving = '-';
   DEBUG_REGS   yLOG_value   ("copy rc"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(check counts)-------------------*/
   DEBUG_REGS   yLOG_value   ("nbuf"      , s_regs [x_reg].nbuf);
   /*> if (s_regs [x_reg].nbuf <= 0)  yvikeys_mreg__wipe (s_creg, '-');               <*/
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char*
ymap_mreg_list          (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_reg       =    0;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   /*---(identify register)--------------*/
   DEBUG_REGS   yLOG_char    ("a_abbr"    , a_abbr);
   x_reg  = ymap__mreg_by_abbr  (a_abbr);
   DEBUG_REGS   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  "n/a";
   }
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return s_regs [x_reg].labels;
}



/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char
ymap__mreg_clear             (char a_1st)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x, y;
   ushort      u;
   ushort      x_beg, x_end;
   ushort      y_beg, y_end;
   ushort      z;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   DEBUG_REGS   yLOG_char    ("a_1st"     , a_1st);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MREG)) {
      DEBUG_REGS   yLOG_note    ("can not execute until operational");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save selection)-----------------*/
   rc = yMAP_visu_range (&u, &x_beg, &x_end, &y_beg, &y_end, &z, NULL);
   DEBUG_REGS   yLOG_value   ("visu rc"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(check clearer)------------------*/
   DEBUG_REGS   yLOG_point   ("e_clearer" , myMAP.e_clearer);
   --rce;  if (myMAP.e_clearer == NULL) {
      DEBUG_REGS   yLOG_note    ("clearer must be set to operate");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   for (x = x_beg; x <= x_end; ++x) {
      for (y = y_beg; y <= y_end; ++y) {
         rc = myMAP.e_clearer (a_1st, u, x, y, z);
         if (rc == 0)  a_1st = '-';
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char ymap_mreg_clear        (void) { ymap__mreg_clear ('y'); }
char ymap_mreg_clear_combo  (void) { ymap__mreg_clear ('-'); }

static ushort  s_boff  = 0;
static ushort  s_xoff  = 0;
static ushort  s_yoff  = 0;
static ushort  s_zoff  = 0;

static char    s_reg   = 0;
static char    s_clear = 0;
static char    s_reqs  = 0;
static char    s_pros  = 0;
static char    s_intg  = 0;

char         /*-> prepare for a paste ----------------[ ------ [fe.842.023.21]*/ /*-[01.0000.015.!]-*/ /*-[--.---.---.--]-*/
ymap__mreg_paste_check  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_nbuf      =    0;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MREG)) {
      DEBUG_REGS   yLOG_note    ("can not execute until operational");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check paster)-------------------*/
   DEBUG_REGS   yLOG_point   ("e_paster"  , myMAP.e_paster);
   --rce;  if (myMAP.e_paster == NULL) {
      DEBUG_REGS   yLOG_note    ("paster must be set to operate");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(identify register)--------------*/
   DEBUG_REGS   yLOG_char    ("s_creg"    , s_creg);
   s_reg  = ymap__mreg_by_abbr  (s_creg);
   DEBUG_REGS   yLOG_value   ("s_reg"     , s_reg);
   --rce;  if (s_reg < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(check for empty)----------------*/
   x_nbuf = s_regs [s_reg].nbuf;
   DEBUG_REGS   yLOG_value   ("x_nbuf"    , x_nbuf);
   /*> --rce;  if (x_nbuf <= 0) {                                                     <* 
    *>    DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return  rce;                                                                <* 
    *> }                                                                              <*/
   /*---(get current position)-----------*/
   yMAP_current (NULL, &s_boff, &s_xoff, &s_yoff, &s_zoff);
   DEBUG_REGS   yLOG_value   ("s_boff"    , s_boff);
   DEBUG_REGS   yLOG_value   ("s_xoff"    , s_xoff);
   DEBUG_REGS   yLOG_value   ("s_yoff"    , s_yoff);
   DEBUG_REGS   yLOG_value   ("s_zoff"    , s_zoff);
   /*---(make into offsets)--------------*/
   s_boff -=  s_regs [s_reg].u_all;
   s_xoff -=  s_regs [s_reg].x_beg;
   s_yoff -=  s_regs [s_reg].y_beg;
   s_zoff -=  s_regs [s_reg].z_all;
   DEBUG_REGS   yLOG_value   ("s_boff (*)", s_boff);
   DEBUG_REGS   yLOG_value   ("s_xoff (*)", s_xoff);
   DEBUG_REGS   yLOG_value   ("s_yoff (*)", s_yoff);
   DEBUG_REGS   yLOG_value   ("s_zoff (*)", s_zoff);
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> prepare for a paste ----------------[ ------ [fe.842.023.21]*/ /*-[01.0000.015.!]-*/ /*-[--.---.---.--]-*/
ymap__mreg_paste_set    (char *a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   int         i           =    0;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_clear   = '-';
   s_reqs    = '-';
   s_pros    = '-';
   s_intg    = '-';
   /*---(defense)------------------------*/
   DEBUG_REGS   yLOG_point   ("a_type"    , a_type);
   --rce;  if (a_type == NULL) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_REGS   yLOG_info    ("a_type"    , a_type);
   x_len = strllen (a_type, LEN_LABEL);
   DEBUG_REGS   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <  4) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(lookup on ref)------------------*/
   if (x_len == 4) {
      for (i = 0; i < MAX_PASTING; ++i) {
         if (a_type [0] != s_pasting [i].ref [0])   continue;
         if (a_type [1] != s_pasting [i].ref [1])   continue;
         if (a_type [2] != s_pasting [i].ref [2])   continue;
         if (a_type [3] != s_pasting [i].ref [3])   continue;
         n = i;
         break;
      }
   }
   DEBUG_REGS   yLOG_value   ("ref n"     , n);
   /*---(lookup on name)-----------------*/
   if (n < 0) {
      for (i = 0; i < MAX_PASTING; ++i) {
         if (a_type [0] != s_pasting [i].name [0])     continue;
         if (strcmp (a_type, s_pasting [i].name) != 0) continue;
         n = i;
         break;
      }
      DEBUG_REGS   yLOG_value   ("name n"    , n);
   }
   /*---(check for failures)-------------*/
   --rce;  if (n < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(mark settings)------------------*/
   s_clear = s_pasting [n].clear;
   s_reqs  = s_pasting [n].reqs;
   s_pros  = s_pasting [n].pros;
   s_intg  = s_pasting [n].intg;
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> prepare for a paste ----------------[ ------ [fe.842.023.21]*/ /*-[01.0000.015.!]-*/ /*-[--.---.---.--]-*/
ymap__mreg_paste_clear  (char a_1st)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x, y;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   DEBUG_REGS   yLOG_char    ("a_1st"     , a_1st);
   /*---(check clearer)------------------*/
   DEBUG_REGS   yLOG_point   ("e_clearer" , myMAP.e_clearer);
   --rce;  if (myMAP.e_clearer == NULL) {
      DEBUG_REGS   yLOG_note    ("clearer must be set to operate");
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   DEBUG_REGS   yLOG_complex ("range"     , "%3dx to %3dx, %3dy to %3dy", s_regs [s_reg].x_beg + s_xoff, s_regs [s_reg].x_end + s_xoff, s_regs [s_reg].y_beg + s_yoff, s_regs [s_reg].y_end + s_yoff);
   for (x = s_regs [s_reg].x_beg; x <= s_regs [s_reg].x_end; ++x) {
      for (y = s_regs [s_reg].y_beg; y <= s_regs [s_reg].y_end; ++y) {
         DEBUG_REGS   yLOG_complex ("target"    , "%c, %3dx, %3dy, %3dz", a_1st, x + s_xoff, y + s_yoff, s_regs [s_reg].z_all + s_zoff);
         rc = myMAP.e_clearer (a_1st, s_regs [s_reg].u_all + s_boff, x + s_xoff, y + s_yoff, s_regs [s_reg].z_all + s_zoff);
         if (rc == 0)  a_1st = '-';
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__mreg_paste        (char a_1st, char *a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x, y, z;
   int         c           =    0;
   tITEM      *x_curr      = NULL;
   char        x_list      [LEN_RECD] = "";
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   DEBUG_REGS   yLOG_char    ("a_1st"     , a_1st);
   /*---(prepare)------------------------*/
   rc = ymap__mreg_paste_check    ();
   DEBUG_REGS   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(settings)-----------------------*/
   rc = ymap__mreg_paste_set (a_type);
   DEBUG_REGS   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clearing)-----------------------*/
   DEBUG_REGS   yLOG_char    ("s_clear"   , s_clear);
   if (s_clear == 'y') {
      ymap__mreg_paste_clear (a_1st);
      a_1st = '-';  /* link pasting to clearing */
   }
   if (s_reqs == '-') {
      DEBUG_REGS   yLOG_note    ("requested clear only");
      DEBUG_REGS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(collect routes)-----------------*/
   DEBUG_REGS   yLOG_value   ("nbuf"      , s_regs [s_reg].nbuf);
   DEBUG_REGS   yLOG_point   ("e_router"  , myMAP.e_router);
   if (myMAP.e_router != NULL) {
      x_curr = s_regs [s_reg].hbuf;
      --rce;  while (x_curr != NULL) {
         DEBUG_CMDS   yLOG_complex ("item"      , "%-10p, %-10p, %-10p, %-10p", x_curr, x_curr->data, x_curr->b_prev, x_curr->b_next);
         rc = myMAP.e_router (x_curr->data, x_list);
         if (rc < 0) {
            DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         if (x_list != NULL && strlen (x_list) > 1)  x_curr->routes = strdup (x_list);
         x_curr = x_curr->b_next;
      }
   }
   /*---(paste in order)-----------------*/
   DEBUG_REGS   yLOG_value   ("nbuf"      , s_regs [s_reg].nbuf);
   x_curr = s_regs [s_reg].hbuf;
   --rce;  while (x_curr != NULL) {
      DEBUG_CMDS   yLOG_complex ("item"      , "%-10p, %-10p, %-10p, %-10p", x_curr, x_curr->data, x_curr->b_prev, x_curr->b_next);
      rc = myMAP.e_paster (s_reqs, s_pros, s_intg, a_1st, s_boff, s_xoff, s_yoff, s_zoff, x_curr->data, x_curr->routes);
      if (rc < 0) {
         DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++c;
      a_1st = '-';
      x_curr = x_curr->b_next;
   }
   /*---(finish)-------------------------*/
   DEBUG_REGS   yLOG_value   ("nbuf"      , s_regs [s_reg].nbuf);
   DEBUG_REGS   yLOG_point   ("e_finisher", myMAP.e_finisher);
   if (myMAP.e_finisher != NULL) {
      x_curr = s_regs [s_reg].hbuf;
      --rce;  while (x_curr != NULL) {
         DEBUG_CMDS   yLOG_complex ("item"      , "%-10p, %-10p, %-10p, %-10p", x_curr, x_curr->data, x_curr->b_prev, x_curr->b_next);
         rc = myMAP.e_finisher (s_boff, s_xoff, s_yoff, s_zoff, x_curr->data);
         x_curr = x_curr->b_next;
      }
   }
   /*---(update)-------------------------*/
   /*> yCALC_garbage_collect ();                                                      <*/
   /*> yCALC_calculate ();                                                            <*/
   /*> yvikeys_map_reposition  ();                                                    <*/
   yMAP_refresh ();
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char  ymap_mreg_paste       (char *a_type) { ymap__mreg_paste ('y', a_type); }
char  ymap_mreg_paste_combo (char *a_type) { ymap__mreg_paste ('-', a_type); }

char
ymap_mreg_visual        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_reg       =    0;
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ymap__mreg_paste_check    ();
   DEBUG_REGS   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(select)-------------------------*/
   ymap_visu_exact (
         s_regs [x_reg].u_all + s_boff,
         s_regs [x_reg].x_beg + s_xoff, s_regs [x_reg].x_end + s_xoff,
         s_regs [x_reg].y_beg + s_yoff, s_regs [x_reg].y_end + s_yoff,
         s_regs [x_reg].z_all + s_zoff, s_regs [x_reg].z_all + s_zoff);
   yMAP_jump (
         s_regs [x_reg].u_all + s_boff,
         s_regs [x_reg].x_end + s_xoff,
         s_regs [x_reg].y_end + s_yoff,
         s_regs [x_reg].z_all + s_zoff);
   /*---(complete)-----------------------*/
   DEBUG_REGS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       mode handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___MODE____________o () { return; }

char
ymap_mreg_smode         (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *x_majors    = "m'";
   static char x_prev      =  '-';
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_char    ("a_major"   , a_major);
   DEBUG_USER   yLOG_char    ("a_minor"   , chrvisible (a_minor));
   DEBUG_USER   yLOG_char    ("x_prev"    , x_prev);
   /*> myVIKEYS.info_win = '-';                                                       <*/
   /*---(defenses)-----------------------*/
   DEBUG_USER   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (SMOD_MREG)) {
      DEBUG_USER   yLOG_note    ("not the correct mode");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(exit mode)----------------------*/
   if (a_minor == G_KEY_ESCAPE || a_minor == G_KEY_RETURN) {
      DEBUG_USER   yLOG_note    ("escape/return means leave");
      yMODE_exit ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return  0;
   }
   /*---(register selection)-------------*/
   --rce;  if (a_major == '"') {
      if (strchr ("+-", a_minor) != NULL) {
         DEBUG_USER   yLOG_note    ("enter export-import");
         ymap__mreg_set    (a_minor);
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return a_minor;
      } else if (strchr (S_REG_LIST, a_minor) != 0) {
         ymap__mreg_set    (a_minor);
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return 0;
      } else if (a_minor == '?') {
         /*> my.info_win = G_INFO_REGS;                                               <*/
         /*> REG_set ('"');                                                           <*/
         /*> yVIKEYS_mode_exit ();                                                          <*/
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return  0;
      } else if (a_minor == '!') {
         /*> my.layout_status = G_STATUS_REGS;                                        <*/
         /*> REG_set ('"');                                                           <*/
         /*> yVIKEYS_mode_exit ();                                                    <*/
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return  0;
      }
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(register actions)---------------*/
   --rce;  if (a_major == ' ') {
      /*---(multikey prefixes)-----------*/
      switch (a_minor) {
         /*---(multikey prefixes)-----------*/
      case 'p'  :
         DEBUG_USER   yLOG_note    ("p for paste normal");
         ymap_mreg_paste ("normal");
         yMODE_exit ();
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      case 'P'  :
         DEBUG_USER   yLOG_note    ("P is a multi-key");
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return a_minor;
      case 'y'  :
         DEBUG_USER   yLOG_note    ("y for yank/copy");
         ymap_mreg_save  ();
         ymap_visu_clear ();
         yMODE_exit ();
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      case 'Y'  :
         DEBUG_USER   yLOG_note    ("y for yank/clear");
         ymap_mreg_save  ();
         ymap_mreg_clear ();
         ymap_visu_clear ();
         yMODE_exit ();
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      case 'x'  :
         DEBUG_USER   yLOG_note    ("x for clear");
         ymap_mreg_clear ();
         ymap_visu_clear ();
         yMODE_exit ();
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      }
   }
   /*---(export-import)------------------*/
   --rce;  if (strchr ("+-", a_major) != NULL) {
      DEBUG_USER   yLOG_note    ("calling external export-import function");
      DEBUG_USER   yLOG_point   ("e_exim"    , myMAP.e_exim);
      if (myMAP.e_exim != NULL)  rc = myMAP.e_exim (a_major, a_minor);
      DEBUG_USER   yLOG_value   ("rc"        , rc);
      ymap_visu_clear ();
      yMODE_exit ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(pasting actions)----------------*/
   --rce;  if (a_major == 'P') {
      switch (a_minor) {
      case '_' :  rc = ymap_mreg_visual ();            break;
      case '#' :  rc = ymap_mreg_paste  ("clear");     break;
      case 'n' :  rc = ymap_mreg_paste  ("normal");    break;
      case 'r' :  rc = ymap_mreg_paste  ("replace");   break;
      case 'd' :  rc = ymap_mreg_paste  ("duplicate"); break;
      case 'c' :  rc = ymap_mreg_paste  ("combo");     break;
      case 'm' :  rc = ymap_mreg_paste  ("move");      break;
      case 'f' :  rc = ymap_mreg_paste  ("force");     break;
      default  :  rc = rce;                               break;
      }
      yMODE_exit ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(failure)------------------------*/
   --rce;
   yMODE_exit ();
   DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char*
ymap_mreg_detail        (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =    0;
   char        t           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_REGS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   sprintf (myMAP.g_print, "n/a");
   n = ymap__mreg_by_abbr (a_abbr);
   DEBUG_REGS   yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_REGS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create line)--------------------*/
   sprintf (t, "%dx%d", s_regs [n].x_end -  s_regs [n].x_beg + 1, s_regs [n].y_end -  s_regs [n].y_beg + 1);
   sprintf (myMAP.g_print, "%c � %2du � %4dn %4db %4de %4dx � %4dn %4db %4de %4dx � %4dc %s",
         a_abbr, s_regs [n].u_all,
         s_regs [n].x_min, s_regs [n].x_beg, s_regs [n].x_end, s_regs [n].x_max,
         s_regs [n].y_min, s_regs [n].y_beg, s_regs [n].y_end, s_regs [n].y_max,
         s_regs [n].nbuf , t);
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return myMAP.g_print;
}

