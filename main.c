#include "shell.h"

/**
 * main - entry point
 * @arc: arg count
 * @arv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arc, char **arv)
{
	info_t info[] = { INFO_INIT };
	int gr = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (gr)
		: "r" (gr));

	if (arc == 2)
	{
		gr = open(arv[1], O_RDONLY);
		if (gr == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(arv[0]);
				_eputs(": 0: Can't open ");
				_eputs(arv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}

		info->readfd = gr;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, arv);
	return (EXIT_SUCCESS);
}
