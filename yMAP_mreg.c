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




char        s_print     [LEN_RECD]  = "";


#define     S_REG_MAX   100
#define     LEN_BUF    1000


typedef  struct  cITEM  tITEM;
struct cITEM {
   void       *data;
   char       *reqs;
   char       *pros;
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
   char       *reqs;
   char       *pros;
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

/*
 * pasting elements
 * 
 *    clear -- is the destination area fully cleared before pasting
 *       -  no, merge by only writing over necessary cells
 *       y  yes, clear all cells in destination area
 *
 *    reqs  -- how are the copied cell's formulas adjusted
 *       n  no, all formulas are used exactly as originally copied
 *       r  default, relative addresses are adjusted, absolute kept original
 *       i  same as 'r', but inner address absolutes are treated as relative
 *       b  all, all addresses are adjusted, inner or outer
 *
 *    pros  -- how are provider's formulas adjusted
 *       N  default, provider formulas are not updated at all
 *       R  relative references to copied cells are adjusted to new location
 *       A  both, relative and absolute references are adjusted to new location
 *       S  split, formulas are remade to reflect both original and new location
 *
 *    integration -- not defined yes
 *       -  default
 *
 *
 */


#define   MAX_PASTING           500
typedef  struct cPASTING tPASTING;
struct cPASTING {
   char        abbr;
   char        ref         [LEN_LABEL];
   char        name        [LEN_LABEL];
   char        primary;
   char        clear;
   char        reqs;
   char        pros;
   char        intg;
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
   { 'd', "-iN-", "duplicate"   , '-',    '-', 'i', 'N', '-',    "tbd" },
   { '-', "-iR-", ""            , '-',    '-', 'i', 'R', '-',    "tbd" },
   { 'a', "-iA-", "append"      , '-',    '-', 'i', 'A', '-',    "tbd" },
   { '-', "-iS-", ""            , '-',    '-', 'i', 'S', '-',    "tbd" },
   /*-13/16--*/
   { 'c', "-bN-", "combo"       , '-',    '-', 'b', 'N', '-',    "tbd" },
   { 'm', "-bR-", "move"        , '-',    '-', 'b', 'R', '-',    "tbd" },
   { 'f', "-bA-", "force"       , '-',    '-', 'b', 'A', '-',    "tbd" },
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
   { 'N', "yrN-", "NORMAL"      , 'y',    'y', 'r', 'N', '-',    "tbd" },
   { '-', "yrR-", ""            , '-',    'y', 'r', 'R', '-',    "tbd" },
   { '-', "yrA-", ""            , '-',    'y', 'r', 'A', '-',    "tbd" },
   { '-', "yrS-", ""            , '-',    'y', 'r', 'S', '-',    "tbd" },
   /*-29/32--*/
   { 'D', "yiN-", "DUPLICATE"   , 'y',    'y', 'i', 'N', '-',    "tbd" },
   { '-', "yiR-", ""            , '-',    'y', 'i', 'R', '-',    "tbd" },
   { 'A', "yiA-", "APPEND"      , '-',    'y', 'i', 'A', '-',    "tbd" },
   { '-', "yiS-", ""            , '-',    'y', 'i', 'S', '-',    "tbd" },
   /*-33/36--*/
   { 'C', "ybN-", "COMBO"       , 'y',    'y', 'b', 'N', '-',    "tbd" },
   { 'M', "ybR-", "MOVE"        , 'y',    'y', 'b', 'R', '-',    "tbd" },
   { 'F', "ybA-", "FORCE"       , 'y',    'y', 'b', 'A', '-',    "tbd" },
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
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(check)--------------------------*/
   DEBUG_YMAP   yLOG_snote   ("check");
   rc = ystrlchr (S_REG_LIST, a_abbr, S_REG_MAX);
   DEBUG_YMAP   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char 
ymap__mreg_by_abbr      (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_senter  (__FUNCTION__);
   /*---(check)--------------------------*/
   DEBUG_YMAP   yLOG_snote   ("check");
   DEBUG_YMAP   yLOG_snote   (S_REG_LIST);
   n  = ystrlchr (S_REG_LIST, a_abbr, S_REG_MAX);
   DEBUG_YMAP   yLOG_sint    (n);
   --rce;  if (n  < 0) {
      DEBUG_YMAP   yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_sexit   (__FUNCTION__);
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
      DEBUG_YMAP   yLOG_note    ("can not execute until operational");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(reset)--------------------------*/
   ymap__mreg_reset ();
   /*---(get register number)------------*/
   x_reg  = ymap__mreg_by_abbr  (a_abbr);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_creg = a_abbr;
   /*---(complete)-----------------------*/
   return 0;
}

char ymap_mreg_curr     (void) { return s_creg; }

char         /*-> indicate whether cell is in a reg --[ leaf   [ge.430.419.80]*/ /*-[00.0000.209.#]-*/ /*-[--.---.---.--]-*/
yMAP_inside             (ushort u, ushort x, ushort y, ushort z)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_reg       = 0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(get register number)------------*/
   DEBUG_YMAP   yLOG_char    ("s_creg"    , s_creg);
   x_reg  = ymap__mreg_by_abbr  (s_creg);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_complex ("register"  , "%c, %2d, %c, %2du, %3dx to %3dx, %3dy to %3dy", s_creg, x_reg, s_regs [x_reg].type, s_regs [x_reg].u_all, s_regs [x_reg].x_beg, s_regs [x_reg].x_end, s_regs [x_reg].y_beg, s_regs [x_reg].y_end);
   /*---(defense)------------------------*/
   --rce;  if (s_regs [x_reg].type != S_REG_ACTIVE) {
      DEBUG_YMAP   yLOG_note    ("register inactive");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(misses)-------------------------*/
   if (u != s_regs [x_reg].u_all) {
      DEBUG_YMAP   yLOG_note    ("u failed");
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (x <  s_regs [x_reg].x_beg || x >  s_regs [x_reg].x_end) {
      DEBUG_YMAP   yLOG_note    ("x failed");
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (y <  s_regs [x_reg].y_beg || y >  s_regs [x_reg].y_end) {
      DEBUG_YMAP   yLOG_note    ("y failed");
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (z != s_regs [x_reg].z_all) {
      DEBUG_YMAP   yLOG_note    ("z failed");
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(complete------------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 1;
}


/*====================------------------------------------====================*/
/*===----                      memory allocation                       ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
ymap__mreg_new          (char a_abbr, void *a_item, char *a_label, char *a_reqs, char *a_pros)
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
   char       *p           = NULL;
   char       *r           = NULL;
   ushort      x, y;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_abbr"    , a_abbr);
   x_reg  = ymap__mreg_by_abbr  (a_abbr);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YMAP   yLOG_point   ("a_item"    , a_item);
   --rce;  if (a_item == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_point   ("a_label"   , a_label);
   --rce;  if (a_item == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_info    ("a_label"   , a_label);
   /*---(check label)--------------------*/
   rc = ymap_locator (a_label, NULL, NULL, NULL, NULL);
   DEBUG_YMAP   yLOG_value   ("locator"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL && x_tries < 10)  {
      ++x_tries;
      x_new = (tITEM *) malloc (sizeof (tITEM));
   }
   DEBUG_YMAP   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_YMAP   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YMAP   yLOG_note    ("FAILED");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_YMAP   yLOG_note    ("populate");
   x_new->data     = a_item;
   x_new->b_next   = NULL;
   x_new->b_prev   = NULL;
   /*---(requirements)-------------------*/
   x_new->reqs     = s_stubby;
   DEBUG_YMAP   yLOG_point   ("a_reqs"    , a_reqs);
   if (a_reqs != NULL && a_reqs [0] == ',') {
      DEBUG_YMAP   yLOG_info    ("a_reqs"    , a_reqs);
      DEBUG_YMAP   yLOG_note    ("load requirements");
      x_new->reqs     = strdup (a_reqs);
      DEBUG_YMAP   yLOG_info    ("->reqs"    , x_new->reqs);
      ystrlcpy (x_labels, "", LEN_RECD);
      if (s_regs [x_reg].reqs != s_stubby) {
         ystrlcat (x_labels, s_regs [x_reg].reqs, LEN_RECD);
         free (s_regs [x_reg].reqs);
      }
      ystrlcat (x_labels, a_reqs, LEN_RECD);
      ySORT_labels (x_labels);
      s_regs [x_reg].reqs = strdup (x_labels);
      DEBUG_YMAP   yLOG_info    (".reqs"     , s_regs [x_reg].reqs);
   } else {
      DEBUG_YMAP   yLOG_note    ("NO new requirements");
   }
   /*---(providers)----------------------*/
   x_new->pros     = s_stubby;
   DEBUG_YMAP   yLOG_point   ("a_pros"    , a_pros);
   if (a_pros != NULL && a_pros [0] == ',' && strcmp (a_pros, ",ROOT,") != 0) {
      DEBUG_YMAP   yLOG_info    ("a_pros"    , a_pros);
      DEBUG_YMAP   yLOG_note    ("load providers");
      x_new->pros     = strdup (a_pros);
      DEBUG_YMAP   yLOG_info    ("->pros"    , x_new->pros);
      ystrlcpy (x_labels, "", LEN_RECD);
      if (s_regs [x_reg].pros != s_stubby) {
         ystrlcat (x_labels, s_regs [x_reg].pros, LEN_RECD);
         free (s_regs [x_reg].pros);
      }
      ystrlcat (x_labels, a_pros, LEN_RECD);
      ySORT_labels (x_labels);
      s_regs [x_reg].pros = strdup (x_labels);
      DEBUG_YMAP   yLOG_info    (".pros"     , s_regs [x_reg].pros);
   } else {
      DEBUG_YMAP   yLOG_note    ("NO new providers");
   }
   /*---(tie to master list)-------------*/
   if (s_regs [x_reg].hbuf == NULL) {
      DEBUG_YMAP   yLOG_note    ("nothing in master list, make first");
      s_regs [x_reg].hbuf = x_new;
   } else  {
      DEBUG_YMAP   yLOG_note    ("append to master list");
      s_regs [x_reg].tbuf->b_next = x_new;
      x_new->b_prev  = s_regs [x_reg].tbuf;
   }
   s_regs [x_reg].tbuf = x_new;
   /*---(labels)-------------------------*/
   if (s_regs [x_reg].labels != s_stubby)  {
      DEBUG_YMAP   yLOG_note    ("append to labels");
      DEBUG_YMAP   yLOG_info    ("labels"    , s_regs [x_reg].labels);
      ystrlcpy (x_labels, s_regs [x_reg].labels, LEN_RECD);
      free (s_regs [x_reg].labels);
      sprintf (t, "%s,", a_label);
   } else {
      DEBUG_YMAP   yLOG_note    ("first label");
      ystrlcpy (x_labels, "", LEN_RECD);
      sprintf (t, ",%s,", a_label);
   }
   DEBUG_YMAP   yLOG_info    ("x_labels"  , x_labels);
   DEBUG_YMAP   yLOG_info    ("label"     , t);
   ystrlcat (x_labels, t, LEN_RECD);
   /*> ySORT_labels (x_labels);                                                       <*/
   s_regs [x_reg].labels = strdup (x_labels);
   DEBUG_YMAP   yLOG_info    ("labels"    , s_regs [x_reg].labels);
   /*---(list)---------------------------*/
   /*> x_curr = s_regs [x_reg].hbuf;                                                                                                                <* 
    *> while  (x_curr != NULL) {                                                                                                                    <* 
    *>    /+> DEBUG_YMAP   yLOG_complex ("item"      , "%-10p, %-10p, %-10p, %-10p", x_curr, x_curr->data, x_curr->b_prev, x_curr->b_next);   <+/   <* 
    *>    x_curr = x_curr->b_next;                                                                                                                  <* 
    *> }                                                                                                                                            <*/
   /*---(update counts)------------------*/
   ++s_regs [x_reg].nbuf;
   DEBUG_YMAP   yLOG_value   ("nbuf"      , s_regs [x_reg].nbuf);
   /*---(update bounds)------------------*/
   if (a_reqs != NULL && a_reqs [0] == ',') {
      ystrlcpy (x_labels, a_reqs, LEN_RECD);
      p = strtok_r (x_labels, ",", &r);
      while (p != NULL) {
         /*---(get coords)---------------*/
         rc = ymap_locator (p, NULL, &x, &y, NULL);
         if (rc >= 0) {
            /*---(update mins)-----------*/
            if (x < s_regs [x_reg].x_min)  s_regs [x_reg].x_min = x;
            if (y < s_regs [x_reg].y_min)  s_regs [x_reg].y_min = y;
            /*---(update maxs)-----------*/
            if (x > s_regs [x_reg].x_max)  s_regs [x_reg].x_max = x;
            if (y > s_regs [x_reg].y_max)  s_regs [x_reg].y_max = y;
         }
         /*---(next)---------------------*/
         p = strtok_r (NULL    , ",", &r);
         /*---(done)---------------------*/
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_mreg_list          (char *r_abbr, int *r_count, char r_list [LEN_HUGE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   int         x_reg       = 0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_abbr  != NULL)   *r_abbr  = s_creg;
   if (r_count != NULL)   *r_count = 0;
   if (r_list  != NULL)   strcpy (r_list, "");
   /*---(get register number)------------*/
   DEBUG_YMAP   yLOG_char    ("s_creg"    , s_creg);
   x_reg  = ymap__mreg_by_abbr (s_creg);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(copy)---------------------------*/
   if (s_regs [x_reg].nbuf > 0) {
      if (r_count != NULL)   *r_count = s_regs [x_reg].nbuf;
      if (r_list  != NULL)   ystrlcpy (r_list, s_regs [x_reg].labels, LEN_HUGE);
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("a_abbr"    , a_abbr);
   DEBUG_YMAP   yLOG_char    ("a_scope"   , a_scope);
   /*---(get register number)------------*/
   x_reg  = ymap__mreg_by_abbr (a_abbr);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(boundaries)---------------------*/
   DEBUG_YMAP   yLOG_note    ("reset all values to zero");
   s_regs [x_reg].u_all  = 0;
   s_regs [x_reg].x_min  = s_regs [x_reg].y_min  = 0;
   s_regs [x_reg].x_beg  = s_regs [x_reg].y_beg  = 0;
   s_regs [x_reg].x_end  = s_regs [x_reg].y_end  = 0;
   s_regs [x_reg].x_max  = s_regs [x_reg].y_max  = 0;
   s_regs [x_reg].z_all  = 0;
   s_regs [x_reg].type   = S_REG_EMPTY;
   /*---(cells)--------------------------*/
   DEBUG_YMAP   yLOG_note    ("clear all register positions");
   --rce;
   x_curr = s_regs [x_reg].tbuf;
   while (x_curr != NULL) {
      x_next = x_curr->b_prev;
      if (myMAP.e_regkill != NULL && a_scope != YSTR_INIT && x_curr->data != NULL) {
         rc = myMAP.e_regkill (x_curr->data);
         if (rc < 0) {
            DEBUG_YMAP   yLOG_note    ("found a bad register position");
            DEBUG_YMAP   yLOG_value   ("posid"     , i);
            DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
            return rce;
         }
      }
      x_curr->data   = NULL;
      x_curr->b_next = NULL;
      x_curr->b_prev = NULL;
      if (x_curr->reqs != s_stubby)  { free (x_curr->reqs); x_curr->reqs = s_stubby; }
      if (x_curr->pros != s_stubby)  { free (x_curr->pros); x_curr->pros = s_stubby; }
      free (x_curr);
      x_curr = x_next;
   }
   s_regs [x_reg].hbuf = NULL;
   s_regs [x_reg].tbuf = NULL;
   s_regs [x_reg].nbuf = 0;
   /*---(labels)-------------------------*/
   if (a_scope != YSTR_INIT) {
      if (s_regs [x_reg].labels != s_stubby)  free (s_regs [x_reg].labels);
      if (s_regs [x_reg].reqs   != s_stubby)  free (s_regs [x_reg].reqs);
      if (s_regs [x_reg].pros   != s_stubby)  free (s_regs [x_reg].pros);
   }
   s_regs [x_reg].labels = s_stubby;
   DEBUG_YMAP   yLOG_info    ("labels"    , s_regs [x_reg].labels);
   s_regs [x_reg].reqs   = s_stubby;
   DEBUG_YMAP   yLOG_info    ("reqs"      , s_regs [x_reg].reqs);
   s_regs [x_reg].pros   = s_stubby;
   DEBUG_YMAP   yLOG_info    ("pros"      , s_regs [x_reg].pros);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char ymap_mreg_wipe_curr     (void) { return ymap__mreg_wipe  (s_creg, '-'); }


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
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("a_scope"   , a_scope);
   --rce;  switch (a_scope) {
   case YSTR_ILOWER  : case YSTR_IUPPER  : case YSTR_INUMBER :
   case YSTR_IGREEK  : case YSTR_IFULL   : case YSTR_INIT    :
      break;
   default :
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   s_creg = '"';
   DEBUG_YMAP   yLOG_value   ("s_nreg"    , s_nreg);
   for (i = 0; i < s_nreg; ++i) {
      x_abbr = S_REG_LIST [i];
      if (a_scope == YSTR_IUPPER  && strchr (YSTR_UPPER , x_abbr) == NULL)  continue;
      if (a_scope == YSTR_ILOWER  && strchr (YSTR_LOWER , x_abbr) == NULL)  continue;
      if (a_scope == YSTR_INUMBER && strchr (YSTR_NUMBER, x_abbr) == NULL)  continue;
      if (a_scope == YSTR_IGREEK  && strchr (YSTR_GREEK , x_abbr) == NULL)  continue;
      ymap__mreg_wipe (x_abbr, a_scope);
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> clear all selections ---------------[ shoot  [gz.311.001.02]*/ /*-[00.0000.102.1]-*/ /*-[--.---.---.--]-*/
ymap_mreg_init                  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (SMOD_MREG)) {
      DEBUG_YMAP   yLOG_note    ("status is not ready for init");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(macro abbrev list)--------------*/
   ystrlcpy (S_REG_LIST, "\""       , S_REG_MAX);
   ystrlcat (S_REG_LIST, YSTR_LOWER , S_REG_MAX);
   ystrlcat (S_REG_LIST, YSTR_UPPER , S_REG_MAX);
   ystrlcat (S_REG_LIST, YSTR_NUMBER, S_REG_MAX);
   ystrlcat (S_REG_LIST, YSTR_GREEK , S_REG_MAX);
   ystrlcat (S_REG_LIST, "-+¤"      , S_REG_MAX);
   DEBUG_YMAP   yLOG_info    ("S_REG_LIST", S_REG_LIST);
   s_nreg   = strlen (S_REG_LIST);
   DEBUG_YMAP   yLOG_value   ("s_nreg"    , s_nreg);
   /*---(registers)----------------------*/
   ymap_mreg_purge    (YSTR_INIT);
   myMAP.e_copier   = NULL;
   myMAP.e_clearer  = NULL;
   myMAP.e_paster   = NULL;
   myMAP.e_finisher = NULL;
   myMAP.e_regkill  = NULL;
   myMAP.e_exim     = NULL;
   /*---(update status)------------------*/
   yMODE_init_set   (SMOD_MREG, NULL, ymap_mreg_smode);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> clear all selections ---------------[ shoot  [gz.311.001.02]*/ /*-[00.0000.102.1]-*/ /*-[--.---.---.--]-*/
ymap_mreg_wrap          (void)
{
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(registers)----------------------*/
   ymap_mreg_purge    (YSTR_INIT);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_mreg_config        (void *a_clearer, void *a_copier, void *a_paster, void *a_finisher, void *a_regkill, void *a_exim)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMAP  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (SMOD_MREG)) {
      DEBUG_YMAP   yLOG_note    ("init must complete before config");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   DEBUG_YMAP  yLOG_point   ("a_clearer" , a_clearer);
   myMAP.e_clearer    = a_clearer;
   DEBUG_YMAP  yLOG_point   ("a_copier"  , a_copier);
   myMAP.e_copier     = a_copier;
   DEBUG_YMAP  yLOG_point   ("a_paster"  , a_paster);
   myMAP.e_paster     = a_paster;
   DEBUG_YMAP  yLOG_point   ("a_finisher", a_finisher);
   myMAP.e_finisher   = a_finisher;
   DEBUG_YMAP  yLOG_point   ("a_regkill" , a_regkill);
   myMAP.e_regkill    = a_regkill;
   DEBUG_YMAP  yLOG_point   ("a_exim"    , a_exim);
   myMAP.e_exim       = a_exim;
   /*---(update status)------------------*/
   yMODE_conf_set   (SMOD_MREG, '1');
   /*---(complete)-----------------------*/
   DEBUG_YMAP  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           attaching                          ----===*/
/*====================------------------------------------====================*/
static void  o___ATTACH__________o () { return; }

static char    s_saving   = '-';

char         /*-> attach a cell to a universe --------[ ------ [fe.870.378.72]*/ /*-[00.0000.025.7]-*/ /*-[--.---.---.--]-*/
yMAP_mreg_add           (void *a_thing, char *a_label, char *a_reqs, char *a_pros)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          =   0;
   char        t           [LEN_LABEL]  = "";
   char        x_labels    [LEN_RECD]   = "";
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_char    ("s_saving"  , s_saving);
   --rce;  if (s_saving != 'y') {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YMAP   yLOG_char    ("s_creg"    , s_creg);
   /*---(attach)-------------------------*/
   rc = ymap__mreg_new (s_creg, a_thing, a_label, a_reqs, a_pros);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MREG)) {
      DEBUG_YMAP   yLOG_note    ("can not execute until operational");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check copier)-------------------*/
   DEBUG_YMAP   yLOG_point   ("e_copier"  , myMAP.e_copier);
   --rce;  if (myMAP.e_copier == NULL) {
      DEBUG_YMAP   yLOG_note    ("copier must be set to operate");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(identify register)--------------*/
   DEBUG_YMAP   yLOG_char    ("s_creg"    , s_creg);
   x_reg  = ymap__mreg_by_abbr  (s_creg);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(wipe register)------------------*/
   rc = ymap__mreg_wipe  (s_creg, '-');
   DEBUG_YMAP   yLOG_value   ("wipe rc"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(save selection)-----------------*/
   rc = yMAP_visu_range (&u, &xb, &xe, &yb, &ye, &z, NULL, NULL);
   DEBUG_YMAP   yLOG_value   ("visu rc"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
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
   DEBUG_YMAP   yLOG_value   ("copy rc"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(check counts)-------------------*/
   DEBUG_YMAP   yLOG_value   ("nbuf"      , s_regs [x_reg].nbuf);
   /*> if (s_regs [x_reg].nbuf <= 0)  yvikeys_mreg__wipe (s_creg, '-');               <*/
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char*
ymap_mreg_list          (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_reg       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(identify register)--------------*/
   DEBUG_YMAP   yLOG_char    ("a_abbr"    , a_abbr);
   x_reg  = ymap__mreg_by_abbr  (a_abbr);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  "n/a";
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return s_regs [x_reg].labels;
}

char*
yMAP_mreg_reqs          (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_reg       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(identify register)--------------*/
   DEBUG_YMAP   yLOG_char    ("a_abbr"    , a_abbr);
   x_reg  = ymap__mreg_by_abbr  (a_abbr);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  "n/a";
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return s_regs [x_reg].reqs;
}

char*
yMAP_mreg_pros          (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_reg       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(identify register)--------------*/
   DEBUG_YMAP   yLOG_char    ("a_abbr"    , a_abbr);
   x_reg  = ymap__mreg_by_abbr  (a_abbr);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  "n/a";
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return s_regs [x_reg].pros;
}

char*
yMAP_mreg_labels        (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_reg       =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(identify register)--------------*/
   DEBUG_YMAP   yLOG_char    ("a_abbr"    , a_abbr);
   x_reg  = ymap__mreg_by_abbr  (a_abbr);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  "n/a";
   }
   c = s_regs [x_reg].nbuf;
   DEBUG_YMAP   yLOG_value   ("c"         , c);
   --rce;  if (c <= 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  "n/a";
   }
   DEBUG_YMAP   yLOG_info    ("labels"    , s_regs [x_reg].labels);
   ystrlcpy (s_print, s_regs [x_reg].labels, LEN_RECD);
   ySORT_labels (s_print);
   DEBUG_YMAP   yLOG_info    ("s_print"   , s_print);
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return s_print;
}




/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char
ymap__mreg_clear             (char a_first, char a_last)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x, y;
   ushort      u, xb, xe, yb, ye, z;
   /*> ushort      x_beg, x_end;                                                      <* 
    *> ushort      y_beg, y_end;                                                      <* 
    *> ushort      z;                                                                 <*/
   long        x_stamp     =    0;
   char        x_save      =  '-';
   int         x_reg       =    0;
   char        x_label     [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("h_1st"     , myMAP.h_1st);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MREG)) {
      DEBUG_YMAP   yLOG_note    ("can not execute until operational");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save current register)----------*/
   x_save = s_creg;
   DEBUG_YMAP   yLOG_value   ("x_save"    , x_save);
   s_creg = '¤';
   DEBUG_YMAP   yLOG_value   ("s_creg"    , s_creg);
   /*---(get register number)------------*/
   x_reg  = ymap__mreg_by_abbr (s_creg);
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   --rce;  if (x_reg < 0) {
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_YMAP   yLOG_value   ("x_reg"     , x_reg);
   /*---(save selection)-----------------*/
   rc = yMAP_visu_range (&u, &xb, &xe, &yb, &ye, &z, NULL, NULL);
   DEBUG_YMAP   yLOG_value   ("visu rc"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YMAP   yLOG_complex ("visual"    , "%2du, %3dx to %3dx, %3dy to %3dy", u, xb, xe, yb, ye);
   s_regs [x_reg].u_all   = u;
   s_regs [x_reg].x_beg   = s_regs [x_reg].x_min   = xb;
   s_regs [x_reg].x_end   = s_regs [x_reg].x_max   = xe;
   s_regs [x_reg].y_beg   = s_regs [x_reg].y_min   = yb;
   s_regs [x_reg].y_end   = s_regs [x_reg].y_max   = ye;
   s_regs [x_reg].z_all   = z;
   s_regs [x_reg].type    = S_REG_ACTIVE;
   DEBUG_YMAP   yLOG_complex ("register"  , "%c, %2d, %c, %2du, %3dx to %3dx, %3dy to %3dy", s_creg, x_reg, s_regs [x_reg].type, s_regs [x_reg].u_all, s_regs [x_reg].x_beg, s_regs [x_reg].x_end, s_regs [x_reg].y_beg, s_regs [x_reg].y_end);
   /*---(add position mark)--------------*/
   rc = ymap_addresser (x_label, s_regs [x_reg].u_all, s_regs [x_reg].x_beg, s_regs [x_reg].y_beg, s_regs [x_reg].z_all);
   DEBUG_YMAP   yLOG_value   ("addresser" , rc);
   if (myMAP.h_1st == 'y' && rc >= 0) {
      DEBUG_YMAP   yLOG_info    ("x_label"   , x_label);
      rc = yMAP_mundo_position (YMAP_BEG, x_label);
      DEBUG_YMAP   yLOG_value   ("position"  , rc);
      myMAP.h_1st = '-';
   }
   /*---(check clearer)------------------*/
   DEBUG_YMAP   yLOG_point   ("e_clearer" , myMAP.e_clearer);
   --rce;  if (myMAP.e_clearer == NULL) {
      DEBUG_YMAP   yLOG_note    ("clearer must be set to operate");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call clear)---------------------*/
   s_saving = 'y';
   x_stamp  = rand ();
   rc = myMAP.e_clearer (myMAP.h_1st, 'c', x_stamp);
   DEBUG_YMAP   yLOG_value   ("clear"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   rc = ymap__mreg_wipe  (s_creg, '-');
   s_saving = '-';
   s_creg = x_save;
   s_regs [x_reg].type    = S_REG_EMPTY;
   /*---(add position mark)--------------*/
   if (a_last == 'y') {
      DEBUG_YMAP   yLOG_info    ("x_label"   , x_label);
      rc = yMAP_mundo_position (YMAP_ADD, x_label);
      DEBUG_YMAP   yLOG_value   ("position"  , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char ymap_mreg_clear        (void) { myMAP.h_1st = 'y';  return ymap__mreg_clear ('y', 'y'); }
char ymap_mreg_clear_combo  (void) { return ymap__mreg_clear ('y', '-'); }

static short   s_boff  = 0;
static short   s_xoff  = 0;
static short   s_yoff  = 0;
static short   s_zoff  = 0;

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
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MREG)) {
      DEBUG_YMAP   yLOG_note    ("can not execute until operational");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check paster)-------------------*/
   DEBUG_YMAP   yLOG_point   ("e_paster"  , myMAP.e_paster);
   --rce;  if (myMAP.e_paster == NULL) {
      DEBUG_YMAP   yLOG_note    ("paster must be set to operate");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(identify register)--------------*/
   DEBUG_YMAP   yLOG_char    ("s_creg"    , s_creg);
   s_reg  = ymap__mreg_by_abbr  (s_creg);
   DEBUG_YMAP   yLOG_value   ("s_reg"     , s_reg);
   --rce;  if (s_reg < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(check for empty)----------------*/
   x_nbuf = s_regs [s_reg].nbuf;
   DEBUG_YMAP   yLOG_value   ("x_nbuf"    , x_nbuf);
   --rce;  if (x_nbuf <= 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(get current position)-----------*/
   yMAP_current (NULL, &s_boff, &s_xoff, &s_yoff, &s_zoff);
   DEBUG_YMAP   yLOG_value   ("s_boff"    , s_boff);
   DEBUG_YMAP   yLOG_value   ("s_xoff"    , s_xoff);
   DEBUG_YMAP   yLOG_value   ("s_yoff"    , s_yoff);
   DEBUG_YMAP   yLOG_value   ("s_zoff"    , s_zoff);
   /*---(make into offsets)--------------*/
   s_boff -=  s_regs [s_reg].u_all;
   s_xoff -=  s_regs [s_reg].x_beg;
   s_yoff -=  s_regs [s_reg].y_beg;
   s_zoff -=  s_regs [s_reg].z_all;
   DEBUG_YMAP   yLOG_value   ("s_boff (*)", s_boff);
   DEBUG_YMAP   yLOG_value   ("s_xoff (*)", s_xoff);
   DEBUG_YMAP   yLOG_value   ("s_yoff (*)", s_yoff);
   DEBUG_YMAP   yLOG_value   ("s_zoff (*)", s_zoff);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> prepare for a paste ----------------[ ------ [fe.842.023.21]*/ /*-[01.0000.015.!]-*/ /*-[--.---.---.--]-*/
ymap__mreg_paste_set    (char *a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         i           =    0;
   int         n           =   -1;
   char        x_label     [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_clear   = '-';
   s_reqs    = '-';
   s_pros    = '-';
   s_intg    = '-';
   /*---(defense)------------------------*/
   DEBUG_YMAP   yLOG_point   ("a_type"    , a_type);
   --rce;  if (a_type == NULL) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_info    ("a_type"    , a_type);
   x_len = ystrllen (a_type, LEN_LABEL);
   DEBUG_YMAP   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <  4) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
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
   DEBUG_YMAP   yLOG_value   ("ref n"     , n);
   /*---(lookup on name)-----------------*/
   if (n < 0) {
      for (i = 0; i < MAX_PASTING; ++i) {
         if (a_type [0] != s_pasting [i].name [0])     continue;
         if (strcmp (a_type, s_pasting [i].name) != 0) continue;
         n = i;
         break;
      }
      DEBUG_YMAP   yLOG_value   ("name n"    , n);
   }
   /*---(check for failures)-------------*/
   --rce;  if (n < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(mark settings)------------------*/
   s_clear = s_pasting [n].clear;
   s_reqs  = s_pasting [n].reqs;
   s_pros  = s_pasting [n].pros;
   s_intg  = s_pasting [n].intg;
   /*---(set the destination)------------*/
   yMAP_visu_exact (
         s_regs [s_reg].u_all + s_boff,
         s_regs [s_reg].x_beg + s_xoff, s_regs [s_reg].x_end + s_xoff,
         s_regs [s_reg].y_beg + s_yoff, s_regs [s_reg].y_end + s_yoff,
         s_regs [s_reg].z_all + s_zoff, s_regs [s_reg].z_all + s_zoff,
         'e');
   /*---(add position mark)--------------*/
   rc = ymap_addresser (x_label, s_regs [s_reg].u_all + s_boff, s_regs [s_reg].x_beg + s_xoff, s_regs [s_reg].y_beg + s_yoff, s_regs [s_reg].z_all + s_zoff);
   DEBUG_YMAP   yLOG_value   ("addresser" , rc);
   if (rc >= 0) {
      DEBUG_YMAP   yLOG_info    ("x_label"   , x_label);
      rc = yMAP_mundo_position (YMAP_BEG, x_label);
      DEBUG_YMAP   yLOG_value   ("position"  , rc);
      myMAP.h_1st = '-';
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__mreg_paste        (char *a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x, y, z;
   int         c           =    0;
   tITEM      *x_curr      = NULL;
   char        x_list      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *r           = NULL;
   int         x_before    =    0;
   int         x_after     =    0;
   char        x_label     [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("h_1st"     , myMAP.h_1st);
   /*---(prepare)------------------------*/
   rc = ymap__mreg_paste_check    ();
   DEBUG_YMAP   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get mundo count)----------------*/
   x_before = yMAP_mundo_count ();
   DEBUG_YMAP   yLOG_value   ("x_before"  , x_before);
   /*---(settings)-----------------------*/
   rc = ymap__mreg_paste_set (a_type);
   DEBUG_YMAP   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clearing)-----------------------*/
   DEBUG_YMAP   yLOG_char    ("s_clear"   , s_clear);
   if (s_clear == 'y') {
      /*> ymap__mreg_paste_clear ();                                                  <*/
      ymap__mreg_clear ('y', '-');
   }
   if (s_reqs == '-') {
      DEBUG_YMAP   yLOG_note    ("requested clear only");
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(get mundo count)----------------*/
   x_after  = yMAP_mundo_count ();
   DEBUG_YMAP   yLOG_value   ("x_after"   , x_after );
   if (x_after > x_before) {
      DEBUG_YMAP   yLOG_note    ("cleared cells first, append mundo not new");
      myMAP.h_1st = '-';
      DEBUG_YMAP   yLOG_char    ("h_1st"     , myMAP.h_1st);
   }
   /*---(sync point)---------------------*/
   ystrlcpy (x_list, "", LEN_RECD);
   if (strcmp (s_regs [s_reg].reqs, "n/a") != 0)  ystrlcat (x_list, s_regs [s_reg].reqs, LEN_RECD);
   if (strcmp (s_regs [s_reg].pros, "n/a") != 0)  ystrlcat (x_list, s_regs [s_reg].pros, LEN_RECD);
   if (strcmp (x_list, "") != 0) {
      ySORT_labels (x_list);
      if (myMAP.h_1st == 'y')  yMAP_mundo_sync (YMAP_BEG, x_list, "");
      else                     yMAP_mundo_sync (YMAP_ADD, x_list, "");
      myMAP.h_1st = '-';
   }
   /*---(paste in order)-----------------*/
   DEBUG_YMAP   yLOG_value   ("nbuf"      , s_regs [s_reg].nbuf);
   x_curr = s_regs [s_reg].hbuf;
   --rce;  while (x_curr != NULL) {
      DEBUG_YMAP   yLOG_complex ("item"      , "%-10p, %-10p, %-10p, %-10p", x_curr, x_curr->data, x_curr->b_prev, x_curr->b_next);
      rc = myMAP.e_paster (s_reqs, myMAP.h_1st, s_boff, s_xoff, s_yoff, s_zoff, x_curr->data);
      if (rc < 0) {
         DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++c;
      myMAP.h_1st = '-';
      x_curr = x_curr->b_next;
   }
   /*---(finish)-------------------------*/
   DEBUG_YMAP   yLOG_point   ("e_finisher", myMAP.e_finisher);
   if (myMAP.e_finisher != NULL) {
      ystrlcpy  (x_list, s_regs [s_reg].pros, LEN_RECD);
      DEBUG_YMAP   yLOG_info    ("pros"      , s_regs [s_reg].pros);
      DEBUG_YMAP   yLOG_info    ("x_list"    , x_list);
      p = strtok_r (x_list, ",", &r);
      while (p != NULL) {
         DEBUG_YMAP   yLOG_info    ("p"         , p);
         rc = myMAP.e_finisher (s_pros, p, s_regs [s_reg].labels, s_boff, s_xoff, s_yoff, s_zoff);
         p = strtok_r (NULL  , ",", &r);
      }
   }
   /*---(check for retouches)------------*/
   ystrlcpy  (x_list, s_regs [s_reg].labels, LEN_RECD);
   if (s_regs [s_reg].reqs [0] == ',')   ystrlcat  (x_list, s_regs [s_reg].reqs, LEN_RECD);
   if (s_regs [s_reg].pros [0] == ',')   ystrlcat  (x_list, s_regs [s_reg].pros, LEN_RECD);
   ySORT_labels (x_list);
   p = strtok_r (x_list, ",", &r);
   while (p != NULL) {
      rc = myMAP.e_paster ('?', myMAP.h_1st, s_boff, s_xoff, s_yoff, s_zoff, p);
      if (rc >=  0)  myMAP.h_1st = '-';
      p = strtok_r (NULL  , ",", &r);
   }
   /*---(add position mark)--------------*/
   rc = ymap_addresser (x_label, s_regs [s_reg].u_all + s_boff, s_regs [s_reg].x_beg + s_xoff, s_regs [s_reg].y_beg + s_yoff, s_regs [s_reg].z_all + s_zoff);
   DEBUG_YMAP   yLOG_value   ("addresser" , rc);
   if (rc >= 0) {
      DEBUG_YMAP   yLOG_info    ("x_label"   , x_label);
      rc = yMAP_mundo_position (YMAP_ADD, x_label);
      DEBUG_YMAP   yLOG_value   ("position"  , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char  ymap_mreg_paste       (char *a_type) { myMAP.h_1st = 'y'; return ymap__mreg_paste (a_type); }
char  ymap_mreg_paste_combo (char *a_type) { return ymap__mreg_paste (a_type); }

char
ymap_mreg_visual        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_reg       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ymap__mreg_paste_check    ();
   DEBUG_YMAP   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(select)-------------------------*/
   yMAP_visu_exact (
         s_regs [x_reg].u_all + s_boff,
         s_regs [x_reg].x_beg + s_xoff, s_regs [x_reg].x_end + s_xoff,
         s_regs [x_reg].y_beg + s_yoff, s_regs [x_reg].y_end + s_yoff,
         s_regs [x_reg].z_all + s_zoff, s_regs [x_reg].z_all + s_zoff,
         'e');
   /*> yMAP_jump (                                                                    <* 
    *>       s_regs [x_reg].u_all + s_boff,                                           <* 
    *>       s_regs [x_reg].x_end + s_xoff,                                           <* 
    *>       s_regs [x_reg].y_end + s_yoff,                                           <* 
    *>       s_regs [x_reg].z_all + s_zoff);                                          <*/
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       mode handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___MODE____________o () { return; }

char
yMAP_mreg_hmode         (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        c           =    0;
   /*---(quick-out)----------------------*/
   if (a_minor == 0)            return 0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("a_major"   , a_major);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(single-key)---------------------*/
   if (a_major == G_KEY_SPACE) {
      if (strchr ("pyYx", a_minor) != NULL) {
         DEBUG_YMAP   yLOG_note    ("un-named register map operations");
         ymap__mreg_reset ();
         yMODE_enter (SMOD_MREG);
         ymap_mreg_smode (a_major, a_minor);
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return 1;
      }
      if (a_minor == 'P') {
         DEBUG_YMAP   yLOG_note    ("un-named register multi-key paste start");
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return a_minor;
      }
   }
   /*---(multi-key)----------------------*/
   if (a_major == 'P') {
      DEBUG_YMAP   yLOG_note    ("un-named register multi-key paste end");
      ymap__mreg_reset ();
      yMODE_enter (SMOD_MREG);
      ymap_mreg_smode (a_major, a_minor);
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_mreg_smode         (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *x_majors    = "m'";
   static char x_prev      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("a_major"   , a_major);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , ychrvisible (a_minor));
   DEBUG_YMAP   yLOG_char    ("x_prev"    , x_prev);
   /*> myVIKEYS.info_win = '-';                                                       <*/
   /*---(defenses)-----------------------*/
   DEBUG_YMAP   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (SMOD_MREG)) {
      DEBUG_YMAP   yLOG_note    ("not the correct mode");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(exit mode)----------------------*/
   if (a_minor == G_KEY_ESCAPE || a_minor == G_KEY_RETURN) {
      DEBUG_YMAP   yLOG_note    ("escape/return means leave");
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return  0;
   }
   /*---(register selection)-------------*/
   --rce;  if (a_major == '"') {
      if (strchr ("+-", a_minor) != NULL) {
         DEBUG_YMAP   yLOG_note    ("enter export-import");
         ymap__mreg_set    (a_minor);
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return a_minor;
      } else if (strchr (S_REG_LIST, a_minor) != 0) {
         ymap__mreg_set    (a_minor);
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return 0;
      } else if (a_minor == '?') {
         /*> my.info_win = G_INFO_REGS;                                               <*/
         /*> REG_set ('"');                                                           <*/
         /*> yVIKEYS_mode_exit ();                                                          <*/
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return  0;
      } else if (a_minor == '!') {
         /*> my.layout_status = G_STATUS_REGS;                                        <*/
         /*> REG_set ('"');                                                           <*/
         /*> yVIKEYS_mode_exit ();                                                    <*/
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return  0;
      }
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(register actions)---------------*/
   --rce;  if (a_major == ' ') {
      /*---(multikey prefixes)-----------*/
      switch (a_minor) {
         /*---(multikey prefixes)-----------*/
      case 'p'  :
         DEBUG_YMAP   yLOG_note    ("p for paste normal");
         ymap_mreg_paste ("normal");
         ymap_visu_clear ();
         yMODE_exit ();
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      case 'P'  :
         DEBUG_YMAP   yLOG_note    ("P is a multi-key");
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return a_minor;
      case 'y'  :
         DEBUG_YMAP   yLOG_note    ("y for yank/copy");
         ymap_mreg_save  ();
         ymap_visu_clear ();
         yMODE_exit ();
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      case 'Y'  :
         DEBUG_YMAP   yLOG_note    ("Y for yank/clear");
         ymap_mreg_save  ();
         ymap_mreg_clear ();
         ymap_visu_clear ();
         yMODE_exit ();
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      case 'x'  :
         DEBUG_YMAP   yLOG_note    ("x for clear");
         ymap_mreg_clear ();
         ymap_visu_clear ();
         yMODE_exit ();
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      }
   }
   /*---(export-import)------------------*/
   --rce;  if (strchr ("+-", a_major) != NULL) {
      DEBUG_YMAP   yLOG_note    ("calling external export-import function");
      DEBUG_YMAP   yLOG_point   ("e_exim"    , myMAP.e_exim);
      if (myMAP.e_exim != NULL)  rc = myMAP.e_exim (a_major, a_minor);
      DEBUG_YMAP   yLOG_value   ("rc"        , rc);
      ymap_visu_clear ();
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(pasting actions)----------------*/
   --rce;  if (a_major == 'P') {
      switch (a_minor) {
      case '_' :  rc = ymap_mreg_visual ();            break;
      case '#' :  rc = ymap_mreg_paste  ("clear");     break;
      case 'n' :  rc = ymap_mreg_paste  ("normal");    break;
      case 'N' :  rc = ymap_mreg_paste  ("NORMAL");    break;
      case 'a' :  rc = ymap_mreg_paste  ("append");    break;
      case 'A' :  rc = ymap_mreg_paste  ("APPEND");    break;
      case 'd' :  rc = ymap_mreg_paste  ("duplicate"); break;
      case 'D' :  rc = ymap_mreg_paste  ("DUPLICATE"); break;
      case 'c' :  rc = ymap_mreg_paste  ("combo");     break;
      case 'C' :  rc = ymap_mreg_paste  ("COMBO");     break;
      case 'm' :  rc = ymap_mreg_paste  ("move");      break;
      case 'M' :  rc = ymap_mreg_paste  ("MOVE");      break;
      case 'f' :  rc = ymap_mreg_paste  ("force");     break;
      case 'F' :  rc = ymap_mreg_paste  ("FORCE");     break;
      default  :  rc = rce;                            break;
      }
      ymap_visu_clear ();
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(failure)------------------------*/
   --rce;
   yMODE_exit ();
   DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
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
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   sprintf (myMAP.g_print, "n/a");
   n = ymap__mreg_by_abbr (a_abbr);
   DEBUG_YMAP   yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create line)--------------------*/
   sprintf (t, "%dx%d", s_regs [n].x_end -  s_regs [n].x_beg + 1, s_regs [n].y_end -  s_regs [n].y_beg + 1);
   sprintf (myMAP.g_print, "%c § %2du § %4dn %4db %4de %4dx § %4dn %4db %4de %4dx § %4dc %s",
         a_abbr, s_regs [n].u_all,
         s_regs [n].x_min, s_regs [n].x_beg, s_regs [n].x_end, s_regs [n].x_max,
         s_regs [n].y_min, s_regs [n].y_beg, s_regs [n].y_end, s_regs [n].y_max,
         s_regs [n].nbuf , t);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return myMAP.g_print;
}


