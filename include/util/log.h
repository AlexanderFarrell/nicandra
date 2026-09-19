#ifndef NICANDRA_LOG_H
#define NICANDRA_LOG_H

#define C_RESET     "\x1B[0m"
#define C_BLACK     "\x1B[30m"
#define C_RED       "\x1B[31m"
#define C_GREEN     "\x1B[32m"
#define C_YELLOW    "\x1B[33m"
#define C_BLUE      "\x1B[34m"
#define C_MAGENTA   "\x1B[35m"
#define C_CYAN      "\x1B[36m"
#define C_WHITE     "\x1B[37m"

#include <stdarg.h>
#include <stdio.h>

inline void nc_log_verbose(const char * format, ...) {
#ifdef NICANDRA_LOG_VERBOSE_ENABLED
    va_list args;
    va_start(args, format);
    printf("[Verbose] ");
    vprintf(format, args);
    va_end(args);
#endif
}

inline void nc_log_info(const char * format, ...) {
    va_list args;
    va_start(args, format);
    printf("[Info] ");
    vprintf(format, args);
    va_end(args);
}

inline void nc_log_warn(const char * format, ...) {
    va_list args;
    va_start(args, format);
    printf("%s[Warn] ", C_YELLOW);
    vprintf(format, args);
    printf(C_RESET);
    va_end(args);
}

inline void nc_log_error(const char * format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "%s[Error] ", C_RED);
    vfprintf(stderr, format, args);
    fprintf(stderr, C_RESET);
    va_end(args);
}


#endif