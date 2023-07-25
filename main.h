#ifndef MAIN_H
#define MAIN_H

/* header files */
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

/* function prototypes */
int custom_putchar(char c);
int _printf(const char *format, ...);
int custom_puts(const char *str);
int print_integer(int n);
void specifiers(va_list parameter_list, const char *format, int i, int *count);
#endif
