#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @header: address of pointer to header node
 * @strr: strr field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **header, const char *strr, int number)
{
	list_t *new_header;

	if (!header)
		return (NULL);
	new_header = malloc(sizeof(list_t));
	if (!new_header)
		return (NULL);
	_memset((void *)new_header, 0, sizeof(list_t));
	new_header->number = number;
	if (strr)
	{
		new_header->strr = _strdup(strr);
		if (!new_header->strr)
		{
			free(new_header);
			return (NULL);
		}
	}
	new_header->next = *header;
	*header = new_header;
	return (new_header);
}

/**
 * add_node_end - adds a node to the end of the list
 * @header: address of pointer to header node
 * @strr: strr field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **header, const char *strr, int number)
{
	list_t *new_node, *node;

	if (!header)
		return (NULL);

	node = *header;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->number = number;
	if (strr)
	{
		new_node->strr = _strdup(strr);
		if (!new_node->strr)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*header = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the strr element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->strr ? h->strr : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @header: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **header, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!header || !*header)
		return (0);

	if (!index)
	{
		node = *header;
		*header = (*header)->next;
		free(node->strr);
		free(node);
		return (1);
	}
	node = *header;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->strr);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to header node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *header;

	if (!head_ptr || !*head_ptr)
		return;
	header = *head_ptr;
	node = header;
	while (node)
	{
		next_node = node->next;
		free(node->strr);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
