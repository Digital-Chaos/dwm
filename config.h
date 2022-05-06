/* See LICENSE file for copyright and license details. */

/* font defintions */
#define FONT_MONO               "mono-9:bold"
#define FONT_AWESOME_BRANDS     "Font Awesome 6 Brands-9"
#define FONT_AWESOME_FREE       "Font Awesome 6 Free Solid-9"

/* font awesome icons */
static const char icon_music[]       = "\uf001";
static const char icon_headphones[]  = "\uf025";
static const char icon_globe[]       = "\uf0ac";
static const char icon_envelope[]    = "\uf0e0";
static const char icon_gamepad[]     = "\uf11b";
static const char icon_terminal[]    = "\uf120";
static const char icon_code[]        = "\uf121";
static const char icon_firefox[]     = "\uf269";
static const char icon_freebsd[]     = "\uf3a4";

/* appearance */
static const unsigned int borderpx  = 1;        /* window border (pixels) */
static const unsigned int snap      = 8;        /* snap distance (pixels) */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { FONT_MONO, FONT_AWESOME_BRANDS, FONT_AWESOME_FREE };
static const char dmenufont[]       = FONT_MONO;
static const char col_gray1[]       = "#111111";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#006688";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1, col_cyan },
};

/* tagging */
//static const char *tags[] = { "term", "code", "mail", "web", "games", "music" };
static const char *tags[] = { icon_freebsd, icon_code, icon_envelope, icon_globe, icon_gamepad, icon_music };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          	instance    title       tags mask     isfloating   monitor */
	{ "Gimp",         	NULL,       NULL,       0,            1,           -1 },
	{ "Sylpheed",  		NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Thunderbird",  	NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Firefox",      	NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Geany", 		NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Sublime_text", 	NULL,       NULL,       1 << 1,       0,           -1 },
	{ "jetbrains-idea", 	NULL,       NULL,       1 << 1,       0,           -1 },
	{ "jetbrains-idea-ce", 	NULL,       NULL,       1 << 1,       0,           -1 },
	{ "SDL_App", 		NULL,       NULL,       1 << 4,       1,           -1 },
	{ "Snes9x-gtk", 	NULL,       NULL,       1 << 4,       1,           -1 },
	{ "mGBA", 		NULL,       NULL,       1 << 4,       1,           -1 },
	{ "DarkPlaces", 	NULL,       NULL,       1 << 4,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

/* layouts - first entry is default*/
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

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
static const char *dmenucmd[]       = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]        = { "xterm", NULL };
static const char *lockcmd[]        = { "slock", NULL };
static const char *brightupcmd[]    = { "intel_backlight", "incr", NULL };
static const char *brightdowncmd[]  = { "intel_backlight", "decr", NULL };
static const char *volumemutecmd[]  = { "mixer", "vol",   "0", NULL };
static const char *volumeupcmd[]    = { "mixer", "vol", "+10", NULL };
static const char *volumedowncmd[]  = { "mixer", "vol", "-10", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_F1,     spawn,          {.v = brightdowncmd } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = brightupcmd } },
	{ MODKEY,                       XK_F10,    spawn,          {.v = volumemutecmd } },
	{ MODKEY,                       XK_F11,    spawn,          {.v = volumedowncmd } },
	{ MODKEY,                       XK_F12,    spawn,          {.v = volumeupcmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Up,     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_Down,   incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_v,      view,           {0} },
	{ MODKEY,             		XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask        button          function        argument */
	{ ClkLtSymbol,          0,                Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,                Button1,        zoom,           {0} },
//	{ ClkWinTitle,          MODKEY,           Button1,        zoom,           {0} },
//	{ ClkStatusText,        0,                Button1,        spawn,          {.v = dmenucmd } },
	{ ClkClientWin,         MODKEY,           Button1,        movemouse,      {0} },
//	{ ClkClientWin,         MODKEY|ShiftMask, Button1,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,           Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,           Button3,        zoom,           {0} },
	{ ClkTagBar,            0,                Button1,        view,           {0} },
	{ ClkTagBar,            0,                Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,           Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,           Button3,        toggletag,      {0} },
};
