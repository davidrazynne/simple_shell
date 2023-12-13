#include "shell.h"

/**
 * interactive - returns 1 if shell interactive mode is positive
 * @info: structure location/address
 * Return: 1 (interactive0) or  0 (if not).
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - confirms if character is a delimeter.
 * @c: the character to confirm.
 * @delim: delim string.
 * Return: 1 (true) 0 (false)
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - this fxn will if char is an alphabetic character
 * @c: The input char
 * Return: 1 (alphabetic) 0 (if not)
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - modifies a string into an int
 * @s: str to be modified
 * Return: converted int , 0 if no conversion.
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

