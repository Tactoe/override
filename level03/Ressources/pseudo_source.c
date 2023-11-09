#include <stdio.h>
#include <stdlib.h>

void decrypt(int n)

{
  uint len;
  int in_GS_OFFSET;
  uint i;
  char buff [17];
  int iStack_10;
  
  buff[0] = 'Q';
  buff[1] = '}';
  buff[2] = '|';
  buff[3] = 'u';
  buff[4] = '`';
  buff[5] = 's';
  buff[6] = 'f';
  buff[7] = 'g';
  buff[8] = '~';
  buff[9] = 's';
  buff[10] = 'f';
  buff[11] = '{';
  buff[12] = '}';
  buff[13] = '|';
  buff[14] = 'a';
  buff[15] = '3';
  buff[16] = '\0';

  // 0x0804869c <+60>:    lea    -0x1d(%ebp),%eax
  //  0x0804869f <+63>:    movl   $0xffffffff,-0x2c(%ebp)
  //  0x080486a6 <+70>:    mov    %eax,%edx
  //  0x080486a8 <+72>:    mov    $0x0,%eax
  //  0x080486ad <+77>:    mov    -0x2c(%ebp),%ecx
  //  0x080486b0 <+80>:    mov    %edx,%edi
  //  0x080486b2 <+82>:    repnz scas %es:(%edi),%al

  // translated by ghidra as

  // char *pcVar4;
  //   char cVar1;
  // len = 0xffffffff;
  // pcVar4 = buff;
  // do {
  //   if (len == 0) break;
  //   len = len - 1;
  //   cVar1 = *pcVar4;
  //   pcVar4 = pcVar4 + 1;
  // } while (cVar1 != '\0');

// easier to say

  len = strlen(buffer);

  i = 0;
  // 0x080486c7 <+103>:   lea    -0x1d(%ebp),%eax
  //  0x080486ca <+106>:   add    -0x28(%ebp),%eax
  //  0x080486cd <+109>:   movzbl (%eax),%eax
  //  0x080486d0 <+112>:   mov    %eax,%edx
  //  0x080486d2 <+114>:   mov    0x8(%ebp),%eax
  //  0x080486d5 <+117>:   xor    %edx,%eax
  //  0x080486d7 <+119>:   mov    %eax,%edx
  //  0x080486d9 <+121>:   lea    -0x1d(%ebp),%eax
  //  0x080486dc <+124>:   add    -0x28(%ebp),%eax
  //  0x080486df <+127>:   mov    %dl,(%eax)
  //  0x080486e1 <+129>:   addl   $0x1,-0x28(%ebp)
  //  0x080486e5 <+133>:   mov    -0x28(%ebp),%eax
  //  0x080486e8 <+136>:   cmp    -0x24(%ebp),%eax
  //  0x080486eb <+139>:   jb     0x80486c7 <decrypt+103>

  // translated by ghidra as

  // bool bVar6;
  // bool bVar7;
  //   while( true ) {
  //   bVar6 = i < ~len - 1;
  //   bVar7 = i == ~len - 1;
  //   if (!bVar6) break;
  //   buff[i] = (byte)n ^ buff[i];
  //   i = i + 1;
  // }

  //easier to say 

  while(i < len) {
    buff[i] = n ^ buff[i];
    i++;
  }
  // pbVar6 = (byte *)"Congratulations!";
  // 0x080486ed <+141>:   lea    -0x1d(%ebp),%eax
  //  0x080486f0 <+144>:   mov    %eax,%edx
  //  0x080486f2 <+146>:   mov    $0x80489c3,%eax
  //  0x080486f7 <+151>:   mov    $0x11,%ecx
  //  0x080486fc <+156>:   mov    %edx,%esi
  //  0x080486fe <+158>:   mov    %eax,%edi
  //  0x08048700 <+160>:   repz cmpsb %es:(%edi),%ds:(%esi) // It compares two strings byte by byte until it finds a difference or reaches the end of one of the strings.

// translated by ghidra as 

  // byte *pbVar3;
  // byte *pbVar5;
  // int iVar2;
  // iVar2 = 0x11;
  // pbVar3 = (byte *)buff;
  // pbVar5 = (byte *)"Congratulations!";
  // do {
  //   if (iVar2 == 0) break;
  //   iVar2 = iVar2 + -1;
  //   bVar6 = *pbVar3 < *pbVar5;
  //   bVar7 = *pbVar3 == *pbVar5;
  //   pbVar3 = pbVar3 + 1;
  //   pbVar5 = pbVar5 + 1;
  // } while (bVar7);

  // easier to use

  strncmp(buff, "Congratulations!", 0x11);

  
  if ((!bVar7 && !bVar8) == bVar7) {
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
  switch(n) {
  default:
    n = rand();
    decrypt(n);
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
