#include "shell.h"

/**
 * hsh - this is the mainn entry to the shell loop
 * @av: argmt vectr
 * @info: paramtr and return info structure
 * Return: (success), 1 (error), or  the actual error code
 */

int hsh(info_t *info, char **av)
{
	ssize_t d = 0;
	int builtin_ret = 0;

	while (d != -1 && builtin_ret != -2)
	{
	clear_info(info);
		if (interactive(info))
		_puts("Razo$ ");
		_eputchar(BUF_FLUSH);
		d = get_input(info);
		if (d != -1)
	{
		set_info(info, av);
		builtin_ret = find_builtin(info);
		if (builtin_ret == -1)
		find_cmd(info);
	}
		else if (interactive(info))
		_putchar('\n');
		free_info(info, 0);
	}
		write_history(info);
		free_info(info, 1);
		if (!interactive(info) && info->status)
		exit(info->status);
		if (builtin_ret == -2)
		{
		if (info->err_num == -1)
		exit(info->status);
		exit(info->err_num);
		}
		return (builtin_ret);
}

/**
 * find_builtin - this will find any builtin cmd
 * @info: paramtr and return info structure
 * Return: 0 (builtin executed successfully)
 * 1 (builtin found bt nt successful)
 * 2 (builtin signals exit()
 * -1 (builtin nt found)
 */
int find_builtin(info_t *info)
{
		int a, built_in_ret = -1;
		builtin_table builtintbl[] = {
	{"exit", _myexit},
	{"env", _myenv},
	{"help", _myhelp},
	{"history", _myhistory},
	{"setenv", _mysetenv},
	{"unsetenv", _myunsetenv},
	{"cd", _mycd},
	{"alias", _myalias},
		{NULL, NULL}
		};

		for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[a].func(info);
			break;
		}
		return (built_in_ret);
}

/**
 * find_cmd - this fxn will find a cmd in PATH
 * @info: paramtr and return info structure
 * Return: (void)
 */
void find_cmd(info_t *info)
{
		char *path = NULL;
		int a, k;

		info->path = info->argv[0];
		if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
		for (a = 0, k = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
		k++;
		if (!k)
		return;

		path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
		if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
		else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
		|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		fork_cmd(info);
		else if (*(info->arg) != '\n')
	{
		info->status = 127;
		print_error(info, "not found\n");
	}
	}
}

/**
 * fork_cmd - this will fork open  thread that executes a Command
 * @info: paramtr and return information structure
 * Return: (void)
 */
void fork_cmd(info_t *info)
{
		pid_t child_pid;

		child_pid = fork();
		if (child_pid == -1)
	{

		perror("Error:");
		return;
	}
		if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
	{
		free_info(info, 1);
		if (errno == EACCES)
		exit(126);
		exit(1);
	}

	}
		else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
	{
		info->status = WEXITSTATUS(info->status);
		if (info->status == 126)
		print_error(info, "No permission to do this\n");
	}
	}
}
