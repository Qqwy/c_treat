#ifndef _UTILS_PRINT_H
#define _UTILS_PRINT_H

/*
  Prints to STDOUT, and adds a terminating newline (\n) at the end.
 */
void println(const char* format, ...);

/*
  Prints to STDERR.
 */
void printerr(const char* format, ...);

#endif //_UTILS_PRINT_H
