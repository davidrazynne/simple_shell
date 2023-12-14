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
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
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
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
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

