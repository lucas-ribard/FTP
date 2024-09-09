#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *pong = "pong";

    // create the socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Échec de la création du socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Échec du bind" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // listen
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Échec du listen" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "En attente de connexion..." << std::endl;

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        std::cerr << "Échec de l'acceptation" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //read write
    read(new_socket, buffer, 1024);
    std::cout << "Message reçu : " << buffer << std::endl;
    send(new_socket, pong, strlen(pong), 0);
    std::cout << "Réponse envoyée : pong" << std::endl;

    // close everything
    close(new_socket);
    close(server_fd);
    return 0;
}
