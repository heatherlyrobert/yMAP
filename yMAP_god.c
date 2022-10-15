/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"


enum {
   GOD_VANTAGE , GOD_SPIN    , GOD_ORBIT   ,
   GOD_CRAB    , GOD_BOOM    , GOD_DOLLY   ,
   GOD_LEFT    , GOD_ELEVATE , GOD_APPROACH,
   GOD_PITCH   , GOD_ROLL    , GOD_YAW     ,
};

struct tAXIS {
   /*---(user set)-----------------------*/
   char        txt;               /* label for axis                           */
   double      min;               /* minimum value                            */
   double      max;               /* maximum value                            */
   double      start;             /* start/default value                      */
   double      curr;              /* current setting                          */
   double      step;              /* smallist increment                       */
   double      minor;             /* middle step multiplier                   */
   double      major;             /* major step multiplier                    */
   /*---(user set)-----------------------*/
   double      range;             /* full range (max - min)                   */
   double      half;              /* halfway point in range (center)          */
   double      scale;             /* unit for 100 point scale                 */
   char        wrap;              /* label for axis                           */
   /*---(done)---------------------------*/
} axis[15] = {
   /* txt, ---min, ---max, -start, --curr, --step, -range, --half, -scale, wr */
   /* world rotations                                                         */
   {  'v',      0,    360,      0,      0,      5,      5,     45,    360,    180,    3.6, 'y'},
   {  's',      0,    360,      0,      0,      5,      5,     45,    360,    180,    3.6, 'y'},
   {  'o',      0,    360,      0,      0,      5,      5,     45,    360,    180,    3.6, 'y'},
   /* world translations                                                      */
   {  'c',   -800,    800,      0,      0,     20,      5,     45,   1600,    800,     16, 'n'},
   {  'b',   -800,    800,      0,      0,     20,      5,     45,   1600,    800,     16, 'n'},
   {  'd',    100,   1700,    800,    800,     20,      5,     45,   1600,    800,     16, 'n'},
   /* end-of-table                                                            */
   {  '-',      0,      0,      0,      0,      0,      0,      0,      0, 'n'},
};

char
yMAP_god_axis           (char a_txt, double a_min, double a_max, double a_start, double a_step, double a_minor, double a_major)
{
   int  i;
   /*> printf ("\n");                                                                 <* 
    *> printf ("%c, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf\n",                <* 
    *>          a_txt, a_min, a_max, a_start, a_step, a_minor, a_major);              <*/
   for (i = 0; i < 6; ++i) {
      if (axis[i].txt != a_txt)   continue;
      axis[i].min   =  a_min;
      axis[i].max   =  a_max;
      axis[i].start =  a_start;
      axis[i].step  =  a_step;
      axis[i].minor =  a_minor;
      axis[i].major =  a_major;
      axis[i].range =  a_max - a_min;
      axis[i].half  =  axis[i].range / 2;
      axis[i].scale =  (float) (axis[i].range) / 100.0;
      axis[i].curr  =  a_start;
      /*> printf ("\na, ----min-, ----max-, --start-, ---step-, --minor-, --major-, --range-, ---half-, --scale-, w, ---curr-\n");   <* 
       *> printf ("%c, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %c, %8.2lf\n",                        <* 
       *>       a_txt, axis[i].min, axis[i].max, axis[i].start, axis[i].step, axis[i].minor, axis[i].major,                          <* 
       *>       axis[i].range, axis[i].half, axis[i].scale, axis[i].wrap, axis[i].curr);                                             <*/
      break;
   }
   return 0;
}

