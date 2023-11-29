#include "shell.h"

/**
 * isCmdChain - tests if the current char in the buffer is a chain delimiter
 * @info: the parameter structure
 * @buf: the char buffer
 * @p: address of the current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */

int isCmdChain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = j;
	return (1);
}

/**
 * checkCmdChain - checks if we should continue chaining based on
 * the last status
 * @info: the parameter structure
 * @buf: the char buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void checkCmdChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * replaceCmdAlias - replaces aliases in the tokenized string
 * @info: the parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replaceCmdAlias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _custom_strchr(node->str, '=');
		if (!p)
			return (0);
		p = custom_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replaceCmdVars - replaces variables in the tokenized string
 * @info: the parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceCmdVars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!custom_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
					custom_strdup(convertNum(info->status, 10, 0)));
			continue;
		}
		if (!custom_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
					custom_strdup(convertNum(getpid(), 10, 0)));
			continue;
		}
		node = _nodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
					custom_strdup(_custom_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], custom_strdup(""));
	}
	return (0);
}

/**
 * replaceString - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
