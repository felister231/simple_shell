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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_Numstr() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct data_info
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

    char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} data_info;



#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_info *);
} builtin_table;


/* funloop.c */
int hsh(data_info *, char **);
int fun_findBuiltin(data_info *);
void find_commandLine(data_info *);
void fork_commandline(data_info *);

/* funparser.c */
int is_commandline(data_info *, char *);
char *duplicate_chars(char *, int, int);
char *pathCmd(data_info *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* funerrors.c */
void _eputs(char *);
int errorputchar(char);
int put_Filedescriptor(char c, int fd);
int putstrfd(char *str, int fd);

/* funstring.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *str_Startwith(const char *, const char *);
char *_strcat(char *, char *);

/* funstring1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* funexits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* funtokenizer.c */
char **strtow(char *, char *);
char **str_Delim(char *, char);

/* reallocfunc.c */
char *_memset(char *, char, unsigned int);
void freealloc(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* funmemory.c */
int free_memory(void **);

/* funatoi.c */
int interactive(data_info *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* funerrors1.c */
int _erratoi(char *);
void print_Errorstderr(data_info *, char *);
int print_Intdescriptor(int, int);
char *convert_Numstr(long int, int, int);
void remove_Bufcomments(char *);

/* funbuiltin.c */
int shell_exit(data_info *);
int shell_cd(data_info *);
int shell_help(data_info *);

/* funbuiltin1.c */
int shell_history(data_info *);
int shell_alias(data_info *);

/*getlinefun.c */
ssize_t get_userinput(data_info *);
int _getline(data_info *, char **, size_t *);
void singleintHandler(int);

/* fungetinfo.c */
void clear_Datainfo(data_info *);
void set_Datainfo(data_info *, char **);
void free_Datainfo(data_info *, int);

/* funenv.c */
char *_getenviroment(data_info *, const char *);
int _myenvironment(data_info *);
int _mysetenviroment(data_info *);
int unset_Environ_variroment(data_info *);
int enviro_list_pop(data_info *);

/* fungetenv.c */
char **get_Enviroment_var(data_info *);
int unset_Environ_var(data_info *, char *);
int update_Env(data_info *, char *, char *);

/* funhistory.c */
char *get_Filehist(data_info *data);
int write_cmdhistory(data_info *data);
int readAll_his(data_info *data);
int history_build_ls(data_info *data, char *buf, int linecount);
int renum_Nodehistory(data_info *data);

/* funlists.c */
list_t *addStart_node(list_t **, const char *, int);
list_t *nodeAdd_end(list_t **, const char *, int);
size_t nodePrint_str(const list_t *);
int deleteNode_index(list_t **, unsigned int);
void freeMem_list(list_t **);

/* funlists1.c */
size_t getList_len(const list_t *);
char **convert_list_to_str(list_t *);
size_t print_list(const list_t *);
list_t *strNode_with(list_t *, char *, char);
ssize_t getIndex_node(list_t *, list_t *);

/* funvar.c */
int chainCmd(data_info *, char *, size_t *);
void bufferUpdate_check(data_info *, char *, size_t *, size_t, size_t);
int cmdAlias_replace(data_info *);
int variableReplace(data_info *);
int strContent_replace(char **, char *);


int set_alias(data_info *info, char *alias);
ssize_t input_buffer(data_info *info, char **buf, size_t *len);
ssize_t read_buffer(data_info *info, char *buf, size_t *i);



#endif