char             /* [------] adjust the six degrees of freedom ---------------*/
yMAP_god_move           (int a_index, char a_dir)
{
   /*---(locals)-----------+-----------+-*/
   int         truncer     = 0;
   double      step        = 0.0;
   /*---(before)-------------------------*/
   /*> printf ("\naction %1d %c\n", a_index, a_dir);                                                                                       <* 
    *> printf ("   ------  a, ----min-, ----max-, --start-, ---step-, --minor-, --major-, --range-, ---half-, --scale-, w, ---curr-\n");   <* 
    *> printf ("   before  %c, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %c, %8.2lf\n",                      <* 
    *>       axis[a_index].txt  , axis[a_index].min  , axis[a_index].max  , axis[a_index].start,                                           <* 
    *>       axis[a_index].step , axis[a_index].minor, axis[a_index].major,                                                                <* 
    *>       axis[a_index].range, axis[a_index].half , axis[a_index].scale,                                                                <* 
    *>       axis[a_index].wrap , axis[a_index].curr);                                                                                     <*/
   /*---(adjust to direction)------------*/
   switch (a_dir) {
   case '0'  :  /* back to start/default */
      axis[a_index].curr   = axis[a_index].start;
      break;
   case '+'  : /* single step positive   */
      axis[a_index].curr  += axis[a_index].step;
      break;
   case '-'  : /* single step negative   */
      axis[a_index].curr  -= axis[a_index].step;
      break;
   case '>'  : /* minor stop positive    */
      step                = (axis[a_index].step * axis[a_index].minor);
      axis[a_index].curr += step;
      truncer             = (int)    (axis[a_index].curr / step);
      axis[a_index].curr  = (double) truncer * step;
      break;
   case '<'  : /* minor stop negative    */
      step                = (axis[a_index].step * axis[a_index].minor);
      axis[a_index].curr -= step;
      if (axis[a_index].curr < axis[a_index].min && axis[a_index].wrap == 'y')
         axis[a_index].curr += axis[a_index].max;
      truncer             = (int)    (axis[a_index].curr / step);
      axis[a_index].curr  = (double) truncer * step;
      break;
   case 'f'  : /* major stop positive    */
      step                = (axis[a_index].step * axis[a_index].major);
      axis[a_index].curr += step;
      truncer             = (int)    (axis[a_index].curr / step);
      axis[a_index].curr  = (double) truncer * step;
      break;
   case 'r'  : /* major stop negative    */
      step                = (axis[a_index].step * axis[a_index].major);
      axis[a_index].curr -= step;
      if (axis[a_index].curr < axis[a_index].min && axis[a_index].wrap == 'y')
         axis[a_index].curr += axis[a_index].max;
      truncer             = (int)    (axis[a_index].curr / step);
      axis[a_index].curr  = (double) truncer * step;
      break;
   }
   /*---(contain in legal bounds)--------*/
   if (axis[a_index].wrap == 'n') {
      if (axis[a_index].curr < axis[a_index].min) axis[a_index].curr  = axis[a_index].min;
      if (axis[a_index].curr > axis[a_index].max) axis[a_index].curr  = axis[a_index].max;
   } else {
      if (axis[a_index].curr < axis[a_index].min) axis[a_index].curr += axis[a_index].max;
      if (axis[a_index].curr > axis[a_index].max) axis[a_index].curr -= axis[a_index].max;
   }
   /*---(output)-------------------------*/
   /*> printf ("   after   %c, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %8.2lf, %c, %8.2lf\n",   <* 
    *>       axis[a_index].txt  , axis[a_index].min  , axis[a_index].max  , axis[a_index].start,                        <* 
    *>       axis[a_index].step , axis[a_index].minor, axis[a_index].major,                                             <* 
    *>       axis[a_index].range, axis[a_index].half , axis[a_index].scale,                                             <* 
    *>       axis[a_index].wrap , axis[a_index].curr);                                                                  <*/
   /*---(complete)-----------------------*/
   return 0;
}

