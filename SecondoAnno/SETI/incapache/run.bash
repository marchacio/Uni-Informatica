#!/bin/bash

#File bash per compilare ed eseguire velocemente 
# il labo

arg=8000
if [[ $# != 0 ]] ; then arg=$1; fi

cd /home/marco/Uni-Informatica/SecondoAnno/SETI/incapache

#rimuovi il vecchio file, cosi in caso la compilazione 
#non vada a buon fine, non esegue nulla
rm -f bin/incapache 

#compila...
make
printf "\n\n"

#...ed esegui
cd bin
./incapache ../www-root/ $arg
