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
    int client_sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    if (argc != 4) {
        printf("Usage: %s [server_address] [port_number] [file_name.txt]\n", argv[0]);
        exit(1);
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    char *filename = argv[3];

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("Error: Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error: Connection to server failed");
        exit(1);
    }
    printf("Connected to server at %s:%d\n", ip, port);

    if (write(client_sock, filename, strlen(filename)) < 0) {
        perror("Error: Failed to send filename");
        exit(1);
    }
    printf("Requested file: %s\n", filename);

    int file_fd = creat("receive.txt", 0666); 
    if (file_fd < 0) {
        perror("Error: Failed to create receive.txt");
        exit(1);
    }

    int bytes_read;
    int total_bytes = 0;
    int first_chunk = 1;

    printf("Receiving file from server\n");
    while ((bytes_read = read(client_sock, buffer, BUFFER_SIZE)) > 0) {
        if (first_chunk && strncmp(buffer, "ERROR_FILE_NOT_FOUND", 20) == 0) {
            printf("Server reported: File not found.\n");
            close(file_fd);
            unlink("receive.txt");
            exit(1);
        }
        first_chunk = 0;

        if (write(file_fd, buffer, bytes_read) < 0) {
            perror("Error: Failed to write to file");
            break;
        }
        total_bytes += bytes_read;
    }

    if (bytes_read < 0) {
        perror("Error: Read from socket failed");
    } else {
        printf("File successfully received and saved as 'receive.txt' (%d bytes).\n", total_bytes);
    }

    close(file_fd);
    close(client_sock);
    return 0;
}