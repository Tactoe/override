#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth(char *login,uint serial)

{
  size_t loginLength;
  int i;
  uint hash;
  
  login[strcspn(login,"\n")] = '\0';
  loginLength = strnlen(login,0x20);
  if ((int)loginLength < 6) {
    return 1;
  }
  else {
    if (ptrace(0, 0 , 1, 0) == -1) {
      puts("\x1b[32m.---------------------------.");
      puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
      puts("\x1b[32m\'---------------------------\'");
      return 1;
    }
    else {
      hash = ((int)login[3] ^ 0x1337U) + 0x5eeded;
      for (i = 0; i < (int)loginLength; i = i + 1) {
        if (login[i] < 32) {
          return 1;
        }
	int edx = 0x88233b2b;
        temp = ((int)login[i] ^ hash);
	int x = temp * edx;
	x = (temp - edx) / 2) + edx;
	x = (x / 1024) * 1337
	hash = hash + (temp - x);
      }
      if (serial == hash) {
        return 0;
      }
      else {
        return 1;
      }
    }
  }
}

int main(void)

{
  uint serial;
  char login [32];
  
  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(login,0x20,stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  scanf("%u", &serial);

  if (auth(login, serial) == 0) {
    puts("Authenticated!");
    system("/bin/sh");
    return 0;
  }
  return 1;
}
