#include "stockolm.h"

// -h -r -s -v

void    error_usage(int argc, char **argv, char ** envp, char *error)
{
    printf("\033[0;31mE: %s\n\033[0;37mUsage: ./stockolm [options]\nFor more information try: ./stockolm -h\n", error);
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