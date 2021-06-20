#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "chat.h"

int client;
char *name;

bool open_connection() {
  
  struct sockaddr_in saddr, caddr;
  struct receive_args args;
  int server;
  
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(16455);
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);

  server = socket(AF_INET, SOCK_STREAM, 0);

  int bind_flag = bind(server, (const struct sockaddr *)&saddr, sizeof(saddr));
  int listen_flag = listen(server, 5);

  uint32_t caddr_len = sizeof(caddr);
  
  if (server == -1 || bind_flag == -1 || listen_flag == -1) {
    return false;
  }

  //args.name = get_name();
  
  while (true) {
    
    client = accept(server, (struct sockaddr *)&caddr, &caddr_len);
    //    args.client = client;

    
    pthread_t send_thread, receive_thread;
    pthread_create(&receive_thread, NULL, chat_receive, &client);
    pthread_create(&send_thread, NULL, chat_send, &client);
    pthread_join(receive_thread, NULL);    
    pthread_join(send_thread, NULL);
  }
  
  return true;
}

void server_disconnect() {
  close(client);
  client = -1;
}

int main() {
  open_connection();
  
  server_disconnect(); 
}
