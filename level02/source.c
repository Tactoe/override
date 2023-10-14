#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)

{
  char password [100];
  char filePassword [42];
  char username [100];
  int freadReturn;
  FILE *filePointer;
  
    memset(password, 0, 12);
    memset(filePassword, 0, 5);
    memset(username, 0, 12);

  filePointer = fopen("/home/users/level03/.pass","r");
  if (filePointer == (FILE *)0x0) {
    fwrite("ERROR: failed to open password file\n",1,0x24,stderr);
    exit(1);
  }
  freadReturn = fread(filePassword,1,0x29,filePointer);
  if (freadReturn != 0x29) {
    fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
    // there's 2 calls to fwrite with this value in the binary but only one is displayed??
    // fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
    exit(1);
  }
  // strcspn(var, "\n") are basically strlens 
  filePassword[strcspn(filePassword,"\n")] = '\0';
  fclose(filePointer);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets(username,100,stdin);
  username[strcspn(username,"\n")] = '\0';
  printf("--[ Password: ");
  fgets(password,100,stdin);
  password[strcspn(password,"\n")] = '\0';
  puts("*****************************************");
  if (strncmp(filePassword,password,0x29) == 0) {
    printf("Greetings, %s!\n",username);
    system("/bin/sh");
    return 0;
  }
  printf(username);
  puts(" does not have access!");
  exit(1);
}
