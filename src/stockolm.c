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

// -h -r -s -v

void    decrypt(int argc, char **argv, char ** envp);

void    encrypt(int argc, char **argv, char ** envp, int mode);

void    error_usage(int argc, char **argv, char ** envp, char *error)
{
    printf("\033[0;31mE: %s\n\033[0;37mUsage: ./stockolm [options]\nFor more information try: ./stockolm -h\n", error);
}

void    help(void)
{
    printf("Usage: ./stockolm [options]\nOptions:\n");
    printf("  -h, -help\t\tPrint this message and exit.\n");
    printf("  -r, -reverse\t\tDecrypts the content from the infection folder.\n\t\t\tThis option needs to be followed by a file containing the private key to decrypt.\n");
    printf("  -s, -silent\t\tDon't echo recipes.\n");
    printf("  -v, -version\t\tPrint the version number of stockolm\n");
}

void    version(void)
{
    printf("Stockolm v1.0.0\n");
}

void    simple_option(int argc, char **argv, char ** envp)
{
    if (strncmp(argv[1], "-h\0", 3) == 0 || strncmp(argv[1], "-help\0", 6) == 0)
        help();
    else if (strncmp(argv[1], "-v\0", 3) == 0 || strncmp(argv[1], "-version\0", 9) == 0)
        version();
    else if (strncmp(argv[1], "-s\0", 3) == 0 || strncmp(argv[1], "-silent\0", 8) == 0)
        encrypt(argc, argv, envp, 1);
    else if (strncmp(argv[1], "-r\0", 3) == 0 || strncmp(argv[1], "-reverse\0", 9) == 0)
        error_usage(argc, argv, envp, "Option -r needs to be followed by the file containing the private key to desencypt");
    else
        error_usage(argc, argv, envp, "Invalid option");
}

void    decrypt(int argc, char **argv, char ** envp)
{
    printf("Decrypt\n");
}

t_files *files_lst_new(char *filename)
{
    t_files *n;
    int     i = 0;
    int     j = 0;
    int     z = 0;
    
    n = (t_files *)malloc(sizeof(t_files));
    if (!n)
        return (NULL);
    while (filename[j] != '\0')
        j++;
    n->filename = malloc(sizeof(char) * j);
    strcpy(n->filename, filename);
    while (filename[i] != '\0')
    {
        if (filename[i] == '.')
            break;
        i++;
    }
    n->name = malloc(sizeof(char) * (i + 1));
    strncpy(n->name, filename, i);
    n->name[i] == '\0';
    n->extension = malloc(sizeof(char) * (j - i));
    while (filename[i] != '\0')
    {
        n->extension[z] == filename[i];
        i++;
        z++;
    }
    n->extension[z] = '\0';
    n->next = NULL;
    return (n);
}

static t_files	*last_files(t_files	*files)
{
	if (!files)
		return (NULL);
	while (files->next)
		files = files->next;
	return (files);
}

int    files_add_back(t_files  **files, t_files *new)
{
    t_files	*t;

	if (!files || !new)
		return (-1);
	t = *files;
	if (*files)
	{
		t = last_files(*files);
		t->next = new;
	}
	else
		*files = new;
	return (0);
}

void    encrypt(int argc, char **argv, char ** envp, int mode)
{
    DIR *folder;
    struct dirent   *entry;
    int             i = 0;
    int             n = 0;
    char            path[100];
    t_files         *files;
    
    while (envp[i])
    {
        if (strncmp(envp[i], "HOME=", 5) == 0)
        {
            int j = 5;
            while (envp[i][j] != '\0')
            {
                path[j - 5] = envp[i][j];
                j++;
            }
            path[j - 5] = '/';
            path[j - 4] = 'i';
            path[j - 3] = 'n';
            path[j - 2] = 'f';
            path[j - 1] = 'e';
            path[j] = 'c';
            path[j + 1] = 't';
            path[j + 2] = 'i';
            path[j + 3] = 'o';
            path[j + 4] = 'n';
            path[j + 5] = '\0';
        }
        i++;
    }
    printf("--> %s\n", path);
    folder = opendir(path);
    while (entry = readdir(folder))
    {
        if (strcmp(entry->d_name, ".\0") != 0 && strcmp(entry->d_name, "..\0") != 0)
        {
            if (n == 0)
                files = files_lst_new(entry->d_name);
            else
                files_add_back(&files, files_lst_new(entry->d_name));
            n++;
        }
        printf("File %s\n", entry->d_name);
    }
    if (!mode)
        printf("Encrypt\n");
    else
        printf("Encrypt silent\n");
}

int main(int argc, char **argv, char ** envp)
{
    if (argc == 1)
        encrypt(argc, argv, envp, 0);
    else if (argc == 2)
    {
        if (argv[1][0] == '-')
            simple_option(argc, argv, envp);
        else
            error_usage(argc, argv, envp, "Invalid second argument");
    }
    else if (argc == 3)
    {
        if (strncmp(argv[1], "-r\0", 3) == 0 || strncmp(argv[1], "-reverse\0", 9) == 0)
        {
            decrypt(argc, argv, envp);
        }
        else
            error_usage(argc, argv, envp, "Invalid secon argument or invalid number of arguments");
    }
    else
        error_usage(argc, argv, envp, "Invalid number of arguments");
}