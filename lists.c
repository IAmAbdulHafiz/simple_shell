#include "shell.h"

/**
 * _addNode - Adds a node to the start of the list.
 * @head: Address of pointer to the head node.
 * @str: Str field of the node.
 * @num: Node index used by history.
 *
 * Return: Address of the new node.
 */
list_t *_addNode(list_t **head, const char *str, int num)
{
	list_t *newNode;

	if (!head)
		return (NULL);
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	_custom_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (str)
	{
		newNode->str = custom_strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	newNode->next = *head;
	*head = newNode;
	return (newNode);
}

/**
 * _addNodeEnd - Adds a node to the end of the list.
 * @head: Address of pointer to the head node.
 * @str: Str field of the node.
 * @num: Node index used by history.
 *
 * Return: Address of the new node.
 */
list_t *_addNodeEnd(list_t **head, const char *str, int num)
{
	list_t *newNode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	_custom_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (str)
	{
		newNode->str = custom_strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 * _printListStr - Prints only the str element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t _printListStr(const list_t *h)
{
	size_t i = 0;

	while (h)
	{

		e_puts(h->str ? h->str : "(nil)");
		e_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _deleteNodeAtIndex - Deletes a node at the given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int _deleteNodeAtIndex(list_t **head, unsigned int index)
{
	list_t *node, *prevNode;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prevNode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prevNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * _freeList - Frees all nodes of a list.
 * @headPtr: Address of pointer to the head node.
 *
 * Return: void
 */
void _freeList(list_t **headPtr)
{
	list_t *node, *nextNode, *head;

	if (!headPtr || !*headPtr)
		return;
	head = *headPtr;
	node = head;
	while (node)
	{
		nextNode = node->next;
		free(node->str);
		free(node);
		node = nextNode;
	}
	*headPtr = NULL;
}
