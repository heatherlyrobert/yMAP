/*============================----beg-of-source---============================*/
#ifndef yMAP
#define yMAP yes



typedef  unsigned char        uchar;


#define     LEN_HUGE       10000
#define     YMAP_EMPTY      -666

typedef  struct cMAP  tMAP;
struct cMAP {
   /*---(identity)-------------*/
   char        which;                       /* b, x, y, or z                  */
   /*---(lefts)----------------*/
   int         umin;                        /* lowest map position            */
   int         gmin;                        /* global min, used or not        */
   int         gamin;                       /* min of all used space          */
   int         glmin;                       /* min for col/row                */
   int         gprev;                       /* prev change for "end"          */
   /*---(current)--------------*/
   int         map         [LEN_HUGE];      /* full col/row map               */
   /*---(rights)---------------*/
   int         gnext;                       /* next change for "end"          */
   int         glmax;                       /* max for col/row                */
   int         gamax;                       /* max of all used space          */
   int         gmax;                        /* global max, used or not        */
   int         umax;                        /* highest map position           */
   /*---(screen)---------------*/
   int         ubeg;                        /* beg abs pos shown on screen    */
   int         ucur;                        /* cur abs pos shown on screen    */
   int         uend;                        /* end abs pos shown on screen    */
   int         ulen;                        /* len shown on screen (end-beg+1)*/
   int         uavail;                      /* full availible room on screen  */
   int         utend;                       /* hypothetical abs end for screen*/
   /*---(grids)----------------*/
   int         gbeg;                        /* grid at start of screen        */
   int         gcur;                        /* current grid position          */
   int         gend;                        /* grid at end of screen          */
   /*---(done)-----------------*/
};
tMAP        g_bmap;
tMAP        g_xmap;
tMAP        g_ymap;
tMAP        g_zmap;


#define     YMAP_BMAP            'b'
#define     YMAP_XMAP            'x'
#define     YMAP_YMAP            'y'
#define     YMAP_ZMAP            'z'

#define     YMAP_RIGHT           'r'
#define     YMAP_OFFICE          'o'

/*---(completely clean and populate)-----*/
#define     YMAP_INIT            'I'
/*---(changed focus of map)--------------*/
#define     YMAP_MAJOR           'M'
/*---(same focus, different pos)---------*/
#define     YMAP_MINOR           'n'
/*---(update as neccessary)--------------*/
#define     YMAP_UPDATE          'u'



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yMAP_version           (void);
char        yMAP_init              (void);
char        yMAP_wrap              (void);
char*       yMAP__unit             (char *a_question, char a_index);


char        yMAP_clear             (tMAP *a_map);

#endif
/*============================----end-of-source---============================*/
