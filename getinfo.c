#include "shell.h"

/**
 * initializeInfo - Initializes the info_t struct.
 * @info: The address of the struct to be initialized.
 */
void initializeInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setupInfo - Sets up the info_t struct.
 * @info: The address of the struct to be set up.
 * @av: The argument vector.
 */
void setupInfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = splitString(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = custom_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceCmdAlias(info);
		replaceCmdVars(info);
	}
}

/**
 * freeInfo - Frees the fields of the info_t struct.
 * @info: The address of the struct to be freed.
 * @all: True if freeing all fields.
 */
void freeInfo(info_t *info, int all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			_freeList(&(info->env));
		if (info->history)
			_freeList(&(info->history));
		if (info->alias)
			_freeList(&(info->alias));
		free_string_array(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->input_fd > 2)
			close(info->input_fd);
		_putchar(BUF_FLUSH);
	}
}
