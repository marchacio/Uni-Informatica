#!/bin/bash

#Questo script bash manda N richieste al server su localhost.
#N può essere passato come unico argomento allo script.

N=100
if [[ $# != 0 ]] ; then N=$1; fi 

for (( c=0; c<N; c++ ))
do
   #esegui la richiesta della homepage e di un paio di immagini
   curl localhost:8000/ localhost:8000/images/calendar.png localhost:8000/images/uncadunca.jpg
done 
