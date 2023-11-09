#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void log_wrapper(FILE *filePointer,char *headerText,char *filePath)

{
  char buffer [264];
  
  strcpy(buffer,headerText);
  snprintf(buffer + strlen(buffer), 0xfe - strlen(buffer), filePath);
  buffer[strcspn(buffer,"\n")] = '\0';
  fprintf(filePointer,"LOG: %s\n",buffer);
  return;
}

int main(int ac,char **av)

{
  int writeTo;
  FILE *backupLogFile;
  FILE *userFile;
  char c;
  char buffer [100];
  
  if (ac != 2) {
    printf("Usage: %s filename\n",*av);
  }
  backupLogFile = fopen("./backups/.log","w");
  if (backupLogFile == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n","./backups/.log");
    exit(1);
  }
  log_wrapper(backupLogFile,"Starting back up: ",av[1]);
  userFile = fopen(av[1],"r");
  if (userFile == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n",av[1]);
    exit(1);
  }
  strcpy(buffer, "./backups/");
  strncat(buffer,av[1], 99 - strlen(buffer));
  writeTo = open(buffer,0xc1,0x1b0);
  if (writeTo < 0) {
    printf("ERROR: Failed to open %s%s\n","./backups/",av[1]);
    exit(1);
  }
  while( true ) {
    c = fgetc(userFile);
    if (c == -1) break;
    write(writeTo,&c,1);
  }
  log_wrapper(backupLogFile,"Finished back up ",av[1]);
  fclose(userFile);
  close(writeTo);
  return 0;
}