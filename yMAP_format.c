/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMAP.h"
#include    "yMAP_priv.h"


static char  s_hist = YMAP_BEG;

#define    MAX_FORMATS      100
static const struct {
   uchar       type;
   uchar       abbr;
   uchar       desc        [LEN_DESC];
} s_formats [MAX_FORMATS] = {
   /*---(widths)-----------------------------*/
   { YMAP_WIDTH    , 'M' , "base minimum"     },
   { YMAP_WIDTH    , 'm' , "minimal"          },
   { YMAP_WIDTH    , 'h' , "less by one"      },
   { YMAP_WIDTH    , 'H' , "less by five"     },
   { YMAP_WIDTH    , 'l' , "more by one"      },
   { YMAP_WIDTH    , 'L' , "more by five"     },
   { YMAP_WIDTH    , 'n' , "normal"           },
   { YMAP_WIDTH    , 'N' , "normal+"          },
   { YMAP_WIDTH    , 'w' , "wide"             },
   { YMAP_WIDTH    , 'W' , "widest"           },
   /*---(heights)----------------------------*/
   { YMAP_HEIGHT   , 'J' , "smallest"         },
   { YMAP_HEIGHT   , 'j' , "less by one"      },
   { YMAP_HEIGHT   , 'k' , "more by one"      },
   { YMAP_HEIGHT   , 'K' , "largest"          },
   /*---(alignments)-------------------------*/
   { YMAP_ALIGN    , '<' , "left"             },
   { YMAP_ALIGN    , '|' , "center"           },
   { YMAP_ALIGN    , '>' , "right"            },
   { YMAP_ALIGN    , '[' , "left-bracketed"   },
   { YMAP_ALIGN    , '^' , "center-bracketed" },
   { YMAP_ALIGN    , ']' , "right-bracketed"  },
   { YMAP_ALIGN    , '{' , "left-bracketed+"  },
   { YMAP_ALIGN    , '}' , "right-bracketed+" },
   { YMAP_ALIGN    , ':' , "left-colon"       },
   { YMAP_ALIGN    , '\'', "right-colon"      },
   /*---(numbers)----------------------------*/
   { YMAP_FORMAT   , 'i' , "integer"          },
   { YMAP_FORMAT   , 'I' , "int-indented"     },
   { YMAP_FORMAT   , 'f' , "float"            },
   { YMAP_FORMAT   , 'e' , "exponential"      },
   { YMAP_FORMAT   , 'E' , "exp-spaced"       },
   /*---(commas)-----------------------------*/
   { YMAP_FORMAT   , ',' , "comma"            },
   { YMAP_FORMAT   , 'c' , "comma"            },
   { YMAP_FORMAT   , 'C' , "comma+"           },
   { YMAP_FORMAT   , 'a' , "accounting"       },
   { YMAP_FORMAT   , 'A' , "accounting+"      },
   { YMAP_FORMAT   , '$' , "dollar"           },
   { YMAP_FORMAT   , 's' , "signed"           },
   { YMAP_FORMAT   , 'S' , "signed+"          },
   { YMAP_FORMAT   , '#' , "technical"        },
   { YMAP_FORMAT   , 'p' , "point"            },
   { YMAP_FORMAT   , 'P' , "point+"           },
   /*---(bases)------------------------------*/
   { YMAP_FORMAT   , 'r' , "roman lower"      },
   { YMAP_FORMAT   , 'R' , "roman upper"      },
   { YMAP_FORMAT   , 'o' , "octal"            },
   { YMAP_FORMAT   , 'O' , "octal-spaced"     },
   { YMAP_FORMAT   , 'x' , "hex"              },
   { YMAP_FORMAT   , 'X' , "hex-spaced"       },
   { YMAP_FORMAT   , 'b' , "binary"           },
   { YMAP_FORMAT   , 'B' , "binary-spaced"    },
   { YMAP_FORMAT   , 'z' , "base62"           },
   { YMAP_FORMAT   , 'Z' , "base62-spaced"    },
   /*---(datetimes)--------------------------*/
   { YMAP_FORMAT   , 't' , "time"             },
   { YMAP_FORMAT   , 'T' , "timestamp"        },
   { YMAP_FORMAT   , 'd' , "date"             },
   { YMAP_FORMAT   , 'D' , "full date"        },
   /*---(string fillers)---------------------*/
   { YMAP_FORMAT   , '!' , "empty"            },
   { YMAP_FORMAT   , '-' , "dashes"           },
   { YMAP_FORMAT   , '=' , "equals"           },
   { YMAP_FORMAT   , '_' , "underlines"       },
   { YMAP_FORMAT   , '.' , "dots"             },
   { YMAP_FORMAT   , '+' , "dots and pluses"  },
   { YMAP_FORMAT   , '@' , "dots and bigs"    },
   { YMAP_FORMAT   , '~' , "ruler"            },
   /*---(decimals)---------------------------*/
   { YMAP_DECIMALS , '0' , "integer"          },
   { YMAP_DECIMALS , '1' , "exactly one"      },
   { YMAP_DECIMALS , '2' , "exactly two"      },
   { YMAP_DECIMALS , '3' , "exactly three"    },
   { YMAP_DECIMALS , '4' , "exactly four"     },
   { YMAP_DECIMALS , '5' , "exactly five"     },
   { YMAP_DECIMALS , '6' , "exactly six"      },
   { YMAP_DECIMALS , '7' , "exactly seven"    },
   { YMAP_DECIMALS , '8' , "exactly eight"    },
   { YMAP_DECIMALS , '9' , "exactly nine"     },
   /*---(multiples)--------------------------*/
   { YMAP_MULTIPLE , '?' , "all to defaults"  },
   { YMAP_MULTIPLE , 'G' , "real with 6 dec"  },
   { YMAP_MULTIPLE , 'g' , "real with 3 dec"  },
   /*---(done)-------------------------------*/
   { 0             ,  0  , "end-of-list"      },
};

