En decompilant le programme et en reconstituant le code source on remarque des potentiels failles. Le main est une boucle While attendant un input qui soit egale a store / read / quit.
Le main met a zero tous l'environment ainsi que argv.
Un tableau de int de 100 element est initialiser a zero, c'est notre liste de contact pour le telephone, il est stocker sur la stack.

Store lance la fonction store_number qui prend en argument l'adresse de notre tableau, 2 valeur vont etre demander via le stdin. Nous avons Number puis index ( les deux sont des unsigned int ), Number va etre stocker a l'index fourni ( Attention un bitshiftleft de 2 est realiser sur index ) 
Mais l'index n'est pas verifier sauf par une condition ` Index % 3 == 0  ` et dans ce cas il va return 1 et ne rien stocker.

Read lance la fonction read_number avec comme argument l'adresse de notre tableau.
la fonction va demander un index afin d'afficher la valeur a cette index. ( Attention aussi au bitShiftLeft de 2 sur index )
A contrario de Store l'index n'a pas de verification, ce qui signifie que l'on peut lire ou l'on souhaite.

Quit ne lance pas de fonction, il va couper la boucle while et return 1.

Sachant que notre tableau est stocker dans la stack, on peut s'y promener et aller chercher au dessus de notre Tableau pour avoir par exemple les registres.
Il nous faut d'abbord l'adresse de notre tableau et on l'obtient facilement avec gdb, il suffit de regarder l'argument de store_number ou bien read_number.
```
 b *0x080488e7  
 p $esp+0x24
 ```
On obtient : 0xffffd554

Ensuite afin de chercher quelque adresse des registre on utilise ` info frame `
```
Stack level 0, frame at 0xffffd720:
 eip = 0x8048882 in main; saved eip 0xf7e45513
 called by frame at 0xffffd790
 Arglist at 0xffffd718, args:
 Locals at 0xffffd718, Previous frame's sp is 0xffffd720
 Saved registers:
  ebx at 0xffffd70c, ebp at 0xffffd718, esi at 0xffffd710,
  edi at 0xffffd714, eip at 0xffffd71c
```

La frame commence a 0xffffd720, et s'en suit notre registre enregister a differentes adresses.
EIP nous interesse car grace a lui nous pouvons utiliser un ret2libc et executer system(),
L'idee sera d'ecrire l'addresse de system a l'emplacement d'EIP puis de preparer le retour et l'argument de system de cette maniere

Adresse de system() + Adresse de exit() + Adresse de Args

```
 print &system --> 0xf7e6aed0
 print &exit --> 0xf7e5eb70
 find &system,+9999999,"/bin/sh" -- > 0xf7f897ec
```

Maintenant pour trouver l'index qui nous permet d'acceder a EIP nous devons le calculer,
pour rappel store_number et read_number execute un  bitshiftLEFT de 2 sur l'index qu'on lui donne.

Calculons la difference de taille entre l'adresse de EIP et le debut de notre tableau.
0xffffd71c - 0xffffd554 = 0x1c8 = 456
On termine par effectuer un bitshiftRIGHT de 2 sur 456 et on obtient notre index a utiliser.
456 / (2^2) = 114

Sauf que store_number verifie si l'index n'est pas utilisable en faisant INDEX % 3 == 0,
On peut toujours essayer de lire a cette index et cela fonctionne, d'ailleurs on obtient 4158936339 qui vaut 0xF7E45513 en hex, c'est bel et bien notre EIP.

On remarque que l'index est verifier avant d'avoir son bitshift left, que si on overflow lors du bitshift on peux passer n'importe qu'elle index tant que le calcul 
` ( UINTMAX+1 / (2^2) + INDEX QUE L'ON VEUT ) % 3 ) != 0 ` est valide
Si on utilise 114 en tant qu'INDEX dans notre calcul on obtient:
	4294967296 / 2^2 = 1073741824
	1073741824 + 114 = 1073741938
	1073741938 % 3 = 1
Avec 1073741938 on peut normalement acceder a l'index 114 tout en passant la verification.

Essayer d'utiliser read avec et on obtient 4158936339 = 0xf7e45513 en hex ( donc EIP )
Si on utiliser store avec cette index et que l'on quit le program segfault car EIP n'est plus reconnu.

On peut donc appliquer notre ret2libc, en ecrivant a l'indice 114 system(), a l'indice 115 exit() et enfin a l'indice 116 l'adresse de la string /bin/sh.
Il faut convertir les adresse en decimal afin de les ecrires correctement dans la stack.

&system --> 0xf7e6aed0 = 4159090384
&exit --> 0xf7e5eb70  = 4159040368
"/bin/sh" -- > 0xf7f897ec = 4160264172

```
 store
 4159090384
 1073741938
 
 store
 4159040368
 115

 store
 4160264172
 116

 quit

 cat /home/users/level08/.pass
```
