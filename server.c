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

bool open_connection() {
  
  struct sockaddr_in saddr, caddr;
  int server, client;
  
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(16453);
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);

  server = socket(AF_INET, SOCK_STREAM, 0);

  int bind_flag = bind (server, (const struct sockaddr *)&saddr, sizeof(saddr));
  int listen_flag = listen(server, 5);

  uint32_t caddr_len = sizeof(caddr);

  client = accept(server, (struct sockaddr *)&caddr, &caddr_len);
  
  char message[] = "hello";
  
  send(client, message, sizeof(message), 0);

  if (server == -1 || bind_flag == -1 || listen_flag == -1) {
    return false;
  }

  return true;
}

int main() {
  open_connection();
}
