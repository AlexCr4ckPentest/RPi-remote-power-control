#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

int run_server(unsigned port)
{
    if (getuid() != 0)
    {
        fprintf(stderr, "Error: server must run as root!\n");
        return 1;
    }

    int server_socket_fd;
    int client_socket_fd;
    
    struct sockaddr_in server_addr;
    char received_command[9] = {0};

    server_socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server_socket_fd < 0)
    {
        fprintf(stderr, "Error: socket() syscall failed, code: 0x%.3x\n", errno);
        return 2;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    const int bind_result = bind(server_socket_fd, (struct sockaddr*)&server_addr, (socklen_t)sizeof(server_addr));

    if (bind_result < 0)
    {
        fprintf(stderr, "Error: failed to bind port %d, code: 0x%.3x\n", port, errno);
        return 3;
    }

    listen(server_socket_fd, 1);
    client_socket_fd = accept(server_socket_fd, NULL, NULL);

    if (client_socket_fd < 0)
    {
        fprintf(stderr, "Error: failed to accept connection, code: 0x%.3x\n", errno);
        return 4;
    }

    read(client_socket_fd, received_command, sizeof(received_command));

    close(client_socket_fd);
    close(server_socket_fd);

    // Need run as root
    system(received_command);

    return 0;
}
