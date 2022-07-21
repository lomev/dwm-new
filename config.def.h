/* See LICENSE file for copyright and license details. */

#define STATUSBAR               "dwmblocks"
#define OPAQUE                  0xffU
#define MODKEY                  Mod4Mask

/* appearance */
static unsigned int borderpx  = 2;    /* border pixel of windows */
static unsigned int snap      = 8;    /* snap pixel */
static unsigned int underline = 1;	  /* thickness / height of the underline */
static int swallowfloating    = 0;    /* 1 means swallow floating windows by default */
static int floatposgrid_x     = 5;    /* float grid columns */
static int floatposgrid_y     = 5;    /* float grid rows */
static int horizpadbar        = 2;    /* horizontal padding for statusbar */
static int vertpadbar         = 8;    /* vertical padding for statusbar */
static int vertpad            = 0;    /* vertical padding of bar */
static int sidepad            = 0;    /* horizontal padding of bar */
static int showbar            = 1;    /* 0 means no bar */
static int topbar             = 1;    /* 0 means bottom bar */
static int smartgaps          = 0;    /* 1 means no outer gap when there is only one window */
static int viewontag          = 1;    /* Switch view on tag switch */

/* gaps */
static unsigned int gappih    = 8;    /* horiz inner gap between windows */
static unsigned int gappiv    = 8;    /* vert inner gap between windows */
static unsigned int gappoh    = 8;    /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 16;   /* vert outer gap between windows and screen edge */

/* fonts */
static const char *fonts[]    = { "monospace:size=9", "Siji" };

/* cholorscheme */
static char normbordercolor[] = "#444444";
static char normbgcolor[]     = "#222222";
static char normfgcolor[]     = "#bbbbbb";
static char selbordercolor[]  = "#005577";
static char selbgcolor[]      = "#005577";
static char selfgcolor[]      = "#eeeeee";
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const unsigned int baralpha    = 0x64;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3] = {
	/*               fg      bg        border   */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha  },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha  },
};

/* scratchpads */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {"st", "-n", "spterm", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-e", "lf", NULL };
const char *spcmd3[] = {"st", "-n", "spcalc", "-f", "monospace:size=15", "-e", "bc", "-lq", NULL };

static Sp scratchpads[] = {
	/* name      cmd */
	{ "spterm",  spcmd1 },
	{ "spfm",    spcmd2 },
	{ "spcalc",  spcmd3 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title           tags mask     isfloating   isterminal  noswallow  floatpos               monitor */
	{ "Gimp",     NULL,       NULL,           0,            1,           0,           0,        NULL,                  -1 },
	{ "firefox",  NULL,       NULL,           1 << 8,       0,           0,          -1,        NULL,                  -1 },
	{ "St",       NULL,       NULL,           0,            0,           1,           0,        NULL,                  -1 },
	{ "mpv",      NULL,       NULL,           0,            1,           0,           0,        "100% 100% 320W 180H", -1 },
	{ NULL,       NULL,       "Event Tester", 0,            0,           0,           1,        NULL,                  -1 },
	{ NULL,       "spterm",	  NULL,           SPTAG(0),     1,           1,           0,        "50% 50% 800W 300H",   -1 },
	{ NULL,       "spfm",     NULL,           SPTAG(1),     1,           1,           0,        "0X 0Y 100% 30%",      -1 },
	{ NULL,       "spcalc",   NULL,           SPTAG(2),     1,           1,           0,        "100% 100% 400W 300H", -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " \ue002",  tile },
	{ " \ue000",  monocle },
	{ " \ue26b",  deck },
	{ " \ue003",  bstack },
	{ " \ue004",  bstackhoriz },
	{ " \ue00a",  horizgrid },
	{ " \ue005",  gaplessgrid },
	{ " \ue006",  NULL },
	{ NULL,       NULL },
};

/* Xresources preferences to load at startup */
ResourcePref resources[] = {
	{ "normbgcolor",        STRING,  &normbgcolor },
	{ "normbordercolor",    STRING,  &normbordercolor },
	{ "normfgcolor",        STRING,  &normfgcolor },
	{ "selbgcolor",         STRING,  &selbgcolor },
	{ "selbordercolor",     STRING,  &selbordercolor },
	{ "selfgcolor",         STRING,  &selfgcolor },
	{ "borderpx",          	INTEGER, &borderpx },
	{ "snap",          		INTEGER, &snap },
	{ "showbar",          	INTEGER, &showbar },
	{ "topbar",          	INTEGER, &topbar },
	{ "horizpadbar",      	INTEGER, &horizpadbar },
	{ "vertpadbar",      	INTEGER, &vertpadbar },
	{ "vertpad",          	INTEGER, &vertpad },
	{ "sidepad",        	INTEGER, &sidepad },
	{ "nmaster",          	INTEGER, &nmaster },
	{ "resizehints",       	INTEGER, &resizehints },
	{ "gappih",       	    INTEGER, &gappih },
	{ "gappiv",       	    INTEGER, &gappiv },
	{ "gappoh",       	    INTEGER, &gappoh },
	{ "gappov",       	    INTEGER, &gappov },
	{ "smartgaps",     	    INTEGER, &smartgaps },
	{ "viewontag",     	    INTEGER, &viewontag },
	{ "mfact",      	 	FLOAT,   &mfact },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "togglefullscr",  togglefullscr },
	{ "shiftview",      shiftview },
	{ "defaultgaps",    defaultgaps },
	{ "togglegaps",     togglegaps },
	{ "incrgaps",       incrgaps },
	{ "transfer",       transfer },
	{ "pushdown",       pushdown },
	{ "pushup",         pushup },
	{ "cyclelayout",    cyclelayout },
	{ "togglescratch",  togglescratch },
	{ "goback",         goback },
};
