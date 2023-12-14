#include "shell.h"

/**
 * bfree - clears off pointer and voids the location
 *
 * @ptr: location of pointer to be cleared
 *
 * Return: 1(cleared), 0 (not cleared)
 */

int bfree(void **ptr)
{

	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}

