#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


#define PORT 9000


int checkEvenParity(char data[]) {
   int count = 0;
   for (int i = 0; data[i] != '\0'; i++) {
       if (data[i] == '1')
           count++;
   }
   return (count % 2 == 0);
}


int main() {
   int server_fd, new_socket;
   struct sockaddr_in address;
   int addrlen = sizeof(address);
   char buffer[1024] = {0};




   server_fd = socket(AF_INET, SOCK_STREAM, 0);
   if (server_fd == -1) {
       perror("Socket failed");
       exit(1);
   }


   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);




   if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
       perror("Bind failed");
       exit(1);
   }




   listen(server_fd, 3);
   printf("Receiver waiting on port %d...\n", PORT);


   new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t *)&addrlen);
   if (new_socket < 0) {
       perror("Accept failed");
       exit(1);
   }


   printf("Sender connected.\n");


   while (1) {
       memset(buffer, 0, sizeof(buffer));
       int valread = read(new_socket, buffer, sizeof(buffer));
       if (valread <= 0)
           break;


       printf("\nReceived data: %s\n", buffer);


       if (checkEvenParity(buffer))
           printf("Status: No error detected (Even parity OK)\n");
       else
           printf("Status: ERROR detected! (Parity mismatch)\n");
   }


   close(new_socket);
   close(server_fd);
   return 0;
}
