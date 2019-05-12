/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 15;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int baralpha  = OPAQUE;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 0;     /* 0 means no systray */
static const char *fonts[]          = { "ohsnap:size=12" };
static const char dmenufont[]       = "ohsnap:size=12";

/*static const char norm_fg[] = "#ebdbb2";
static const char norm_bg[] = "#282828";
static const char norm_border[] = "#689d6a";
static const char sel_fg[] = "#b8bb26";
static const char sel_bg[] = "#282828";
static const char sel_border[] = "#fabd2f";*/

#include "/home/nightowl/.cache/wal/colors-wal-dwm.h" 

/*static const char *colors[][3]      = {*/
    /*               fg           bg         border                         */
    /*[SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};*/

static const unsigned int alphas[][3]      = {
       /*               fg      bg        border     */
       [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
       [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "☷", "☲", "☴", "☵", "☰" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "feh",      NULL,	  NULL,	      0,	    0,		 -1 },
	{ "mpv",      NULL,	  NULL,	      0,	    0,	 	 -1 },
	{ "Artifact", NULL,	  NULL,	      0,	    0,		 -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "⚇",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "⚉",      monocle },
	{ "|⚉|",    centeredmaster },
	{ ">⚉>",      centeredfloatingmaster },	
};

#include <X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_history", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg, "-sf", sel_fg, NULL };
static const char *qutebrowser[] = { "qutebrowser", NULL };
static const char *qutebrowsermedia[] = { "qutebrowser", "-B", "/home/nightowl/.config/qutebrowser_media", NULL };
static const char *discord[] = { "qutebrowser", "-B", "/home/nightowl/.config/qutebrowser_discord", NULL };
static const char *tabbedterm[] = { "tabbed", "-c", "-o", norm_bg, "-O", norm_fg, "-t", sel_bg, "-T", sel_fg, "-r", "2", "st", "-w", "''", "-f", dmenufont, NULL };
static const char *vpn[] = { "dmenu_ovpn", NULL };
static const char *ssh[] = { "dmenu_ssh", NULL };
static const char *surf[] = { "tabbed", "-c", "-n", "surf", "-o", norm_bg, "-O", norm_fg, "-t", sel_bg, "-T", sel_fg, "-r", "2", "surf", "-e", "''", "duckduckgo.com", NULL };
static const char *volup[] = { "amixer", "set", "Master", "5%+", NULL };
static const char *voldn[] = { "amixer", "set", "Master", "5%-", NULL };
static const char *record[] = { "dmenurecord", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = vpn } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = ssh } },
	{ MODKEY,                       XK_Return, spawn,          {.v = tabbedterm} },
        { MODKEY,                       XK_q,      spawn,          {.v = qutebrowser } },
	{ MODKEY|ControlMask,           XK_q,      spawn,          {.v = surf } },
        { MODKEY,                       XK_t,      spawn,          {.v = qutebrowsermedia } },
	{ MODKEY,                       XK_z,      spawn,          {.v = discord } },
	{ MODKEY|ControlMask,		XK_r,	   spawn,	   {.v = record } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	/*{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volup } },
        { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldn } },
        { 0,                            XF86XK_AudioMute,        spawn, {.v = mute } },*/
	{ MODKEY,			XK_Up,			 spawn, {.v = volup } },
	{ MODKEY,			XK_Down,		 spawn, {.v = voldn } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = tabbedterm } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

