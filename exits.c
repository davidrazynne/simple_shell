#include "shell.h"

/**
 **_strncpy - this is a strng coppier
 *@dest: where the copied strng will be pasted
 *@src: location of the origin of strng
 *@n: number of chars to be copied by *_strncpy
 *Return: the added strng
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - this will add 2 strngs
 *@dest: strng 1
 *@src: strng 2
 *@n: size
 *Return: total added string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - finds a char in a string
 *@s: targeted stng
 *@c: target char
 *Return: (s)pointer to memry area
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

