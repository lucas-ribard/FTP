#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *ping = "ping";
    char buffer[1024] = {0};

    // socket creation
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Échec de la création du socket" << std::endl;
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // address conversion
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Adresse invalide" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Échec de la connexion" << std::endl;
        return -1;
    }
    // read write
    send(sock, ping, strlen(ping), 0);
    std::cout << "Message envoyé : ping" << std::endl;
    read(sock, buffer, 1024);
    std::cout << "Réponse reçue : " << buffer << std::endl;
    close(sock);
    return 0;
}
