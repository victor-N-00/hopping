#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (sockaddr*)&server, sizeof(server));

    fd_set readfds;
    char buffer[1024];

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        FD_SET(sock, &readfds);

        select(sock + 1, &readfds, nullptr, nullptr, nullptr);

        if (FD_ISSET(0, &readfds)) {
            memset(buffer, 0, sizeof(buffer));
            read(0, buffer, sizeof(buffer));
            send(sock, buffer, strlen(buffer), 0);
        }

        if (FD_ISSET(sock, &readfds)) {
            memset(buffer, 0, sizeof(buffer));
            int n = recv(sock, buffer, sizeof(buffer), 0);
            if (n <= 0) break;
            std::cout << buffer;
        }
    }

    close(sock);
}
