#include "rhombus.h"

/*
Scrivere una funzione con un parametro n di tipo intero che stampa un rombo di asterischi che sulla diagonale ha 2*n+1
caratteri. Ad esempio, dato 8 stampa
*
*
che sulla diagonale ha 17 caratteri.
[SUGGERIMENTO: 1)è più facile stampare il rombo con due cicli,
  il primo per le righe in cui il numero di asterischi cresce
  e il secondo per le righe in cui il numero di asterischi diminuisce.]
[SUGGERIMENTO: 2) usate la funzione replicate2_line]
*/

int main() {

  int n = 8;

  stampaCicloCrescente(n);
  stampaCicloDecrescente(n);

  return 0;
}
