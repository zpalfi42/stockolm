#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <dirent.h>

typedef struct s_files
{
    char            *filename;
    char            *extension;
    char            *name;
    struct s_files  *next;
}   t_files;

t_files *files_lst_new(char *filename);
t_files *last_files(t_files	*files);
t_files *get_files(char *path);

char    *get_path(char **envp);

int     files_add_back(t_files  **files, t_files *new);

void    error_usage(int argc, char **argv, char ** envp, char *error);
void    encrypt(int argc, char **argv, char **envp, int mode);
void    simple_option(int argc, char **argv, char ** envp);
void    decrypt(int argc, char **argv, char ** envp);
void    version(void);
void    help(void);