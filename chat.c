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
    // something is wroing here this is the problem

    scanf("%19s", message);
    write(*client, message, sizeof(message));
  }
  return NULL;
}

void *chat_receive(void *arg) {

  int *client = (int *) arg;
  char message[20];

  while (read(*client, message, sizeof(message)) > 0) {
    printf(" ");
    printf("%s", message);
  }
  return NULL;
}

char* get_name() {
  char *name = malloc(20);
  printf("Enter your name:");
  scanf("%19s", name);
  return name;
}
