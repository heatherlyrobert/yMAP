/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"




/*
 *
 *  0 zeroth            mih               mouse/rat
 *  1 first             hun               muskox/ox
 *  2 second            cai               tiger
 *  3 third             oxi               rabbit
 *  4 fourth            caji              dragon
 *  5 fifth             voo               snake
 *  6 sixth             vaki              horse
 *  7 seventh           vuku              goat
 *  8 eighth            vaxac             monkey
 *  9 ninth             bolon             rooster
 *
 *  missing dog and pig
 *
 *  a ant               aardvark          antelope, anteater
 *  b bat               buffalo
 *  c canary            camel             cat, chicken
 *  d duck              dolphin           dog, deer
 *  e elephant          elephant
 *  f frog              falcon            fish, flamingo, firefly, terret
 *  g gorilla           giraffe           goose
 *  h hippo             hippo             hen, hog, horse
 *  i iguana            iguana            ibex
 *  j jaguar            jaguar            jackal, jellyfish
 *  k kangaroo          kangaroo
 *  l lion              llama             lamb, leopard
 *  m monkey            millipede         mouse, millipede, mole, muskox, moth, moose
 *  n narwhal           nautilus          nightingale
 *  o owl               octopus           ostrich, orangutan
 *  p penguin           peacock           pig, patypus, parrot, porcupine
 *  q quail             quetzal           quetzal, quetzalcoatl
 *  r raccoon           rhino             rat, rabbit, rooster, rhino, raccoon, reindeer, robin
 *  s squirrel          squirrel          snake, seal
 *  t tiger             tortoise          tick, tarntuala, tortoise, turkey, toad, turtle, tuna
 *  u umbrella bird     unicorn           urchin
 *  v                   vulture           vulture, viper
 *  w whale             warthog           walrus, wolf, warthog
 *  x fox               axolotl  
 *  y yak               yeti              yeti
 *  z zebra             zebra   
 *
 *
 */

static const char    s_unames [][LEN_LABEL] = {
   "mouse",             /*  "mih",  */
   "muskox",            /*  "hun",  */
   "tiger",             /*  "cai", */
   "rabbit",            /*  "oxi", */
   "dragon",            /*  "caji", */
   "snake",             /*  "voo", */
   "horse",             /*  "vaki", */
   "goat",              /*  "vuku", */
   "monkey",            /*  "vaxac", */
   "rooster",           /*  "bolon", */
   "aardvark",
   "buffalo",
   "camel",
   "dolphin",
   "elephant",
   "falcon",
   "giraffe",
   "hippo",
   "iguana",
   "jaguar",
   "kangaroo",
   "llama",
   "millipede",         /*  "monkey", */
   "nautilus",
   "octopus",
   "peacock",
   "quetzal",
   "rhino",             /*  "rabbit", */
   "squirrel",
   "tortoise",          /*  "tiger", */
   "unicorn",
   "vulture",
   "warthog",           /*  "walrus", */
   "axolotl",
   "yeti",
   "zebra",
   "summary",
   "system",
   "temporary",
   "question",
};

char*
yMAP_univ_name          (char n)
{
   if (!VALID_tab (n))  return "tbd";
   return  s_unames [n];
}


char ymap_univ_current       (void) { return g_umap.gcur; }

