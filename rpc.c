#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdarg.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 4457



static struct option program_options[] =
{
    {"help",        no_argument,        0, 0},
    {"server",      no_argument,        0, 0},
    {"reboot",      required_argument,  0, 0},
    {"poweroff",    required_argument,  0, 0}
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



int run_server()
{
    int server_socket_fd;
    int client_socket_fd;
    
    struct sockaddr_in server_addr;
    char received_command[9] = {0};

    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket_fd, (struct sockaddr*)&server_addr, (socklen_t)sizeof(server_addr)) < 0)
    {
        return 2;
    }

    listen(server_socket_fd, 1);

    if ((client_socket_fd = accept(server_socket_fd, NULL, NULL)) < 0)
    {
        return 3;
    }

    read(client_socket_fd, received_command, sizeof(received_command));

    close(client_socket_fd);
    close(server_socket_fd);

    // Need run as root
    system(received_command);

    return 0;
}



int run_client(const char* const cmd, const char* remote_addr)
{
    if (cmd == NULL)
    {
        return 1;
    }

    const int cmd_is_reboot     = (strcmp(cmd, "reboot") == 0);
    const int cmd_is_poweroff   = (strcmp(cmd, "poweroff") == 0);

    if (cmd_is_reboot)
    {

    }
    else if (cmd_is_poweroff)
    {

    }
    else
    {
        return 2;
    }

    return 0;
}



int main(int argc, char** argv)
{
    if (argc < 2)
    {
        show_help(argv[0]);
        exit(0);
    }

    int option_index;
    int curr_option;
    int error_code;

    while (1)
    {
        curr_option = getopt_long_only(argc, argv, "h:srp", program_options, &option_index);

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
            error_code = run_server();
            break;
        case 'r':
            error_code = run_client("reboot");
            break;
        case 'p':
            error_code = run_client("poweroff");
            break;
        }
    }

    return error_code;
}