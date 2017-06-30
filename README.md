# SE207 Dépôt Git

Bienvenue sur le gitLab de Erwan CHERIAUX !

Découverte de la bibliothèque SystemC.
Analyse de simulation avec gtkwave.

Le Makefile est adapter à mon ordinateur personnel. 
Il faut mettre les entrer les commandes suivantes pour travailler sur un PC de l'école:

- export SYSTEMC=/comelec/softs/opt/systemc/current
- export LDFLAGS="-L /comelec/softs/opt/systemc/current/lib-linux64"

# projet-video

## zoom
make && ./simulation.x 2500000 && eog wallace_copie00.png

## zoom + moyenneur
make && ./simulation.x 2500000 moyenneur && eog wallace_copie00.png

## zoom + sobel
make && ./simulation.x 2500000 sobel && eog wallace_copie00.png
