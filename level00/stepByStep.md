level0:
On voit un binaire, on l'ouvre avec un outil de reverse-engineering, on voit qu'il ouvre un shell d'un autre utilisateur si on lui donne la bonne valeur (5276)
Donc il suffit de faire ./level00, entrer password: 5276 et de cat /home/user/level01/.pass