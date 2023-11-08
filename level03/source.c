#include <stdio.h>
#include <stdlib.h>

void decrypt(int n)

{
  uint i;
  uint len;
  char buff [] = `"Q}|u`sfg~sf{}|a3"`;
  
  len = strlen(buff);

  i = 0;
  while(i < len) {
    buff[i] = n ^ buff[i];
    i++;
  }

  if (strncmp(buff, "Congratulations!", 0x11);) {
    system("/bin/sh");
  }
  else {
    puts("\nInvalid Password");
  }
}

void test(int userInput,int leetDood)
{
  int n;
  
  n = leetDood - userInput;
  switch(key) {
  default:
    n = rand();
    decrypt(key);
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
    decrypt(n);
    break;
  }
  return;
}

int main(void)

{
  uint __seed;
  int password;
  int local_10;
  
  __seed = time((time_t *)0x0);
  srand(__seed);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf("%d",&password);
  test(password,0x1337d00d);
  return 0;
}
