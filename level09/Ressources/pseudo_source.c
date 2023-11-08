#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void secret_backdoor(void)
{
  char buffer [128];
  
  fgets(buffer,0x80,_stdin);
  system(buffer);
  return;
}

void set_msg(message *message)

{
  char buffer [1024];
  
  // 0x0000000000000944 <+18>:    lea    -0x400(%rbp),%rax
  //  0x000000000000094b <+25>:    mov    %rax,%rsi
  //  0x000000000000094e <+28>:    mov    $0x0,%eax
  //  0x0000000000000953 <+33>:    mov    $0x80,%edx
  //  0x0000000000000958 <+38>:    mov    %rsi,%rdi
  //  0x000000000000095b <+41>:    mov    %rdx,%rcx
  //  0x000000000000095e <+44>:    rep stos %rax,%es:(%rdi)

  // is translated by ghidra as

  // long lVar1;
  // undefined8 *puVar2;
  // puVar2 = (undefined8 *)buffer;
  // for (lVar1 = 0x80; lVar1 != 0; lVar1 = lVar1 + -1) {
  //   *puVar2 = 0;
  //   puVar2 = puVar2 + 1;
  // }
  
  // easier to say

  memset(local_buffer, '\0', 1024);

  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets(buffer,0x400,_stdin);
  strncpy(message->msg,buffer,(long)*(int *)&message->length);
  return;
}

void set_username(message *message)
{
  char buffer [128];
  int i;
  
  // long lVar1;
  // undefined8 *puVar2;
  // puVar2 = (undefined8 *)buffer;
  // for (lVar1 = 0x10; lVar1 != 0; lVar1 = lVar1 + -1) {
  //   *puVar2 = 0;
  //   puVar2 = puVar2 + 1;
  // }

  // same as above

  memset(local_buffer, '\0', 128);

  puts(">: Enter your username");
  printf(">>: ");
  fgets(buffer,0x80,_stdin);
  for (i = 0; (i < 0x29 && (buffer[i] != '\0')); i = i + 1) {
    message->username[i] = buffer[i];
  }
  printf(">: Welcome, %s",message->username);
  return;
}

void handle_msg(void)

{
  message mess;
  
  //   0x00000000000008d8 <+24>:    movq   $0x0,(%rax)
  //  0x00000000000008df <+31>:    movq   $0x0,0x8(%rax)
  //  0x00000000000008e7 <+39>:    movq   $0x0,0x10(%rax)
  //  0x00000000000008ef <+47>:    movq   $0x0,0x18(%rax)
  //  0x00000000000008f7 <+55>:    movq   $0x0,0x20(%rax)

  // is translated by ghidra as

  // mess.username[0] = '\0';
  // mess.username[1] = '\0';
  // mess.username[2] = '\0';
  // mess.username[3] = '\0';
  // [...]
  // mess.username[38] = '\0';
  // mess.username[39] = '\0';

  // easier to say 
  
  memset(message.username, 0, 0x28); // 40

  mess.length = 0x8c;
  set_username(&mess);
  set_msg(&mess);
  puts(">: Msg sent!");
  return;
}

int main(void)
{
  puts(
      "--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n- -------------------------------------------"
      );
  handle_msg();
  return 0;
}