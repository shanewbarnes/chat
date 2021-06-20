#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "chat.h"

int client;
char *name;

bool client_connect() {
  
  struct sockaddr_in caddr;
  struct hostent *host;
  struct receive_args args;
  char *ip;
  char hostbuffer[256];
  
  caddr.sin_family = AF_INET;
  caddr.sin_port = htons(16455);

  gethostname(hostbuffer, sizeof(hostbuffer));
  host = gethostbyname(hostbuffer);
  ip = inet_ntoa(*((struct in_addr*) host->h_addr_list[0]));

  inet_aton(ip, &caddr.sin_addr);

  client = socket(AF_INET, SOCK_STREAM, 0);
  //args.client = client;

  int connect_flag = connect(client, (const struct sockaddr *)&caddr, sizeof(caddr));

  if (client == -1 || connect_flag == -1) {
    return false;
  }

  //args.name = get_name();

  pthread_t send_thread, receive_thread;
  pthread_create(&receive_thread, NULL, chat_receive, &client);
  pthread_create(&send_thread, NULL, chat_send, &client);
  pthread_join(receive_thread, NULL);
  pthread_join(send_thread, NULL);
  
  return true;
}

void client_disconnect() {
  close(client);
  client = -1;
}

int main() {
  client_connect();  
  client_disconnect();
}
