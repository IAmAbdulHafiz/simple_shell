#include "shell.h"

/**
 * main_shell_loop - main shell loop
 * @shell_info: the parameter & return info struct
 * @args: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_shell_loop(info_t *shell_info, char **args)
{
	ssize_t read_result = 0;
	int builtin_result = 0;

	while (read_result != -1 && builtin_result != -2)
	{
		clear_info(shell_info);
		if (interactive(shell_info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_result = get_input(shell_info);
		if (read_result != -1)
		{
			set_info(shell_info, args);
			builtin_result = find_builtin(shell_info);
			if (builtin_result == -1)
				find_cmd(shell_info);
		}
		else if (interactive_mode(shell_info))
			_putchar('\n');
		free_shell_info(shell_info, 0);
	}
	write_history(shell_info);
	free_shell_info(shell_info, 1);
	if (!interactive_mode(shell_info) && shell_info->status)
		exit(shell_info->status);
	if (builtin_result == -2)
	{
		if (shell_info->err_num == -1)
			exit(shell_info->status);
		exit(shell_info->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin - finds a builtin command
 * @shell_info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *shell_info)
{
	int i, builtin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(shell_info->argv[0], builtintbl[i].type) == 0)
		{
			shell_info->line_count++;
			builtin_ret = builtintbl[i].func(shell_info);
			break;
		}
	return (builtin_ret);
}

/**
 * find_command - finds a command in PATH
 * @shell_info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *shell_info)
{
	char *path = NULL;
	int i, k;

	shell_info->path = shell_info->argv[0];
	if (shell_info->linecount_flag == 1)
	{
		shell_info->line_count++;
		shell_info->linecount_flag = 0;
	}
	for (i = 0, k = 0; shell_info->arg[i]; i++)
		if (!is_delim(shell_info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_command(shell_info,
			_getenv(shell_info, "PATH="),
			shell_info->argv[0]);
	if (path)
	{
		shell_info->path = path;
		fork_exec_command(shell_info);
	}
	else
	{
		if ((interactive_mode(shell_info) ||
					_getenv(shell_info, "PATH=") ||
					shell_info->argv[0][0] == '/') &&
				find_command(shell_info, shell_info->argv[0]))
			fork_exec_command(shell_info);
		else if (*(shell_info->arg) != '\n')
		{
			shell_info->status = 127;
			print_error(shell_info, "not found\n");
		}
	}
}

/**
 * fork_exec_command - forks an exec thread to run a command
 * @shell_info: the parameter & return info struct
 *
 * Return: void
 */
void fork_exec_command(info_t *shell_info)
{
	pid_t child_pid;

	child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return;
		}
	if (child_pid == 0)
	{
		if (execve(shell_info->path, shell_info->argv,
				get_environ(shell_info)) == -1)
		{
			free_shell_info(shell_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shell_info->status));
		if (WIFEXITED(shell_info->status))
		{
			shell_info->status = WEXITSTATUS(shell_info->status);
			if (shell_info->status == 126)
				print_error(shell_info, "Permission denied\n");
		}
	}
}
