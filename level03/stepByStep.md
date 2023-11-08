level3:

Cette fois, il semblerait qu'on ait un password avec une seed random. On voit plusieurs fonctions, main, test et decrypt. Il y a un appel a /bin/sh dans decrypt et pas de fonction sensibles aux overflows visibles, il va falloir trouver le bon nombre à entrer pour y accéder.

La fonction test prend l'input de l'utilisateur et le soustrait à la valeur 0x1337d00d (322424845). Ensuite, si le résultat est compris entre 1 et 9 ou 16 et 21, il est utilisé par la fonction decrypt, autrement c'est un int généré par rand().

En essayant tous les nombres possibles entre les résultats acceptés (de 322424844 à 322424835 et de 322424829 à 322424824), on voit que 18 (322424827) nous permet d'accéder au shell admin.

En creusant on peut voir que c'est parce que l'appel à system s'effectue uniquement si une comparaison réussit entre

string1 "Congratulations!"

et 

string2 `"Q}|u`sfg~sf{}|a3"` 
 
qui subit une modification. La modification en question est `string2[i] = n ^ string2[i]`, où n est le résultat de la soustraction vue plus haut. 18 est le nombre qui permet à l'opération XOR de faire match "Q}|u`sfg~sf{}|a3" avec "Congratulations!"