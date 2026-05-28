#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

#define REQ_NAME 1
#define REQ_NUM 9
#define ETX 3

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    unsigned char buffer[BUFFER_SIZE] = {0};
    char input[256];
    int choice;

    if (argc != 2) {
        printf("Usage: %s <Server IP>\n", argv[0]);
        return -1;
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed. \n");
        return -1;
    }

    printf("Search by: \n1. Name\n2. Number\nChoice (1 or 2): ");
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);
    int packet_len = 0;

    if (choice == 2) {
        printf("Enter the numeric address: ");
        fgets(input, sizeof(input), stdin);
        int val = atoi(input);

        buffer[0] = REQ_NUM;
        memcpy(&buffer[1], &val, sizeof(int));
        
        packet_len = 1 + sizeof(int);
        buffer[packet_len] = ETX;
        packet_len++;
    } else {
        printf("Enter the name: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        int name_len = strlen(input);
        buffer[0] = REQ_NAME;
        memcpy(&buffer[1], input, name_len);
        
        packet_len = 1 + name_len;
        buffer[packet_len] = ETX;
        packet_len++;
    }

    write(sock, buffer, packet_len);
    
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_read = read(sock, buffer, BUFFER_SIZE);

    for (int i = 0; i < bytes_read; i++) {
        if (buffer[i] == ETX) {
            buffer[i] = '\0';
            break;
        }
    }

    printf("Server response: %s\n", buffer);
    close(sock);
    return 0;
}