char
yMAP_god_key            (uchar a_key)
{
   /*> printf("handling a <<%c>>\n", a_key);                                          <*/
   /*---(x-axis linear)------------------*/
   switch (a_key) {
   case  12  :  yMAP_god_move (GOD_CRAB     , 'f');   break;
   case  'L' :  yMAP_god_move (GOD_CRAB     , '>');   break;
   case  'l' :  yMAP_god_move (GOD_CRAB     , '+');   break;
   case  'h' :  yMAP_god_move (GOD_CRAB     , '-');   break;
   case  'H' :  yMAP_god_move (GOD_CRAB     , '<');   break;
   case   8  :  yMAP_god_move (GOD_CRAB     , 'r');   break;
   }
   /*---(y-axis linear)------------------*/
   switch (a_key) {
   case  11  :  yMAP_god_move (GOD_BOOM     , 'f');   break;
   case  'K' :  yMAP_god_move (GOD_BOOM     , '>');   break;
   case  'k' :  yMAP_god_move (GOD_BOOM     , '+');   break;
   case  'j' :  yMAP_god_move (GOD_BOOM     , '-');   break;
   case  'J' :  yMAP_god_move (GOD_BOOM     , '<');   break;
   case  10  :  yMAP_god_move (GOD_BOOM     , 'r');   break;
   }
   /*---(z-axis linear)------------------*/
   switch (a_key) {
   case  15  :  yMAP_god_move (GOD_DOLLY    , 'f');   break;   /* <Ctrl-o>     */
   case  'O' :  yMAP_god_move (GOD_DOLLY    , '>');   break;
   case  'o' :  yMAP_god_move (GOD_DOLLY    , '+');   break;
   case  'i' :  yMAP_god_move (GOD_DOLLY    , '-');   break;
   case  'I' :  yMAP_god_move (GOD_DOLLY    , '<');   break;
   case   9  :  yMAP_god_move (GOD_DOLLY    , 'r');   break;   /* <Ctrl-i>     */
   }
   /*---(x-axis pitch)-------------------*/
   switch (a_key) {
   case   1  :  yMAP_god_move (GOD_VANTAGE  , 'f');   break;   /* <Ctrl-a>     */
   case  'V' :  yMAP_god_move (GOD_VANTAGE  , '>');   break;
   case  'v' :  yMAP_god_move (GOD_VANTAGE  , '+');   break;
   case  'p' :  yMAP_god_move (GOD_VANTAGE  , '-');   break;
   case  'P' :  yMAP_god_move (GOD_VANTAGE  , '<');   break;
   case  16  :  yMAP_god_move (GOD_VANTAGE  , 'r');   break;   /* <Ctrl-p>     */
   }
   /*---(y-axis yaw)---------------------*/
   switch (a_key) {
   case  25  :  yMAP_god_move (GOD_ORBIT    , 'r');   break;   /* <Ctrl-y>     */
   case  'Y' :  yMAP_god_move (GOD_ORBIT    , '<');   break;
   case  'y' :  yMAP_god_move (GOD_ORBIT    , '-');   break;
   case  't' :  yMAP_god_move (GOD_ORBIT    , '+');   break;
   case  'T' :  yMAP_god_move (GOD_ORBIT    , '>');   break;
   case  20  :  yMAP_god_move (GOD_ORBIT    , 'f');   break;   /* <Ctrl-t>     */
   }
   /*---(z-axis roll)--------------------*/
   switch (a_key) {
   case  18  :  yMAP_god_move (GOD_SPIN     , 'r');   break;   /* <Ctrl-r>     */
   case  'R' :  yMAP_god_move (GOD_SPIN     , '<');   break;
   case  'r' :  yMAP_god_move (GOD_SPIN     , '-');   break;
   case  'w' :  yMAP_god_move (GOD_SPIN     , '+');   break;
   case  'W' :  yMAP_god_move (GOD_SPIN     , '>');   break;
   case  23  :  yMAP_god_move (GOD_SPIN     , 'f');   break;   /* <Ctrl-w>     */

   }
   /*---(x-axis yaw)---------------------*/
   switch (a_key) {
   case  '0' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                yMAP_god_move (GOD_DOLLY    , '0');
                yMAP_god_move (GOD_VANTAGE  , '0');
                yMAP_god_move (GOD_SPIN     , '0');
                yMAP_god_move (GOD_ORBIT    , '0');
                break;

   case  '1' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                yMAP_god_move (GOD_DOLLY    , '0');
                axis[GOD_VANTAGE].curr =   0; yMAP_god_move (GOD_VANTAGE  , ' ');
                axis[GOD_SPIN   ].curr =   0; yMAP_god_move (GOD_SPIN     , ' ');
                axis[GOD_ORBIT  ].curr =   0; yMAP_god_move (GOD_ORBIT    , ' ');
                break;

   case  '2' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                yMAP_god_move (GOD_DOLLY    , '0');
                axis[GOD_VANTAGE].curr =   0; yMAP_god_move (GOD_VANTAGE  , ' ');
                axis[GOD_SPIN   ].curr =   0; yMAP_god_move (GOD_SPIN     , ' ');
                axis[GOD_ORBIT  ].curr =  90; yMAP_god_move (GOD_ORBIT    , ' ');
                break;

   case  '3' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                yMAP_god_move (GOD_DOLLY    , '0');
                axis[GOD_VANTAGE].curr =   0; yMAP_god_move (GOD_VANTAGE  , ' ');
                axis[GOD_SPIN   ].curr =   0; yMAP_god_move (GOD_SPIN     , ' ');
                axis[GOD_ORBIT  ].curr = 180; yMAP_god_move (GOD_ORBIT    , ' ');
                break;

   case  '4' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                yMAP_god_move (GOD_DOLLY    , '0');
                axis[GOD_VANTAGE].curr =   0; yMAP_god_move (GOD_VANTAGE  , ' ');
                axis[GOD_SPIN   ].curr =   0; yMAP_god_move (GOD_SPIN     , ' ');
                axis[GOD_ORBIT  ].curr = 270; yMAP_god_move (GOD_ORBIT    , ' ');
                break;

   case  '5' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                yMAP_god_move (GOD_DOLLY    , '0');
                axis[GOD_VANTAGE].curr =  90; yMAP_god_move (GOD_VANTAGE  , ' ');
                axis[GOD_SPIN   ].curr =   0; yMAP_god_move (GOD_SPIN     , ' ');
                axis[GOD_ORBIT  ].curr =   0; yMAP_god_move (GOD_ORBIT    , ' ');
                break;

   case  '6' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                yMAP_god_move (GOD_DOLLY    , '0');
                axis[GOD_VANTAGE].curr = 270; yMAP_god_move (GOD_VANTAGE  , ' ');
                axis[GOD_SPIN   ].curr =   0; yMAP_god_move (GOD_SPIN     , ' ');
                axis[GOD_ORBIT  ].curr =   0; yMAP_god_move (GOD_ORBIT    , ' ');
                break;

   case  '7' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                yMAP_god_move (GOD_DOLLY    , '5');
                axis[GOD_VANTAGE].curr =   0; yMAP_god_move (GOD_VANTAGE  , ' ');
                axis[GOD_SPIN   ].curr =   0; yMAP_god_move (GOD_SPIN     , ' ');
                axis[GOD_ORBIT  ].curr =  20; yMAP_god_move (GOD_ORBIT    , ' ');
                break;

   case  '8' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                yMAP_god_move (GOD_DOLLY    , '5');
                axis[GOD_VANTAGE].curr =  50; yMAP_god_move (GOD_VANTAGE  , ' ');
                axis[GOD_SPIN   ].curr =   0; yMAP_god_move (GOD_SPIN     , ' ');
                axis[GOD_ORBIT  ].curr =  20; yMAP_god_move (GOD_ORBIT    , ' ');
                break;

   case  '9' :  yMAP_god_move (GOD_CRAB     , '0');
                yMAP_god_move (GOD_BOOM     , '0');
                axis[GOD_DOLLY  ].curr = 300; yMAP_god_move (GOD_DOLLY    , ' ');
                axis[GOD_VANTAGE].curr =  90; yMAP_god_move (GOD_VANTAGE  , ' ');
                axis[GOD_SPIN   ].curr =   0; yMAP_god_move (GOD_SPIN     , ' ');
                axis[GOD_ORBIT  ].curr =  00; yMAP_god_move (GOD_ORBIT    , ' ');
                break;
   }
   return 0;
}

