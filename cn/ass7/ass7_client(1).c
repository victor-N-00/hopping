#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    pid_t pid;

    char *ip = "127.0.0.1"; 
    if (argc > 1) {
        ip = argv[1];
    }

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed. Is the server running?");
        exit(1);
    }
    printf("Connected to server at %s. Type 'exit' to quit.\n\n", ip);
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
                printf("\n[Notice]: Server disconnected.\n");
                kill(getppid(), SIGTERM);
                exit(0);
            }
            printf("\r[Server]: %s", buffer);
        }
    } else {
        while (1) {
            memset(buffer, 0, BUFFER_SIZE);
            fgets(buffer, BUFFER_SIZE, stdin);
            
            send(client_socket, buffer, strlen(buffer), 0);
            
            if (strncmp(buffer, "exit", 4) == 0) {
                printf("Disconnecting...\n");
                kill(pid, SIGTERM);
                break;
            }
        }
    }

    close(client_socket);
    return 0;
}