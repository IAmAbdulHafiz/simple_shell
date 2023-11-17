#include "shell.h"

/**
 * _custom_history - Displays the history list, one command per line,
 * preceded with line numbers starting at 0.
 * @info: Structure containing potential arguments.
 * Maintains constant function prototype.
 *
 * Return: Always 0.
 */
int _custom_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * custom_unset_alias - Unsets an alias.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: 0 on success, 1 on error.
 */
int custom_unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias,
				node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * custom_set_alias - Sets an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: 0 on success, 1 on error.
 */
int custom_set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (custom_unset_alias(info, str));

	custom_unset_alias(info, str);
	return ((add_node_end(&(info->alias), str, 0) == NULL));
}

/**
 * print_custom_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int print_custom_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _custom_alias - Mimics the alias built-in (man alias).
 * @info: Structure containing potential arguments.
 * Maintains constant function prototype.
 *
 * Return: Always 0.
 */
int _custom_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_custom_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			custom_set_alias(info, info->argv[i]);
		else
			print_custom_alias(node_starts_with(info->alias,
						info->argv[i], '='));
	}
	return (0);
}
