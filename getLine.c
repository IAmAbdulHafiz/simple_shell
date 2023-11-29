#include "shell.h"

/**
 * bufferInput - Buffers chained commands.
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t bufferInput(info_t *info, char **buf, size_t *len)
{
	ssize_t bytesRead = 0;
	size_t lenBuffer = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handleSIGINT);
#if USE_GETLINE
		bytesRead = getline(buf, &lenBuffer, stdin);
#else
		bytesRead = _get_line(info, buf, &lenBuffer);
#endif
		if (bytesRead > 0)
		{
			if ((*buf)[bytesRead - 1] == '\n')
			{
				(*buf)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			info->linecount_flag = 1;
			_rem_comments(*buf);
			buildHistoryList(info, *buf, info->histcount++);
			*len = bytesRead;
			info->cmd_buf = buf;
		}
	}
	return (bytesRead);
}

/**
 * getInput - Gets a line minus the newline.
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t bytesRead = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytesRead = bufferInput(info, &buf, &len);
	if (bytesRead == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		checkCmdChain(info, buf, &j, i, len);
		while (j < len)
		{
			if (isCmdChain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (custom_strlen(p));
	}

	*buf_p = buf;
	return (bytesRead);
}

/**
 * readBuffer - Reads a buffer.
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buf, size_t *i)
{
	ssize_t bytesRead = 0;

	if (*i)
		return (0);
	bytesRead = read(info->input_fd, buf, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*i = bytesRead;
	return (bytesRead);
}

/**
 * _get_line - Gets the next line of input from STDIN.
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytesRead = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	bytesRead = readBuffer(info, buf, &len);
	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
		return (-1);

	c = _custom_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = custom_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_custom_strncat(new_p, buf + i, k - i);
	else
		_custom_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handleSIGINT - Handles the SIGINT signal.
 * @sigNum: the signal number
 *
 * Return: void
 */
void handleSIGINT(__attribute__((unused))int sigNum)
{
	e_puts("\n");
	e_puts("$ ");
	_putchar(BUF_FLUSH);
}

