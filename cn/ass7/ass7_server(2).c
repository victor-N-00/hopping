#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    char filename[256];

    if (argc != 2) {
        printf("Usage: %s [port_number]\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Error: Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error: Bind failed");
        exit(1);
    }

    listen(server_sock, 5);
    printf("Server is listening on port %d\n", port);

    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    if (client_sock < 0) {
        perror("Error: Accept failed");
        exit(1);
    }
    printf("Client connected.\n");

    memset(filename, 0, sizeof(filename));
    if (read(client_sock, filename, sizeof(filename)) < 0) {
        perror("Error: Failed to read filename from socket");
        exit(1);
    }
    printf("Client requested file: %s\n", filename);

    int file_fd = open(filename, O_RDONLY);
    if (file_fd < 0) {
        perror("Error: File not found or cannot be opened");
        write(client_sock, "ERROR_FILE_NOT_FOUND", 20);
    } else {
        int bytes_read;
        printf("Transferring file to the client\n");
        while ((bytes_read = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
            if (write(client_sock, buffer, bytes_read) < 0) {
                perror("Error: Failed to write to socket");
                break;
            }
        }
        printf("[+] File transfer complete.\n");
        close(file_fd);
    }
    close(client_sock);
    close(server_sock);
    return 0;
}