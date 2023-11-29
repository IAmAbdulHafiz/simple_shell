#include "shell.h"

/**
 * getHistoryFile - Retrieves the history file.
 * @info: Parameter struct
 *
 * Return: Allocated string containing the history file
 */
char *getHistoryFile(info_t *info)
{
	char *buf, *t_dir;

	t_dir = custom_getenv(info, "HOME=");
	if (!t_dir)
		return (NULL);
	buf = malloc(sizeof(char) * (custom_strlen(t_dir) +
				custom_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	custom_strcpy(buf, t_dir);
	custom_strcat(buf, "/");
	custom_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * _writeHistory - Writes history to a file.
 * @info: Parameter struct
 *
 * Return: 1 on success, else -1
 */
int _writeHistory(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		custom_putsfd(node->str, fd);
		custom_putfd('\n', fd);
	}
	custom_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _readHistory - Reads history from a file.
 * @info: Parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int _readHistory(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildHistoryList(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildHistoryList(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		_deleteNodeAtIndex(&(info->history), 0);
	renumberHistory(info);
	return (info->histcount);
}

/**
 * buildHistoryList - Adds an entry to the history linked list.
 * @info: Parameter struct
 * @buf: Buffer
 * @linecount: History linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	_addNodeEnd(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumberHistory - Renumbers the history linked list after changes.
 * @info: Parameter struct
 *
 * Return: The new histcount
 */
int renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
