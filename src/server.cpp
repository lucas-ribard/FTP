#include "network_utils.hpp"
#include <iostream>
#include <unistd.h>

#define PORT 8080

int main() {
    int server_fd = create_socket();
    struct sockaddr_in address;

    bind_socket(server_fd, address, PORT);
    listen_socket(server_fd);

    std::cout << "En attente de connexions..." << std::endl;
    
    int new_socket = accept_connection(server_fd, address);
    
    char buffer[1024] = {0};
    receive_message(new_socket, buffer, 1024);
    std::cout << "Message reçu : " << buffer << std::endl;

    const char *pong = "pong";
    send_message(new_socket, pong);
    std::cout << "Réponse envoyée : pong" << std::endl;

    close(new_socket);
    close(server_fd);
    return 0;
}
