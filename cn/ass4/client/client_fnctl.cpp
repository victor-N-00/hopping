#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (sockaddr*)&server, sizeof(server));

    fcntl(sock, F_SETFL, O_NONBLOCK);
    fcntl(0, F_SETFL, O_NONBLOCK);

    char buffer[1024];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int n = recv(sock, buffer, sizeof(buffer), 0);
        if (n > 0) std::cout << buffer;

        memset(buffer, 0, sizeof(buffer));
        n = read(0, buffer, sizeof(buffer));
        if (n > 0) send(sock, buffer, strlen(buffer), 0);
    }

    close(sock);
}
