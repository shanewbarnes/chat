#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <assert.h>

#include "chat.h"

void *chat_send(void *arg) {

  int *connection = (int *) arg;
  char message[256];
  
  while (true) {
    scanf("%255s", message);
    write(*connection, message, sizeof(message));
  
    }
  return NULL;
}

void *chat_receive(void *arg) {

  int *connection = (int *) arg;
  char message[256];

  while (read(*connection, message, sizeof(message)) > 0) { 
    printf("\n%s\n", message);
  }
  
  return NULL;
}

char* get_name() {
  char *name = malloc(20);
  printf("Enter your name:");
  scanf("%19s", name);
  return name;
}
