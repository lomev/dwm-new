/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 8;        /* snap pixel */
static unsigned int gappih    = 4;       /* horiz inner gap between windows */
static unsigned int gappiv    = 4;       /* vert inner gap between windows */
static unsigned int gappoh    = 4;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 4;       /* vert outer gap between windows and screen edge */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */

/* fonts */
static const char *fonts[] = { "monospace:size=10",
                               "Siji" };

/* default cholorscheme */
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

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const unsigned int ulinepad      = 0;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestrok    = 1;	/* thickness / height of the underline */
static const unsigned int ulinevoffset  = 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall               = 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
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
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "gappih",       	    INTEGER, &gappih },
		{ "gappiv",       	    INTEGER, &gappiv },
		{ "gappoh",       	    INTEGER, &gappoh },
		{ "gappov",       	    INTEGER, &gappov },
		{ "smartgaps",     	    INTEGER, &smartgaps },
		{ "mfact",      	 	FLOAT,   &mfact },
};

/* key definitions */
#define MODKEY Mod4Mask

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

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
};
