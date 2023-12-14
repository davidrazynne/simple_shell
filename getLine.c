#include "shell.h"

/**
 * input_buf - the fxn will buffer imput cmds
 * @info: prmtr structure
 * @buf: location of buffer
 * @len: location of length  variable
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t d = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		d = getline(buf, &len_p, stdin);
#else
		d = _getline(info, buf, &len_p);
#endif
		if (d > 0)
		{
			if ((*buf)[d - 1] == '\n')
			{
				(*buf)[d - 1] = '\0';
				d--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = d;
				info->cmd_buf = buf;
			}
		}
	}
	return (d);
}

/**
 * get_input - this pulls a line
 * @info: prmtr structure
 * Return: memoryread that from get_input
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t a, b, len;
	ssize_t d = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	d = input_buf(info, &buf, &len);
	if (d == -1)
		return (-1);
	if (len)
	{
		b = a;
		p = buf + a;

		check_chain(info, buf, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (d);
}

/**
 * read_buf - as the mane suggests, it will read buffer
 * @info: prmtr structure
 * @buf: actual buffer
 * @i: buffers' size(in read_buf)
 * Return: r (as read)
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t d = 0;

	if (*i)
		return (0);
	d = read(info->readfd, buf, READ_BUF_SIZE);
	if (d >= 0)
		*i = d;
	return (d);
}

/**
 * _getline - gets the next line of input from standard input
 * @info: prmtr structure
 * @ptr: location of pntr to buffr
 * @length: the length of preallocated pntr buffer
 * Return: s(as read)
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t k;
	ssize_t d = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == len)
		a = len = 0;

	d = read_buf(info, buf, &len);
	if (d == -1 || (d == 0 && len == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + a, k - a);
	else
		_strncpy(new_p, buf + a, k - a + 1);

	s += k - a;
	a = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - handles brakers like ctrl-c
 * @sig_num: the signal handler no
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

