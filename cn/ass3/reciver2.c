
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define ROWS 4
#define COLS 4


int main() {
   int server_sock, client_sock;
   struct sockaddr_in server_addr, client_addr;
   socklen_t addr_size;
 
   char received[ROWS + 1][COLS + 2];
   int row_parity_count, col_parity_count;
   int error_row = -1, error_col = -1;


   server_sock = socket(AF_INET, SOCK_STREAM, 0);
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(9000);
   server_addr.sin_addr.s_addr = INADDR_ANY;


   bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
   listen(server_sock, 5);


   printf("Waiting for sender on port 9000...\n");
   addr_size = sizeof(client_addr);
   client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);


   for (int i = 0; i <= ROWS; i++) {
       char buffer[10] = {0};
       recv(client_sock, buffer, COLS + 2, 0);
       sscanf(buffer, "%s", received[i]);
   }


   printf("\nReceived 2D Data Block:\n");
   for (int i = 0; i <= ROWS; i++) {
       printf("%s\n", received[i]);
   }


   for (int i = 0; i <= ROWS; i++) {
       row_parity_count = 0;
       for (int j = 0; j <= COLS; j++) {
           if (received[i][j] == '1') row_parity_count++;
       }
       if (row_parity_count % 2 != 0) {
           error_row = i;
       }
   }


   for (int j = 0; j <= COLS; j++) {
       col_parity_count = 0;
       for (int i = 0; i <= ROWS; i++) {
           if (received[i][j] == '1') col_parity_count++;
       }
       if (col_parity_count % 2 != 0) {
           error_col = j;
       }
   }


   printf("\n--- Results ---\n");
   if (error_row == -1 && error_col == -1) {
       printf("Status: No errors detected.\n");
   } else if (error_row != -1 && error_col != -1) {
       printf("Status: Single-bit error detected!\n");
       printf("Location: Row %d, Column %d\n", error_row + 1, error_col + 1);
   }else{
       printf("multiple errors detected \n");
   }


   close(client_sock);
   close(server_sock);
   return 0;
}
