#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for read and write operations */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Constants for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Constants for convertNum() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * A structure representing a singly linked list.
 * @num: The number field
 * @str: A string
 * @next: Points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * A structure containing pseudo-arguments to pass into a function,
 * allowing a uniform prototype for the function pointer struct.
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on, count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @input_fd: the fd from which to read line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int input_fd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 * A structure containing a builtin string and related function.
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function declarations */
int is_terminal(int fd); 

/* Function prototype in toem_shloop.c */
int main_shell_loop(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_exec_command(info_t *);

/*Function prototype in toem_parser.c */
int isExc(info_t *, char *);
char *dupChar(char *, int, int);
char *findCommandPath(info_t *, char *, char *);

/* Function prototype in loophsh.c */
int loophsh(char **);

/* Function prototype in toem_errors.c */
void custom_puts(char *str);
int custom_eputchar(char);
int custom_putfd(char c, int fd);
int custom_putsfd(char *str, int fd);

/* Function prototype in toem_string.c */
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *custom_starts_with(const char *, const char *);
char *custom_strcat(char *, char *);

/* Function prototype in toem_string1.c */
char *custom_strcpy(char *, char *);
char *custom_strdup(const char *);
void e_puts(char *);
int _putchar(char);

/* Function prototype in toem_exits.c */
char *_custom_strncpy(char *, char *, int);
char *_custom_strncat(char *, char *, int);
char *_custom_strchr(char *, char);

/* Function prototype in toem_tokenizer.c */
char **splitString(char *, char *);
char **splitString2(char *, char);

/* Function prototype in toem_realloc.c */
char *_custom_memset(char *, char, unsigned int);
void free_string_array(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

/* Function prototype in toem_memory.c */
int bfree(void **);

/* Function prototype in toem_atoi.c */
int inter_m(info_t *shell_info);
int isDelim(char character, char *separator_chars);
int is_alphabetic(int ch);
int c_atoi(char *str);

/* Function prototype in toem_errors1.c */
int custom_erratoi(char *s);
void c_print_error(info_t *info, char *estr);
int custom_print_d(int input, int fd);
char *convertNum(long int num, int base, int flags);
void _rem_comments(char *buf);


/* Function prototype in toem_builtin.c */
int _custom_exit(info_t *info);
int _custom_cd(info_t *info);
int _custom_help(info_t *info);

/* Function prototype in toem_builtin1.c */
int _custom_history(info_t *);
int _custom_alias(info_t *);

/* Function prototype in toem_getline.c */
ssize_t getInput(info_t *);
int _get_line(info_t *info, char **ptr, size_t *length);
void handleSIGINT(int sigNum);

/* Function prototype in toem_getinfo.c */
void initializeInfo(info_t *info);
void setupInfo(info_t *info, char **av);
void freeInfo(info_t *info, int all);
void replaceAlias(info_t *info);
void replaceVariables(info_t *info);

/* Function prototype in toem_environ.c */
char *custom_getenv(info_t *info, const char *name);
int _custom_env(info_t *info);
int _custom_setenv(info_t *info);
int _custom_unsetenv(info_t *info);
int populate_custom_env_list(info_t *info);

/* Function prototype in toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setEnv(info_t *, char *, char *);

/* Function prototype in toem_history.c */
char *getHistoryFile(info_t *info);
int _writeHistory(info_t *info);
int _readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

/* Function prototype in toem_lists.c */
list_t *_addNode(list_t **, const char *, int);
list_t *_addNodeEnd(list_t **, const char *, int);
size_t _printListStr(const list_t *);
int _deleteNodeAtIndex(list_t **, unsigned int);
void _freeList(list_t **);

/* Function prototype in toem_lists1.c */
size_t _listLength(const list_t *);
char **_listToStrings(list_t *);
size_t _printList(const list_t *);
list_t *_nodeStartsWith(list_t *, char *, char);
ssize_t _getNodeIndex(list_t *, list_t *);

/* Function prototype in toem_vars.c */
int isCmdChain(info_t *, char *, size_t *);
void checkCmdChain(info_t *, char *, size_t *, size_t, size_t);
int replaceCmdAlias(info_t *);
int replaceCmdVars(info_t *);
int replaceString(char **, char *);

#endif /*MAIN EXIT */
