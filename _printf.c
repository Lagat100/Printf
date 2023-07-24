#include "main.h"
#include <stdio.h>
#include <stdarg.h>

void print_buffer(char buffer[], int *buff_index);

/**
 * _printf - This is the Printf function
 * @format: string format.
 * Return: All the printed characters
 *
 */

int _printf(const char *format, ...)
{
	int index, printed = 0, printed_char = 0;
	int flags, size, width, precision, buff_index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (index = 0; format && format[index] != '\0'; index++)
	{
		if (format[index] != '%')
		{
			buffer[buff_index++] = format[index];
			if (buff_index == BUFF_SIZE)
				print_buffer(buffer, &buff_index);
			/* write(1, &format[index], 1);*/
			printed_char++;
		}
		else
		{
			print_buffer(buffer, &buff_index);
			flags = get_flags(format, &index);
			size = get_size(format, &index);
			width = get_width(format, &index, list);
			precision = get_precision(format, &index, list);
			++index;
			printed = handle_print(format, &index, list, buffer, flags, size, width, precision);
			if (printed == -1)
				return (-1);
			printed_char += printed;
		}
	}

	print_buffer(buffer, &buff_index);

	va_end(list);

	return (printed_char);
}

/**
 * print_buffer - Function prints the contents of the buffer if exists
 * @buffer: An array of characters
 * @buff_index: Index added to the next chararacter, also represents the length
 */

void print_buffer(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);

	*buff_index = 0;
}
