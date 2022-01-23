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
    *>    x_visu = myMAP.v_visus + n;                                                                              <* 
    *> } else {                                                                                              <* 
    *>    x_visu = myMAP.v_curr;                                                                                   <* 
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
ymap_visu_line          (tVISU *a_visu, char a_size, short a_wide, char *a_list)
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
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   /*---(fix sizes)----------------------*/
   if (strchr ("hg", a_size) != NULL)  a_size = 'l';
   if (a_size == '-')  return -10;
   /*---(prefix)-------------------------*/
   switch (a_size) {
   case 'u'  : case 't'  :
      sprintf (x_pre, "vis %c%c", a_visu->abbr, a_visu->modded);
      break;
   default   :
      sprintf (x_pre, "visual  %c %c%c", a_visu->abbr, a_visu->active, a_visu->modded);
      break;
   }
   /*---(middle)-------------------------*/
   strlpadn (a_visu->u_all , b, '.', '>', 2);
   sprintf (u, "%su", b);
   strlpadn (a_visu->x_beg , b, '.', '>', 4);
   strlpadn (a_visu->x_end , e, '.', '>', 4);
   strlpadn (a_visu->x_root, r, '.', '>', 4);
   sprintf (x, "%c %sb %se %sr", a_visu->x_lock, b, e, r);
   strlpadn (a_visu->y_beg , b, '.', '>', 4);
   strlpadn (a_visu->y_end , e, '.', '>', 4);
   strlpadn (a_visu->y_root, r, '.', '>', 4);
   sprintf (y, "%c %sb %se %sr", a_visu->y_lock, b, e, r);
   strlpadn (a_visu->z_beg , b, '.', '>', 4);
   strlpadn (a_visu->z_end , e, '.', '>', 4);
   strlpadn (a_visu->z_root, r, '.', '>', 4);
   sprintf (z, "%c %sb %se %sr", a_visu->z_lock, b, e, r);
   sprintf (t, "%dx%d", a_visu->x_end -  a_visu->x_beg + 1, a_visu->y_end -  a_visu->y_beg + 1);
   strlpad  (a_visu->b_label, b, '.', '<', 7);
   strlpad  (a_visu->e_label, e, '.', '<', 7);
   /*---(concatenate)--------------------*/
   switch (a_size) {
   case 'u'  :
      sprintf (a_list, "%s   ´", x_pre);
      break;
   case 't'  :
      sprintf (a_list, "%s %-5.5s %-5.5s ´", x_pre, b, e);
      break;
   case 's'  :
      sprintf (a_list, "%s ´ %-7.7s %-7.7s %-8.8s´", x_pre, b, e, t);
      break;
   case 'm'  :
      sprintf (a_list, "%s ´ %-13.13s ´ %-13.13s ´ %-7.7s %-7.7s %-6.6s´", x_pre, x, y, b, e, t);
      break;
   case '+'  :  /* standard unit testing format */
      sprintf (a_list, "%s ´ %s ´ %s ´ %s ´ %-7.7s %-7.7s %s", x_pre, u, x, y, b, e, t);
      break;
   default   :
      sprintf (a_list, "%s ´ %s ´ %s ´ %s ´ %s ´ %-7.7s %-7.7s %-10.10s  ´", x_pre, u, x, y, z, b, e, t);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMAP_visu_status        (char a_size, short a_wide, char *a_list)
{
   ymap_visu_line (myMAP.v_curr, a_size, a_wide, a_list);
   return 0;
}

char         /*-> list history -----------------------[ leaf   [ge.740.042.20]*/ /*-[03.0000.103.!]-*/ /*-[--.---.---.--]-*/
ymap_visu_dump          (FILE *f)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_RECD]  = "";
   /*---(print)--------------------------*/
   fprintf (f, "#! parsing åÏ·ÏÏ···Ï-····Ï·Ï---··Ï---··Ï---····Ï·Ï---··Ï---··Ï---····Ï·Ï---··Ï---··Ï---····Ï------·Ï------·Ï----------··æ\n");
   fprintf (f, "#! titles  åv·am···un····x·beg···end···root····y·beg···end···root····z·beg···end···root····beg·····end·····size·········æ\n");
   for (i = 0; i < myMAP.v_nvisu; ++i) {
      if (i % 25 == 0)  fprintf (f, "\n#--- ´ uni ´ x-axis------------- ´ y-axis------------- ´ z-axis------------- ´ beg---- end---- size------- ´\n");
      if (i %  5 == 0)  fprintf (f, "\n");
      ymap_visu_line (myMAP.v_visus + i, 'l', 0, t);
      fprintf (f, "%s\n", t + 8);
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      mundo reporting                         ----===*/
/*====================------------------------------------====================*/
static void  o___MUNDO___________o () { return; }

char*
yMAP_mundo_detail       (int n)
{
   int         c           =    0;
   tHIST      *x_curr      = NULL;
   char        s           [LEN_HUND]  = "";
   char        t           [LEN_HUND]  = "";
   char        r           [LEN_LABEL] = "";
   if      (n == -1)  n  = myMAP.h_index;
   else if (n <  0)   return "n/a";
   x_curr = myMAP.h_head;
   while (x_curr != NULL) {
      if (c == n) {
         sprintf (s, "%2då%-.30sæ", strlen (x_curr->before), x_curr->before);
         sprintf (t, "%2då%-.30sæ", strlen (x_curr->after ), x_curr->after );
         strlcpy (r, ymap_mundo_action (x_curr->mode, x_curr->act), LEN_LABEL);
         sprintf (myMAP.g_print, "%-3d %-3d %c %c %-10.10s %-6.6s %-34.34s  %s",
               myMAP.h_count, c, x_curr->mode, x_curr->act, r, x_curr->label, s, t);
         return myMAP.g_print;
      }
      x_curr = x_curr->h_next;
      ++c;
   }
   return "n/a";
}

char         /*-> list history -----------------------[ leaf   [ge.740.042.20]*/ /*-[03.0000.103.!]-*/ /*-[--.---.---.--]-*/
ymap_mundo_dump         (FILE *f)
{
   /*---(locals)-----------+-----------+-*/
   int         c           = 0;
   tHIST      *x_curr      = NULL;
   /*---(print)--------------------------*/
   fprintf (f, "s_count = %d\n" , myMAP.h_count);
   fprintf (f, "s_index = %d\n" , myMAP.h_index);
   x_curr = myMAP.h_head;
   while (x_curr != NULL) {
      if (c % 5 == 0)  fprintf (f, "\n-ref- § m § a § ---action--- § --label--- § ---before----------------------------------------- § ---after------------------------------------------ §\n");
      fprintf (f, "%-5d § %c § %c § %-12.12s § %-10.10s § %-50.50s § %-50.50s §\n",
            c, x_curr->mode, x_curr->act,
            ymap_mundo_action (x_curr->mode, x_curr->act),
            x_curr->label, x_curr->before, x_curr->after);
      ++c;
      x_curr = x_curr->h_next;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ymap__map_dump          (FILE *f, char *a_axis)
{
   tyMAP      *x_map       = NULL;
   tGRID      *x_grid      = NULL;
   ymap_pick_map (a_axis, &x_map, &x_grid);
   fprintf (f, "\n");
   fprintf (f, "axis     %c\n", a_axis);
   fprintf (f, "load     %s\n", ymap_print (a_axis));
   fprintf (f, "pos      L %2di  §  U %4da %4db %4dc %4de %4dt %4dl %4dx  §  G %4db %4dc %4de\n",
         x_map->inc,
         x_map->uavail, x_map->ubeg, x_map->ucur, x_map->uend, x_map->utend, x_map->ulen, x_map->umax,
         x_map->gbeg, x_map->gcur, x_map->gend);
   fprintf (f, "grid     %4dg %4da %4dl § %4dp %4du § %4db %4dc %4de § %4du %4dn § %4dl %4da %4dg\n",
         x_map->gmin , x_map->gamin, x_map->glmin, x_map->gprev, x_map->gpuse,
         x_map->gbeg , x_map->gcur , x_map->gend ,
         x_map->gnuse, x_map->gnext, x_map->glmax, x_map->gamax, x_map->gmax );
   ymap_display_units (x_map, myMAP.g_print);
   fprintf (f, "units    %3då%sæ\n", strlen (myMAP.g_print), myMAP.g_print);
   ymap_display_map  (x_map, myMAP.g_print);
   fprintf (f, "map      %3då%sæ\n", strlen (myMAP.g_print), myMAP.g_print);
   return 0;
}

char
ymap_map_dump           (FILE *f)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(univers)------------------------*/
   ymap__map_dump (f, YMAP_UNIV);
   ymap__map_dump (f, YMAP_XAXIS);
   ymap__map_dump (f, YMAP_YAXIS);
   ymap__map_dump (f, YMAP_ZAXIS);
   ymap__map_dump (f, YMAP_WHEN);
   /*---(complete)-----------------------*/
   DEBUG_YMODE   yLOG_exit    (__FUNCTION__);
   return 0;
}




