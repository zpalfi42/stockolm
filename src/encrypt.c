#include "stockolm.h"

void    encrypt(int argc, char **argv, char **envp, int mode)
{
    char            *path;
    t_files         *files;

    path = get_path(envp);
    files = get_files(path);

    //For printing files struct info:
    // t_files *aux;
    // aux = files;
    // while (aux)
    // {
    //     printf ("File : %s\nPrefix: %s\nExtension: %s\n\n", aux->filename, aux->name, aux->extension);
    //     aux = aux->next;
    // }

    if (!mode)
        printf("Encrypt\n");
    else
        printf("Encrypt silent\n");
}