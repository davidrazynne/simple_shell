#include "shell.h"

/**
 * main - main entry entry point to the program
 * @ac: argument count
 * @av: argument vectr
 *
 * Return: 0(success), 1 (no successful)
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fde = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fde)
			: "r" (fde));

	if (ac == 2)
	{
		fde = open(av[1], O_RDONLY);
		if (fde == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fde;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
