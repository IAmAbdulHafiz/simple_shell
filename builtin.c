#include "shell.h"

/**
 * _custom_exit - Terminate the shell.
 * @info: Structure containing potential arguments.
 * Maintains constant function prototype.
 * Return: Exits with a specific status (0) if info.argv[0] is not "exit".
 */
int _custom_exit(info_t *info)
{
	int exit_code;

	if (info->argv[1])
	{
		exit_code = custom_erratoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			c_print_error(info, "Illegal number: ");
			custom_puts(info->argv[1]);
			custom_eputchar('\n');
			return (1);
		}
		info->err_num = custom_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _custom_cd - Change the current working directory of the process.
 * @info: Structure containing potential arguments.
 * Maintains constant function prototype.
 * Return: Always 0.
 */

int _custom_cd(info_t *info)
{
	char *current_path, *t_dir, buffer[1024];
	int chdir_result;

	current_path = getcwd(buffer, 1024);
	if (!current_path)
		e_puts("TODO: >>getcwd failure message here<<\n");

	if (!info->argv[1])
	{
		t_dir = custom_getenv(info, "HOME=");
		if (!t_dir)
			chdir_result = chdir((t_dir = custom_getenv(info, "PWD=")) ? t_dir : "/");
		else
			chdir_result = chdir(t_dir);
	}
	else if (custom_strcmp(info->argv[1], "-") == 0)
	{
		if (!custom_getenv(info, "OLDPWD="))
		{
			e_puts(current_path);
			_putchar('\n');
			return (1);
		}
		e_puts(custom_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = chdir((t_dir = custom_getenv(info, "OLDPWD=")) ? t_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);

	if (chdir_result == -1)
	{
		c_print_error(info, "can't cd to ");
		custom_puts(info->argv[1]), custom_eputchar('\n');
	}
	else
	{
		_setEnv(info, "OLDPWD", "PWD=");
		_setEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _custom_help - Display helpful information.
 * @info: Structure containing potential arguments.
 * Maintains constant function prototype.
 * Return: Always 0.
 */
int _custom_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	e_puts("Help call works. Function not yet implemented.\n");
	if (0)
		e_puts(*arg_array);
	return (0);
}
