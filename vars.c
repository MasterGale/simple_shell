#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @bf: the char buffer
 * @po: address of current position in bf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *inf, char *bf, size_t *po)
{
	size_t m = *po;

	if (bf[m] == '|' && bf[m + 1] == '|')
	{
		bf[m] = 0;
		m++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (bf[m] == '&' && bf[m + 1] == '&')
	{
		bf[m] = 0;
		m++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (bf[m] == ';') /* found end of this command */
	{
		bf[m] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*po = m;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @bf: the char buffer
 * @po: address of current position in bf
 * @l: starting position in bf
 * @leng: length of bf
 *
 * Return: Void
 */
void check_chain(info_t *inf, char *bf, size_t *po, size_t l, size_t leng)
{
	size_t m = *po;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			bf[l] = 0;
			m = leng;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			bf[l] = 0;
			m = leng;
		}
	}

	*po = m;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *inf)
{
	int l;
	list_t *node;
	char *po;

	for (l = 0; l < 10; l++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		po = _strchr(node->str, '=');
		if (!po)
			return (0);
		po = _strdup(po + 1);
		if (!po)
			return (0);
		inf->argv[0] = po;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *inf)
{
	int l = 0;
	list_t *node;

	for (l = 0; inf->argv[l]; l++)
	{
		if (inf->argv[l][0] != '$' || !inf->argv[l][1])
			continue;

		if (!_strcmp(inf->argv[l], "$?"))
		{
			replace_string(&(inf->argv[l]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[l], "$$"))
		{
			replace_string(&(inf->argv[l]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[l][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[l]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[l], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
