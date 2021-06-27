#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>

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



void terminate()
{
    exit(EXIT_SUCCESS);
}

void daemonize_process()
{
    pid_t pid = fork();

    if (pid < 0) { exit(EXIT_FAILURE); }
    if (pid > 0) { exit(EXIT_SUCCESS); }

    if (setsid() < 0) { exit(EXIT_FAILURE); }

    signal(SIGTERM, terminate);
    signal(SIGHUP, SIG_IGN);

    pid = fork();

    if (pid < 0) { exit(EXIT_FAILURE); }
    if (pid > 0) { exit(EXIT_SUCCESS); }

    umask(0);

    chdir("/");

    openlog("rpc-server", LOG_PID, LOG_DAEMON);
}



int main(int argc, char** argv)
{
    if (argc < 2)
    {
        show_help(argv[0]);
        exit(EXIT_SUCCESS);
    }

    int curr_option = 0;
    int error_code = 0;

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
            daemonize_process();
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
