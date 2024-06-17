#ifndef MOSS_REPORT_H
#define MOSS_REPORT_H

#include <mossio.h>

#define severity_str_helper(s) #s
#define severity_str(s) severity_str_helper(s)

#define ANSI_CLEAR    "\x1b[0m"
#define ANSI_BOLD_RED "\x1b[1;31m"
#define ANSI_RED      "\x1b[0;31m"
#define ANSI_GREEN    "\x1b[0;32m"
#define ANSI_YELLOW   "\x1b[0;33m"
#define ANSI_BLUE     "\x1b[0;34m"
#define ANSI_PURPLE   "\x1b[0;35m"
#define ANSI_CYAN     "\x1b[0;36m"
#define ANSI_WHITE    "\x1b[0;37m"

typedef char* String;

typedef enum {
    SUCCESS,
    INFO,
    DEBUG,
    WARN,
    ERROR,
    FATAL,
} ReportType;

static String ReportTypeColour[] = {
    [SUCCESS] = ANSI_GREEN,
    [INFO]    = ANSI_BLUE,
    [DEBUG]   = ANSI_PURPLE,
    [WARN]    = ANSI_YELLOW,
    [ERROR]   = ANSI_RED,
    [FATAL]   = ANSI_BOLD_RED,
};

#define report(file,severity,msg,...) \
    do { \
        // TODO: rewrite this when fprintf is properly implemented
        flanterm_write()
        fprintf(file, \
                ANSI_CLEAR "[%s" severity_str(severity) ANSI_CLEAR "] ["ANSI_CYAN"%s"ANSI_CLEAR"] ["ANSI_CYAN"%i"ANSI_CLEAR":"ANSI_CYAN"%s"ANSI_CLEAR"] " ANSI_WHITE \
                msg, ReportTypeColour[severity], __TIME__, __LINE__, __FILE__ __VA_OPT__(,) __VA_ARGS__); \
        puts(""); \
    } while (0)

#define report_and_exit(file,exit_code,severity,msg,...) \
    do { \
        report(file, severity, msg, __VA_ARGS__); \
        puts(""); \
        exit(exit_code); \
    } while (0)

#endif // MOSS_REPORT_H
