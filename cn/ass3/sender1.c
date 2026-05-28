#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main() {
   int sock;
   struct sockaddr_in server;
   char data[50];


   sock = socket(AF_INET, SOCK_STREAM, 0);


   server.sin_family = AF_INET;
   server.sin_port = htons(9000);
   server.sin_addr.s_addr = inet_addr("127.0.0.1");
   connect(sock, (struct sockaddr *)&server, sizeof(server));


   printf("Enter binary dataword: ");
   scanf("%s", data);


   printf("Transmitted data (with parity): %s\n", data);
   send(sock, data, strlen(data), 0);


   close(sock);
   return 0;
}
