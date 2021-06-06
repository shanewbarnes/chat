#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "chat.h"

void *chat_send(void *arg) {

  int *client = (int *) arg;
  char message[20];
  
  while (true) {
    printf("Name: ");
    scanf("%19s", message);
    send(*client, message, sizeof(message), 0);
  }
  return NULL;
}

void *chat_receive(void *arg) {

  int *client = (int *) arg;
  char message[20];
  
  while (recv(*client, message, sizeof(message), 0) > 0) {
    printf("\n%s\n", message);
  }
  return NULL;
}
