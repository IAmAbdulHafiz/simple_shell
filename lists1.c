#include "shell.h"

/**
 * _listLength - Determines the length of the linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t _listLength(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _listToStrings - Returns an array of strings of the list->str.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **_listToStrings(list_t *head)
{
	list_t *node = head;
	size_t i = _listLength(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(custom_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = custom_strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * _printList - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t _printList(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		e_puts(convertNum(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		e_puts(h->str ? h->str : "(nil)");
		e_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _nodeStartsWith - Returns the node whose string starts with the prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: Matched node or NULL.
 */
list_t *_nodeStartsWith(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = custom_starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _getNodeIndex - Gets the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1.
 */
ssize_t _getNodeIndex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
