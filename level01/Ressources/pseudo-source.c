#include <stdio.h>
#include <stdlib.h>

char a_user_name[256];

int verify_user_name() {
    puts("verifying username....\n");
//     08048478 ba 40 a0        MOV        EDX,a_user_name
//          04 08
// 0804847d b8 a8 86        MOV        EAX,s_dat_wil_080486a8                           = "dat_wil"
//          04 08
// 08048482 b9 07 00        MOV        ECX,0x7
//          00 00
// 08048487 89 d6           MOV        ESI,EDX
// 08048489 89 c7           MOV        EDI,EAX
// 0804848b f3 a6           CMPSB.REPE ES:EDI=>s_dat_wil_080486a8,ESI=>a_user_name      = "dat_wil"

// ghidra translation gives 

  // iVar1 = 7;
  // pbVar2 = &a_user_name;
  // pbVar3 = (byte *)"dat_wil";
  // do {
  //   if (iVar1 == 0) break;
  //   iVar1 = iVar1 + -1;
  //   uVar4 = *pbVar2 < *pbVar3;
  //   uVar5 = *pbVar2 == *pbVar3;
  //   pbVar2 = pbVar2 + (uint)bVar6 * -2 + 1;
  //   pbVar3 = pbVar3 + (uint)bVar6 * -2 + 1;
  // } while ((bool)uVar5);
  // return (int)(char)((!(bool)uVar4 && !(bool)uVar5) - uVar4);

// simpler to say
    return strncmp("dat_wil", a_user_name, 7);
}


int verify_user_pass(char *password)
{
//   080484b2 b9 05 00        MOV        ECX,0x5
//          00 00
// 080484b7 89 d6           MOV        ESI,EDX
// 080484b9 89 c7           MOV        EDI,EAX
// 080484bb f3 a6           CMPSB.REPE ES:EDI=>s_admin_080486b0,ESI                     = "admin"

// ghidra translation gives

// int iVar1;
// byte *pbVar2;
// undefined in_CF;
// undefined in_ZF;
// iVar1 = 5;
// pbVar2 = (byte *)"admin";
// do {
//   if (iVar1 == 0) break;
//   iVar1 = iVar1 + -1;
//   in_CF = (byte)*password < *pbVar2;
//   in_ZF = *password == *pbVar2;
//   password = (char *)((byte *)password + 1);
//   pbVar2 = pbVar2 + 1;
// } while ((bool)in_ZF);
// return (int)(char)((!(bool)in_CF && !(bool)in_ZF) - in_CF);

// simpler to say
  return strncmp("admin", password, 5);
}



int main(void)
{
  int iVar1;
  char buffer [64];
  
//   080484db 8d 5c 24 1c     LEA        EBX=>buffer,[ESP + 0x1c]
// 080484df b8 00 00        MOV        EAX,0x0
//          00 00
// 080484e4 ba 10 00        MOV        EDX,0x10
//          00 00
// 080484e9 89 df           MOV        EDI,EBX
// 080484eb 89 d1           MOV        ECX,EDX
// 080484ed f3 ab           STOSD.REP  ES:EDI

// ghidra translation gives

//   undefined4 *puVar2;
//   puVar2 = (undefined4 *)buffer;
//   for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
//     *puVar2 = 0;
//     puVar2 = puVar2 + 1;
//   }

// simpler to just write
	memset(buffer, 0, 64);

  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");
  fgets(&a_user_name,256,stdin);
  iVar1 = verify_user_name();
  if (iVar1 == 0) {
    puts("Enter Password: ");
    fgets(buffer,100,stdin);
    iVar1 = verify_user_pass(buffer);
    if ((iVar1 == 0) || (iVar1 != 0)) {
      puts("nope, incorrect password...\n");
      iVar1 = 1;
    }
    else {
      iVar1 = 0;
    }
  }
  else {
    puts("nope, incorrect username...\n");
    iVar1 = 1;
  }
  return iVar1;
}