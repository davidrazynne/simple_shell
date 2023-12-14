#include "shell.h"

/**
 * _memset - loads memry with byte of same type
 * @s:  memory area where bytes will be loaded
 * @b: byte to load with parameter s
 * @n: count of bytes to load
 * Return: (s)
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - clears a chain of strngs
 * @pp: the chain of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - fxn Reassigns memory block
 * @ptr: directs to to initial block memory allocated
 * @old_size: capacity of initial block byte
 * @new_size: capacity of current block byte
 *
 * Return: pntr to (p)
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

