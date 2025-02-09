#ifndef FORMATCODE
#define FORMATCODE

// TIMESTAMP FORMAT
#define DAY "%d"
#define SDAY "%a"
#define FDAY "%A"

#define MONTH "%m"
#define SMONTH "%b"
#define FMONTH "%B"

#define SYEAR "%y"
#define FYEAR "%Y"

#define SECOND "%S"
#define MINUTE "%M"
#define HOUR "%H"

#define TIMEZONE "%Z"

#define NEW_LINE '\n'

// ASCII COLOR CODE
#define RESET_COLOR "\x1b[0m"

#define FG_BLACK "\033[30m"
#define FG_RED "\033[31m"
#define FG_GREEN "\033[32m"
#define FG_YELLOW "\033[33m"
#define FG_BLUE "\033[34m"
#define FG_MAGENTA "\033[35m"
#define FG_CYAN "\033[36m"
#define FG_WHITE "\033[37m"
#define FG_GRAY "\033[90m"

#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"
#define BG_GRAY "\033[100m"

#define NONE ""

// ASCII CLEAR CODE
#define CLEAR "\x1b[2J"

// USER DEFINE
#define TIMESTAMP_FORMAT SDAY "-" SMONTH "-" SYEAR "|" SECOND ":" MINUTE ":" HOUR "|" TIMEZONE

#endif