# devoir1_INFO0952
INFO0952 - Complément d'informatique : modèle de schelling

compile with:
make

execute with:
./Schelling -r R -b B -h H -w W -s S -f F -p P
simulera l’évolution du modèle où :
— la grille a une taille de H × W ;
— la probabilité qu’une case soit occupée par un étudiant en ingénieur civil est R ;
— la probabilité qu’une case soit occupée par un étudiant en droit est B ;
— le ratio de satisfaction satisRatio vaut S.
Cette commande créera un fichier nommé F (simu.gif par défaut) contenant le gif généré.
P représente simplement la taille d’une case sur le gif (10 est une bonne valeur en général,
sauf si la grille est vraiment grande). L’exécution de la commande ./Schelling sans argument est équivalent à l’appel suivant :
./schelling -r 0.4 -b 0.4 -h 50 -w 50 -s 0.7 -f simul.gif -p 10
