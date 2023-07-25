#include "main.h"

/**
 * _printf - Custom printf function
 * @format: Format string to be outputted
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, count = 0;
	va_list args;

	va_start(args, format);

	if (format == NULL)
		return (-1);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			i++;
			handle_specifier(args, format, i, &count);
		}
		else
		{
			count += custom_putchar(format[i]);
		}
	}

	va_end(args);
	return (count);
}

/**
 * custom_putchar - Prints a character
 * @c: Character to be printed
 * Return: The number of characters printed (i.e., 1)
 */
int custom_putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * custom_puts - Custom puts
 * @str: Pointer to array of characters (string)
 * Return: Number of characters printed
 */
int custom_puts(const char *str)
{
	int i = 0;

	for (; str[i] != '\0'; i++)
		custom_putchar(str[i]);

	/* custom_putchar('\n'); */
	return (i);
}

/**
 * handle_specifier - Handles format specifiers for our custom printf
 * @args: Argument list
 * @format: Format string
 * @i: Iterator
 * @count: Return value tracking
 */
void handle_specifier(va_list args, const char *format, int i, int *count)
{
	char parameter;
	const char *par_str;
	int par_int;

	switch (format[i])
	{
		case 'c':
			parameter = va_arg(args, int);
			(*count) += custom_putchar(parameter);
			break;
		case 's':
			par_str = va_arg(args, const char *);
			if (par_str == NULL)
			{
				(*count) += custom_puts("(null)");
				return;
			}
			(*count) += custom_puts(par_str);
			break;
		case '%':
			(*count) += custom_putchar('%');
			break;
		case 'd':
			par_int = va_arg(args, int);
			(*count) += print_integer(par_int);
			break;
		case 'i':
			par_int = va_arg(args, int);
			(*count) += print_integer(par_int);
			break;
		default:
			(*count) += custom_putchar('%');
			(*count) += custom_putchar(format[i]);
	}
}

/**
 * print_integer - Prints integers
 * @n: Number to print
 * Return: Number of characters printed
 */
int print_integer(int n)
{
	int i, count = 0;
	char n_arr[20]; /* Up to 20 digits */

	if (n < 0)
	{
		count += custom_putchar('-');
		n = -n;
	}

	if (n == 0)
	{
		count += custom_putchar('0');
		return (count);
	}

	i = 0;
	while (n > 0)
	{
		n_arr[i++] = '0' + n % 10;
		n /= 10;
	} /* Printing digits into the array */

	count += i; /* Taking the size of the array */

	while (--i >= 0)
		custom_putchar(n_arr[i]);

	return (count);
}

