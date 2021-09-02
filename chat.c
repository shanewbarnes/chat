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

void *chat_send(void *args) {
  
  struct receive_args *fargs = args;
  int connection = fargs -> client;
  char *fname = fargs -> name;

  strcat(fname, ": ");

  char message[256];
  char messagebuf[256];  
  
  while (true) {
    fgets(message, sizeof(message), stdin);
    strcpy(messagebuf, fname);
    strcat(messagebuf, message);
    write(connection, messagebuf, sizeof(messagebuf));
    //memset(message, 0, strlen(message));
    //memset(messagebuf, 0, strlen(messagebuf));
  }
  return NULL;
}

void *chat_receive(void *arg) {

  int *connection = (int *) arg;

  char message[256];

  while (read(*connection, message, sizeof(message)) > 0) {
    printf("%s\n", message);
  }
  return NULL;
}

char* get_name() {
  char *name = malloc(32);
  printf("Enter your name: ");
  scanf("%31s", name);
  return name;
}
