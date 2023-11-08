En analysant l'ASM du binaire , on remarque qu'aucun format string attack ou buffer overflow sera utile,
le binaire attend 2 entrer, un login et un serial number.
Si on a le bon duo alors un appel a system avec /bin/sh sera executer.

Si on regarde dans l'ASM le main prend nos 2 input et les utilises pour appeler la fonction auth, celle-ci va regarder si notre login a plus de 5 caractere sinon l'execution s'arrete, il y a un appel de ptrace bloquant notre debuggueur.
Puis auth Hash notre login et le compare avec un resultat stocker dans $ebp-0x10 a la fin de la fonction.

ce que l'on peut faire c'est passer par gdb afin de regarder la valeur qui est comparer et enfin avoir notre serial pour notre login.


On va donc mettre un breakpoint apres ptrace pour changer la valeur de retour et continuer l'execution,
puis on met un breakpoint avant la toute derniere comparaison pour avoir le serial.

```
disass auth

b *0x080487ba
b *0x08048866

run

"bramarien"
"000000000"

set $eax=0
continue
print $ebp-0x10 --> 0xffffd298
x/d 0xffffd298 --> 6235754

```

Maintenant on peux essayer sans GDB en utilisant comme login bramarien et comme serial 6235754

` cat /home/users/level07/.pass `
