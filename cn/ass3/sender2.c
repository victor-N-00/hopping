#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define ROWS 4
#define COLS 4


int main() {
   int sock;
   struct sockaddr_in server;
   char matrix[ROWS + 1][COLS + 2];
   int i, j, count;


   sock = socket(AF_INET, SOCK_STREAM, 0);
   server.sin_family = AF_INET;
   server.sin_port = htons(9000);
   server.sin_addr.s_addr = inet_addr("172.29.3.174");


   connect(sock, (struct sockaddr *)&server, sizeof(server));


   printf("Enter %d datawords of length %d:\n", ROWS, COLS);
   for(i = 0; i < ROWS+1; i++) {
       printf("Word %d: ", i + 1);
       scanf("%s", matrix[i]);
   }


   for (i = 0; i < ROWS; i++) {
       // count = 0;
       // for (j = 0; j < COLS; j++) {
       //     if (matrix[i][j] == '1') count++;
       // }
       // matrix[i][COLS] = (count % 2 == 0) ? '0' : '1';
       matrix[i][COLS + 1] = '\0';
   }


   // for (j = 0; j <= COLS; j++){
   //     count = 0;
   //     for (i = 0; i < ROWS; i++) {
   //         if (matrix[i][j] == '1') count++;
   //     }
   //     matrix[ROWS][j] = (count % 2 == 0) ? '0' : '1';
   // }
   matrix[ROWS][COLS + 1] = '\0';


   printf("\nFinal Matrix to Transmit (with 2D Parity):\n");
   for (i = 0; i <= ROWS; i++) {
       printf("%s\n", matrix[i]);
       send(sock, matrix[i], strlen(matrix[i]), 0);
       send(sock, "\n", 1, 0);
   }


   printf("\nData transmitted successfully.\n");
   close(sock);
   return 0;
}
