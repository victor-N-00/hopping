#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define DB_FILE "database.txt"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    char response[BUFFER_SIZE] = "Address not found";
    int requested_id;

    if (read(client_socket, buffer, sizeof(buffer)) > 0) {
        requested_id = atoi(buffer);
        FILE *file = fopen(DB_FILE, "r");
        if (file != NULL) {
            char line[BUFFER_SIZE];
            int current_id;
            char name[256];

            while (fgets(line, sizeof(line), file)) {
                if (sscanf(line, "%d %s", &current_id, name) == 2) {
                    if (current_id == requested_id) {
                        strcpy(response, name);
                        break;
                    }
                }
            }
            fclose(file);
        } else {
            strcpy(response, "Server Error: Cannot open database.txt");
        }
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Directory Server is running on port %d...\n", PORT);

    while(1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket >= 0) {
            handle_client(client_socket);
        }
    }    
    return 0;
}