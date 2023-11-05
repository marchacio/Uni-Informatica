#!/bin/bash

#-----------------------------------------------------------------------------------------
# QUESTO FILE GENERA UN GRAFICO CHE CONFRONTA IL MODELLO BANDA-LATENZA
# CON I DATI CONTENUTI DAL FILE .BAT PASSATO COME PRIMO ED UNICO PARAMETRO:
# ES: > ./graph.bash ../data_localhost/tcp_throughput.dat
#-----------------------------------------------------------------------------------------

#il primo parametro è il nome del file .dat:
#   controlla che sia passato almeno un parametro
if [[ $# != 1 ]] ; then printf "\nErrore: file .dat richiesto: mancante\n\n" ; exit 1; fi

headLine=$(head -n 1 $1)
tailLine=$(tail -n 1 $1)

#N1 è la dimensione MINIMA dei pacchetti contenuti nel file .dat
N1=$(echo $headLine | awk '{print $1}')
#T1 è il throughput MEDIO MINIMO dei pacchetti contenuti nel file .dat
T1=$(echo $headLine | awk '{print $3}')

#N2 è la dimensione MASSIMA dei pacchetti contenuti nel file .dat
N2=$(echo $tailLine | awk '{print $1}')
#T2 è il throughput MEDIO MASSIMO dei pacchetti contenuti nel file .dat
T2=$(echo $tailLine | awk '{print $3}')

#CALCOLO B(banda) e L0(latenza):
# prima di calcolare B e L0, bisogna trovare il DELAY (D) del messaggio
# più piccolo (1) e più grande (2):
#   dati il throughput T e la dimensione N, la formula per il delay D è: D=N/T
#
#Per l'utilizzo del comando bc: https://www.geeksforgeeks.org/bc-command-linux-examples/
D1=$(echo "scale=9;$N1/$T1" | bc -l)
D2=$(echo "scale=9;$N2/$T2" | bc -l)

#DEBUG:
#echo "$N1/$T1 = $D1" 
#echo "$N2/$T2 = $D2"

#Adesso possiamo calcolare B e L0:
B=$(echo "scale=9;($N2-$N1)/($D2-$D1)" | bc -l)
L0=$(echo "scale=9;($D1*$N2-$D2*$N1)/($N2-$N1)" | bc -l)

#DEBUG:
#echo "Banda: $B" 
#echo "Latenza: $L0"

#ottieni il nome del file
nomeFile=$(basename -- "$1")
nomeFile="${nomeFile%.*}"

set -e
gnuplot <<-eNDgNUPLOTcOMMAND
    lbf(x) = x / ( $L0 + x / $B )

	set term png size 900, 700
	set output "MODELLO_BL_$nomeFile.png"
	set logscale x 2
	set logscale y 10
	set xlabel "msg size (B)"
	set ylabel "throughput (KB/s)"
	plot "$1" using 1:2 title "$nomeFile median Throughput" \
			with linespoints, \
		lbf(x) title "Latency-Bandwidth model with L=$L0 and B=$B" with linespoints
	clear
eNDgNUPLOTcOMMAND