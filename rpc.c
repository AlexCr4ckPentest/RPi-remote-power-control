#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "include/run_server.h"
#include "include/run_client.h"

#define PORT 4457



static struct option program_options[] =
{
    {"help",        no_argument,        0, 'h'},
    {"server",      no_argument,        0, 's'},
    {"reboot",      required_argument,  0, 'r'},
    {"poweroff",    required_argument,  0, 'p'}
};



void show_help(const char* exe_name)
{
    printf("Usage: %s [OPTION]... [ARG]...\n", exe_name);
    printf("\tOption\t\t\tDescription\n");
    printf("\t---------------------------------------------\n");
    printf("\t--help\t\t\tdisplay help and exit\n");
    printf("\t--server\t\trun server mode\n");
    printf("\t--reboot [addr]\t\treboot the target\n");
    printf("\t--poweroff [addr]\tshutdown the target\n");
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        show_help(argv[0]);
        exit(EXIT_SUCCESS);
    }

    int curr_option;
    int error_code;

    while (1)
    {
        curr_option = getopt_long_only(argc, argv, "hs:rp", program_options, NULL);

        if (curr_option == -1)
        {
            break;
        }

        switch (curr_option)
        {
        case 'h':
            show_help(argv[0]);
            exit(EXIT_SUCCESS);
            break;
        case 's':
            error_code = run_server(PORT);
            break;
        case 'r':
            error_code = run_client("reboot", optarg, PORT);
            break;
        case 'p':
            error_code = run_client("poweroff", optarg, PORT);
            break;
        }
    }

    return error_code;
}