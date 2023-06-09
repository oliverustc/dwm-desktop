/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 8; /* border pixel of windows */
static const unsigned int gappx = 5;    /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    1; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 0;      /* 0 means bottom bar */
static const char *fonts[] = {"Font Awesome 6 Free Solid:style=medium:size=13",
                              "WenQuanYi Zen Hei Mono:size=15"};
static const char dmenufont[] = "Hack Nerd Font Mono:size=15";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};

/* tagging */
static const char *tags[] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
    {MODKEY, KEY, view, {.ui = 1 << TAG}},                                     \
        {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},             \
        {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                      \
        {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
    {                                                                          \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                   \
    }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *roficmd[] = {"rofi", "-show", "drun"};

static const Key keys[] = {
    /* modifier                   key                   function         argument */
    {MODKEY,                      XK_space,             spawn,           {.v = roficmd}},
    {MODKEY,                      XK_Return,            spawn,           {.v = termcmd}},
    {MODKEY,                      XK_b,                 togglebar,       {0}},
    {MODKEY,                      XK_j,                 focusstack,      {.i = +1}},
    {MODKEY,                      XK_k,                 focusstack,      {.i = -1}},
    {MODKEY,                      XK_i,                 incnmaster,      {.i = +1}},
    {MODKEY,                      XK_d,                 incnmaster,      {.i = -1}},
    {MODKEY,                      XK_s,                 togglesticky,    {0}},
    {MODKEY,                      XK_h,                 setmfact,        {.f = -0.05}},
    {MODKEY,                      XK_l,                 setmfact,        {.f = +0.05}},
    {MODKEY|ShiftMask,            XK_Return,            zoom,            {0}},  
    {MODKEY,                      XK_Tab,               view,            {0}}, 
    {MODKEY,                      XK_q,                 killclient,      {0}},
    {MODKEY,                      XK_t,                 setlayout,       {.v = &layouts[0]}},
    {MODKEY,                      XK_f,                 setlayout,       {.v = &layouts[1]}}, 
    {MODKEY,                      XK_m,                 setlayout,       {.v = &layouts[2]}},
    {MODKEY|ShiftMask,            XK_t,                 togglefloating,  {0}},
    {MODKEY,                      XK_0,                 view,            {.ui = ~0}},
    {MODKEY|ShiftMask,            XK_0,                 tag,             {.ui = ~0}},
    {MODKEY,                      XK_comma,             focusnthmon,     {.i = 2}}, /*focus 左侧竖屏显示器*/
    {MODKEY,                      XK_period,            focusnthmon,     {.i = 0}}, /*focus 中间显示器*/
    {MODKEY,                      XK_slash,             focusnthmon,     {.i = 1}}, /*focus 右侧显示器*/
    {MODKEY|ControlMask,          XK_comma,             spawn,           SHCMD("xdotool mousemove 720 1280")}, /* 移动鼠标到左侧显示器*/  
    {MODKEY|ControlMask,          XK_period,            spawn,           SHCMD("xdotool mousemove 3360 1040")},/* 移动鼠标到中间显示器*/  
    {MODKEY|ControlMask,          XK_slash,             spawn,           SHCMD("xdotool mousemove 7200 1040")},/* 移动鼠标到右侧显示器*/ 
    {MODKEY|ShiftMask,            XK_comma,             tagnthmon,       {.i = 2}}, /*移动窗口 到左侧显示器*/
    {MODKEY|ShiftMask,            XK_period,            tagnthmon,       {.i = 0}}, /*移动窗口 到中间显示器*/
    {MODKEY|ShiftMask,            XK_slash,             tagnthmon,       {.i = 1}}, /*移动窗口 到右侧显示器*/
    {MODKEY|ShiftMask,            XK_minus,             setgaps,         {.i = -1}},
    {MODKEY|ShiftMask,            XK_equal,             setgaps,         {.i = +1}},
    {MODKEY|ShiftMask,            XK_equal,             setgaps,         {.i = 0}},
    {MODKEY|ShiftMask,            XK_q,                 quit,            {0}},
    {MODKEY|ShiftMask,            XK_r,                 quit,            {1}},
    {ControlMask|ALTKEY,          XK_l,                 spawn,           SHCMD("~/.dwm/scripts/lock.sh")},
    {ALTKEY,                      XK_f,                 spawn,           SHCMD("~/.dwm/scripts/app.sh firefox")},
    {ALTKEY,                      XK_g,                 spawn,           SHCMD("~/.dwm/scripts/app.sh chrome")},
    {ALTKEY,                      XK_c,                 spawn,           SHCMD("~/.dwm/scripts/app.sh chromium")},
    {ALTKEY,                      XK_s,                 spawn,           SHCMD("~/.dwm/scripts/app.sh flameshot")},
    {ALTKEY,                      XK_o,                 spawn,           SHCMD("~/.dwm/scripts/app.sh obsidian")},
    {MODKEY,                      XK_e,                 spawn,           SHCMD("~/.dwm/scripts/app.sh dolphin")},
    {ALTKEY,                      XK_v,                 spawn,           SHCMD("~/.dwm/scripts/app.sh vscode")},
    {MODKEY,                      XK_v,                 spawn,           SHCMD("alacritty -e nvim")},
    {ALTKEY,                      XK_m,                 spawn,           SHCMD("alacritty -e btop")},
    {ALTKEY,                      XK_p,                 spawn,           SHCMD("~/.dwm/scripts/wallpaper.sh")},
    {ALTKEY|ShiftMask,            XK_p,                 spawn,           SHCMD("~/.dwm/scripts/poems.sh")},
    {MODKEY,                      XK_w,                 spawn,           SHCMD("~/.dwm/scripts/rdesktop.sh laptop")},
    {MODKEY|ShiftMask,            XK_w,                 spawn,           SHCMD("~/.dwm/scripts/rdesktop.sh desktop")},
    {ALTKEY|ControlMask,          XK_s,                 spawn,           SHCMD("~/.dwm/scripts/app.sh chrome scholar.google.com.hk")},
    {ALTKEY|ControlMask,          XK_t,                 spawn,           SHCMD("~/.dwm/scripts/app.sh chrome www.deepl.com/translator")},
    TAGKEYS(XK_1, 0) 
    TAGKEYS(XK_2, 1) 
    TAGKEYS(XK_3, 2) 
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4) 
    TAGKEYS(XK_6, 5) 
    TAGKEYS(XK_7, 6) 
    TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8)

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
