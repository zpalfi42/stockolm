#include "stockolm.h"

// We search in the env the $HOME variable and add /infection to it.
// If everything goes well we should have the path of the folder that we want to work on.
char    *get_path(char **envp)
{
    int     i;
    int     j;
    int     z;
    char    *path;

    while (envp[i])
    {
        if (strncmp(envp[i], "HOME=", 5) == 0)
        {
            j = 5;
            while(envp[i][z] != '\0')
                z++;
            path = malloc(sizeof(char) * (z + 6));
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
            break ;
        }
        i++;
    }
    return (path);
}

// Next we save all the information of the files in the path that we searched before.
// We save all this info in our s_files struct.
t_files *get_files(char *path)
{
    struct dirent   *entry;
    t_files         *files;
    DIR             *folder;
    int             n = 0;
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
    }
    return (files);
}