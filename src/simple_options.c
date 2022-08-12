#include "stockolm.h"

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