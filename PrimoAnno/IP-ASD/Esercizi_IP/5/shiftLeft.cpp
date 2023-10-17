#include <iostream>

/*
Scrivere il programma che esegua la traslazione (“shift”) verso sinistra degli elementi di un vettore letto in ingresso, ovvero
ogni elemento deve essere copiato in quello di indice immediatamente minore. Il valore del primo elemento deve essere
perso, quello dell’ultimo deve essere rimpiazzato da 0. Quindi stampa il risultato.
Ad esempio: [1 10 15 18] −→ [10 15 18 0]
[ File shiftLeft.cpp ]
*/


main(){

  const int N = 5;
  int numeri[N];

  //richiedi input all'utente
  for(int i = 0; i < N; i++){
    std::cout << "Inserisci il valore n. "  << i+1 << ": ";
    std::cin >> numeri[i];
  }

  //Shifting
  for (int i = 1; i < N; i++) {
    numeri[i-1] = numeri[i];

    if(i == N-1)
      numeri[N-1] = 0;
  }

  //Stampa risultato
  std::cout << "\nL'array shiftato e': ";
  for(int i = 0; i < N; ++i)
    std::cout << numeri[i] << " ";

  return 0;
}