#define    MAX_UNITS         30
static const struct {
   uchar       type;
   uchar       abbr;
   uchar       desc        [LEN_DESC];
} s_units [MAX_UNITS] = {
   /*---(units of measure)-------------------*/
   { YMAP_UNITS    , '-' , "none"             },
   { YMAP_UNITS    , 'Y' , "yotta +24"        },
   { YMAP_UNITS    , 'Z' , "zetta +21"        },
   { YMAP_UNITS    , 'E' , "exa   +18"        },
   { YMAP_UNITS    , 'P' , "peta  +15"        },
   { YMAP_UNITS    , 'T' , "tera  +12"        },
   { YMAP_UNITS    , 'G' , "giga  +9"         },
   { YMAP_UNITS    , 'M' , "mega  +6"         },
   { YMAP_UNITS    , 'K' , "kilo  +3"         },
   { YMAP_UNITS    , 'H' , "hecto +2"         },
   { YMAP_UNITS    , 'D' , "deca  +1"         },
   { YMAP_UNITS    , '.' , "norm  +0"         },
   { YMAP_UNITS    , 'd' , "deci  -1"         },
   { YMAP_UNITS    , 'c' , "centa -2"         },
   { YMAP_UNITS    , 'm' , "mili  -3"         },
   { YMAP_UNITS    , 'u' , "micro -6"         },
   { YMAP_UNITS    , 'n' , "nano  -9"         },
   { YMAP_UNITS    , 'p' , "pico  -12"        },
   { YMAP_UNITS    , 'f' , "femto -15"        },
   { YMAP_UNITS    , 'a' , "atto  -18"        },
   { YMAP_UNITS    , 'z' , "zepto -21"        },
   { YMAP_UNITS    , 'y' , "yocto -24"        },
   /*---(special)----------------------------*/
   { YMAP_UNITS    , '3' , "smallest"         },  /* integer of 1-3 places   */
   /*---(done)-------------------------------*/
   { 0             ,  0  , "end-of-list"      },
};

char
ymap__format_abbr       (char a_abbr)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_abbr == 0)   return rce;
   for (i = 0; i < MAX_FORMATS; ++i) {
      if (s_formats [i].abbr == 0)       break;
      if (s_formats [i].abbr != a_abbr)  continue;
      return i;
   }
   --rce;  return rce;
}

char
ymap__format_units      (char a_abbr)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_abbr == 0)   return rce;
   for (i = 0; i < MAX_UNITS; ++i) {
      if (s_units [i].abbr == 0)       break;
      if (s_units [i].abbr != a_abbr)  continue;
      return i;
   }
   --rce;  return rce;
}

