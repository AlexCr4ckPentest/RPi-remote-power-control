#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int run_client(const char* const cmd, const char* remote_addr_str, unsigned port)
{
    const int cmd_is_reboot     = (strcmp(cmd, "reboot") == 0);
    const int cmd_is_poweroff   = (strcmp(cmd, "poweroff") == 0);

    if (!(cmd_is_reboot || cmd_is_poweroff))
    {
        fprintf(stderr, "Error: unknown command: '%s'\n", cmd);
        return 1;
    }

    int socket_fd;
    struct sockaddr_in remote_endpoint;

    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socket_fd < 0)
    {
        fprintf(stderr, "Error: socket() syscall failed, code: 0x%.3x\n", errno);
        return 2;
    }

    remote_endpoint.sin_family = AF_INET;
    remote_endpoint.sin_port = htons(port);
    inet_pton(AF_INET, remote_addr_str, &remote_endpoint.sin_addr);

    const int connection_result = connect(socket_fd, (struct sockaddr*)&remote_endpoint, (socklen_t)(sizeof(remote_endpoint)));

    if (connection_result < 0)
    {
        fprintf(stderr, "Error: failed to connect with %s:%d, code: 0x%.3x\n", remote_addr_str, port, errno);
        return 3;
    }

    printf("Sending '%s' command to %s:%d\n", cmd, remote_addr_str, port);

    write(socket_fd, cmd, strlen(cmd) + 1);
    close(socket_fd);

    return 0;
}
