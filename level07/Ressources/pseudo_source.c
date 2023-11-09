#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_stdin(void)
{
  int i;
  
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
  __isoc99_scanf("%u",&userInput);
  clear_stdin();
  return userInput;
}

int store_number(int *buffer)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  printf(" Number: ");
  uVar1 = get_unum();
  printf(" Index: ");
  uVar2 = get_unum();
  if ((uVar2 % 3 == 0) || (uVar1 >> 0x18 == 0xb7)) {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    iVar3 = 1;
  }
  else {
    buffer[uVar2] = uVar1;
    iVar3 = 0;
  }
  return iVar3;
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
  char cVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  int *piVar5;
  char *pcVar6;
  byte *pbVar7;
  int in_GS_OFFSET;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  byte bVar11;
  char **envCopy;
  char **avCopy;
  int buffer [100];
  int i;
  char command [20];
  int local_14;
  
  bVar11 = 0;
  avCopy = av;
  envCopy = env;
  local_14 = *(int *)(in_GS_OFFSET + 0x14);
  i = 0;
  command[0] = '\0';
  command[1] = '\0';
  command[2] = '\0';
  command[3] = '\0';
  command[4] = '\0';
  command[5] = '\0';
  command[6] = '\0';
  command[7] = '\0';
  command[8] = '\0';
  command[9] = '\0';
  command[10] = '\0';
  command[11] = '\0';
  command[12] = '\0';
  command[13] = '\0';
  command[14] = '\0';
  command[15] = '\0';
  command[16] = '\0';
  command[17] = '\0';
  command[18] = '\0';
  command[19] = '\0';
  // piVar5 = buffer;
  // for (iVar2 = 100; iVar2 != 0; iVar2 = iVar2 + -1) {
  //   *piVar5 = 0;
  //   piVar5 = piVar5 + 1;
  // }
  memset(buffer, 0, 100);
  for (; *avCopy != (char *)0x0; avCopy = avCopy + 1) {
    // uVar3 = 0xffffffff;
    // pcVar6 = *avCopy;
    // do {
    //   if (uVar3 == 0) break;
    //   uVar3 = uVar3 - 1;
    //   cVar1 = *pcVar6;
    //   pcVar6 = pcVar6 + (uint)bVar11 * -2 + 1;
    // } while (cVar1 != '\0');
    strlen avCopy;
    memset(*avCopy,0,~uVar3 - 1);
    memset(*avCopy,0,strlen(avCopy));
  }
  for (; *envCopy != (char *)0x0; envCopy = envCopy + 1) {
    // uVar3 = 0xffffffff;
    // pcVar6 = *envCopy;
    // do {
    //   if (uVar3 == 0) break;
    //   uVar3 = uVar3 - 1;
    //   cVar1 = *pcVar6;
    //   pcVar6 = pcVar6 + (uint)bVar11 * -2 + 1;
    // } while (cVar1 != '\0');
    strlen envCopy;
    memset(*envCopy,0,~uVar3 - 1);
    memset(*envCopy,0,strlen(envCopy));
  }
  puts(
      "----------------------------------------------------\n  Welcome to wil\'s crappy number stora ge service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n"
      );
  do {
    printf("Input command: ");
    i = 1;
    fgets(command,0x14,stdin);
    // uVar3 = 0xffffffff;
    // pcVar6 = command;
    // do {
    //   if (uVar3 == 0) break;
    //   uVar3 = uVar3 - 1;
    //   cVar1 = *pcVar6;
    //   pcVar6 = pcVar6 + (uint)bVar11 * -2 + 1;
    // } while (cVar1 != '\0');
    strlen command;
    uVar3 = ~uVar3;
    bVar8 = uVar3 == 1;
    bVar10 = uVar3 == 2;
    command[uVar3 - 2] = '\0';
    // iVar2 = 5;
    // pbVar4 = (byte *)command;
    // pbVar7 = (byte *)"store";
    // do {
    //   if (iVar2 == 0) break;
    //   iVar2 = iVar2 + -1;
    //   bVar8 = *pbVar4 < *pbVar7;
    //   bVar10 = *pbVar4 == *pbVar7;
    //   pbVar4 = pbVar4 + (uint)bVar11 * -2 + 1;
    //   pbVar7 = pbVar7 + (uint)bVar11 * -2 + 1;
    // } while (bVar10);
    strncmp;
    bVar9 = false;
    bVar8 = (!bVar8 && !bVar10) == bVar8;
    if (bVar8) {
      i = store_number(buffer);
    }
    else {
      // iVar2 = 4;
      // pbVar4 = (byte *)command;
      // pbVar7 = (byte *)"read";
      // do {
      //   if (iVar2 == 0) break;
      //   iVar2 = iVar2 + -1;
      //   bVar9 = *pbVar4 < *pbVar7;
      //   bVar8 = *pbVar4 == *pbVar7;
      //   pbVar4 = pbVar4 + (uint)bVar11 * -2 + 1;
      //   pbVar7 = pbVar7 + (uint)bVar11 * -2 + 1;
      // } while (bVar8);
      strncmp;
      bVar10 = false;
      bVar8 = (!bVar9 && !bVar8) == bVar9;
      if (bVar8) {
        i = read_number(buffer);
      }
      else {
        // iVar2 = 4;
        // pbVar4 = (byte *)command;
        // pbVar7 = (byte *)"quit";
        // do {
        //   if (iVar2 == 0) break;
        //   iVar2 = iVar2 + -1;
        //   bVar10 = *pbVar4 < *pbVar7;
        //   bVar8 = *pbVar4 == *pbVar7;
        //   pbVar4 = pbVar4 + (uint)bVar11 * -2 + 1;
        //   pbVar7 = pbVar7 + (uint)bVar11 * -2 + 1;
        // } while (bVar8);
        strncmp;
        if ((!bVar10 && !bVar8) == bVar10) {
          // canary check to see if the stack hasn't exploded, can be ignored in clean source
          if (local_14 == *(int *)(in_GS_OFFSET + 0x14)) {
            return 0;
          }
                    /* WARNING: Subroutine does not return */
          __stack_chk_fail();
        }
      }
    }
    if (i == 0) {
      printf(" Completed %s command successfully\n",command);
    }
    else {
      printf(" Failed to do %s command\n",command);
    }
    command[0] = '\0';
    command[1] = '\0';
    command[2] = '\0';
    command[3] = '\0';
    command[4] = '\0';
    command[5] = '\0';
    command[6] = '\0';
    command[7] = '\0';
    command[8] = '\0';
    command[9] = '\0';
    command[10] = '\0';
    command[11] = '\0';
    command[12] = '\0';
    command[13] = '\0';
    command[14] = '\0';
    command[15] = '\0';
    command[16] = '\0';
    command[17] = '\0';
    command[18] = '\0';
    command[19] = '\0';
  } while( true );
}