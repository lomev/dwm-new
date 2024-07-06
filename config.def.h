/* See LICENSE file for copyright and license details. */

#define MODKEY                  Mod4Mask
#define OPAQUE                  0xffU
#define COL_NONE                "#000000"
#define ICONSIZE                (bh - 4)
#define ICONSPACING             (bh - 12)

/* appearance */
static unsigned int borderpx  = 1;    /* border pixel of windows */
static unsigned int snap      = 8;    /* snap pixel */
static int horizpadbar        = 2;    /* horizontal padding for statusbar */
static int vertpadbar         = 6;    /* vertical padding for statusbar */
static int showbar            = 1;    /* 0 means no bar */
static int topbar             = 1;    /* 0 means bottom bar */
static int smartgaps          = 0;    /* 1 means no outer gap when there is only one window */
static int viewontag          = 1;    /* switch view on tag switch */
static int showsystray        = 1;    /* 0 means no systray */

/* systray settings */
static int systrayspacing     = 2;    /* systray spacing */

/* gaps */
static unsigned int gappih    = 4;    /* horiz inner gap between windows */
static unsigned int gappiv    = 4;    /* vert inner gap between windows */
static unsigned int gappoh    = 4;    /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 4;    /* vert outer gap between windows and screen edge */

/* fonts */
static char font_mono[256]    = { "monospace:size=9" };
static char font_glyphs[256]  = { "Siji:size=10" };
static const char *fonts[]    = { font_glyphs, font_mono };

/* colorscheme */
static char col_normborder[]  = "#444444";
static char col_normbg[]      = "#222222";
static char col_normfg[]      = "#bbbbbb"; 
static char col_selborder[]   = "#005577";
static char col_selbg[]       = "#005577";
static char col_selfg[]       = "#eeeeee";
static char col_statusfg[]    = "#bbbbbb";
static char col_statusbg[]    = "#222222";
static char col_normtitlefg[] = "#222222";
static char col_normtitlebg[] = "#eeeeee";
static char col_normtagsfg[]  = "#bbbbbb";
static char col_normtagsbg[]  = "#222222";
static char col_seltitlefg[]  = "#eeeeee";
static char col_seltitlebg[]  = "#005577";
static char col_seltagsfg[]   = "#eeeeee";
static char col_seltagsbg[]   = "#005577";
static char *colors[][3]      = {
	/*                    fg               bg               border         */
	[SchemeNorm]      = { col_normfg,      col_normbg,      col_normborder },
	[SchemeSel]       = { col_selfg,       col_selbg,       col_selborder  },
	[SchemeStatus]    = { col_statusfg,    col_statusbg,    COL_NONE       },
	[SchemeTagsNorm]  = { col_normtagsfg,  col_normtagsbg,  COL_NONE       },
	[SchemeTagsSel]   = { col_seltagsfg,   col_seltagsbg,   COL_NONE       },
	[SchemeTitleNorm] = { col_normtitlefg, col_normtitlebg, COL_NONE       },
	[SchemeTitleSel]  = { col_seltitlefg,  col_seltitlebg,  COL_NONE       },
};

