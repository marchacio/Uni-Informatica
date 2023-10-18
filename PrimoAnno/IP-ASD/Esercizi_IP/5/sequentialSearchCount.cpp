#include <iostream>

/*
7. Modificare i precedenti esercizi 1 e 2 nel seguente modo:
(a) Dichiarino una variabile intera count inizializzata a 0
(b) Ogni volta che nel programma compare un riferimento a un elemento dell’array, incrementino count
(c) Alla fine, stampino il valore di count (numero di accessi effettuati all’array)
[ File sequentialSearchCount.cpp ] [ File binarySearchCount.cpp ]
*/

main() {

  const int N = 15;

  int count = 0;

  int item;
  std::cout << "Inserisci un numero intero da cercare: ";
  std::cin >> item;

  int v[N];

  for (int i = 0; i < N; ++i) {
    int val;
    std::cout << "Valore n." << i << ": ";
    std::cin >> val;

    v[i] = val;
    count++;
  }

  int loc = -1;
  bool found = false;

  for (int i = 0; i < N; ++i) {
    count++;

    if(v[i] == item){
      found = true;
      loc = i;
    }
  }

  if(found)
    std::cout << "Trovato in posizione " << loc;
  else
    std::cout << "Non trovato";

  std::cout << "\nNumero di accessi: " << count;

  return 0;
}
