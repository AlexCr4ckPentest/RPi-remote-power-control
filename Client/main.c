#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define REMOTE_PORT 4455



static inline void show_usage(const char* program_name)
{
    printf("Usage: %s <address> <command>\n", program_name);
    puts("Available commands:\n"
        "reboot - reboot the target\n"
        "poweroff - shutdown the target");
}



int main(int argc, char** argv)
{
    if (argc < 3) {
        show_usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    int socket_fd;
    const char* remote_addr_str = argv[1];
    const char* command = argv[2];
    const size_t command_size = strlen(command) + 1;

    struct sockaddr_in remote_addr;

    if ((strcmp(command, "reboot") != 0) && (strcmp(command, "poweroff") != 0)) {
        printf("%s: Error: unknown command: %s\n", argv[0], command);
        exit(EXIT_FAILURE);
    }

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("%s: Error: socket: error code: %.2x\n", argv[0], socket_fd);
        exit(socket_fd);
    }

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(REMOTE_PORT);
    inet_pton(AF_INET, remote_addr_str, &remote_addr.sin_addr);

    if (connect(socket_fd, (struct sockaddr*)&remote_addr, (socklen_t)sizeof(remote_addr)) < 0) {
        printf("%s: Error: connect: error code: %.2x\n", argv[0], socket_fd);
        exit(socket_fd);
    }

    write(socket_fd, command, command_size);
    close(socket_fd);

    return 0;
}