#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)

{
  int iVar1;
  size_t sVar2;
  char password [100];
  char filePassword [42];
  char username [100];
  int iStack_14;
  FILE *filePointer;
  
  // just a bunch of STOSQ.REP instructions which can be translated as memset

//   undefined8 *puVar4;
//   long lVar3;
//   puVar4 = (undefined8 *)username;
//   for (lVar3 = 0xc; lVar3 != 0; lVar3 = lVar3 + -1) {
//     *puVar4 = 0;
//     puVar4 = puVar4 + 1;
//   }
//   *(undefined4 *)puVar4 = 0;
//   puVar4 = (undefined8 *)filePassword;
//   for (lVar3 = 5; lVar3 != 0; lVar3 = lVar3 + -1) {
//     *puVar4 = 0;
//     puVar4 = puVar4 + 1;
//   }
//   *(undefined *)puVar4 = 0;
//   puVar4 = (undefined8 *)password;
//   for (lVar3 = 0xc; lVar3 != 0; lVar3 = lVar3 + -1) {
//     *puVar4 = 0;
//     puVar4 = puVar4 + 1;
//   }
  *(undefined4 *)puVar4 = 0;
  filePointer = fopen("/home/users/level03/.pass","r");
  if (filePointer == (FILE *)0x0) {
    fwrite("ERROR: failed to open password file\n",1,0x24,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  sVar2 = fread(filePassword,1,0x29,filePointer);
  iStack_14 = (int)sVar2;
  sVar2 = strcspn(filePassword,"\n");
  filePassword[sVar2] = '\0';
  if (iStack_14 != 0x29) {
    fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
    fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  fclose(filePointer);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets(username,100,stdin);
  sVar2 = strcspn(username,"\n");
  username[sVar2] = '\0';
  printf("--[ Password: ");
  fgets(password,100,stdin);
  sVar2 = strcspn(password,"\n");
  password[sVar2] = '\0';
  puts("*****************************************");
  iVar1 = strncmp(filePassword,password,0x29);
  if (iVar1 == 0) {
    printf("Greetings, %s!\n",username);
    system("/bin/sh");
    return 0;
  }
  printf(username);
  puts(" does not have access!");
  exit(1);
}
