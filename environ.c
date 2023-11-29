#include "shell.h"

/**
 * _custom_env - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Maintains a constant function prototype.
 * Return: Always 0.
 */
int _custom_env(info_t *info)
{
	_printListStr(info->env);
	return (0);
}

/**
 * custom_getenv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * Maintains a constant function prototype.
 * @name: Environment variable name.
 *
 * Return: The value.
 */
char *custom_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = custom_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _custom_setenv - Initializes a new environment variable or modifies
 * an existing one.
 * @info: Structure containing potential arguments.
 * Maintains a constant function prototype.
 * Return: Always 0.
 */
int _custom_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		custom_puts("Incorrect number of arguments\n");
		return (1);
	}
	if (_setEnv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _custom_unsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * Maintains a constant function prototype.
 * Return: Always 0.
 */
int _custom_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		custom_puts("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_custom_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Maintains a constant function prototype.
 * Return: Always 0.
 */
int populate_custom_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_addNodeEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