/* transparency */
static const unsigned int baralpha    = 0x64;
static const unsigned int alphas[][3] = {
	/*               fg      bg        border */
	[SchemeNorm] = { OPAQUE, baralpha, OPAQUE },
	[SchemeSel]  = { OPAQUE, baralpha, OPAQUE },
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
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const int floatposgrid_x  = 5;  /* float grid columns */
static const int floatposgrid_y  = 5;  /* float grid rows */
static const int swallowfloating = 0;  /* 1 means swallow floating windows by default */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title     tags mask     isfloating   isterminal  noswallow  floatpos               monitor */
	{ "Gimp",     NULL,       NULL,     0,            1,           0,          1,         NULL,                  -1 },
	{ "firefox",  NULL,       NULL,     1 << 4,       0,           0,          1,         NULL,                  -1 },
	{ "St",       NULL,       NULL,     0,            0,           1,          0,         NULL,                  -1 },
	{ "sxiv",     NULL,       NULL,     0,            1,           0,          0,         NULL,                  -1 },
	{ "dragon",   NULL,       NULL,     0,            1,           0,          0,         "50% 0Y 80W 180H",     -1 },
	{ "mpv",      NULL,       NULL,     0,            1,           0,          0,         "100% 100% 320W 180H", -1 },
	{ NULL,       "spterm",	  NULL,     SPTAG(0),     1,           1,          0,         "50% 50% 800W 300H",   -1 },
	{ NULL,       "spfm",     NULL,     SPTAG(1),     1,           1,          0,         "0X 0Y 100% 30%",      -1 },
	{ NULL,       "spcalc",   NULL,     SPTAG(2),     1,           1,          0,         "100% 100% 400W 300H", -1 },
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */

static const char statussep = ';';  /* separator between status bars */
static const BarRule barrules[] = {
	/* monitor  bar    alignment         widthfunc              drawfunc              clickfunc           name */
	{ 'A',      0,     BAR_ALIGN_LEFT,   width_systray,         draw_systray,         click_systray,      "systray" },
	{ -1,       0,     BAR_ALIGN_LEFT,   width_ltsymbol,        draw_ltsymbol,        click_ltsymbol,     "layout" },
	{ -1,       0,     BAR_ALIGN_LEFT,   width_status2d,        draw_status2d,        click_statuscmd,    "status2d" },
	{ -1,       0,     BAR_ALIGN_RIGHT,  width_tags,            draw_tags,            click_tags,         "tags" },
	{ -1,       0,     BAR_ALIGN_NONE,   width_awesomebar,      draw_awesomebar,      click_awesomebar,   "awesomebar" },
};

/* layout(s) */
static float mfact     = 0.55;        /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;           /* number of clients in master area */
static int resizehints = 0;           /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;  /* 1 will force focus on the fullscreen window */

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
	{ "col_normbg",         STRING,  &col_normbg, },
	{ "col_normborder",     STRING,  &col_normborder },
	{ "col_normfg",         STRING,  &col_normfg },
	{ "col_selbg",          STRING,  &col_selbg, },
	{ "col_selborder",      STRING,  &col_selborder },
	{ "col_selfg",          STRING,  &col_selfg },
	{ "col_statusfg",       STRING,  &col_statusfg },
	{ "col_statusbg",       STRING,  &col_statusbg },
	{ "col_normtitlefg",    STRING,  &col_normtitlefg },
	{ "col_normtitlebg",    STRING,  &col_normtitlebg },
	{ "col_normtagsfg",     STRING,  &col_normtagsfg },
	{ "col_normtagsbg",     STRING,  &col_normtagsbg },
	{ "col_seltitlefg",     STRING,  &col_seltitlefg },
	{ "col_seltitlebg",     STRING,  &col_seltitlebg },
	{ "col_seltagsfg",      STRING,  &col_seltagsfg },
	{ "col_seltagsbg",      STRING,  &col_seltagsbg },
	{ "font",               STRING,  &font_mono },
	{ "borderpx",          	INTEGER, &borderpx },
	{ "snap",          		INTEGER, &snap },
	{ "showbar",          	INTEGER, &showbar },
	{ "topbar",          	INTEGER, &topbar },
	{ "smartgaps",     	    INTEGER, &smartgaps },
	{ "viewontag",     	    INTEGER, &viewontag },
	{ "showsystray",   	    INTEGER, &showsystray },
	{ "gappih",       	    INTEGER, &gappih },
	{ "gappiv",       	    INTEGER, &gappiv },
	{ "gappoh",       	    INTEGER, &gappoh },
	{ "gappov",       	    INTEGER, &gappov },
	{ "nmaster",          	INTEGER, &nmaster },
	{ "resizehints",       	INTEGER, &resizehints },
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
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5 } },
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
	{ "floatpos",       floatpos },
};
