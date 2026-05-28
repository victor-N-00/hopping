#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    int client_fd = accept(server_fd, nullptr, nullptr);

    fd_set readfds;
    char buffer[1024];

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        FD_SET(client_fd, &readfds);

        select(client_fd + 1, &readfds, nullptr, nullptr, nullptr);

        if (FD_ISSET(0, &readfds)) {
            memset(buffer, 0, sizeof(buffer));
            read(0, buffer, sizeof(buffer));
            send(client_fd, buffer, strlen(buffer), 0);
        }

        if (FD_ISSET(client_fd, &readfds)) {
            memset(buffer, 0, sizeof(buffer));
            int n = recv(client_fd, buffer, sizeof(buffer), 0);
            if (n <= 0) break;
            std::cout << buffer;
        }
    }

    close(client_fd);
    close(server_fd);
}
