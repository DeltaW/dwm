/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 25;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 25;       /* vert inner gap between windows */
static const unsigned int gappoh    = 25;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 25;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Liberation Mono:size=20", "fontawesome:size=20" };
static const char dmenufont[]       = "Liberation Mono:size=20";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeSel]  = { "#fdffa1", col_gray1, "#fdffa1" },
};
static const unsigned int alphas[][3] = {
	/*		fg	bg	border	*/
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* scratchpads */
typedef struct {
       const char *name;
       const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "100x25", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "100x25", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
const char *spcmd4[] = {"st", "-n", "spncmpcpp", "-g", "100x25", "-e", "ncmpcpp", NULL };
const char *spcmd5[] = {"st", "-n", "spbc", "-g", "100x25", "-e", "bc", NULL };
const char *spcmd6[] = {"st", "-n", "sphtop", "-g", "100x25", "-e", "htop", NULL };
static Sp scratchpads[] = {
	/* name			cmd  */
	{ "spterm",		spcmd1 },
	{ "spranger",	spcmd2 },
	{ "keepassxc",	spcmd3 },
	{ "spncmpcpp",	spcmd4 },
	{ "spbc",		spcmd5 },
	{ "sphtop",		spcmd6 },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance      title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",        NULL,         NULL,           0,         1,          0,           0,        -1 },
	{ "PacketTracer",NULL,         NULL,           0,         1,          0,           0,        -1 },
	{ "Steam",       "Steam",      NULL,           0,         0,          0,           0,         1 }, /* start steam on right monitor */
	{ "steam_app_1449850",  "steam_app_1449850", NULL, 0,     0,          0,           0,         1 }, /* start master duel on right monitor */
	{ "discord",     "discord",    NULL,           0,         0,          0,           0,         0 }, /* start discord on left monitor */
	{ "Brave-browser","brave-browser",    NULL,    0,         0,          0,           0,         0 }, /* start brave on left monitor */
	{ "Ardesia",     NULL,         NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",     NULL,         NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st-256color", NULL,         NULL,           0,         0,          1,           0,        -1 }, /* st */
	{ NULL,          "spterm",     NULL,           SPTAG(0),  1,          1,           0,        -1 }, /* scratchpad st */
	{ NULL,          "spfm",       NULL,           SPTAG(1),  1,          1,           0,        -1 }, /* scratchpass ranger */
	{ NULL,          "keepassxc",  NULL,           SPTAG(2),  0,          1,           0,        -1 }, /* scratchpad keepass */
	{ NULL,          "spncmpcpp",  NULL,           SPTAG(3),  1,          1,           0,        -1 }, /* scratchpad ncmpcpp */
	{ NULL,          "spbc",       NULL,           SPTAG(4),  1,          1,           0,        -1 }, /* scratchpad calculator */
	{ NULL,          "sphtop",     NULL,           SPTAG(5),  1,          1,           0,        -1 }, /* scratchpad htop*/
	{ NULL,          NULL,         "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ "Zathura",     NULL,         NULL,	       0,         0,          0,           1,        -1 }, /* block swallowing zathura so that live latex preview opens in another window */

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */ //0
	{ "[M]",      monocle }, // 1
	{ "[@]",      spiral }, /* fibonacci */ // 2
	{ "[\\]",     dwindle }, // 3
	{ "H[]",      deck }, // 4
	{ "TTT",      bstack }, // 5
	{ "===",      bstackhoriz }, // 6
	{ "HHH",      grid }, //7
	{ "###",      nrowgrid }, // 8
	{ "---",      horizgrid }, // 9
	{ ":::",      gaplessgrid }, // 10
	{ "|M|",      centeredmaster }, // 11
	{ ">M>",      centeredfloatingmaster }, // 12
	{ "><>",      NULL },    /* no layout function means floating behavior */ // 13
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */

	/* dmenu */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },

	/* st */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },

	/* quit dwm or rather start .xinitrc dwm start loop */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

        /* media keys */
        { 0,                            XF86XK_AudioPlay,               spawn, SHCMD("mpc toggle") },
        { 0,                            XF86XK_AudioPrev,               spawn, SHCMD("mpc prev") },
        { 0,                            XF86XK_AudioNext,               spawn, SHCMD("mpc next") },
        { 0,                            XF86XK_AudioLowerVolume,        spawn, SHCMD("mpc volume -1") },
        { 0,                            XF86XK_AudioRaiseVolume,        spawn, SHCMD("mpc volume +1") },

	/* screenshot */
        { MODKEY,                       XK_s, 	   spawn, SHCMD("/home/dennis/.local/bin/screenshot") },
	/* dmenu font awesome icon selector */
        { MODKEY,                       XK_u,      spawn, SHCMD("/home/dennis/.local/bin/dmenu-unicodeselect") },
    /* dmenu screenkey */
        { Mod4Mask,                       XK_k,      spawn, SHCMD("/home/dennis/.local/bin/dmenu-screenkey") },
    { Mod4Mask,           XK_b,      spawn, SHCMD("/home/dennis/.local/bin/bookmark-selection.sh") },
    { Mod4Mask,           XK_i,      spawn, SHCMD("/home/dennis/.local/bin/bookmark-insertion.sh") },

	{ Mod4Mask,                     XK_y,      togglescratch,  {.ui = 0 } },
	{ Mod4Mask,                     XK_r,      togglescratch,  {.ui = 1 } },
	{ Mod4Mask,                     XK_p,      togglescratch,  {.ui = 2 } },
	{ Mod4Mask,                     XK_m,      togglescratch,  {.ui = 3 } },
	{ Mod4Mask,                     XK_c,      togglescratch,  {.ui = 4 } },
	{ MODKEY,                       XK_r,      togglescratch,  {.ui = 5 } },


	/* toggle bar */
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	/* window navigation */
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	/* window sizes */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },

	/* close window */
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

	/* layouts */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} }, // monocle
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} }, // fibonacci
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[3]} }, // dwindle
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[7]} }, // fibonacci
	{ MODKEY|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[8]} }, // dwindle
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	/* send window to all tags at once */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	/* warp */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/* view all tags at once */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	/* switch to previously selected tag */
	{ MODKEY,                       XK_Tab,    view,           {0} },

	/* tags */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* gaps */
	{ MODKEY,			  XK_minus,	incrgaps,    {.i = -5 } },
	{ MODKEY,			  XK_plus,	incrgaps,    {.i = +5 } },
	{ MODKEY|ShiftMask,		  XK_minus,	defaultgaps, { 0 } },
	{ MODKEY|ShiftMask,		  XK_plus,	togglegaps,  { 0 } },
	/* default gap keybindings */
	//{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

