#include "shell.h"

/**
 * hsh - main shell loop
 * @information: the parameter & return information struct
 * @arv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *information, char **arv)
{
	ssize_t s = 0;
	int builtin_ret = 0;

	while (s != -1 && builtin_ret != -2)
	{
		clear_info(information);
		if (interactive(information))
			_puts("╰═┅═━–〈HEZKEN ┈➤ ");
		_eputchar(BUF_FLUSH);
		s = get_input(information);
		if (s != -1)
		{
			set_info(information, arv);
			builtin_ret = find_builtin(information);
			if (builtin_ret == -1)
				find_cmd(information);
		}
		else if (interactive(information))
			_putchar('\n');
		free_info(information, 0);
	}
	write_history(information);
	free_info(information, 1);
	if (!interactive(information) && information->status)
		exit(information->status);
	if (builtin_ret == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @information: the parameter & return information struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *information)
{
	int o, built_in_ret = -1;
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

	for (o = 0; builtintbl[o].type; o++)
		if (_strcmp(information->argv[0], builtintbl[o].type) == 0)
		{
			information->line_count++;
			built_in_ret = builtintbl[o].func(information);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @information: the parameter & return information struct
 *
 * Return: void
 */
void find_cmd(info_t *information)
{
	char *path = NULL;
	int o, q;

	information->path = information->argv[0];
	if (information->linecount_flag == 1)
	{
		information->line_count++;
		information->linecount_flag = 0;
	}
	for (o = 0, q = 0; information->arg[o]; o++)
		if (!is_delim(information->arg[o], " \t\n"))
			q++;
	if (!q)
		return;

	path = find_path(information, _getenv(information, "PATH="), information->argv[0]);
	if (path)
	{
		information->path = path;
		fork_cmd(information);
	}
	else
	{
		if ((interactive(information) || _getenv(information, "PATH=")
			|| information->argv[0][0] == '/') && is_cmd(information, information->argv[0]))
			fork_cmd(information);
		else if (*(information->arg) != '\n')
		{
			information->status = 127;
			print_error(information, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @information: the parameter & return information struct
 *
 * Return: void
 */
void fork_cmd(info_t *information)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(information->path, information->argv, get_environ(information)) == -1)
		{
			free_info(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(information->status));
		if (WIFEXITED(information->status))
		{
			information->status = WEXITSTATUS(information->status);
			if (information->status == 126)
				print_error(information, "Permission denied\n");
		}
	}
}
