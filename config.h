// -------------------------------- Appearance ---------------------------------


static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

// 0: sloppy systray follows selected monitor, >0: pin systray to monitor X 
static const unsigned int systraypinning = 0;
// systray spacing 
static const unsigned int systrayspacing = 2;
// 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor
static const int systraypinningfailfirst = 1;

static const int systrayonleft = 0;

// 0 means no systray
static const int showsystray = 1;


static const char *fonts[] = { "UbuntuMono Nerd Font:size=14:weight=bold:antialias=true:autohint:true" };
static const char dmenufont[] = "UbuntuMono Nerd Font:size=12:antialias=true:autohint=true";



// ---------------------------------- Colors -----------------------------------
struct Theme {
    char *inactive;
    char *active;
    char *bg;
    char *focus;
};

static const struct Theme purple = {
    .inactive = "#4c566a",
    .active = "#ffffff",
    .bg = "#0f101a",
    .focus = "#a151d3"
};

static const char window_border[] = "#000000";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	{ purple.inactive, purple.bg, window_border },
    { purple.active, purple.focus,  purple.focus  },

};



// -------------------------------- Workspaces ---------------------------------

static const char *tags[] = { "  ", "  ", "  ", "   ", " 󰙯 ", " 󰓇 ", "  " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

// ---------------------------------- Layouts ----------------------------------

static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

// -------------------------------- Keybindings --------------------------------

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

//helper for spawning shell commands in the pre dwm-5.0 fashion
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// Commands
static char dmenumon[2] = "0";
static const char *termcmd[]  = { "alacritty", NULL };
static const char *dmenucmd[] = {
    "dmenu_run", "-m", dmenumon,
    "-fn", dmenufont,
    NULL
};


static const Key keys[] = {

	// ------------------ Windows ------------------

	// Switch between windows
    { MODKEY, XK_a, focusstack, {.i = +1 } },
    { MODKEY, XK_d, focusstack, {.i = -1 } },

	//Change window sizes
	{ MODKEY|ShiftMask, XK_a, setmfact, {.f = -0.05} },
    { MODKEY|ShiftMask, XK_d, setmfact, {.f = +0.05} },

	//change number of windows in master stack
	{ MODKEY|ControlMask, XK_a, incnmaster, {.i = +1 } },
    { MODKEY|ControlMask, XK_d, incnmaster, {.i = -1 } },

	// Change layouts
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },

	//cycle layout
	{ MODKEY,                       XK_space,  setlayout,      {0} },

	//make the current window float
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	// Focus next - prev monitor
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },

	// Send window to next - prev monitor
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },


	//Kill window
	{ MODKEY,             XK_c,      killclient,     {0} },


	// Restart dwm
    { MODKEY|ControlMask, XK_r, quit, {1} },

    // Quit dwm
    { MODKEY|ControlMask, XK_q, quit, {0} },

	//hide the top bar
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	{ MODKEY,             			XK_Return, zoom,           {0} },

	//change to the last used workspace
	{ MODKEY,                       XK_Tab,    view,           {0} },
	
	
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	//{ MODKEY,               XK_Right,      setcolor,       {0} },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	// ------------------- Apps --------------------

    // rofi
    { MODKEY, 						XK_p, 		spawn, 			SHCMD("rofi -show drun") },

    // Window nav (rofi)
    { MODKEY|ShiftMask, 			XK_p, 		spawn, 			SHCMD("rofi -show") },

    // Terminal
    { MODKEY|ShiftMask, 			XK_Return,  spawn, 			SHCMD("alacritty") },

    // File explorer
    { MODKEY, 						XK_e, 		spawn, 			SHCMD("thunar") },

    // Browser
    { MODKEY, 						XK_n, 		spawn, 			SHCMD("firefox") },

    // Screenshot
    { MODKEY, 						XK_s, 		spawn, 			SHCMD("scrot -e 'xclip -selection clipboard -t image/png < $f'") },
    { MODKEY|ShiftMask, 			XK_s, 		spawn, 			SHCMD("scrot -s -e 'xclip -selection clipboard -t image/png < $f'") },

	
	
    // ----------------- Hardware ------------------

    // Volume
    {MODKEY, XK_F2, spawn, SHCMD("pactl -- set-sink-volume 0 -10%")},
    {MODKEY, XK_F3, spawn, SHCMD("pactl -- set-sink-volume 0 +10%")},
    {MODKEY, XK_F8, spawn, SHCMD("pactl set-sink-mute 0 toggle")},

    // Brightness
    {MODKEY, XK_F4, spawn, SHCMD("brightnessctl set 10%-")},
    {MODKEY, XK_F5, spawn, SHCMD("brightnessctl set +10%")},

};


//click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin
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

