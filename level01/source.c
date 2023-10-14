#include <stdio.h>
#include <stdlib.h>

char a_user_name[256];

int verify_user_name() {
    puts("verifying username....\n");
    return strncmp("dat_wil", a_user_name, 7);
}


int verify_user_pass(char *password)
{
  return strncmp("admin", password, 5);
}



int main(void)
{
  int i;
  char buffer [64];
	memset(buffer, 0, 64);

  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");
  fgets(&a_user_name,256,stdin);
  i = verify_user_name();
  if (i == 0) {
    puts("Enter Password: ");
    fgets(buffer,100,stdin);
    i = verify_user_pass(buffer);
    if ((i == 0) || (i != 0)) {
      puts("nope, incorrect password...\n");
      i = 1;
    }
    else {
      i = 0;
    }
  }
  else {
    puts("nope, incorrect username...\n");
    i = 1;
  }
  return i;
}