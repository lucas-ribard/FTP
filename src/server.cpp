#include "network_utils.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main()
{
    int server_fd = create_socket();
    struct sockaddr_in address;

    bind_socket(server_fd, address, PORT);
    listen_socket(server_fd);

    std::cout << "En attente de connexions..." << std::endl;

    int new_socket = accept_connection(server_fd, address);

    char buffer[1024] = {0};
    receive_message(new_socket, buffer, 1024);
    std::cout << "Message reçu : " << buffer << std::endl;

    if (strcmp(buffer, "ping") != 0){
        std::cerr << "Message invalide, le server attend 'ping' " << std::endl;

        close(new_socket);
        close(server_fd);

        exit(EXIT_FAILURE);
    }
    else{
        const char *pong = "pong";
        send_message(new_socket, pong);
        std::cout << "Réponse envoyée : pong" << std::endl;
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
