#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth(char *login,uint serial)

{
  size_t loginLength;
  int iVar1;
  long lVar2;
  int local_18;
  uint local_14;
  
  loginLength = strcspn(login,"\n");
  login[loginLength] = '\0';
  loginLength = strnlen(login,0x20);
  if ((int)loginLength < 6) {
    iVar1 = 1;
  }
  else {
    lVar2 = ptrace(PTRACE_TRACEME);
    if (lVar2 == -1) {
      puts("\x1b[32m.---------------------------.");
      puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
      puts("\x1b[32m\'---------------------------\'");
      iVar1 = 1;
    }
    else {
      local_14 = ((int)login[3] ^ 0x1337U) + 0x5eeded;
      for (local_18 = 0; local_18 < (int)loginLength; local_18 = local_18 + 1) {
        if (login[local_18] < ' ') {
          return 1;
        }
        local_14 = local_14 + ((int)login[local_18] ^ local_14) % 0x539;
      }
      if (serial == local_14) {
        iVar1 = 0;
      }
      else {
        iVar1 = 1;
      }
    }
  }
  return iVar1;
}

int main(void)

{
  int iVar1;
  int iVar2;
  int in_GS_OFFSET;
  uint serial;
  char login [32];
  
  iVar1 = *(int *)(in_GS_OFFSET + 0x14);
  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(login,0x20,stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  __isoc99_scanf("%u",&serial);
  iVar2 = auth(login,serial);
  if (iVar2 == 0) {
    puts("Authenticated!");
    system("/bin/sh");
  }
  // canary check to see if the stack hasn't exploded, can be ignored in clean source
  if (iVar1 != *(int *)(in_GS_OFFSET + 0x14)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (uint)(iVar2 != 0);
}