char
ymap_god_mode           (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          = 0;
   char        x_minors    [LEN_FULL]  = "ypdx";
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_complex ("a_major"   , "%c (%3d)", a_major, a_major);
   DEBUG_USER   yLOG_complex ("a_minor"   , "%c (%3d)", a_minor, a_minor);
   /*---(defenses)-----------------------*/
   DEBUG_USER   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (MODE_GOD     )) {
      DEBUG_USER   yLOG_note    ("not the correct mode");
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(mode changes)-------------------*/
   if (a_minor == G_KEY_ESCAPE || a_minor == G_KEY_RETURN || a_minor == G_KEY_ENTER ) {
      DEBUG_USER   yLOG_note    ("escape/return, nothing to do");
      yMODE_exit  ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(single key)---------------------*/
   --rce;
   if (a_major == ' ' || a_major == G_CHAR_SPACE) {
      DEBUG_USER   yLOG_note    ("single keys, no major");
      /*---(repeat)----------------------*/
      if (yKEYS_is_repeater (a_minor)) {
         DEBUG_USER   yLOG_note    ("repeating");
         yMODE_enter  (PMOD_REPEAT);
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return a_minor;
      }
      switch (a_minor) {
      /* crab  /horz  */  case 'h': case 'l': case 'H': case 'L':
      /* boom  /vert  */  case 'j': case 'k': case 'J': case 'K':
      /* dolly /zoom  */  case 'i': case 'I': case 'o': case 'O':
      /* x-axis/pitch */  case 'p': case 'P': case 'v': case 'V':
      /* y-axis/yaw   */  case 'y': case 'Y': case 't': case 'T':
      /* z-axis/roll  */  case 'r': case 'R': case 'w': case 'W':
         yMAP_god_key (a_minor);
         break;
      case '\\'     :
         DEBUG_USER   yLOG_note    ("entering menu sub-mode");
         yMODE_enter  (SMOD_MENUS   );
         /*> yvikeys_menu_start  ();                                                  <*/
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return a_minor;
         break;
      case ',':
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return a_minor;
         break;
      case ':' :
         ySRC_start   (":");
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         rc = 'a';
         break;
      case ';' :
         ySRC_start   (";");
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         rc = 'a';
         break;
      }
   }
   /*---(buffer/area)--------------------*/
   if (a_major == ',') {
      switch (a_minor) {
      case 'p':
         yMODE_enter  (MODE_PROGRESS);
         /*> TICK_draw ();                                                            <*/
         break;
      }
   }
   /*---(complete)------------------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 0;
}

