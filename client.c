#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
/*
#include <errno.h>
#include <err.h>
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

bool client_connect() {

  char *ip = "127.0.0.1";
  struct sockaddr_in caddr;
  int client;
  
  caddr.sin_family = AF_INET;
  caddr.sin_port = htons(16453);
  
  inet_aton(ip, &caddr.sin_addr);

  client = socket(AF_INET, SOCK_STREAM, 0);

  int connect_flag = connect(client, (const struct sockaddr *)&caddr, sizeof(caddr));

  char message[6];
  
  recv(client, message, sizeof(message), 0);

  printf("%s", message);
  
  if (client == -1 || connect_flag == -1) {
    return false;
  }
  
  close(client);
  client = -1;

  return true;
}

int main() {
  client_connect();
}