char
yMAP_universe           (ushort a_pos, uchar a_used)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_used      =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(get existing)-------------------*/
   rc = yMAP_by_index (YMAP_UNIV, a_pos, NULL, NULL, NULL, &x_used);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check and change)---------------*/
   if (a_used != YMAP_CURR) {
      yMAP_entry (YMAP_UNIV, a_pos, YMAP_LEAVE, -1, a_used);
   }
   /*---(request update)-----------------*/
   ymap_uchange (YMAP_POS);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_switch             (ushort a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_used      =    0;
   ushort      x_curr      =    0;
   ushort      bx, cx, ex;
   ushort      by, cy, ey;
   ushort      bz, cz, ez;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_value   ("a_pos"     , a_pos);
   /*---(short-cut)----------------------*/
   rc = yMAP_axis_grid (YMAP_UNIV , NULL, &x_curr, NULL, NULL);
   DEBUG_YMAP   yLOG_value   ("x_curr"    , x_curr);
   --rce;  if (a_pos == x_curr) {
      DEBUG_YMAP   yLOG_note    ("already in requested universe");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   rc = yMAP_by_index (YMAP_UNIV, a_pos, NULL, NULL, NULL, &x_used);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_used == YMAP_NADA) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(xpos)---------------------------*/
   myMAP.e_sizer (YMAP_XAXIS, NULL, &bx, &cx, &ex, NULL, NULL);
   DEBUG_YMAP   yLOG_complex ("xaxis"     , "%4db, %4dc, %4de", bx, cx, ex);
   /*---(ypos)---------------------------*/
   myMAP.e_sizer (YMAP_YAXIS, NULL, &by, &cy, &ey, NULL, NULL);
   DEBUG_YMAP   yLOG_complex ("yaxis"     , "%4db, %4dc, %4de", by, cy, ey);
   /*---(zpos)---------------------------*/
   myMAP.e_sizer (YMAP_ZAXIS, NULL, &bz, &cz, &ez, NULL, NULL);
   DEBUG_YMAP   yLOG_complex ("zaxis"     , "%4db, %4dc, %4de", bz, cz, ez);
   /*---(refresh)------------------------*/
   ymap_uchange (YMAP_FULL);
   yMAP_refresh ();  /* call refresh twice ?????? */
   /*---(universe)-----------------------*/
   myMAP.u_last = g_umap.gcur;
   DEBUG_YMAP   yLOG_value   ("gcur"      ,  g_umap.gcur);
   DEBUG_YMAP   yLOG_value   ("max"       ,  g_umap.gmax);
   DEBUG_YMAP   yLOG_note    ("set universe grid");
   DEBUG_YMAP   yLOG_note    ("call refresh");
   rc = ymap_set_by_grid (&g_umap, YMAP_IGNORE, a_pos, YMAP_IGNORE);
   DEBUG_YMAP   yLOG_value   ("set grid"  , rc);
   if (rc < 0)  {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_value   ("gcur"      ,  g_umap.gcur);
   yMAP_refresh ();  /* must update BEFORE moving in xyz */
   DEBUG_YMAP   yLOG_value   ("gcur"      ,  g_umap.gcur);
   /*---(xpos)---------------------------*/
   ymap_set_by_grid (&g_xmap, bx, cx, ex);
   ymap_set_by_grid (&g_ymap, by, cy, ey);
   ymap_set_by_grid (&g_zmap, bz, cz, ez);
   DEBUG_YMAP   yLOG_value   ("gcur"      ,  g_umap.gcur);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_univ_change        (char a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_used      =    0;
   ushort      b, c, e;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yMAP_by_index (YMAP_UNIV, a_pos, NULL, NULL, NULL, &x_used);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_used == YMAP_NADA) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(universe)-----------------------*/
   myMAP.u_last  = g_umap.gcur;
   if (myMAP.e_switcher != NULL)  rc = myMAP.e_switcher (a_pos);
   else                           rc = yMAP_switch (a_pos);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap_univ_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (UMOD_UNIVERSE)) {
      DEBUG_YMAP   yLOG_note    ("status is not ready for init");
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear callbacks)----------------*/
   DEBUG_YMAP   yLOG_note    ("clear callbacks");
   myMAP.e_switcher = NULL;
   myMAP.u_last     = -1;
   /*---(update status)------------------*/
   yMODE_init_set   (UMOD_UNIVERSE, NULL, ymap_univ_umode);
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_univ_config        (void *a_switcher)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (UMOD_UNIVERSE)) {
      DEBUG_PROG   yLOG_note    ("init must complete before config");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   myMAP.e_switcher   = a_switcher;
   /*---(update status)------------------*/
   yMODE_conf_set   (UMOD_UNIVERSE, '1');
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> process keys for universe move -----[ leaf   [ge.F64.217.CA]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
ymap_univ_umode         (uchar a_major, uchar a_minor)
{
   /*---(design notes)-------------------*/
   /*
    *   this should imitate our RBUF capability in vimm
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL];
   char       *p           = NULL;
   char        u           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_char    ("a_major"   , a_major);
   DEBUG_YMAP   yLOG_char    ("a_minor"   , a_minor);
   /*---(check universe mode)------------*/
   DEBUG_YMAP   yLOG_value   ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (UMOD_UNIVERSE)) {
      DEBUG_YMAP   yLOG_note    ("not the correct mode");
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   --rce;  if (a_major != ',') {
      DEBUG_YMAP   yLOG_note    ("can only be called with , for major");
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   --rce;  if (a_minor == 0) {
      DEBUG_YMAP   yLOG_note    ("freaking null, get outta here");
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(mode changes)-------------------*/
   if (a_minor == G_KEY_ESCAPE || a_minor == G_KEY_RETURN) {
      DEBUG_YMAP   yLOG_note    ("escape or return, choose nothing");
      yMODE_exit ();
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(absolute mode)------------------*/
   p = strchr (YSTR_UNIV, a_minor);
   if (p != NULL)  u = p - YSTR_UNIV;
   --rce;  if (u >= 0) {
      DEBUG_YMAP   yLOG_note    ("absolute mode");
      rc = ymap_univ_change (u);
      yMODE_exit  ();
      DEBUG_YMAP   yLOG_value   ("change"    , rc);
      if (rc < 0) {
         DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(look for cursoring)-------------*/
   DEBUG_YMAP   yLOG_complex ("map"       , "%2dh, %2du, %2dp, %2dl, %2dn, %2du, %2dt", g_umap.gamin, g_umap.gpuse, g_umap.gprev, myMAP.u_last, g_umap.gnext, g_umap.gnuse, g_umap.gamax);
   --rce;  switch (a_minor) {
   case  YDLST_HEAD  :
      DEBUG_YMAP   yLOG_note    ("switch to first/head used universe");
      ymap_univ_change (g_umap.gamin);
      break;
   case  YDLST_PREV  :
      DEBUG_YMAP   yLOG_note    ("switch to previous used universe");
      ymap_univ_change (g_umap.gpuse);
      break;
   case  YDLST_LUSED :
      DEBUG_YMAP   yLOG_note    ("switch to last used universe");
      ymap_univ_change (myMAP.u_last);
      break;
   case  YDLST_NEXT  :
      DEBUG_YMAP   yLOG_note    ("switch to next used universe");
      ymap_univ_change (g_umap.gnuse);
      break;
   case  YDLST_TAIL  :
      DEBUG_YMAP   yLOG_note    ("switch to last/tail used universe");
      ymap_univ_change (g_umap.gamax);
      break;
   case '!'          :
      DEBUG_YMAP   yLOG_note    ("request universe status line");
      yCMD_direct (":status universe");
      break;
   default  :
      DEBUG_YMAP   yLOG_note    ("unknown, nothing to do");
      yMODE_exit  ();
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(complete)-----------------------*/
   yMODE_exit  ();
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}
