#include "shell.h"

/**
 * custom_erratoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: (0) if no numbers in the string, the converted number otherwise.
 *         (-1) on error.
 */
int custom_erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: Determine why this makes main return 255? */

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * c_print_error - Prints an error message.
 * @info: The parameter & return info struct.
 * @estr: String containing the specified error type.
 *
 * Return: (void) Nothing.
 */
void c_print_error(info_t *info, char *estr)
{
	custom_puts(info->fname);
	custom_puts(": ");
	custom_print_d(info->line_count, STDERR_FILENO);
	custom_puts(": ");
	custom_puts(info->argv[0]);
	custom_puts(": ");
	custom_puts(estr);
}

/**
 * custom_print_d - Prints a decimal (integer) number (base 10).
 * @input: The input.
 * @fd: The file descriptor to write to.
 *
 * Return: (count) Number of characters printed.
 */
int custom_print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_val, current;

	if (fd == STDERR_FILENO)
		__putchar = custom_eputchar;

	if (input < 0)
	{
		abs_val = -input;
		__putchar('-');
		count++;
	}
	else
		abs_val = input;

	current = abs_val;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_val / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertNum - Converter function, a clone of itoa.
 * @num: Number.
 * @base: Base.
 * @flags: Argument flags.
 *
 * Return: (ptr) String.
 */
char *convertNum(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * _rem_comments - Function replaces the first instance of '#'
 * with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: (void) Always 0.
 */
void _rem_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
