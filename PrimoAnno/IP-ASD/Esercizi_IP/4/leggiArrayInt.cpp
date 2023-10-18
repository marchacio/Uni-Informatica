#include <iostream>

/*
Leggi un array di int da tastiera. Scrivere un programma che dichiara un array v di N interi e lo “popola” leggendo valori
da input. [ File leggiArrayInt.cpp ]

// Dichiarare una costante N con valore 10
// Dichiarare un array a di N interi
// Iterare sulla variabile intera i a partire da 0 e fino a N escluso:
// Dichiarare una variabile intera val
// Stampare il messaggio composto da:
// - la stringa "Valore n. "
/ - il valore di i
// - il separatore ": "
// Leggere da input un valore di val
// Assegnare all'elemento i-esimo di a il valore di val
*/

main() {

  const int N = 10;

  int v[N];

  for (int i = 0; i < N; ++i) {
    int val;
    std::cout << "Valore n." << i << ": ";
    std::cin >> val;

    v[i] = val;
  }

  return 0;
}
