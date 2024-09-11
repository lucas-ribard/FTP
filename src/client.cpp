#include "./common/network_utils.hpp"
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 4)
    {

        std::cerr << "Usage : ./lpf ip:port -upload/-download filename" << std::endl;
        std::cout << "hint : ip:port should be 127.0.0.1:8080" << std::endl;
        return -1;
    }

    std::string ip_port(argv[1]);  // ip:port
    std::string command(argv[2]);  // Command ( -upload, -download)
    std::string filename(argv[3]); // file

    int sock = create_socket();
    std::string ip = ip_port.substr(0, ip_port.find(":"));       // Extrait l'IP
    int port = std::stoi(ip_port.substr(ip_port.find(":") + 1)); // Extrait le port
    connect_to_server(sock, ip.c_str(), port);

    std::cout << "Entrer votre message : " << std::endl;

    std::string input;
    std::cin >> input;
    send_message(sock, input.c_str());
    std::cout << "Message envoyé : " << input << std::endl;

    char buffer[1024] = {0};
    receive_message(sock, buffer, 1024);
    std::cout << "Réponse reçue : " << buffer << std::endl;

    close(sock);
    return 0;
}
