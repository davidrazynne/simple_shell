#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmp - this fxn will analyze strngs alphabeticaly
 * @s1: initial strng
 * @s2: subsequent strng
 *
 * Return: -ve (s1 less than s2), +ve(s1 greater than s2) 0 (s1 equals s2)
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - analyzes two parameters strng and substrng
 * @needle: actual substrng to look for
 * @haystack: actaul strng to look into
 * Return: pntr to subsequent character of haystack, (NULL if none)
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - this fxn will combine 2 stngs
 * @src: this is the origin of buff while
 * @dest:  is destination buff
 * Return: address to destination buff
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

