#include <iostream>

/*
Scrivere un programma che esegua la rotazione (“shift”) verso destra degli elementi di un vettore letto in ingresso, ovvero ogni elemento deve essere copiato in quello di indice immediatamente maggiore, e il valore del primo elemento deve
rimpiazzato da quello dell’ultimo. Quindi stampa il risultato.
Ad esempio: [1 10 15 18] −→ [18 1 10 15]
[ File rotateRight ]
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
  int ultimoNumero = numeri[N-1];
  for (int i = N-1; i > 0; --i) {
    numeri[i] = numeri[i-1];
  }
  numeri[0] = ultimoNumero;

  //Stampa risultato
  std::cout << "\nL'array shiftato e': ";
  for(int i = 0; i < N; ++i)
    std::cout << numeri[i] << " ";

  return 0;
}
