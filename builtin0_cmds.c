#include "shell.h"

/**
 * _myexit - initiates program egress the shell
 * @info: Struct containing argmnts.
 * Return: egress and displays a given egress status and especially ->(0)
 * if info.argv[0] != "exit" or if If there is an exit arguement.
 */
int _myexit(info_t *info)
{
	int xitchck;

	if (info->argv[1])
	{
		xitchck = _erratoi(info->argv[1]);
		if (xitchck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change directory
 * @info: Struct containing argmnts. Sustain constant function prototype.
 * Return: 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdirret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure message right here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdirret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdirret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirret = chdir(info->argv[1]);
	if (chdirret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - the fxn changes current directory of current process
 * @info: Struct containing argmnts. Sustain constant function prototype.
 * Return: 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Function not yet implemented!\n");
	if (0)
		_puts(*arg_array);
	return (0);
}

