#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    int client_fd = accept(server_fd, nullptr, nullptr);

    fcntl(client_fd, F_SETFL, O_NONBLOCK);
    fcntl(0, F_SETFL, O_NONBLOCK);

    char buffer[1024];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int n = recv(client_fd, buffer, sizeof(buffer), 0);
        if (n > 0) std::cout << buffer;

        memset(buffer, 0, sizeof(buffer));
        n = read(0, buffer, sizeof(buffer));
        if (n > 0) send(client_fd, buffer, strlen(buffer), 0);
    }

    close(client_fd);
    close(server_fd);
}
