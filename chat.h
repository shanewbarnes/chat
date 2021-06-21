#ifndef CHAT_H
#define CHAT_H

struct receive_args {
  int client;
  char *name;
};

void *chat_send();

void *chat_receive();

char *get_name();

#endif
