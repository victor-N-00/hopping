#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    pid_t pid;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    listen(server_fd, 5);
    printf("Server is listening on port %d...\n", PORT);
    addr_size = sizeof(client_addr);
    client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
    if (client_socket < 0) {
        perror("Accept failed");
        exit(1);
    }
    printf("Client connected!. Type 'exit' to quit.\n\n");

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        while (1) {
            memset(buffer, 0, BUFFER_SIZE);
            int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
            
            if (bytes_received <= 0) {
                printf("\n[Notice]: Client disconnected.\n");
                kill(getppid(), SIGTERM);
                exit(0);
            }
            printf("\r[Client]: %s", buffer);
        }
    } else {
        while (1) {
            memset(buffer, 0, BUFFER_SIZE);
            fgets(buffer, BUFFER_SIZE, stdin);
            
            send(client_socket, buffer, strlen(buffer), 0);
            if (strncmp(buffer, "exit", 4) == 0) {
                printf("Closing server\n");
                kill(pid, SIGTERM);
            }
        }
    }

    close(client_socket);
    close(server_fd);
    return 0;
}