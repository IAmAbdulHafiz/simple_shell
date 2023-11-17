#include "shell.h"

/**
 * determine_interactive_mode - checks if the shell is in interactive mode
 * @shell_info: structure containing shell information
 *
 * Returns: 1 if in interactive mode, 0 otherwise
 */

int determine_interactive_mode(shell_info_t *shell_info)
{
	return (is_terminal(STDIN_FILENO) && shell_info->input_fd <= 2);
}

/**
 * is_separator_character - checks if a character is a separator
 * @character: the character to check
 * @separator_chars: string containing separator characters
 *
 * Returns: 1 if true, 0 if false
 */

int is_separator_character(char character, char *separator_chars)
{
	while (*separator_chars)
		if (*separator_chars++ == character)
			return (1);
	return (0);
}

/**
 * is_alphabetic - checks for an alphabetic character
 * @ch: The character to check
 *
 * Returns: 1 if ch is alphabetic, 0 otherwise
 */

int is_alphabetic(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_string_to_integer - converts a string to an integer
 * @str: the string to be converted
 *
 * Returns: 0 if no numbers in the string, converted number otherwise
 */

int _atoi(char *str)
{
	int index, sign = 1, flag = 0, result_integer;
	unsigned int result = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result_integer = -result;
	else
		result_integer = result;

	return (result_integer);
}
