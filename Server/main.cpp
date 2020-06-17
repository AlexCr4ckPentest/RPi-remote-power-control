#include <iostream>
#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_acceptor.h>
#include <sockpp/inet_address.h>

constexpr uint16_t port {4455};

int main()
{
    char recived_command[10] {};
    sockpp::tcp_acceptor tcp_acc {port};
    sockpp::tcp_socket client_sock {};

    if (!tcp_acc) return 1;

    client_sock = tcp_acc.accept();

    client_sock.read(recived_command, sizeof(recived_command));
    tcp_acc.close();
    client_sock.close();

    system(recived_command);

    return 0;
}
