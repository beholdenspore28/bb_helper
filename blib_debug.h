#ifndef BLIB_LOG_H
#define BLIB_LOG_H

#include <stdio.h>

#ifndef BLIB_LOG_STRING
#define BLIB_LOG_STRING "BLIB"
#endif

#ifndef BLIB_LOG_STREAM
#define BLIB_LOG_STREAM stdout
#endif

#ifndef BLIB_WARNING_STREAM
#define BLIB_WARNING_STREAM BLIB_LOG_STREAM
#endif

#ifndef BLIB_ERROR_STREAM
#define BLIB_ERROR_STREAM stderr
#endif

#define BLIB_ANSI_COLOR_RED	"\x1b[31m"
#define BLIB_ANSI_COLOR_GREEN	"\x1b[32m"
#define BLIB_ANSI_COLOR_YELLOW	"\x1b[33m"
#define BLIB_ANSI_COLOR_BLUE	"\x1b[34m"
#define BLIB_ANSI_COLOR_MAGENTA	"\x1b[35m"
#define BLIB_ANSI_COLOR_CYAN	"\x1b[36m"
#define BLIB_ANSI_COLOR_RESET	"\x1b[0m"

#define blib_log(..., file, line) {\
	fprintf(BLIB_LOG_STREAM,BLIB_ANSI_COLOR_CYAN "[" BLIB_LOG_STRING "] " __VA_ARGS__);\
	fprintf(BLIB_LOG_STREAM, "\n" BLIB_ANSI_COLOR_RESET);\
}

#define blib_warn(..., file, line) {\
	fprintf(BLIB_WARNING_STREAM, BLIB_ANSI_COLOR_YELLOW BLIB_LOG_STRING __VA_ARGS__);\
	fprintf(BLIB_WARNING_STREAM, "\n" BLIB_ANSI_COLOR_RESET);\
}

#define blib_error(..., file, line) {\
	fprintf(BLIB_ERROR_STREAM, BLIB_ANSI_COLOR_RED BLIB_LOG_STRING __VA_ARGS__);\
	fprintf(BLIB_ERROR_STREAM, "\n" BLIB_ANSI_COLOR_RESET);\
}

#define blib_test()\
	blib_log("this is a test message");\
	blib_warn("this is a test warning");\
	blib_error("this is a test error");

#endif // BLIB_LOG_H
