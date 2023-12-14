#include "shell.h"

/**
 * _myhistory - fxn print history list from 0 each cmd in a line.
 * @info: Struct containing argmnts. Sustain constant function prototype.
 *  Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - fxn remodifies alias to a string
 * @info: paramtr structure
 * @str: the final string alias
 * Return: 0 (success) 1 (no modification)
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int rt;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	rt = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (rt);
}

/**
 * set_alias - fxn remodifies alias to a string
 * @info: paramtr structure
 * @str: the final string alias
 * Return: 0 (success) 1 (no modification)
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - fxn displays alias string
 * @node: reps the node alias
 * Return: 0 (success) 1 (no modification)
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - emulate alias builtin
 * @info: Struct containing argmnts. Sustain constant function prototype.
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		p = _strchr(info->argv[a], '=');
		if (p)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}

