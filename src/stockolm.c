#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>

// -h -r -s -v

void    decrypt(int argc, char **argv, int mode);

void    error_usage(int argc, char **argv, char *error)
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

void    simple_option(int argc, char **argv)
{
    if (strncmp(argv[1], "-h\0", 3) == 0 || strncmp(argv[1], "-help\0", 6) == 0)
        help();
    else if (strncmp(argv[1], "-v\0", 3) == 0 || strncmp(argv[1], "-version\0", 9) == 0)
        version();
    else if (strncmp(argv[1], "-s\0", 3) == 0 || strncmp(argv[1], "-silent\0", 8) == 0)
        decrypt(argc, argv, 1);
    else
        error_usage(argc, argv, "Invalid option");
}

void    decrypt(int argc, char **argv, int mode)
{
    printf("Decrypt\n");
}

void    encrypt(int argc, char **argv)
{
    printf("Encrypt\n");
}

int main(int argc, char **argv)
{
    if (argc == 1)
        encrypt(argc, argv);
    else if (argc == 2)
    {
        if (argv[1][0] == '-')
            simple_option(argc, argv);
        else
            error_usage(argc, argv, "Invalid second argument");
    }
    else if (argc == 3)
    {
        if (strncmp(argv[1], "-r\0", 3) == 0 || strncmp(argv[1], "-reverse\0", 9) == 0)
        {
            decrypt(argc, argv, 0);
        }
        else
            error_usage(argc, argv, "Invalid secon argument or invalid number of arguments");
    }
    else
        error_usage(argc, argv, "Invalid number of arguments");
}