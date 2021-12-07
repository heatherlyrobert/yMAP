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
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   switch (a_minor) {
   case G_KEY_ESCAPE :
      DEBUG_USER   yLOG_note    ("escape to clear selection");
      ymap_visu_clear    ();
      yKEYS_repeat_reset ();
      break;
   case G_KEY_SPACE  :
      DEBUG_USER   yLOG_note    ("space, nothing to do");
      break;
   case  '\0'        :
      DEBUG_USER   yLOG_note    ("null, nothing to do");
      break;
   default           :
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
ymap__multikey          (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =   -1;
   /*---(quick out)----------------------*/
   if (a_major == G_KEY_SPACE)  return 0;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(multi-key)----------------------*/
   switch (a_major) {
   case 'd' : case 'x' :
      /*> rc = ysrc_multi_pure (a_major, a_minor);                                    <*/
      break;
   case 'g' :
      /*> rc = ysrc_move_goto    (a_major, a_minor);                                  <*/
      break;
   case 'z' :
      /*> rc = ysrc_move_scroll  (a_major, a_minor);                                  <*/
      break;
   case 'f' : case 'F' :
      /*> rc = ysrc__source_findchar (a_major, a_minor);                              <*/
      break;
   case 'c' :
      /*> n = yKEYS_repeat_useall ();                                              <* 
       *> for (i = 0; i <= n; ++i) {                                               <* 
       *>    ysrc_multi_pure  ('d', a_minor);                                      <* 
       *> }                                                                        <* 
       *> yMODE_enter (UMOD_INPUT);                                                <* 
       *> SRC_INPT_umode ('m', tolower (a_minor));                                 <* 
       *> rc = tolower (a_minor);                                                  <* 
       *> DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
       *> return rc;                                                               <* 
       *> break;                                                                   <*/
   default  :
      rc = 0;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
ymap_submodes           (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       t           [LEN_TERSE] = "";
   /*---(quick out)----------------------*/
   if (a_major != G_KEY_SPACE)  return 0;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(any time)-----------------------*/
   switch (a_minor) {
   case 'G'      :
      DEBUG_USER   yLOG_note    ("entering god mode");
      yMODE_enter  (MODE_GOD);
      rc = 0;
      break;
   case ':'      :
      DEBUG_USER   yLOG_note    ("entering command mode");
      ySRC_start (":");
      rc = 'A';
      break;
   case '/'      :
      DEBUG_USER   yLOG_note    ("entering search mode");
      ySRC_start ("/");
      rc = ' ';
      break;
   case ';'      :
      DEBUG_USER   yLOG_note    ("entering hint sub-mode");
      ySRC_start (";");
      rc = ' ';
      break;
   case '\\'     :
      DEBUG_USER   yLOG_note    ("entering menu sub-mode");
      yMODE_enter  (SMOD_MENUS);
      /*> yvikeys_menu_start  ();                                                     <*/
      rc = a_minor;
      break;
   case ','      :
      DEBUG_USER   yLOG_note    ("entering buffer sub-mode");
      yMODE_enter  (SMOD_BUFFER);
      rc = a_minor;
      break;
   case '"'      :
      DEBUG_USER   yLOG_note    ("entering mapreg sub-mode");
      yMODE_enter  (SMOD_MREG);
      rc = a_minor;
      break;
   case 'E'      :
      DEBUG_USER   yLOG_note    ("entering error sub-mode");
      yMODE_enter  (SMOD_ERROR);
      rc = a_minor;
      break;
   case 'F'      : case 'f'      :
      DEBUG_USER   yLOG_note    ("entering format external-mode");
      yMODE_enter  (XMOD_FORMAT);
      rc = a_minor;
      break;
   }
   /*---(non-selection)------------------*/
   if (ymap_visu_isdead ()) {
      switch (a_minor) {
      case  G_KEY_RETURN :      /* edit existing cell               */
         DEBUG_USER   yLOG_note    ("edit existing map location");
         ySRC_start ("¦");
         rc = ' ';
         break;
      case  's'  :              /* replace cell entirely            */
         DEBUG_USER   yLOG_note    ("replace existing map location");
         ySRC_start ("");
         rc = ' ';
         break;
      case  '='  : case  '#'  : /* replace cell with formula        */
         DEBUG_USER   yLOG_note    ("replace existing map location with formula");
         sprintf (t, "%c", a_minor);
         ySRC_start (t);
         rc = ' ';
         break;
      case  '+'  : case  '-'  : /* replace cell with a number       */
         DEBUG_USER   yLOG_note    ("replace existing map location with number");
         sprintf (t, "%c", a_minor);
         ySRC_start (t);
         rc = ' ';
         break;
      }
   }
   /*---(visual selection)---------------*/
   if (ymap_visu_islive ()) {
      switch (a_minor) {
      case  '+'  : case  '-'  : /* import and export sub-mode       */
         DEBUG_USER   yLOG_note    ("import/export map registers");
         /*> yMODE_enter (SMOD_MREG);                                                 <* 
          *> rc = yvikeys_mreg_smode  ('"', a_minor);                                 <*/
         break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}


/*> char                                                                              <* 
 *> yvikeys__map_mode_chg   (char a_minor)                                            <* 
 *> {                                                                                 <* 
 *>    char        rc          =   -1;                                                <* 
 *>    char        t           [5];                                                   <* 
 *>    /+---(common modes)----------------+/                                          <* 
 *>    DEBUG_USER   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    DEBUG_USER   yLOG_char    ("change"    , a_minor);                             <* 
 *>    /+---(selecting and marking)-------+/                                          <* 
 *>    switch (a_minor) {                                                             <* 
 *>    case 'v'      :                                                                <* 
 *>       if (yvikeys_visu_islive ())   yvikeys_visu_reverse  ();                     <* 
 *>       else                          yvikeys_visu_makelive ();                     <* 
 *>       rc = 0;                                                                     <* 
 *>       break;                                                                      <* 
 *>    case 'M'      : case 'V'      :                                                <* 
 *>       DEBUG_USER   yLOG_note    ("entering visual selection history sub-mode");   <* 
 *>       rc = yMODE_enter  (UMOD_VISUAL  );                                          <* 
 *>       if (rc >= 0)  rc = a_minor;                                                 <* 
 *>       break;                                                                      <* 
 *>    case 'm'      : case '\''     :                                                <* 
 *>       DEBUG_USER   yLOG_note    ("entering location mark sub-mode");              <* 
 *>       rc = yMODE_enter  (UMOD_MARK    );                                          <* 
 *>       if (rc >= 0)  rc = a_minor;                                                 <* 
 *>       break;                                                                      <* 
 *>    }                                                                              <* 
 *>    if (rc >= 0) {                                                                 <* 
 *>       DEBUG_USER   yLOG_value   ("rc"        , rc);                               <* 
 *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                   <* 
 *>       return rc;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(import/export)---------------+/                                          <* 
 *>    if (yvikeys_visu_islive () && strchr ("+-"   , a_minor) != NULL) {             <* 
 *>       yMODE_enter (SMOD_MREG);                                                    <* 
 *>       rc = yvikeys_mreg_smode  ('"', a_minor);                                    <* 
 *>    }                                                                              <* 
 *>    if (rc >= 0) {                                                                 <* 
 *>       DEBUG_USER   yLOG_value   ("rc"        , rc);                               <* 
 *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                   <* 
 *>       return rc;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_USER   yLOG_exitr   (__FUNCTION__, rc);                                  <* 
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
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_char    ("a_major"   , a_major);
   DEBUG_USER   yLOG_char    ("a_minor"   , chrvisible (a_minor));
   DEBUG_USER   yLOG_value   ("a_minor"   , a_minor);
   /*---(defenses)-----------------------*/
   DEBUG_USER   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (MODE_MAP    )) {
      DEBUG_USER   yLOG_note    ("not the correct mode");
      yMODE_exit  ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(universal)----------------------*/
   rc = ymap__biggies (a_major, a_minor);
   DEBUG_USER   yLOG_value   ("biggies"   , rc);
   if (rc != 0) {
      if (rc > 0)  rc = 0;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(repeat)-------------------------*/
   if (yKEYS_is_repeater (a_minor)) {
      DEBUG_USER   yLOG_note    ("repeating");
      yMODE_enter  (PMOD_REPEAT);
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return a_minor;
   }
   /*---(sub-modes)----------------------*/
   rc = ymap_submodes (a_major, a_minor);
   DEBUG_USER   yLOG_value   ("submodes"  , rc);
   if (rc != 0) {
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(moves)--------------------------*/
   rc = ymap_move_hmode (a_major, a_minor);
   DEBUG_USER   yLOG_value   ("moves"     , rc);
   if (rc != 0) {  /* also for failed goto, scroll, or end multikeys */
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(visual)-------------------------*/
   rc = ymap_visu_hmode (a_major, a_minor);
   DEBUG_USER   yLOG_value   ("visu"      , rc);
   if (rc != 0) {
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(macros)-------------------------*/
   rc = yMACRO_hmode  (a_major, a_minor);
   DEBUG_USER   yLOG_value   ("macros"    , rc);
   if (rc != 0) {
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(single key)---------------------*/
   DEBUG_USER   yLOG_note    ("review single keys");
   /*> --rce;                                                                         <* 
    *> if (a_major == ' ') {                                                          <* 
    *>    DEBUG_USER   yLOG_note    ("no or empty major");                            <* 
    *>    /+---(speed)-----------------------+/                                       <* 
    *>    if (a_minor == '\t' || a_minor == 9) {                                      <* 
    *>       DEBUG_USER   yLOG_note    ("MAP MODE BLITZ");                            <* 
    *>       yvikeys_loop_blitz ();                                                   <* 
    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return 0;                                                                <* 
    *>    } else if (a_minor == '\b' || a_minor == 127) {                             <* 
    *>       DEBUG_USER   yLOG_note    ("MAP MODE UNBLITZ");                          <* 
    *>       yvikeys_loop_unblitz ();                                                 <* 
    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return 0;                                                                <* 
    *>    }                                                                           <* 
    *>    /+---(repeat)----------------------+/                                       <* 
    *>    if (strchr (g_repeat, a_minor) != 0) {                                      <* 
    *>       DEBUG_USER   yLOG_note    ("repeating");                                 <* 
    *>       yMODE_enter  (PMOD_REPEAT);                                              <* 
    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return a_minor;                                                          <* 
    *>    }                                                                           <* 
    *>    /+---(multikey prefixes)-----------+/                                       <* 
    *>    if (yvikeys_visu_isdead () && strchr (g_multimap , a_minor) != 0) {         <* 
    *>       DEBUG_USER   yLOG_note    ("prefix of multimap keystring");              <* 
    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return a_minor;                                                          <* 
    *>    }                                                                           <* 
    *>    if (yvikeys_visu_islive () && strchr (g_multivisu, a_minor) != 0) {         <* 
    *>       DEBUG_USER   yLOG_note    ("prefix of visual multimap keystring");       <* 
    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return a_minor;                                                          <* 
    *>    }                                                                           <* 
    *>    /+---(grouping)--------------------+/                                       <* 
    *>    if (a_minor == '(') {                                                       <* 
    *>       DEBUG_USER   yLOG_note    ("begin group");                               <* 
    *>       yKEYS_group_beg ();                                                      <* 
    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return 0;                                                                <* 
    *>    }                                                                           <* 
    *>    if (a_minor == ')') {                                                       <* 
    *>       DEBUG_USER   yLOG_note    ("end group");                                 <* 
    *>       yKEYS_group_end ();                                                      <* 
    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return 0;                                                                <* 
    *>    }                                                                           <* 
    *>    /+---(funky moves)-----------------+/                                       <* 
    *>    if (a_minor == ':') {                                                       <* 
    *>       x_grid = yKEYS_repeat_useall ();                                         <* 
    *>       if (x_grid > 0) {                                                        <* 
    *>          rc = yvikeys__map_move   (x_grid, &g_ymap);                           <* 
    *>          yvikeys__screen (&g_ymap);                                            <* 
    *>          yvikeys_map_reposition  ();                                           <* 
    *>          DEBUG_USER   yLOG_exit    (__FUNCTION__);                             <* 
    *>          return rc;;                                                           <* 
    *>       }                                                                        <* 
    *>       /+ non-repeat fall thru  +/                                              <* 
    *>    }                                                                           <* 
    *>    if (a_minor == '|') {                                                       <* 
    *>       rc = yvikeys__map_move   (yKEYS_repeat_useall (), &g_xmap);              <* 
    *>       yvikeys__screen (&g_xmap);                                               <* 
    *>       yvikeys_map_reposition  ();                                              <* 
    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return rc;                                                               <* 
    *>    }                                                                           <* 
    *>    if (a_minor == '%') {                                                       <* 
    *>       rc = yvikeys__map_move   (yKEYS_repeat_useall (), &g_ymap);              <* 
    *>       yvikeys__screen (&g_ymap);                                               <* 
    *>       yvikeys_map_reposition  ();                                              <* 
    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
    *>       return rc;                                                               <* 
   *>    }                                                                           <* 
      *>    /+---(mode changes)----------------+/                                       <* 
      *>    if (strchr (s_map_modes, a_minor) != 0) {                                   <* 
         *>       DEBUG_USER   yLOG_note    ("mode changes");                              <* 
            *>       rc = yvikeys__map_mode_chg (a_minor);                                    <* 
            *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
            *>       return rc;                                                               <* 
            *>    }                                                                           <* 
            *>    if (strchr ("yYpPx", a_minor) != 0) {                                       <* 
               *>       DEBUG_USER   yLOG_note    ("switch to a map register mode");             <* 
                  *>       yMODE_enter (SMOD_MREG);                                                 <* 
                  *>       rc = yvikeys_mreg_smode  (G_KEY_SPACE, a_minor);                         <* 
                  *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
                  *>       return rc;                                                               <* 
                  *>    }                                                                           <* 
                  *>    /+---(history)---------------------+/                                       <* 
                  *>    if (a_minor == 'u') {                                                       <* 
                     *>       yvikeys_visu_clear ();                                                   <* 
                        *>       rc = yvikeys_hist_undo ();                                               <* 
                        *>       yvikeys_map_reposition  ();                                              <* 
                        *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
                        *>       return rc;                                                               <* 
                        *>    }                                                                           <* 
                        *>    if (a_minor == 'U') {                                                       <* 
                           *>       yvikeys_visu_clear ();                                                   <* 
                              *>       rc = yvikeys_hist_redo ();                                               <* 
                              *>       yvikeys_map_reposition  ();                                              <* 
                              *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
                              *>       return rc;                                                               <* 
                              *>    }                                                                           <* 
                              *>    /+---(normal)----------------------+/                                       <* 
                              *>    if (strchr (g_hsimple, a_minor) != 0) {                                     <* 
                                 *>       rc = yvikeys__map_horz   (a_major, a_minor);                             <* 
                                    *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
                                    *>       return rc;                                                               <* 
                                    *>    }                                                                           <* 
                                    *>    if (strchr (g_vsimple, a_minor) != 0) {                                     <* 
                                       *>       rc = yvikeys__map_vert   (a_major, a_minor);                             <* 
                                          *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
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
                                                      *>       DEBUG_USER   yLOG_exit    (__FUNCTION__);                                <* 
                                                      *>       if (rc > 0)  rc = -1;                                                    <* 
                                                      *>       return rc;                                                               <* 
                                                      *>    }                                                                           <* 
                                                      *>    DEBUG_USER   yLOG_note    ("no matches found");                             <* 
                                                      *> }                                                                              <*/
                                                      /*---(page family)--------------------*/
                                                      /*> else if (strchr ("cge", a_major) != NULL) {                                    <* 
                                                       *>    rc = yvikeys__combo_moves (a_major, a_minor);                               <* 
                                                       *>    DEBUG_USER   yLOG_exit    (__FUNCTION__);                                   <* 
                                                       *>    return rc;                                                                  <* 
                                                       *> }                                                                              <*/
                                                      /*---(scroll family)------------------*/
                                                      /*> --rce;  if (a_major == 'z') {                                                  <* 
                                                       *>    DEBUG_USER   yLOG_note    ("multikey scrolling");                           <* 
                                                       *>    rc = -66;                                                                   <* 
                                                       *>    /+---(horizontal)------------------+/                                       <* 
                                                       *>    if (strchr (g_hscroll, a_minor) != 0) {                                     <* 
                                                       *>       rc = yvikeys__map_horz   (a_major, a_minor);                             <* 
                                                       *>    }                                                                           <* 
                                                       *>    /+---(vertical)--------------------+/                                       <* 
                                                       *>    if (strchr (g_vscroll, a_minor) != 0) {                                     <* 
                                                       *>       rc = yvikeys__map_vert   (a_major, a_minor);                             <* 
                                                       *>    }                                                                           <* 
                                                       *>    /+---(unrecognized)----------------+/                                       <* 
                                                       *>    if (rc < 0) {                                                               <* 
                                                       *>       DEBUG_USER   yLOG_note    ("unrecognized scroll minor");                 <* 
                                                       *>       DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);                           <* 
                                                       *>       return rce;                                                              <* 
                                                       *>    }                                                                           <* 
                                                       *>    /+---(done)------------------------+/                                       <* 
                                                       *>    DEBUG_USER   yLOG_exit    (__FUNCTION__);                                   <* 
                                                       *>    return rc;                                                                  <* 
                                                       *> }                                                                              <*/
                                                      /*---(paste family)-------------------*/
                                                      /*> if (a_major == 'p') {                                                          <* 
                                                       *>    switch (a_minor) {                                                          <* 
                                                       *>    case '_' :  rc = yvikeys_mreg_visual ();            break;                  <* 
                                                       *>    case '#' :  rc = yvikeys_mreg_paste  ("clear");     break;                  <* 
                                                       *>    case 'n' :  rc = yvikeys_mreg_paste  ("normal");    break;                  <* 
                                                       *>    case 'r' :  rc = yvikeys_mreg_paste  ("replace");   break;                  <* 
                                                       *>    case 'd' :  rc = yvikeys_mreg_paste  ("duplicate"); break;                  <* 
                                                       *>    case 'm' :  rc = yvikeys_mreg_paste  ("move");      break;                  <* 
                                                       *>    case 'f' :  rc = yvikeys_mreg_paste  ("force");     break;                  <* 
                                                       *>    }                                                                           <* 
                                                       *>    DEBUG_USER   yLOG_exit    (__FUNCTION__);                                   <* 
                                                       *>    return rc;                                                                  <* 
                                                       *> }                                                                              <*/
                                                      /*---(delete)-------------------------*/
                                                      /*> if (tolower (a_major) == 'd') {                                                <* 
                                                       *>    rc = yvikeys__combo_delete  (a_major, a_minor);                             <* 
                                                       *>    DEBUG_USER   yLOG_exit    (__FUNCTION__);                                   <* 
                                                       *>    return rc;                                                                  <* 
                                                       *> }                                                                              <*/
                                                      /*---(clear)--------------------------*/
                                                      /*> if (a_major == 'x') {                                                          <* 
                                                       *>    rc = yvikeys__combo_clear   (a_major, a_minor);                             <* 
                                                       *>    DEBUG_USER   yLOG_exit    (__FUNCTION__);                                   <* 
                                                       *>    return rc;                                                                  <* 
                                                       *> }                                                                              <*/
                                                      /*---(append)-------------------------*/
                                                      /*> if (tolower (a_major) == 'a') {                                                <* 
                                                       *>    rc = yvikeys__combo_append  (a_major, a_minor);                             <* 
                                                       *>    DEBUG_USER   yLOG_exit    (__FUNCTION__);                                   <* 
                                                       *>    return rc;                                                                  <* 
                                                       *> }                                                                              <*/
                                                      /*---(complete)------------------------------*/
                                                      DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return rc;
}


