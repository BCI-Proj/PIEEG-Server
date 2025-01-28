//
// Created by Raphael Paquin on 2025-01-28.
// Big thanks to this resource : https://beej.us/guide/bgnet/
// SERVER CODE FOR UDP.
//


#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(const int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "Usage: `" << argv[0] << " <port>`" << std::endl;
        return -1;
    }

    long int port = strtol(argv[1], nullptr, 10);

    int sockfd;
    char buffer[BUFFER_SIZE];
    sockaddr_in serverAddr{}, clientAddr{};
    socklen_t addrLen = sizeof(clientAddr);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Bind the socket
    if (bind(sockfd, reinterpret_cast<const sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return -1;
    }

    std::cout << "Server is running and waiting for messages..." << std::endl;

    while (true) {
        // Receive message
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, reinterpret_cast<sockaddr *>(&clientAddr), &addrLen);
        if (n < 0) {
            perror("Receive failed");
            continue;
        }
        buffer[n] = '\0'; // Null-terminate the message

        if (strncmp(buffer, "exit", 4) == 0) {
            std::cout << "Exiting Server..." << std::endl;
            break;
        }

        std::cout << "Received: " << buffer << std::endl;

        // Send acknowledgment
        const auto ack = "Message received";
        sendto(sockfd, ack, strlen(ack), 0, reinterpret_cast<sockaddr *>(&clientAddr), addrLen);
    }

    close(sockfd);
    return 0;
}
