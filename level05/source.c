#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)

{
  char buffer [100];
  uint i;
  
  fgets(buffer,100,stdin);
  i = 0;
  do {
    if (i >= strlen(buffer)) {
      printf(buffer);
      exit(0);
    }
    if ((buffer[i] > 64) && (buffer[i] < 91)) {
      buffer[i] = buffer[i] ^ 0x20;
    }
    i++;
  } while( true );
}