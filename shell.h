#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>



/* read/write/buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/* cmd conjuctions */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* no_ comversions() */
#define CONVERT_UNSIGNED        2
#define CONVERT_LOWERCASE       1


/* strtok/getline() */
#define USE_STRTOK 0
#define USE_GETLINE 0


#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr - structure forsingly LL (linked lists)
 * @str: this is a strng
 * @num: represents number
 * @next: node that follows (next node)
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * @readfd: file descriptor where line input is read
 * @history: history node
 * @histcount: history for number count of lines
 * @status: return status for last excecuted cmd
 * @path: string path for the current cmd
 * @line_count: the line count
 * @err_num: digit exit error code for exit()s
 * @linecount_flag: include this line of input
 * @fname: filename
 * @env: environ linked list
 * @environ: derived from linked list representation of environmental variables
 * struct passinfo - has arguments to pass into a fxn, enables homogeneous
 * prototype for fxn pntr struct
 * @alias: alias node
 * @env_changed: turned on if environ was modified
 * @argv: array of strngs from arg
 * @argc: arg count
 * @arg: a string containing arg from getline
 * @cmd_buf: location of pointer to cmd_buf
 * @cmd_buf_type: this is for the commands -> (CMD_type ||, &&, ;)
 */
typedef struct passinfo
{

	char *path;
	char *arg;
	char **argv;

	int argc;

	unsigned int line_count;

	int err_num;
	int linecount_flag;

	char *fname;

	list_t *history;
	list_t *alias;
	list_t *env;

	char **environ;

	int env_changed;
	int status;

	char **cmd_buf; /* pointer to commandd, chin buf ,memry mgmnt */
	int cmd_buf_type; /*  this is for the commands -> (CMD_type ||, &&, ;)*/
	int histcount;
	int readfd;
}
info_t;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 *struct builtin - has a builtin strng as well as corresponding fxn
 *@func: the fxn
 *@type: builtin cmd flg

 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* protoptypes for the sourcecode atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* protoptypes for the sourcecode tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* protoptypes for the sourcecode shell_loop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* protoptypes for the sourcecode parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* protoptypes for the sourcecode loophsh.c */
int loophsh(char **);

/* protoptypes for the sourcecode errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* protoptypes for the sourcecode string0.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* protoptypes for the sourcecode  string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* protoptypes for the sourcecode exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* protoptypes for the sourcecode realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* protoptypes for the sourcecode memory.c */
int bfree(void **);

/* protoptypes for the sourcecode errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* protoptypes for the sourcecode builtin0.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);


/* protoptypes  for the sourcecode builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* protoptypes for the sourcecode getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* protoptypes  for the sourcecode getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* protoptypes  for the sourcecode environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* protoptypes for the sourcecode  getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* protoptypes for the sourcecode history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* protoptypes for the sourcecode lists0.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* protoptypes for the sourcecode lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* protoptypes for the sourcecode vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

