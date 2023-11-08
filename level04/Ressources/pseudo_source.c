#include <stdio.h>
#include <stdlib.h>

int main(void)

{
  long lVar1;
  uint status;
  char buffer [32];
  pid_t forkPid;
  
  forkPid = fork();

  // int iVar2;
  // undefined4 *puVar3;
  // byte bVar4;
  // 0x080486e2 <+26>:    lea    0x20(%esp),%ebx
  //  0x080486e6 <+30>:    mov    $0x0,%eax
  //  0x080486eb <+35>:    mov    $0x20,%edx
  //  0x080486f0 <+40>:    mov    %ebx,%edi
  //  0x080486f2 <+42>:    mov    %edx,%ecx
  //  0x080486f4 <+44>:    rep stos %eax,%es:(%edi)

  // is translated by ghidra as

  // puVar3 = (undefined4 *)buffer;
  // bVar4 = 0;
  // for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
  //   *puVar3 = 0;
  //   puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
  // }

  // easier to say

  memset(buffer, 0, 32);
  status = 0;
  if (forkPid == 0) {
    prctl(1,1);
    // PTRACE_TRACEME is a macro for 0
    ptrace(PTRACE_TRACEME,0,0,0);
    puts("Give me some shellcode, k");
    gets(buffer);
  }
  else {
    do {
      wait(&status);
    
      //first check assembly is
  //  0x08048775 <+173>:   mov    0x1c(%esp),%eax
  //  0x08048779 <+177>:   mov    %eax,0xa0(%esp)
  //  0x08048780 <+184>:   mov    0xa0(%esp),%eax
  //  0x08048787 <+191>:   and    $0x7f,%eax
  //  0x0804878a <+194>:   test   %eax,%eax
  //  0x0804878c <+196>:   je     0x80487ac <main+228>

  // checking to see if the status return value is between 0 and 127 (process returned normally)
  // this can be translated as (((status) & 0x7f) == 0) or its macro equivalent WIFEXITED(status)
      if (((status & 0x7f) == 0) 
      
      // second check assembly is
    //0x0804878e <+198>:   mov    0x1c(%esp),%eax
  //  0x08048792 <+202>:   mov    %eax,0xa4(%esp)
  //  0x08048799 <+209>:   mov    0xa4(%esp),%eax
  //  0x080487a0 <+216>:   and    $0x7f,%eax
  //  0x080487a3 <+219>:   add    $0x1,%eax
  //  0x080487a6 <+222>:   sar    %al
  //  0x080487a8 <+224>:   test   %al,%al
  //  0x080487aa <+226>:   jle    0x80487ba <main+242>
  
  // checking to this if the status return value is higher than 127 (process had an error, the error code is 128 + error code. For instance segfault error code is 139 (128 + 11)) 
  // this can be translated as (((status) & 0x7f) != 0) or its macro equivalent WIFSIGNALED(status)
      || ('\0' < (char)(((byte)status & 0x7f) + 1) >> 1)) {
        puts("child is exiting...");
        return 0;
      }
      // PTRACE_TRACEME is a macro for 3
      lVar1 = ptrace(PTRACE_PEEKUSER,forkPid,0x2c,0);
    } while (lVar1 != 0xb);
    puts("no exec() for you");
    kill(forkPid,9);
  }
  return 0;
}