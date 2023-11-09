#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void log_wrapper(FILE *filePointer,char *headerText,char *filePath)

{
  char cVar1;
  size_t sVar2;
  ulong uVar3;
  ulong uVar4;
  char *pcVar5;
  long in_FS_OFFSET;
  byte bVar6;
  undefined8 local_120;
  char buffer [264];
  long local_10;
  
  bVar6 = 0;
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_120 = filePointer;
  strcpy(buffer,headerText);

//  0x0000000000400913 <+79>:    lea    -0x110(%rbp),%rax
//    0x000000000040091a <+86>:    movq   $0xffffffffffffffff,-0x130(%rbp)
//    0x0000000000400925 <+97>:    mov    %rax,%rdx
//    0x0000000000400928 <+100>:   mov    $0x0,%eax
//    0x000000000040092d <+105>:   mov    -0x130(%rbp),%rcx
//    0x0000000000400934 <+112>:   mov    %rdx,%rdi
//    0x0000000000400937 <+115>:   repnz scas %es:(%rdi),%al
//    0x0000000000400939 <+117>:   mov    %rcx,%rax
//    0x000000000040093c <+120>:   not    %rax
//    0x000000000040093f <+123>:   lea    -0x1(%rax),%rdx
//    0x0000000000400943 <+127>:   mov    $0xfe,%eax
//    0x0000000000400948 <+132>:   mov    %rax,%r8
//    0x000000000040094b <+135>:   sub    %rdx,%r8
//    0x000000000040094e <+138>:   lea    -0x110(%rbp),%rax
//    0x0000000000400955 <+145>:   movq   $0xffffffffffffffff,-0x130(%rbp)
//    0x0000000000400960 <+156>:   mov    %rax,%rdx
//    0x0000000000400963 <+159>:   mov    $0x0,%eax
//    0x0000000000400968 <+164>:   mov    -0x130(%rbp),%rcx
//    0x000000000040096f <+171>:   mov    %rdx,%rdi
//    0x0000000000400972 <+174>:   repnz scas %es:(%rdi),%al
//    0x0000000000400974 <+176>:   mov    %rcx,%rax
//    0x0000000000400977 <+179>:   not    %rax
//    0x000000000040097a <+182>:   lea    -0x1(%rax),%rdx
//    0x000000000040097e <+186>:   lea    -0x110(%rbp),%rax
//    0x0000000000400985 <+193>:   add    %rdx,%rax
//    0x0000000000400988 <+196>:   mov    %rsi,%rdx
//    0x000000000040098b <+199>:   mov    %r8,%rsi
//    0x000000000040098e <+202>:   mov    %rax,%rdi
//    0x0000000000400991 <+205>:   mov    $0x0,%eax
//    0x0000000000400996 <+210>:   callq  0x400740 <snprintf@plt>

  // translated by ghidra as

  // uVar3 = 0xffffffffffffffff;
  // pcVar5 = buffer;
  // do {
  //   if (uVar3 == 0) break;
  //   uVar3 = uVar3 - 1;
  //   cVar1 = *pcVar5;
  //   pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  // } while (cVar1 != '\0');
  // uVar4 = 0xffffffffffffffff;
  // pcVar5 = buffer;
  // do {
  //   if (uVar4 == 0) break;
  //   uVar4 = uVar4 - 1;
  //   cVar1 = *pcVar5;
  //   pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  // } while (cVar1 != '\0');
  // snprintf(buffer + (~uVar4 - 1),0xfe - (~uVar3 - 1),filePath);
  
  // easier to say
  snprintf(buffer + strlen(buffer), 0xfe - strlen(buffer), filePath)
  sVar2 = strcspn(buffer,"\n");
  buffer[sVar2] = '\0';
  fprintf(local_120,"LOG: %s\n",buffer);
  // canary check to see if the stack hasn't exploded, can be ignored in clean source
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

int main(int ac,char **av)

{
  char cVar1;
  long lVar2;
  int writeTo;
  int iVar3;
  FILE *backupLogFile;
  FILE *userFile;
  ulong uVar4;
  char *pcVar5;
  long in_FS_OFFSET;
  byte bVar6;
  char c;
  char buffer [100];
  
  bVar6 = 0;
  lVar2 = *(long *)(in_FS_OFFSET + 0x28);
  c = -1;
  if (ac != 2) {
    printf("Usage: %s filename\n",*av);
  }
  backupLogFile = fopen("./backups/.log","w");
  if (backupLogFile == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n","./backups/.log");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  log_wrapper(backupLogFile,"Starting back up: ",av[1]);
  userFile = fopen(av[1],"r");
  if (userFile == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n",av[1]);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  buffer[0] = '.';
  buffer[1] = '/';
  buffer[2] = 'b';
  buffer[3] = 'a';
  buffer[4] = 'c';
  buffer[5] = 'k';
  buffer[6] = 'u';
  buffer[7] = 'p';
  buffer[8] = 's';
  buffer[9] = '/';
  buffer[10] = '\0';
  // 0x0000000000400b27 <+311>:   lea    -0x70(%rbp),%rax
  //  0x0000000000400b2b <+315>:   movq   $0xffffffffffffffff,-0xa8(%rbp)
  //  0x0000000000400b36 <+326>:   mov    %rax,%rdx
  //  0x0000000000400b39 <+329>:   mov    $0x0,%eax
  //  0x0000000000400b3e <+334>:   mov    -0xa8(%rbp),%rcx
  //  0x0000000000400b45 <+341>:   mov    %rdx,%rdi
  //  0x0000000000400b48 <+344>:   repnz scas %es:(%rdi),%al
  //  0x0000000000400b4a <+346>:   mov    %rcx,%rax
  //  0x0000000000400b4d <+349>:   not    %rax
  //  0x0000000000400b50 <+352>:   lea    -0x1(%rax),%rdx
  //  0x0000000000400b54 <+356>:   mov    $0x63,%eax
  //  0x0000000000400b59 <+361>:   mov    %rax,%rcx
  //  0x0000000000400b5c <+364>:   sub    %rdx,%rcx
  //  0x0000000000400b5f <+367>:   mov    %rcx,%rdx
  //  0x0000000000400b62 <+370>:   mov    -0xa0(%rbp),%rax
  //  0x0000000000400b69 <+377>:   add    $0x8,%rax
  //  0x0000000000400b6d <+381>:   mov    (%rax),%rax
  //  0x0000000000400b70 <+384>:   mov    %rax,%rcx
  //  0x0000000000400b73 <+387>:   lea    -0x70(%rbp),%rax
  //  0x0000000000400b77 <+391>:   mov    %rcx,%rsi
  //  0x0000000000400b7a <+394>:   mov    %rax,%rdi
  //  0x0000000000400b7d <+397>:   callq  0x400750 <strncat@plt>

  // translated by ghidra as

  // uVar4 = 0xffffffffffffffff;
  // pcVar5 = buffer;
  // do {
  //   if (uVar4 == 0) break;
  //   uVar4 = uVar4 - 1;
  //   cVar1 = *pcVar5;
  //   pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  // } while (cVar1 != '\0');
  // strncat(buffer,av[1],99 - (~uVar4 - 1));

  // easier to say 

  strncat(buffer,av[1], 99 - strlen(buffer));
  writeTo = open(buffer,0xc1,0x1b0);
  if (writeTo < 0) {
    printf("ERROR: Failed to open %s%s\n","./backups/",av[1]);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  while( true ) {
    iVar3 = fgetc(userFile);
    c = (char)iVar3;
    if (c == -1) break;
    write(writeTo,&c,1);
  }
  log_wrapper(backupLogFile,"Finished back up ",av[1]);
  fclose(userFile);
  close(writeTo);
  if (lVar2 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}