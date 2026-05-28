// server_poll.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    int msg_count = 0;

    struct pollfd fds[2];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
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

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    fds[1].fd = new_socket;
    fds[1].events = POLLIN;

    while (msg_count < 5) {

        poll(fds, 2, -1);  

        if (fds[1].revents & POLLIN) {
            int valread = read(new_socket, buffer, BUFFER_SIZE);
            if (valread <= 0) break;
            buffer[valread] = '\0';
            printf("Client: %s", buffer);
        }

        if (fds[0].revents & POLLIN) {
            fgets(buffer, BUFFER_SIZE, stdin);
            send(new_socket, buffer, strlen(buffer), 0);
            msg_count++;
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
