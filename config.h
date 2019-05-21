/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_burgundy[]        = "#550000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1,  col_gray1 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_gray4  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Wfica",    "Wfica",    NULL,       0,            0,            2 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ALTKEY,                KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask, 	    	KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_burgundy, "-sf", col_gray4, NULL };
/* git://drozdowsky/rc-files/bin/term */
static const char *tabbedcmd[] = { "tabbed", "-d", "-c", "-r", "1", "stmux", "''", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *lockcmd[]  = { "mlock", NULL };
static const char *volup[] =   { "sh", "-c", "~/bin/vol -inc 5", NULL };
static const char *voldown[] = { "sh", "-c", "~/bin/vol -dec 5", NULL };
static const char *lightup[]  = { "sh", "-c", "~/bin/bright 10", NULL };
static const char *lightdown[]  = { "sh", "-c", "~/bin/bright -10", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = tabbedcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_y,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_e,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_comma,  setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_period, setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_s,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ALTKEY,                XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ALTKEY,                XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_h,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_l,	   focusmon,       {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_h,  	   tagmon,         {.i = -1 } },
	{ MODKEY|ALTKEY,                XK_l,      tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_g,      spawn,          {.v = lockcmd } },
    /* Volume and Brightness, more in git://drozdowsky/rc-files/bin     */
	{ MODKEY,                       XK_F10,    spawn,          {.v = volup } },
	{ MODKEY,                       XK_F9,     spawn,          {.v = voldown } },
	{ MODKEY,                       XK_F7,     spawn,          {.v = lightdown } },
	{ MODKEY,                       XK_F8,     spawn,          {.v = lightup } },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,  {.v = volup } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,  {.v = voldown } },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,  {.v = lightdown } },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,  {.v = lightup } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ALTKEY,		        XK_x,	   quit,	       {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button3,        killclient,     {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = volup } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = voldown } },
	{ ClkStatusText,        ShiftMask,      Button4,        spawn,          {.v = lightup } },
	{ ClkStatusText,        ShiftMask,      Button5,        spawn,          {.v = lightdown } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkRootWin,           0,              Button3,        spawn,          SHCMD("~/bin/x9term") },
};
