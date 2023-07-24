#include "main.h"

void print_buffer(char buffer[], int *buff_i);

/**
 * _printf - The printf function
 * @format: format.
 * Return: Printed characters.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_i = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_i++] = format[i];
			if (buff_i == BUFF_SIZE)
				print_buffer(buffer, &buff_i);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_i);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_i);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - The function prints the contents of the buffer if it exist
 * @buffer: An array of characters
 * @buff_i: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_i)
{
	if (*buff_i > 0)
		write(1, &buffer[0], *buff_i);

	*buff_i = 0;
}
