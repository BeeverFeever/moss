#ifndef ANSI_H
#define ANSI_H

#define ANSI_STR_HELPER(s) #s
#define ANSI_STR(s) ANSI_STR_HELPER(s)

#define reset(r)        "\x1b["r"m"
#define colour(c)       "\x1b[0;"c"m"
#define bold(c)         "\x1b[1;"c"m"
#define dim(c)          "\x1b[2;"c"m"
#define italic(c)       "\x1b[3;"c"m"
#define underline(c)    "\x1b[4;"c"m"
#define blink(c)        "\x1b[5;"c"m"
#define reverse(c)      "\x1b[7;"c"m"
#define hidden(c)       "\x1b[8;"c"m"
#define strike(c)       "\x1b[9;"c"m"

// reset states
#define R_ALL       "0"
#define R_FG        DEFAULT
#define R_BG        BG_DEFAULT
#define R_BOLD      "1"
#define R_DIM       "2"
#define R_ITALIC    "3"
#define R_UNDERLINE "4"
#define R_BLINK     "5"
#define R_REVERSE   "7"
#define R_HIDDEN    "8"
#define R_STRIKE    "9"

// fg colours
#define FG_BLACK           "30"
#define FG_RED             "31"
#define FG_GREEN           "32"
#define FG_YELLOW          "33"
#define FG_BLUE            "34"
#define FG_MAGENTA         "35"
#define FG_CYAN            "36"
#define FG_WHITE           "37"
#define FG_DEFAULT         "39"

// bg colours
#define BG_BLACK        "40"
#define BG_RED          "41"
#define BG_GREEN        "42"
#define BG_YELLOW       "43"
#define BG_BLUE         "44"
#define BG_MAGENTA      "45"
#define BG_CYAN         "46"
#define BG_WHITE        "47"
#define BG_DEFAULT      "49"

#endif // ANSI_H
