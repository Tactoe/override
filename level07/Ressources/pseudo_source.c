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
//   08048791 8d 5c 24 24     LEA        EBX=>buffer,[ESP + 0x24]
// 08048795 b8 00 00        MOV        EAX,0x0
//          00 00
// 0804879a ba 64 00        MOV        EDX,0x64
//          00 00
// 0804879f 89 df           MOV        EDI,EBX
// 080487a1 89 d1           MOV        ECX,EDX
// 080487a3 f3 ab           STOSD.REP  ES:EDI

  // translated by ghidra as 

  // piVar5 = buffer;
  // for (iVar2 = 100; iVar2 != 0; iVar2 = iVar2 + -1) {
  //   *piVar5 = 0;
  //   piVar5 = piVar5 + 1;
  // }

  // easier to say
  memset(buffer, 0, 100);

  for (; *avCopy != (char *)0x0; avCopy = avCopy + 1) {
    // 080487a7 8b 44 24 1c     MOV        EAX,dword ptr [ESP + 0x1c]=>avCopy
    // 080487ab 8b 00           MOV        EAX,dword ptr [EAX]
    // 080487ad c7 44 24        MOV        dword ptr [ESP + 0x14]=>local_1cc,0xffffffff
    //          14 ff ff 
    //          ff ff
    // 080487b5 89 c2           MOV        EDX,EAX
    // 080487b7 b8 00 00        MOV        EAX,0x0
    //          00 00
    // 080487bc 8b 4c 24 14     MOV        ECX,dword ptr [ESP + 0x14]=>local_1cc
    // 080487c0 89 d7           MOV        EDI,EDX
    // 080487c2 f2 ae           SCASB.REP   ES:EDI

    // translated by ghidra as

    // uVar3 = 0xffffffff;
    // pcVar6 = *avCopy;
    // do {
    //   if (uVar3 == 0) break;
    //   uVar3 = uVar3 - 1;
    //   cVar1 = *pcVar6;
    //   pcVar6 = pcVar6 + (uint)bVar11 * -2 + 1;
    // } while (cVar1 != '\0');
    // memset(*avCopy,0,~uVar3 - 1);

    //easier to say 

    memset(*avCopy,0,strlen(avCopy));
  }
  for (; *envCopy != (char *)0x0; envCopy = envCopy + 1) {

    // 080487f6 8b 44 24 18     MOV        EAX,dword ptr [ESP + 0x18]=>envCopy
    // 080487fa 8b 00           MOV        EAX,dword ptr [EAX]
    // 080487fc c7 44 24        MOV        dword ptr [ESP + 0x14]=>local_1cc,0xffffffff
    //          14 ff ff 
    //          ff ff
    // 08048804 89 c2           MOV        EDX,EAX
    // 08048806 b8 00 00        MOV        EAX,0x0
    //          00 00
    // 0804880b 8b 4c 24 14     MOV        ECX,dword ptr [ESP + 0x14]=>local_1cc
    // 0804880f 89 d7           MOV        EDI,EDX
    // 08048811 f2 ae           SCASB.RE   ES:EDI

    // translated by ghidra as

    // uVar3 = 0xffffffff;
    // pcVar6 = *envCopy;
    // do {
    //   if (uVar3 == 0) break;
    //   uVar3 = uVar3 - 1;
    //   cVar1 = *pcVar6;
    //   pcVar6 = pcVar6 + (uint)bVar11 * -2 + 1;
    // } while (cVar1 != '\0');
    
    //easier to say 

    memset(*envCopy,0,strlen(envCopy));
  }
  puts(
      "----------------------------------------------------\n  Welcome to wil\'s crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n"
      );
  do {
    printf("Input command: ");
    i = 1;
    fgets(command,0x14,stdin);

    //     08048887 8d 84 24        LEA        EAX=>command,[ESP + 0x1b8]
    //          b8 01 00 00
    // 0804888e c7 44 24        MOV        dword ptr [ESP + 0x14]=>local_1cc,0xffffffff
    //          14 ff ff 
    //          ff ff
    // 08048896 89 c2           MOV        EDX,EAX
    // 08048898 b8 00 00        MOV        EAX,0x0
    //          00 00
    // 0804889d 8b 4c 24 14     MOV        ECX,dword ptr [ESP + 0x14]=>local_1cc
    // 080488a1 89 d7           MOV        EDI,EDX
    // 080488a3 f2 ae           SCASB.RE   ES:EDI

    // translated by ghidra as

    // uVar3 = 0xffffffff;
    // pcVar6 = command;
    // do {
    //   if (uVar3 == 0) break;
    //   uVar3 = uVar3 - 1;
    //   cVar1 = *pcVar6;
    //   pcVar6 = pcVar6 + (uint)bVar11 * -2 + 1;
    // } while (cVar1 != '\0');
    // uVar3 = ~uVar3;
    // bVar8 = uVar3 == 1;
    // bVar10 = uVar3 == 2;
    // command[uVar3 - 2] = '\0';

    //easier to say

    command[strlen(command)] = '\0';

    //     080488b7 8d 84 24        LEA        EAX=>command,[ESP + 0x1b8]
    //          b8 01 00 00
    // 080488be 89 c2           MOV        EDX,EAX
    // 080488c0 b8 5b 8d        MOV        EAX,s_store_08048d5b                             = "store"
    //          04 08
    // 080488c5 b9 05 00        MOV        ECX,0x5
    //          00 00
    // 080488ca 89 d6           MOV        ESI,EDX
    // 080488cc 89 c7           MOV        EDI,EAX
    // 080488ce f3 a6           CMPSB.REPE ES:EDI=>s_store_08048d5b,ESI                     = "store"

    // translated by ghidra as 

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
    // bVar9 = false;
    // bVar8 = (!bVar8 && !bVar10) == bVar8;

    // easier to say
    
    bVar8 = strncmp(command, "store", 5);
    if (bVar8) {
      i = store_number(buffer);
    }
    else {
      // 080488f8 8d 84 24        LEA        EAX=>command,[ESP + 0x1b8]
      //          b8 01 00 00
      // 080488ff 89 c2           MOV        EDX,EAX
      // 08048901 b8 61 8d        MOV        EAX,s_read_08048d61                              = "read"
      //          04 08
      // 08048906 b9 04 00        MOV        ECX,0x4
      //          00 00
      // 0804890b 89 d6           MOV        ESI,EDX
      // 0804890d 89 c7           MOV        EDI,EAX
      // 0804890f f3 a6           CMPSB.REPE ES:EDI=>s_read_08048d61,ESI                      = "read"

      // translated by ghidra as

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
      // bVar10 = false;
      // bVar8 = (!bVar9 && !bVar8) == bVar9;

      // easier to say
      
      bVar8 = strncmp(command, "read", 4);
      if (bVar8) {
        i = read_number(buffer);
      }
      else {

        // 08048939 8d 84 24        LEA        EAX=>command,[ESP + 0x1b8]
        //          b8 01 00 00
        // 08048940 89 c2           MOV        EDX,EAX
        // 08048942 b8 66 8d        MOV        EAX,s_quit_08048d66                              = "quit"
        //          04 08
        // 08048947 b9 04 00        MOV        ECX,0x4
        //          00 00
        // 0804894c 89 d6           MOV        ESI,EDX
        // 0804894e 89 c7           MOV        EDI,EAX
        // 08048950 f3 a6           CMPSB.REPE ES:EDI=>s_quit_08048d66,ESI                      = "quit"


        // translated by ghidra as 

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
        // if ((!bVar10 && !bVar8) == bVar10) {

        // easier to say

        bVar10 = strncmp(command, "quit", 4);

        if (bVar10) {
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