#include "network_utils.hpp"
#include <iostream>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = create_socket();

    connect_to_server(sock, "127.0.0.1", PORT);

    const char *ping = "ping";
    send_message(sock, ping);
    std::cout << "Message envoyé : ping" << std::endl;

    char buffer[1024] = {0};
    receive_message(sock, buffer, 1024);
    std::cout << "Réponse reçue : " << buffer << std::endl;

    close(sock);
    return 0;
}
