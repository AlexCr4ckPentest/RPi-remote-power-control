#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define REMOTE_PORT 4455

#ifdef HOME_LAN_NETWORK
#   define REMOTE_ADDR_STR "127.0.0.1"
#elif defined (HOTSPOT_LAN_NETWORK)
#   define FIRST_REMOTE_ADDR_STR    "192.168.3.148"
#   define SECOND_REMOTE_ADDR_STR   "192.168.3.149"
#endif



static inline void show_usage(const char* program_name)
{
    printf("Usage: %s <remote_command>\n", program_name);
    puts("Available commands:\n"
        "reboot - reboot the target\n"
        "poweroff - shutdown the target");
}



int main(int argc, char** argv)
{
    if (argc < 2) {
        show_usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

#ifdef HOME_LAN_NETWORK
    struct sockaddr_in remote_addr;
#elif defined (HOTSPOT_LAN_NETWORK)
    struct sockaddr_in first_remote_addr;
    struct sockaddr_in second_remote_addr;
#endif // !HOME_LAN_NETWORK

    int socket_fd;
    const char* command = argv[1];
    const size_t command_size = strlen(command) + 1;

    if ((strcmp(command, "reboot") != 0) && (strcmp(command, "poweroff") != 0)) {
        printf("unknown command: %s\n", command);
        exit(EXIT_FAILURE);
    }

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

#ifdef HOME_LAN_NETWORK
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(REMOTE_PORT);
    inet_pton(AF_INET, REMOTE_ADDR_STR, &remote_addr.sin_addr);

    if (connect(socket_fd, (struct sockaddr*)&remote_addr, (socklen_t)sizeof(remote_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
#elif defined (HOTSPOT_LAN_NETWORK)
    inet_pton(AF_INET, FIRST_REMOTE_ADDR_STR, &first_remote_addr.sin_addr);
    inet_pton(AF_INET, SECOND_REMOTE_ADDR_STR, &second_remote_addr.sin_addr);
    
    if ((connect(socket_fd, (struct sockaddr*)&first_remote_addr, (socklen_t)sizeof(first_remote_addr)) < 0)
        && (connect(socket_fd, (struct sockaddr*)&second_remote_addr, (socklen_t)sizeof(second_remote_addr)) < 0))
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
#endif // !HOME_LAN_NETWORK

    write(socket_fd, command, command_size);
    close(socket_fd);

    return 0;
}