#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_stdin(void)
{
  int i = 0;
  
  do {
    i = getchar();
    if ((char)i == '\n') {
      return;
    }
  } while ((char)i != -1);
  return;
}

int get_unum(void)
{
  int userInput;
  
  userInput = 0;
  fflush(stdout);
  scanf("%u",&userInput);
  clear_stdin();
  return userInput;
}

int store_number(int *buffer)
{
  uint unum1;
  uint unum2;
  
  printf(" Number: ");
  unum1 = get_unum();
  printf(" Index: ");
  unum2 = get_unum();
  if ((unum2 % 3 == 0) || (unum1 >> 0x18 == 0xb7)) {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    return 1;
  }
  else {
    buffer[unum2] = unum1;
    return 0;
  }
}

int read_number(int *buffer)
{
  int iVar1;
  
  printf(" Index: ");
  iVar1 = get_unum();
  printf(" Number at data[%u] is %u\n",iVar1,buffer[iVar1]);
  return 0;
}

int main(int ac,char **av,char **env)

{
  char **envCopy;
  char **avCopy;
  int buffer [100];
  int i;
  char command [20];
  
  avCopy = av;
  envCopy = env;
  i = 0;
  memset(command, 0, 20);
  memset(buffer, 0, 20);
  for (; *avCopy != (char *)0x0; **avCopy++) {
    memset(*avCopy, 0, strlen(*avCopy));
  }
  for (; *envCopy != (char *)0x0; **envCopy++) {
    memset(*envCopy, 0, strlen(*envCopy));
  }
  puts(
      "----------------------------------------------------\n  Welcome to wil\'s crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n"
      );
  do {
    printf("Input command: ");
    i = 1;
    fgets(command,0x14,stdin);
    command[strlen(&command) - 1] = '\0';
    if (strncmp(command, "store", 5)) {
      i = store_number(buffer);
    }
    else if (strncmp(command, "read", 4)) {
      i = read_number(buffer);
    }
    else if (strncmp(command, "quit", 4)){
          return 0;
    }

    if (i == 0) {
      printf(" Completed %s command successfully\n",command);
    }
    else {
      printf(" Failed to do %s command\n",command);
    }
    memset(command, 0, 20);
  } while( true );
}