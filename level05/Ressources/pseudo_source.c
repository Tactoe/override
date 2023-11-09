#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  byte bVar4;
  char buffer [100];
  uint i;
  
  bVar4 = 0;
  fgets(buffer,100,stdin);
  i = 0;
  do {
	// 080484d3 8b 9c 24        MOV        EBX,dword ptr [ESP + 0x8c]=>i
	//          8c 00 00 00
	// 080484da 8d 44 24 28     LEA        EAX=>buffer,[ESP + 0x28]
	// 080484de c7 44 24        MOV        dword ptr [ESP + 0x1c]=>local_84,0xffffffff
	//          1c ff ff 
	//          ff ff
	// 080484e6 89 c2           MOV        EDX,EAX
	// 080484e8 b8 00 00        MOV        EAX,0x0
	//          00 00
	// 080484ed 8b 4c 24 1c     MOV        ECX,dword ptr [ESP + 0x1c]=>local_84
	// 080484f1 89 d7           MOV        EDI,EDX
	// 080484f3 f2 ae           SCASB.RE   ES:EDI

    // uVar2 = 0xffffffff;
    // pcVar3 = buffer;
    // do {
    //   if (uVar2 == 0) break;
    //   uVar2 = uVar2 - 1;
    //   cVar1 = *pcVar3;
    //   pcVar3 = pcVar3 + (uint)bVar4 * -2 + 1;
    // } while (cVar1 != '\0');

    // easier to say

    strlen(buffer);
    if (~uVar2 - 1 <= i) {
      printf(buffer);
      exit(0);
    }
    if (('@' < buffer[i]) && (buffer[i] < '[')) {
      buffer[i] = buffer[i] ^ 0x20;
    }
    i = i + 1;
  } while( true );
}