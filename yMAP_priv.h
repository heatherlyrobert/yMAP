/*============================----beg-of-source---============================*/
#ifndef yMAP_priv
#define yMAP_priv yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "vikeys location management"
#define     P_PURPOSE   ""

#define     P_NAMESAKE  "theseus"
#define     P_HERITAGE  ""
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yMAP"
#define     P_FULLPATH  "/usr/local/lib64/libyMAP"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.0-, complete and tie yVIKEYS back into it"
#define     P_VERNUM    "2.0a"
#define     P_VERTXT    "initial split of code"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
#include    <math.h>              /* clibc  standard math library             */
#include    <time.h>              /* clibc  time related functions            */
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
/*---(custom vikeys)---------------------*/
#include    <yKEYS.h>             /* heatherly vikeys key handling            */
#include    <yMODE.h>             /* heatherly vikeys mode tracking           */
#include    <yVIEW.h>             /* heatherly vikeys view management         */





typedef    struct    cMY    tMY;
struct cMY {
   char        orient;            /* normal (down = neg) office (down = pos)  */
};
extern tMY         myMAP;

extern char    (*g_mapper)    (char  a_type);
extern char    (*g_locator)   (char *a_label, int *a_buf, int *a_x, int *a_y, int *a_z);
extern char*   (*g_addresser) (char *a_label, int  a_buf, int  a_x, int  a_y, int  a_z);


/*===[[ yVIEW_base.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        ymap__clear             (char a_full, tMAP *a_map, char a_which);
char        ymap_factory            (tMAP *a_map, char a_which);
char        ymap_load               (char a_style, tMAP *a_map);


#endif

