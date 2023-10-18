#include "shell.h"

/**
 * list_len - determines length of linked list
 * @v: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *v)
{
	size_t k = 0;

	while (v)
	{
		v = v->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t k = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !k)
		return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < k; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[k] = str;
	}
	strs[k] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @v: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *v)
{
	size_t k = 0;

	while (v)
	{
		_puts(convert_number(v->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(v->str ? v->str : "(nil)");
		_puts("\n");
		v = v->next;
		k++;
	}
	return (k);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @f: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char f)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((f == -1) || (*p == f)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}
