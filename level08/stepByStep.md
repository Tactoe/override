L'executable attend en argv[1] le chemin d'un fichier, ensuite fopen est utiliser avec un chemin relatif pour ouvrir le fichier de log avec './backups/.log' exit si il n'y arrive pas.
Si le fichier existe, la fonction log_wrapper s'execute et va ecrire dans le FILE passer en parametre, en concatenant un message et le chemin stocker dans argv[1].

Puis un deuxieme appel a fopen est effectuer qui va ouvrir le fichier au chemin dans argv[1] et stocker le FILE dans une variable qui sera utiliser apres un dernier appel a open

Le dernier open va ouvrir un fichier sur un chemin qu'il aura construit grace a ./backups/ + le chemin specifier ( argv[1] )
Enfin une boucle est presente pour copier le contenu de argv[1] dans notre dossier ./backups/

Sachant que le Suid est activer on peux faire lire le fichier /home/users/level09/.pass mais nous n'avons pas la permission de creer des dossiers dans ~/backups pour obtenir la copie, On va se servir du /tmp afin d'avoir les droits pour creer l'environment a l'executable qu'il lui faut pour faire la copie.

```
 cd /tmp

 mkdir -p ./backups/home/users/level09

 ./level08 /home/users/level09/.pass

 cat /tmp/backups/home/users/level09/.pass

```
