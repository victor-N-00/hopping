#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


void xor_division(char *data, char *poly, char *remainder) {
   int data_len = strlen(data);
   int poly_len = strlen(poly);
   char temp[100];
   strcpy(temp, data);


   for (int i = 0; i <= data_len - poly_len; i++) {
       if (temp[i] == '1') {
           for (int j = 0; j < poly_len; j++) {
               temp[i + j] = (temp[i + j] == poly[j]) ? '0' : '1';
           }
       }
   }
  
   strncpy(remainder, temp + (data_len - poly_len + 1), poly_len - 1);
   remainder[poly_len - 1] = '\0';
}


int main() {
   int sock;
   struct sockaddr_in server;
   char data[100], poly[20], remainder[20], checksum[120];


   sock = socket(AF_INET, SOCK_STREAM, 0);
   server.sin_family = AF_INET;
   server.sin_port = htons(9000);
   server.sin_addr.s_addr = inet_addr("172.29.3.174");


   connect(sock, (struct sockaddr *)&server, sizeof(server));


   printf("Enter Binary Data: ");
   scanf("%s", data);
   printf("Enter Generator Polynomial: ");
   scanf("%s", poly);


   int n = strlen(poly);
   char padded_data[120];
   strcpy(padded_data, data);
   for (int i = 0; i < n - 1; i++) strcat(padded_data, "0");


   xor_division(padded_data, poly, remainder);


   if(remainder[1] == 0) remainder[1] = 1; else remainder[1]=0;


   strcpy(checksum, data);
   strcat(checksum, remainder);


   printf("CRC Remainder: %s\n", remainder);
   printf("Transmitting Codeword: %s\n", checksum);


   send(sock, poly, strlen(poly), 0);
   usleep(1000);
   send(sock, checksum, strlen(checksum), 0);


   close(sock);
   return 0;
}
