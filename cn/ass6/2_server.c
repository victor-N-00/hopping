#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define DB_FILE "database.txt"

#define REQ_NAME 1
#define REQ_NUM 9
#define ETX 3

void handle_client(int client_socket) {
    unsigned char buffer[BUFFER_SIZE] = {0};
    unsigned char reply[BUFFER_SIZE] = {0};
    char response_str[256] = "Address not found";
    
    int bytes_read = read(client_socket, buffer, sizeof(buffer));
    
    if (bytes_read > 0) {
        int req_code = buffer[0];
        int data_len = 0;
        for (int i = 1; i < bytes_read; i++) {
            if (buffer[i] == ETX) {
                data_len = i - 1;
                break;
            }
        }
        FILE *file = fopen(DB_FILE, "r");
        if (file != NULL) {
            char line[BUFFER_SIZE];
            int current_id;
            char name[256];
            int requested_id;
            char requested_name[256] = {0};

            if (req_code == REQ_NUM) {
                memcpy(&requested_id, &buffer[1], sizeof(int));
            } else if (req_code == REQ_NAME) {
                memcpy(requested_name, &buffer[1], data_len);
                requested_name[data_len] = '\0';
            }

            while (fgets(line, sizeof(line), file)) {
                if (sscanf(line, "%d %s", &current_id, name) == 2) {
                    if (req_code == REQ_NUM && current_id == requested_id) {
                        strcpy(response_str, name);
                        break;
                    } 
                    else if (req_code == REQ_NAME && strcmp(name, requested_name) == 0) {
                        sprintf(response_str, "%d", current_id);
                        break;
                    }
                }
            }
            fclose(file);
        } else {
            strcpy(response_str, "Server Error: Cannot open database.txt");
        }
    }

    int reply_len = strlen(response_str);
    memcpy(reply, response_str, reply_len);
    reply[reply_len] = ETX;

    write(client_socket, reply, reply_len + 1);
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

    printf("Directory Server running on port %d with Protocol v2...\n", PORT);
    while(1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket >= 0) {
            handle_client(client_socket);
        }
    }
    return 0;
}