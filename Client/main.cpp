#include <iostream>
#include <string_view>
#include <sockpp/tcp_connector.h>
#include <sockpp/inet_address.h>

constexpr uint16_t remote_port {4455};

#ifdef HOME_NET
    const sockpp::inet_address first_addr {"192.168.3.106", remote_port};
    const sockpp::inet_address second_addr {"192.168.3.107", remote_port};
#elif defined(PHONE_NET)
    const sockpp::inet_address first_addr {"192.168.43.148", remote_port};
    const sockpp::inet_address second_addr {"192.168.43.149", remote_port};
#endif

static inline void show_usage(const char *prog_name);

int main(int argc, char **argv)
{
    if (argc < 2) {
        show_usage(argv[0]);
        return 0;
    }

    std::string_view command {argv[1]};
    sockpp::tcp_connector tcp_conn {};

    if (command != "poweroff" && command != "reboot") {
        std::cerr << "Error: Unknown command: " << command << "\n";
        show_usage(argv[0]);
        return 1;
    }

    if (!tcp_conn.connect(first_addr) && !tcp_conn.connect(second_addr)) {
        std::cerr << "Error: " << tcp_conn.last_error_str() << "\n";
        return 1;
    }

    tcp_conn.write(command.data(), command.size() + 1);
    tcp_conn.close();

    return 0;
}

static inline void show_usage(const char *prog_name)
{
    std::cout << "Usage: " << prog_name << " <comand>\n"
              << "Available commands:\n"
              << "reboot    - reboot the target\n"
              << "poweroff  - shutdown the target\n";
}
