/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"


/*> if      (strcmp (a_question, "pos"            )   == 0) {                                                                                               <* 
 *>    rc = ymap_pick_map (a_index, &x_map, NULL);                                                                                                          <* 
 *>    if (rc < 0)  snprintf (unit_answer, LEN_FULL, "MAP pos      (·) : L  ·i  §  U    ·a    ·b    ·c    ·e    ·t    ·l    ·x  §  G    ·b    ·c    ·e");   <* 
 *>    else         snprintf (unit_answer, LEN_FULL, "MAP pos      (%c) : L %2di  §  U %4da %4db %4dc %4de %4dt %4dl %4dx  §  G %4db %4dc %4de",            <* 
 *>          x_map->axis, x_map->inc,                                                                                                                       <* 
 *>          x_map->uavail, x_map->ubeg, x_map->ucur, x_map->uend, x_map->utend, x_map->ulen, x_map->umax,                                                  <* 
 *>          x_map->gbeg, x_map->gcur, x_map->gend);                                                                                                        <* 
 *> }                                                                                                                                                       <* 
 *> else if (strcmp (a_question, "grid"           )   == 0) {                                                                                               <* 
 *>    rc = ymap_pick_map (a_index, &x_map, NULL);                                                                                                          <* 
 *>    if (rc < 0)  snprintf (unit_answer, LEN_FULL, "MAP grid     (·) :    ·g    ·a    ·l §    ·p §    ·b    ·c    ·e §    ·n §    ·l    ·a    ·g");       <* 
 *>    else         snprintf (unit_answer, LEN_FULL, "MAP grid     (%c) : %4dg %4da %4dl § %4dp § %4db %4dc %4de § %4dn § %4dl %4da %4dg",                  <* 
 *>          x_map->axis,                                                                                                                                   <* 
 *>          x_map->gmin , x_map->gamin, x_map->glmin, x_map->gprev,                                                                                        <* 
 *>          x_map->gbeg , x_map->gcur , x_map->gend ,                                                                                                      <* 
 *>          x_map->gnext, x_map->glmax, x_map->gamax, x_map->gmax );                                                                                       <* 
 *> }                                                                                                                                                       <* 
 *> else if (strcmp (a_question, "current"        )   == 0) {                                                                                               <* 
 *>    yMAP_current (t, &u, &x, &y, &z);                                                                                                                    <* 
 *>    snprintf (unit_answer, LEN_FULL, "MAP current      : %-12.12s  %4du %4dx %4dy %4dz", t, u, x, y, z);                                                 <* 
 *> }                                                                                                                                                       <*/


char
yMAP_current_status     (char a_size, short a_wide, char *a_list)
{
   char        t           [LEN_LABEL] = "";
   char        tt          [LEN_LABEL] = "";
   ushort      u, x, y, z;
   uchar       uu          [LEN_LABEL] = "";
   uchar       xx          [LEN_LABEL] = "";
   uchar       yy          [LEN_LABEL] = "";
   uchar       zz          [LEN_LABEL] = "";
   uchar       x_pre       [LEN_LABEL] = "";
   uchar       x_grid      [LEN_HUND]  = "";
   uchar       x_unit      [LEN_HUND]  = "";
   snprintf (x_pre , LEN_LABEL, " current");
   yMAP_current (t, &u, &x, &y, &z);
   strlpad  (t, tt, '.', '<', 12);
   strlpadn (u, uu, '.', '>', 4);
   strlpadn (x, xx, '.', '>', 4);
   strlpadn (y, yy, '.', '>', 4);
   strlpadn (z, zz, '.', '>', 4);
   snprintf (x_grid, LEN_HUND, "§ G %su %sx %sy %sz", uu, xx, yy, zz);
   yMAP_current_unit (&u, &x, &y, &z);
   strlpadn (u, uu, '.', '>', 4);
   strlpadn (x, xx, '.', '>', 4);
   strlpadn (y, yy, '.', '>', 4);
   strlpadn (z, zz, '.', '>', 4);
   snprintf (x_unit, LEN_HUND, "§ U %su %sx %sy %sz", uu, xx, yy, zz);
   snprintf (a_list, LEN_RECD, "%s %s %s § %s ´", x_pre, x_grid, x_unit, tt);
   return 0;
}

char
yMAP_unit_status        (char a_size, short a_wide, char *a_list)
{
}

char
yMAP_grid_status        (char a_size, short a_wide, char *a_list)
{
}

