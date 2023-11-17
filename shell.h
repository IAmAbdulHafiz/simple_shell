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

/* Constants for convert_number() */
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
 * @readfd: the fd from which to read line input
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
	int readfd;
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
	int input_fd;
	char *name;
	void (*function)(void);
} builtin_table;

typedef struct
{
	int input_fd;
} shell_info_t;


/* Function declarations */
int is_terminal(int fd); 

/* Function prototype in toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/*Function prototype in toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* Function prototype in loophsh.c */
int loophsh(char **);

/* Function prototype in toem_errors.c */
void custom_puts(char *str);
int custom_putchar(char c);
int custom_putfd(char c, int fd);
int custom_putsfd(char *str, int fd);

/* Function prototype in toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* Function prototype in toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Function prototype in toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Function prototype in toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* Function prototype in toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* Function prototype in toem_memory.c */
int bfree(void **);

/* Function prototype in toem_atoi.c */
int determine_interactive_mode(shell_info_t *shell_info);
int is_separator_character(char character, char *separator_chars);
int is_alphabetic(int ch);
int _atoi(char *str);

/* Function prototype in toem_errors1.c */
int custom_erratoi(char *s);
void custom_print_error(info_t *info, char *estr);
int custom_print_d(int input, int fd);
char *custom_convert_number(long int num, int base, int flags);
void custom_remove_comments(char *buf);
void custom_eputs(const char *str);
int custom_eputchar(char c);

/* Function prototype in toem_builtin.c */
int _custom_exit(info_t *info);
int _custom_cd(info_t *info);
int _custom_help(info_t *info);

/* Function prototype in toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* Function prototype in toem_getline.c */
ssize_t customGetline(info_t *info, char **ptr, size_t *length);
void handleSIGINT(int sigNum);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

void remove_comments(char *str);
void check_command_chain(info_t *info, char *buf, size_t *j, size_t i, size_t len);
int is_command_chain(info_t *info, char *buf, size_t *j);


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
void _eputs(const char *str);

/* Function prototype in toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* Function prototype in toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Function prototype in toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* Function prototype in toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Function prototype in toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /*MAIN EXIT */
