#include "shell.h"

/**
 * is_chain - the fxns checks if new character buff is an array delimeter
 * @info: information param  structure
 * @buf: represents character  buff
 * @p: pntr to of new position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t b = *p;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[b] == ';')
	{
		buf[b] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_chain - fxn will check if code will continue to
 * sequencesing based on initial stage
 * @info: information param  structure
 * @p: pntr to of new position in buff
 * @i: initial position in buffer
 * @len: the length of buffer
 * @buf: represents character  buff
 * Return: NULL
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t b = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			b = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			b = len;
		}
	}

	*p = b;
}

/**
 * replace_alias - Fxn will replace alias within tokenized strng
 * @info: info parameter structure
 *
 * Return: 1(replaced), 0 (in not replaced)
 */
int replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - fxn will replace variables within tokenized strng
 * @info: the info parameter structure
 * Return: 1(replaced), 0 (in not replaced)
 */
int replace_vars(info_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			replace_string(&(info->argv[a]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces strng
 * @new: this is the strng
 * @old: pntr of initial/old strng
 * Return: 1(replaced), 0 (in not replaced)
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

