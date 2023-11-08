#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct message
{
    char text[140];
    char username[40];
    int len;
} message;

void secret_backdoor(void)
{
  char buffer [128];
  
  fgets(buffer,0x80,_stdin);
  system(buffer);
  return;
}

void set_msg(message *message)

{
  char buffer [1024];
  
  memset(buffer, '\0', 1024);
  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets(buffer,0x400,_stdin);
  strncpy(message->msg, buffer, message->length);
  return;
}

void set_username(message *message)
{
  char buffer [128];
  int i;
  
  memset(local_buffer, '\0', 128);
  puts(">: Enter your username");
  printf(">>: ");
  fgets(buffer,0x80,_stdin);
  for (i = 0; i < 41 && buffer[i] != '\0'; i++) {
    message->username[i] = buffer[i];
  }
  printf(">: Welcome, %s",message->username);
  return;
}

void handle_msg(void)

{
  message mess;
  
  memset(mess.username, 0, 40);
  mess.length = 0x8c;
  set_username(&mess);
  set_msg(&mess);
  puts(">: Msg sent!");
  return;
}

int main(void)
{
  puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n- -------------------------------------------");
  handle_msg();
  return 0;
}