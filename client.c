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
#include <pthread.h>

#include "chat.h"

int client;

bool client_connect() {

  char *ip = "127.0.0.1";
  struct sockaddr_in caddr;
  
  caddr.sin_family = AF_INET;
  caddr.sin_port = htons(16453);
  
  inet_aton(ip, &caddr.sin_addr);

  client = socket(AF_INET, SOCK_STREAM, 0);

  int connect_flag = connect(client, (const struct sockaddr *)&caddr, sizeof(caddr));
  
  pthread_t send_thread, receive_thread;
  pthread_create(&send_thread, NULL, chat_send, &client);
  pthread_create(&receive_thread, NULL, chat_receive, &client);
  pthread_join(send_thread, NULL);
  pthread_join(receive_thread, NULL);
  
  if (client == -1 || connect_flag == -1) {
    return false;
  }

  return true;
}

void client_disconnect() {
  close(client);
  client = -1;
}

int main() {
  client_connect();
  //client_send();
  client_disconnect();
}
