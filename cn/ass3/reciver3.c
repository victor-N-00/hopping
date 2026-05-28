#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


void verify_crc(char *codeword, char *poly) {
   int cw_len = strlen(codeword);
   int poly_len = strlen(poly);
   char temp[120];
   strcpy(temp, codeword);


   for (int i = 0; i <= cw_len - poly_len; i++) {
       if (temp[i] == '1') {
           for (int j = 0; j < poly_len; j++) {
               temp[i + j] = (temp[i + j] == poly[j]) ? '0' : '1';
           }
       }
   }


   int error = 0;
   for (int i = cw_len - poly_len + 1; i < cw_len; i++) {
       if (temp[i] == '1') error = 1;
   }


   if (error) printf("\nRESULT: Error detected in transmission!\n");
   else printf("\nRESULT: No error detected. Data is correct.\n");
}


int main() {
   int s_sock, c_sock;
   struct sockaddr_in s_addr, c_addr;
   socklen_t size = sizeof(c_addr);
   char poly[20], codeword[120];


   s_sock = socket(AF_INET, SOCK_STREAM, 0);
   s_addr.sin_family = AF_INET;
   s_addr.sin_port = htons(9000);
   s_addr.sin_addr.s_addr = INADDR_ANY;


   bind(s_sock, (struct sockaddr*)&s_addr, sizeof(s_addr));
   listen(s_sock, 5);


   printf("Receiver waiting for CRC data...\n");
   c_sock = accept(s_sock, (struct sockaddr*)&c_addr, &size);


   recv(c_sock, poly, 20, 0);
   recv(c_sock, codeword, 120, 0);


   printf("Received Polynomial: %s\n", poly);
   printf("Received Codeword: %s\n", codeword);


   verify_crc(codeword, poly);


   close(c_sock);
   close(s_sock);
   return 0;
}