char
yMAP_formatter          (void *a_formatter)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (XMOD_FORMAT)) {
      DEBUG_YMAP    yLOG_note    ("init must complete before config");
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pointer)------------------------*/
   DEBUG_YMAP   yLOG_point   ("formatter" , a_formatter);
   --rce;  if (a_formatter == NULL) {
      DEBUG_YMAP    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   myMAP.e_format  = a_formatter;
   /*---(update status)------------------*/
   yMODE_conf_set   (XMOD_FORMAT, '1');
   yMODE_conf_set   (XMOD_UNITS , '1');
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymap__format_range      (uchar a_type, uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   ushort      u, x, y, z;
   int         n           =    0;
   int         c           =    0;
   ushort      x_top, x_left, x_deep;
   char        x_label     [LEN_LABEL] = "";
   uchar       r           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMAP    yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP    yLOG_char    ("a_type"    , a_type);
   DEBUG_YMAP    yLOG_char    ("a_abbr"    , a_abbr);
   DEBUG_YMAP    yLOG_point   ("e_format"  , myMAP.e_format);
   --rce;  if (myMAP.e_format == NULL) {
      DEBUG_YMAP    yLOG_exitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(get first)----------------------*/
   rc = yMAP_visu_first (&u, &x, &y, &z);
   DEBUG_YMAP    yLOG_complex ("first"     , "%4dr, %4du, %4dx, %4dy, %4dz", rc, u, x, y, z);
   x_top    = y;
   x_left   = x;
   x_deep   = z;
   /*---(process range)------------------*/
   while (rc >= 0) {
      ++n;
      rc = ymap_addresser_strict   (x_label, u, x, y, z);
      /*---(filter)----------------------*/
      switch (a_type) {
      case YMAP_WIDTH    : case YMAP_WEXACT   :
         DEBUG_YMAP    yLOG_note    ("width change");
         rc = myMAP.e_format (a_type, a_abbr, u, x, y, z, &r);
         if (rc > 0 && y == x_top && rc != r)  {
            yMAP_mundo_width    (s_hist, x_label, rc, r);
            ymap_wide (x, r);
            s_hist = YMAP_ADD;
         }
         break;
      case YMAP_HEIGHT   : case YMAP_HEXACT   :
         DEBUG_YMAP    yLOG_note    ("height change");
         rc = myMAP.e_format (a_type, a_abbr, u, x, y, z, &r);
         if (rc > 0 && x == x_left && rc != r)  {
            yMAP_mundo_height   (s_hist, x_label, rc, r);
            ymap_tall (y, r);
            s_hist = YMAP_ADD;
         }
         break;
      case YMAP_DEPTH    : case YMAP_DEXACT   :
         DEBUG_YMAP    yLOG_note    ("found a frontmost item");
         rc = myMAP.e_format (a_type, a_abbr, u, x, y, z, &r);
         if (rc > 0 && z == x_deep && rc != r)  {
            yMAP_mundo_depth    (s_hist, x_label, rc, r);
            ymap_deep (z, r);
            s_hist = YMAP_ADD;
         }
         break;
      case YMAP_FORMAT   :
         rc = myMAP.e_format (a_type, a_abbr, u, x, y, z, NULL);
         if (rc > 0) {
            yMAP_mundo_format   (s_hist, x_label, rc, a_abbr);
            s_hist = YMAP_ADD;
         }
         break;
      case YMAP_ALIGN    :
         rc = myMAP.e_format (a_type, a_abbr, u, x, y, z, NULL);
         if (rc > 0) {
            yMAP_mundo_align    (s_hist, x_label, rc, a_abbr);
            s_hist = YMAP_ADD;
         }
         break;
      case YMAP_DECIMALS :
         rc = myMAP.e_format (a_type, a_abbr, u, x, y, z, NULL);
         if (rc > 0) {
            yMAP_mundo_decimals (s_hist, x_label, rc, a_abbr);
            s_hist = YMAP_ADD;
         }
         break;
      case YMAP_UNITS    :
         rc = myMAP.e_format (a_type, a_abbr, u, x, y, z, NULL);
         if (rc > 0) {
            yMAP_mundo_units    (s_hist, x_label, rc, a_abbr);
            s_hist = YMAP_ADD;
         }
         break;
      }
      /*---(get next)--------------------*/
      rc      = yMAP_visu_next  (&u, &x, &y, &z);
      DEBUG_YMAP    yLOG_complex ("next"      , "%4dr, %4du, %4dx, %4dy, %4dz", rc, u, x, y, z);
      /*---(done)------------------------*/
   }
   DEBUG_YMAP    yLOG_value  ("n"         , n);
   DEBUG_YMAP    yLOG_value  ("c"         , c);
   /*---(complete)-----------------------*/
   DEBUG_YMAP    yLOG_exit   (__FUNCTION__);
   return 0;
}

char         /*-> change the col width ---------------[ ------ [gc.320.312.31]*/ /*-[00.0000.404.5]-*/ /*-[--.---.---.--]-*/
ymap__multisize      (char *a_label, uchar a_type, uchar a_size, uchar a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   ushort      uo, xo, yo, zo;
   ushort      u, x, y, z;
   uchar       x_type      =    0;
   ushort      ua, xb, xe, yb, ye, zb, ze;
   char        x_live      =  '-';
   char        r           =  '-';
   /*---(header)-------------------------*/
   DEBUG_YMAP   yLOG_enter   (__FUNCTION__);
   DEBUG_YMAP   yLOG_complex ("args"      , "%-10.10p, %c, %2ds, %2dc", a_label, a_type, a_size, a_count);
   /*---(save current)-------------------*/
   rc = yMAP_current  (NULL, &uo, &xo, &yo, &zo);
   DEBUG_YMAP   yLOG_complex ("current"   , "%4d, %4du, %4dx, %4dy, %4dz", rc, u, x, y, z);
   /*---(defense)------------------------*/
   rc = ymap_locator_strict   (a_label, &u, &x, &y, &z);
   DEBUG_YMAP   yLOG_value   ("locator"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMAP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMAP   yLOG_complex ("coord"     , "%s, %2du, %4dx, %4dy, %4dz", a_label, u, x, y, z);
   /*---(prepare)------------------------*/
   if (a_count >  0)  --a_count;
   DEBUG_YMAP   yLOG_value   ("a_count"   , a_count);
   if (a_size == '-') {
      switch (a_type) {
      case YMAP_XAXIS : a_size = 8; break;
      case YMAP_YAXIS : a_size = 1; break;
      case YMAP_ZAXIS : a_size = 1; break;
      }
   }
   DEBUG_YMAP   yLOG_value   ("a_size"    , a_size);
   /*---(get range)----------------------*/
   x_live = yMAP_visu_islive ();
   yMAP_visu_range (&ua, &xb, &xe, &yb, &ye, &zb, &ze, &r);
   /*---(set range)----------------------*/
   switch (a_type) {
   case YMAP_XAXIS :
      ymap_visu_exact (u, x, x + a_count, 0, g_ymap.gmax, 0, g_zmap.gmax, r);
      x_type = YMAP_WEXACT;
      break;
   case YMAP_YAXIS :
      ymap_visu_exact (u, 0, g_xmap.gmax, y, y + a_count, 0, g_zmap.gmax, r);
      x_type = YMAP_HEXACT;
      break;
   case YMAP_ZAXIS :
      ymap_visu_exact (u, 0, g_xmap.gmax, 0, g_ymap.gmax, z, z + a_count, r);
      x_type = YMAP_DEXACT;
      break;
   }
   /*---(handle)-------------------------*/
   rc = ymap__format_range (x_type, a_size);
   DEBUG_YMAP   yLOG_value   ("format"    , a_count);
   /*---(put range back)-----------------*/
   if (x_live) ymap_visu_exact (ua, xb, xe, yb, ye, zb, ze, r);
   else        { ymap_visu_clear ();  yMAP_jump (uo, xo, yo, zo); }
   /*---(complete)-----------------------*/
   DEBUG_YMAP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yMAP_multi_wide         (char *a_label, uchar a_size, uchar a_count) { s_hist = YMAP_BEG; return ymap__multisize (a_label, YMAP_XAXIS, a_size, a_count); }
char yMAP_multi_tall         (char *a_label, uchar a_size, uchar a_count) { s_hist = YMAP_BEG; return ymap__multisize (a_label, YMAP_YAXIS, a_size, a_count); }
char yMAP_multi_deep         (char *a_label, uchar a_size, uchar a_count) { s_hist = YMAP_BEG; return ymap__multisize (a_label, YMAP_ZAXIS, a_size, a_count); }

char
ymap_multi_wide_def     (char *a_label, uchar a_count)
{
   char        x_label     [LEN_LABEL] = "";
   if (a_label == NULL || a_label [0] == '\0')  yMAP_current (x_label, NULL, NULL, NULL, NULL);
   else                                        strlcpy (x_label, a_label, LEN_LABEL);
   yMAP_multi_wide (x_label, '-', a_count);
   return 0;
}

char
ymap_multi_wide_reset   (char *a_label)
{
   ushort      u           =    0;
   char        x_label     [LEN_LABEL] = "";
   if (a_label == NULL || a_label [0] == '\0')  yMAP_current (NULL, &u, NULL, NULL, NULL);
   else if (strlen (a_label) == 1)              u = INDEX_tab (a_label [0]);
   else                                         ymap_locator_strict (x_label, &u, NULL, NULL, NULL);
   ymap_addresser_strict (x_label, u, 0, 0, 0);
   yMAP_multi_wide (x_label, '-', g_xmap.gmax);
   return 0;
}

char
ymap_multi_tall_def     (char *a_label, uchar a_count)
{
   char        x_label     [LEN_LABEL] = "";
   if (a_label == NULL || a_label [0] == '\0')  yMAP_current (x_label, NULL, NULL, NULL, NULL);
   else                                        strlcpy (x_label, a_label, LEN_LABEL);
   yMAP_multi_tall (x_label, '-', a_count);
   return 0;
}

char
ymap_multi_tall_reset   (char *a_label)
{
   ushort      u           =    0;
   char        x_label     [LEN_LABEL] = "";
   if (a_label == NULL || a_label [0] == '\0')  yMAP_current (NULL, &u, NULL, NULL, NULL);
   else if (strlen (a_label) == 1)              u = INDEX_tab (a_label [0]);
   else                                         ymap_locator_strict (x_label, &u, NULL, NULL, NULL);
   ymap_addresser_strict (x_label, u, 0, 0, 0);
   yMAP_multi_tall (x_label, '-', g_ymap.gmax);
   return 0;
}

char
ymap_multi_deep_def     (char *a_label, uchar a_count)
{
   char        x_label     [LEN_LABEL] = "";
   if (a_label == NULL || a_label [0] == '\0')  yMAP_current (x_label, NULL, NULL, NULL, NULL);
   else                                        strlcpy (x_label, a_label, LEN_LABEL);
   yMAP_multi_deep (x_label, '-', a_count);
   return 0;
}

char
ymap_multi_deep_reset   (char *a_label)
{
   ushort      u           =    0;
   char        x_label     [LEN_LABEL] = "";
   if (a_label == NULL || a_label [0] == '\0')  yMAP_current (NULL, &u, NULL, NULL, NULL);
   else if (strlen (a_label) == 1)              u = INDEX_tab (a_label [0]);
   else                                         ymap_locator_strict (x_label, &u, NULL, NULL, NULL);
   ymap_addresser_strict (x_label, u, 0, 0, 0);
   yMAP_multi_deep (x_label, '-', g_zmap.gmax);
   return 0;
}

char
ymap_format_prepper     (void)
{
   s_hist = YMAP_BEG;
   return 0;
}

char         /*-> keys for units micro-mode ----------[ ------ [gc.MT0.202.C7]*/ /*-[01.0000.112.!]-*/ /*-[--.---.---.--]-*/
ymap_format_xmode       (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   char        n           =    0;
   ushort      uo, xo, yo, zo;
   ushort      ua, xb, xe, yb, ye, zb, ze;
   char        x_live      =  '-';
   char        r           =  '-';
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_char    ("a_major"   , a_major);
   DEBUG_USER   yLOG_char    ("a_minor"   , chrvisible (a_minor));
   /*---(defenses)-----------------------*/
   DEBUG_USER   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (XMOD_FORMAT )) {
      DEBUG_USER   yLOG_note    ("not the correct mode");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for standard controls)----*/
   switch (a_minor) {
   case   G_KEY_RETURN : case   G_KEY_ESCAPE :
      yMODE_exit ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;   /* escape  */
   }
   /*---(check for short units)----------*/
   if (a_minor == 'u') {
      if (a_major == 'f') {
         yMODE_exit ();
         yMODE_enter (XMOD_UNITS);
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return 0;
      } else {
         yMODE_enter (XMOD_UNITS);
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(look up)------------------------*/
   n = ymap__format_abbr (a_minor);
   DEBUG_USER   yLOG_value   ("abbr"      , n);
   --rce;  if (n < 0) {
      if (a_major == 'f')  yMODE_exit   ();
      DEBUG_USER   yLOG_note    ("not a valid format key");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get range)----------------------*/
   yMAP_current (NULL, &uo, &xo, &yo, &zo);
   x_live = yMAP_visu_islive ();
   yMAP_visu_range (&ua, &xb, &xe, &yb, &ye, &zb, &ze, &r);
   DEBUG_YMAP   yLOG_complex ("range"     , "%2du, %4d to %4dx, %4d to %4dy, %4d to %4dz, %c", ua, xb, xe, yb, ye, zb, ze, r);
   /*---(execute)------------------------*/
   switch (s_formats [n].type) {
   case YMAP_WIDTH    :
      ymap_visu_exact (uo, xb, xe, 0, g_ymap.gmax, 0, g_zmap.gmax, r);
      rc = ymap__format_range (s_formats [n].type, a_minor);
      if (x_live) ymap_visu_exact (ua, xb, xe, yb, ye, zb, ze, r);
      else        { ymap_visu_clear ();  yMAP_jump (uo, xo, yo, zo); }
      break;
   case YMAP_HEIGHT   :
      ymap_visu_exact (uo, 0, g_xmap.gmax, yb, ye, 0, g_zmap.gmax, r);
      rc = ymap__format_range (s_formats [n].type, a_minor);
      if (x_live) ymap_visu_exact (ua, xb, xe, yb, ye, zb, ze, r);
      else        { ymap_visu_clear ();  yMAP_jump (uo, xo, yo, zo); }
      break;
   case YMAP_DEPTH    :
      ymap_visu_exact (uo, 0, g_xmap.gmax, 0, g_ymap.gmax, zb, ze, r);
      rc = ymap__format_range (s_formats [n].type, a_minor);
      if (x_live) ymap_visu_exact (ua, xb, xe, yb, ye, zb, ze, r);
      else        { ymap_visu_clear ();  yMAP_jump (uo, xo, yo, zo); }
      break;
   case YMAP_MULTIPLE :
      switch (a_minor) {
      case '?' :
         rc = ymap__format_range (YMAP_ALIGN    , '?');
         rc = ymap__format_range (YMAP_FORMAT   , '?');
         rc = ymap__format_range (YMAP_DECIMALS , '0');
         rc = ymap__format_range (YMAP_UNITS    , '-');
         break;
      case 'G' :
         rc = ymap__format_range (YMAP_FORMAT   , 'f');
         rc = ymap__format_range (YMAP_DECIMALS , '6');
         break;
      case 'g' :
         rc = ymap__format_range (YMAP_FORMAT   , 'f');
         rc = ymap__format_range (YMAP_DECIMALS , '3');
         break;
      }
   default :
      rc = ymap__format_range (s_formats [n].type, a_minor);
      break;
   }
   DEBUG_USER   yLOG_value   ("range"     , rc);
   /*---(after action)-------------------*/
   if (a_major == 'f')   yMODE_exit   ();
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> keys for units micro-mode ----------[ ------ [gc.MT0.202.C7]*/ /*-[01.0000.112.!]-*/ /*-[--.---.---.--]-*/
ymap_units_xmode        (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   char        n           =    0;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_char    ("a_major"   , a_major);
   DEBUG_USER   yLOG_char    ("a_minor"   , chrvisible (a_minor));
   /*---(defenses)-----------------------*/
   DEBUG_USER   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (XMOD_UNITS)) {
      DEBUG_USER   yLOG_note    ("not the correct mode");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(look up)------------------------*/
   n = ymap__format_units (a_minor);
   DEBUG_USER   yLOG_value   ("abbr"      , n);
   --rce;  if (n < 0) {
      DEBUG_USER   yLOG_note    ("not a valid units key");
      yMODE_exit   ();
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(execute)------------------------*/
   rc = ymap__format_range (s_units [n].type, a_minor);
   DEBUG_USER   yLOG_value   ("range"     , rc);
   /*---(after action)-------------------*/
   yMODE_exit   ();
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_value   ("rc"        , rc);
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return rc;
   return 0;
}


