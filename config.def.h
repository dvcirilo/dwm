/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 5;       /* gaps between windows */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int maxsww    = 1920;     /* emulate 16:9 on ultrawide when singlewindow */
static const int showbar            = 1;        /* 0 means no bar */
static const int rmaster            = 0;        /* 1 means master-area is initially on the right */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Noto Mono:size=11:antialias=true:autohint=true", "Noto Emoji Medium:size=11:antialias=true:autohint=true" };
static const char dmenufont[]       = "Noto Mono:size=11:antialias=true:autohint=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005070";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* launcher commands (They must be NULL terminated) */
static const char* rofi[]      = { "rofi", "-show", "combi", NULL };

static const Launcher launchers[] = {
   /* command       name to display */
	{ rofi,         "🚀" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                    instance    title       tags mask    iscentered   isfloating   monitor */
	{ "Lingot",                 NULL,       NULL,          0,          0,               1,           -1 },
	{ "Pianoteq",               NULL,       NULL,          0,          0,               1,           -1 },
	{ "newRPL",                 NULL,       NULL,          0,          0,               1,           -1 },
	{ "DB48X",                  NULL,       NULL,          0,          0,               1,           -1 },
	{ "Free42",                 NULL,       NULL,          0,          0,               1,           -1 },
	{ "SimpleScreenRecorder",   NULL,       NULL,          0,          1,               1,           -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const int lpm[] = {
        /* Index of preferred layout], if LENGTH(lpm)<#monitors -> default layout */
        0, 6
};

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|||",      col },
	{ "[D]",      deck },
	{ "|M|",      centeredmaster },
	{ "===",      verttile },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *pcmanfm[]  = { "pcmanfm", NULL };
static const char *termsamedir[]  = { "samedir", NULL };
static const char *upvol[]            = { "pulseaudio-ctl", "up" };
static const char *downvol[]          = { "pulseaudio-ctl", "down" };
static const char *mutevol[]          = { "pulseaudio-ctl", "mute" };
static const char *mutemic[]          = { "pulseaudio-ctl", "mute-input" };
static const char *backlightup[]      = { "xbacklight", "-inc", "10" };
static const char *backlightdown[]    = { "xbacklight", "-dec"," 10" };
static const char *brightup[]         = { "brightness", "-inc" };
static const char *brightdown[]       = { "brightness", "-dec" };
static const char *playpause[]        = { "playerctl", "play-pause", NULL };
static const char *play_next[]        = { "playerctl", "next", NULL };
static const char *play_prev[]        = { "playerctl", "previous", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	/* { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, */
	{ MODKEY,                       XK_p,      spawn,          {.v = rofi } },
	{ MODKEY,                       XK_w,      spawn,          {.v = pcmanfm } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_s,      view,           {0} },
	{ MODKEY|ShiftMask,             XK_s,      goback,         {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_Return, setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_r,      togglermaster,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { 0,                            XK_Print,  spawn,          SHCMD("maim -s -u | xclip -selection clipboard -t image/png") },
    { ShiftMask,			        XK_Print,  spawn,          SHCMD("maimpick") },
	{ MODKEY,                       XK_o,      spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = termsamedir } },
	{ Mod4Mask,                     XK_l,      spawn,          SHCMD("slock") },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn, {.v = upvol } },  
	{ 0,                            XF86XK_AudioLowerVolume,   spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,          spawn, {.v = mutevol } },
	{ 0,                            XF86XK_AudioMicMute,       spawn, {.v = mutemic } },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn, {.v = backlightup } },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn, {.v = backlightdown } },
    { 0,					        XF86XK_AudioPlay,          spawn, {.v = playpause } },
	{ 0,					        XF86XK_AudioPrev,          spawn, {.v = play_prev } },
	{ 0,					        XF86XK_AudioNext,          spawn, {.v = play_next } },
	{ Mod4Mask,                     XK_k,       spawn,         {.v = brightup } },
	{ Mod4Mask,                     XK_j,       spawn,         {.v = brightdown } },
    TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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
