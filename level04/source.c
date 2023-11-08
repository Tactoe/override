#include <stdio.h>
#include <stdlib.h>

int main(void)

{
    uint status;
    char buffer [32];
    pid_t forkPid;
    
    forkPid = fork();
    memset(buffer, 0, 32);
    if (forkPid == 0) {
        prctl(1,1);
        ptrace(0,0,0,0);
        puts("Give me some shellcode, k");
        gets(buffer);
    }
    else {
        do {
            wait(&status);
            // we can also use the macro equivalents `if (WIFEXITED(status) || WIFSIGNALED(status))`
            // or `if (status <= 127 || status > 127)`
            if ((((status) & 0x7f) == 0) || (((status) & 0x7f) != 0)){
                puts("child is exiting...");
                return 0;
            }
        } while (ptrace(3,forkPid,0x2c,0) != 0xb);
        puts("no exec() for you");
        kill(forkPid,9);
    }
    return 0;
}