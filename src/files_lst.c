#include "stockolm.h"

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
    n->extension = malloc(sizeof(char) * (j - i + 1));
    while (filename[i] != '\0')
    {
        n->extension[z] = filename[i];
        i++;
        z++;
    }
    n->extension[z] = '\0';
    n->next = NULL;
    return (n);
}

t_files *last_files(t_files	*files)
{
	if (!files)
		return (NULL);
	while (files->next)
		files = files->next;
	return (files);
}

int files_add_back(t_files  **files, t_files *new)
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