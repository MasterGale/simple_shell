#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @inf: the inf struct
 * @pat: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *inf, char *pat)
{
	struct stat st;

	(void)inf;
	if (!pat || stat(pat, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, v = 0;

	for (v = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[v++] = pathstr[j];
	buf[v] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @inf: the inf struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full pat of cmd if found or NULL
 */
char *find_path(info_t *inf, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *pat;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			pat = dup_chars(pathstr, curr_pos, j);
			if (!*pat)
				_strcat(pat, cmd);
			else
			{
				_strcat(pat, "/");
				_strcat(pat, cmd);
			}
			if (is_cmd(inf, pat))
				return (pat);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
