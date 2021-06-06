#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
/*
#include <errno.h>
#include <err.h>
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "chat.h"

int client;

bool open_connection() {
  
  struct sockaddr_in saddr, caddr;
  int server;
  
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(16453);
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);

  server = socket(AF_INET, SOCK_STREAM, 0);

  int bind_flag = bind(server, (const struct sockaddr *)&saddr, sizeof(saddr));
  int listen_flag = listen(server, 5);

  uint32_t caddr_len = sizeof(caddr);
  
  if (server == -1 || bind_flag == -1 || listen_flag == -1) {
    return false;
  }
  
  while (true) {
    client = accept(server, (struct sockaddr *)&caddr, &caddr_len);

    pthread_t send_thread, receive_thread;
    pthread_create(&send_thread, NULL, chat_send, &client);
    pthread_create(&receive_thread, NULL, chat_receive, &client);
    pthread_join(send_thread, NULL);
    pthread_join(receive_thread, NULL);
  }
  
  return true;
}

void server_disconnect() {
  close(client);
  client = -1;
}

int main() {
  open_connection();
  //chat_receive();
  server_disconnect(); 
}
