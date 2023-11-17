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
		exit_code = _erratoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
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
	char *current_path, *target_dir, buffer[1024];
	int chdir_result;

	current_path = getcwd(buffer, 1024);
	if (!current_path)
		_puts("TODO: >>getcwd failure message here<<\n");

	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			chdir_result = chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_result = chdir(target_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_path);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);

	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
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
	_puts("Help call works. Function not yet implemented.\n");
	if (0)
		_puts(*arg_array);
	return (0);
}
