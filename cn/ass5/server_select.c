#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    fd_set readfds;
    int msg_count = 0;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Waiting for connection...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    printf("Client connected!\n");

    while (msg_count < 5) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(new_socket, &readfds);

        int max_fd = new_socket;

        select(max_fd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(new_socket, &readfds)) {
            int valread = read(new_socket, buffer, BUFFER_SIZE);
            if (valread <= 0) break;
            buffer[valread] = '\0';
            printf("Client: %s", buffer);
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            fgets(buffer, BUFFER_SIZE, stdin);
            send(new_socket, buffer, strlen(buffer), 0);
            msg_count++;
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
