#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @vari: the string env var property
 */
int _unsetenv(info_t *inf, char *vari)
{
	list_t *node = inf->env;
	size_t v = 0;
	char *y;

	if (!node || !vari)
		return (0);

	while (node)
	{
		y = starts_with(node->str, vari);
		if (y && *y == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), v);
			v = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		v++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @vari: the string env vari property
 * @value: the string env vari value
 *  Return: Always 0
 */
int _setenv(info_t *inf, char *vari, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *y;

	if (!vari || !value)
		return (0);

	buf = malloc(_strlen(vari) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, vari);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = inf->env;
	while (node)
	{
		y = starts_with(node->str, vari);
		if (y && *y == '=')
		{
			free(node->str);
			node->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}
