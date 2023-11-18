#include "shell.h"

/**
 * Retrieves the history file.
 * @param info: Parameter struct
 *
 * Return: Allocated string containing the history file
 */
char *getHistoryFile(info_t *info)
{
	char *buf, *dir;

	dir = _setenv(info, "HOME=");
	if (!dir)
		return NULL;
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return NULL;
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return buf;
}

/**
 * Writes history to a file.
 * @param info: Parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeHistory(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return -1;

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return -1;
	for (node = info->history; node; node = node->next)
	{
		_puts(node->str, fd);
		_puts('\n', fd);
	}
	_puts(BUF_FLUSH, fd);
	close(fd);
	return 1;
}

/**
 * Reads history from a file.
 * @param info: Parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readHistory(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return 0;

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return 0;
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return 0;
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return 0;
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return free(buf), 0;
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return info->histcount;
}

/**
 * Adds an entry to the history linked list.
 * @param info: Parameter struct
 * @param buf: Buffer
 * @param linecount: History linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return 0;
}

/**
 * Renumbers the history linked list after changes.
 * @param info: Parameter struct
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
	return info->histcount = i;
}