char
ymap__visu_entry      (char a_abbr, char *a_entry)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                              <* 
    *> char        rce         =  -10;                                                                       <* 
    *> char        rc          =    0;                                                                       <* 
    *> int         n           =    0;                                                                       <* 
    *> tVISU      *x_visu      = NULL;                                                                       <* 
    *> char        x_size      [LEN_LABEL] = "n/a";                                                          <* 
    *> char        x_root      [LEN_LABEL] = "n/a";                                                          <* 
    *> char        x_beg       [LEN_LABEL] = "n/a";                                                          <* 
    *> char        x_end       [LEN_LABEL] = "n/a";                                                          <* 
    *> /+---(defense)------------------------+/                                                              <* 
    *> --rce; if (a_entry == NULL)   return rce;                                                             <* 
    *> strlcpy (a_entry, "", LEN_RECD);                                                                      <* 
    *> --rce;  if (a_abbr != ':') {                                                                          <* 
    *>    n = ymap_visu_index (a_abbr);                                                                      <* 
    *>    if (n  < 0)   return rce;                                                                          <* 
    *>    x_visu = s_visus + n;                                                                              <* 
    *> } else {                                                                                              <* 
    *>    x_visu = s_curr;                                                                                   <* 
    *> }                                                                                                     <* 
    *> /+---(fill)---------------------------+/                                                              <* 
    *> if (x_visu->active == VISU_YES) {                                                                     <* 
    *>    yvikeys_map_addresser (x_root, x_visu->b_all, x_visu->x_root, x_visu->y_root, x_visu->z_all);      <* 
    *>    --rce;  if (rc < 0) return rce;                                                                    <* 
    *>    sprintf (x_size, "%dx%d", x_visu->x_end - x_visu->x_beg + 1, x_visu->y_end - x_visu->y_beg + 1);   <* 
    *>    strlcpy (x_beg, x_visu->b_label, LEN_LABEL);                                                       <* 
    *>    strlcpy (x_end, x_visu->e_label, LEN_LABEL);                                                       <* 
    *> }                                                                                                     <* 
    *> sprintf (a_entry, "%c %c %-10.10s %-10.10s %-10.10s %-10.10s %c %c %c",                               <* 
    *>       a_abbr, x_visu->active,                                                                         <* 
    *>       x_beg, x_end, x_size, x_root,                                                                   <* 
    *>       x_visu->x_lock, x_visu->y_lock, x_visu->source);                                                <* 
    *> /+---(complete)-----------------------+/                                                              <* 
    *> if (x_visu->active == VISU_NOT)  return 0;                                                            <* 
    *> return 1;                                                                                             <*/
}

char
yMAP_visu_status        (char a_size, short a_wide, char *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_pre       [LEN_DESC]  = "";
   uchar       b           [LEN_LABEL] = "";
   uchar       e           [LEN_LABEL] = "";
   uchar       r           [LEN_LABEL] = "";
   uchar       u           [LEN_DESC]  = "";
   uchar       x           [LEN_DESC]  = "";
   uchar       y           [LEN_DESC]  = "";
   uchar       z           [LEN_DESC]  = "";
   uchar       t           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_MAP    yLOG_enter   (__FUNCTION__);
   /*---(fix sizes)----------------------*/
   if (strchr ("hg", a_size) != NULL)  a_size = 'l';
   if (a_size == '-')  return -10;
   /*---(prefix)-------------------------*/
   switch (a_size) {
   case 'u'  : case 't'  :
      sprintf (x_pre, "vis %c%c", s_curr->abbr, s_curr->modded);
      break;
   default   :
      sprintf (x_pre, "visual  %c %c%c", s_curr->abbr, s_curr->active, s_curr->modded);
      break;
   }
   /*---(middle)-------------------------*/
   strlpadn (s_curr->u_all , b, '.', '>', 2);
   sprintf (u, "%su", b);
   strlpadn (s_curr->x_beg , b, '.', '>', 4);
   strlpadn (s_curr->x_end , e, '.', '>', 4);
   strlpadn (s_curr->x_root, r, '.', '>', 4);
   sprintf (x, "%c %sb %se %sr", s_curr->x_lock, b, e, r);
   strlpadn (s_curr->y_beg , b, '.', '>', 4);
   strlpadn (s_curr->y_end , e, '.', '>', 4);
   strlpadn (s_curr->y_root, r, '.', '>', 4);
   sprintf (y, "%c %sb %se %sr", s_curr->y_lock, b, e, r);
   strlpadn (s_curr->z_beg , b, '.', '>', 4);
   strlpadn (s_curr->z_end , e, '.', '>', 4);
   sprintf (z, "%c %sb %se"    , s_curr->z_lock, b, e);
   sprintf (t, "%dx%d", s_curr->x_end -  s_curr->x_beg + 1, s_curr->y_end -  s_curr->y_beg + 1);
   strlpad  (s_curr->b_label, b, '.', '<', 7);
   strlpad  (s_curr->e_label, e, '.', '<', 7);
   /*---(concatenate)--------------------*/
   switch (a_size) {
   case 'u'  :
      sprintf (a_list, "%s   ´", x_pre);
      break;
   case 't'  :
      sprintf (a_list, "%s %-5.5s %-5.5s ´", x_pre, b, e);
      break;
   case 's'  :
      sprintf (a_list, "%s § %-7.7s %-7.7s %-8.8s´", x_pre, b, e, t);
      break;
   case 'm'  :
      sprintf (a_list, "%s § %-13.13s § %-13.13s § %-7.7s %-7.7s %-6.6s´", x_pre, x, y, b, e, t);
      break;
   default   :
      sprintf (a_list, "%s § %s § %s § %s § %s § %-7.7s %-7.7s %-10.10s  ´", x_pre, u, x, y, z, b, e, t);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_MAP    yLOG_exit    (__FUNCTION__);
   return 0;
}



