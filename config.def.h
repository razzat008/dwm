/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 0; /* border pixel of windows */
static const unsigned int gappx = 4;    /* gap pixel between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const int vertpad = 2;           /* vertical padding of bar */
static const int sidepad = 0;           /* horizontal padding of bar */
// static const char *fonts[]          = { "Iosevka:size=16" };
static const char dmenufont[] = "Iosevka:size=10";
static const char *fonts[] = {"Iosevka:style:medium:size=10", "JetBrainsMono Nerd Font:style:medium:size=10", "Material Design Icons Desktop:size=10"};
static const char col_gray1[] = "#222222"; // backgroud colour normally seen
static const char col_gray2[] = "#E8B082"; // border for unfocused window
static const char col_gray3[] = "#fff";    // font color ;normal
static const char col_gray4[] = "#000000"; // font color when focused on a window
// static const char col_cyan[] = "#E8B082";  // border color when the window is focused
static const char col_cyan[] = "#83bae8";  // border color when the window is focused
                                           //this is the default color #83bae8

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1,   col_gray2},
    [SchemeSel] =  {col_gray4, col_cyan,    col_cyan},
    [SchemeHid] =  {col_cyan,  col_gray1,   col_cyan},
};

/* tagging */
/*
 1= terminal
 2= browser
 4= messenging
 6= discord
 7= emails
 */

static const char *tags[] = {"", "", "3", "", "5", "", " ", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    // {"Gimp",      NULL,       NULL,           0,        0,           -1},
    // {"neovide",   NULL,       NULL,       1 <<2  ,      0,           -1 },
    {"LibreWolf",    NULL,       NULL,       1 <<1 ,       0,           -1},
    {"Signal",       NULL,       NULL,       1 <<3  ,      0,           -1 },
    {"discord",      NULL,       NULL,       1 <<5  ,      0,           -1 },
    {"thunderbird",  NULL,       NULL,       1 <<6  ,      0,           -1 },

    /* class            instance    title       tags mask     isfloating   monitor */
    {"Nitrogen",        NULL,       NULL,       0,                1,        -1},
    {"Gscreenshot",     NULL,       NULL,       0,                1,        -1},
    {"TelegramDesktop", NULL,       NULL,       1 << 3,           0,        -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
#include "horizgrid.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
    {"[@]", spiral},
    {"[\\]", dwindle},
    {"###", horizgrid},
    {"|M|", centeredmaster},
    {">M>", centeredfloatingmaster},
};

/* key definitions */
#define MODKEY Mod4Mask
#define altkey Mod1Mask
#define space 0x20
#define printsc 0xff61
#define brightup 0x1008FF02
// #define altkey Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
      {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb",
col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[] = {"/usr/local/bin/st", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */

//custom keybindings
    {altkey,        space,        spawn, SHCMD("via ")}, //to use via
    {0, XF86XK_AudioRaiseVolume,  spawn, SHCMD("~/.local/bin/volumenotifier up")},
    {0, XF86XK_AudioLowerVolume,  spawn, SHCMD("~/.local/bin/volumenotifier down")},
    {0, XF86XK_AudioMute,         spawn, SHCMD("~/.local/bin/volumenotifier mute")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("brillo -q -U 5")},
    {0, XF86XK_RFKill,            spawn, SHCMD("rfkill toggle all")},
    {0, brightup,                 spawn, SHCMD("brillo -q -A 5")},
    {0, XF86XK_AudioPlay,         spawn, SHCMD("mpc toggle")},
    {0, XF86XK_AudioPrev,         spawn, SHCMD("mpc prev")},
    {0, XF86XK_AudioNext,         spawn, SHCMD("mpc next")},
    {0, printsc,                  spawn, SHCMD("gscreenshot")}, //to take screenshot
    {MODKEY | ShiftMask, XK_p, spawn, SHCMD("~/.scripts/power_menu")},

//to control brightness
    {altkey, 0xff52, spawn, SHCMD("~/.scripts/bright_notif up")},
    {altkey, 0xff54, spawn, SHCMD("~/.scripts/bright_notif down")},

//These were replaced by scripts to support dunst
 // {0, XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer --increase 4")},
 // {0, XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer --decrease 4")},
 // {altkey, XK_p, spawn, SHCMD("firefox --private-window --new-tab")},
 // {altkey, 0xff52, spawn, SHCMD("brillo -q -A 5")},
 // {altkey, 0xff54, spawn, SHCMD("brillo -q -U 5")},

//custom keybindings to Launch applications/programs
    {MODKEY, XK_n,   spawn, SHCMD("nemo")},
    {altkey, XK_f,   spawn, SHCMD("librewolf")},
    // {altkey, XK_m,   spawn, SHCMD("st ncmpcpp")},
    // {altkey, XK_h,   spawn, SHCMD("st htop")},
    // shortcut to view all present keybindings
    // {altkey, XK_k,   spawn, SHCMD("st vim -R ~/.config/suckless/dwm/keymaps.md")},
    {altkey, XK_p,   spawn, SHCMD("librewolf --private-window --new-tab")},
    {altkey, XK_n,   spawn, SHCMD("librewolf --private-window /home/ceaser/Desktop/")},

//mostly inbuilt keybindings
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstackvis, {.i = +1}},
    {MODKEY, XK_k, focusstackvis, {.i = -1}},
    {MODKEY | ShiftMask, XK_j, focusstackhid, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, focusstackhid, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY | ShiftMask, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
// switch between master and slave stack
  //
  	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
  	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
  	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_r, setlayout, {.v = &layouts[3]}},
    {MODKEY | ShiftMask, XK_r, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_g, setlayout, {.v = &layouts[5]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[6]}},
    {MODKEY, XK_o, setlayout, {.v = &layouts[7]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_s, show, {0}},

//hide and show tags
    {MODKEY | ShiftMask, XK_s, showall, {0}},
    {MODKEY | ShiftMask, XK_h, hide, {0}},
//go to tag number
    TAGKEYS(XK_1, 0) 
    TAGKEYS(XK_2, 1) 
    TAGKEYS(XK_3, 2) 
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4) 
    TAGKEYS(XK_6, 5) 
    TAGKEYS(XK_7, 6) 
    TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8)
    {MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
