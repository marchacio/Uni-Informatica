#include <iostream>

/*
Scrivere un programma che effettui la ricerca dell’elemento item (un intero) nell’array v (array di 15 interi letti da input).
[ File sequentialSearch.cpp ]

// dichiarare una variabile const int N inizializzata a 15
// dichiarare una variabile int item
// leggere item da input
// dichiarare un array v di N interi
// leggere v da input (vedi esercizi parte precedente)
// dichiarare una variabile int loc e inizializzarla a -1
// dichiarare una variabile bool found e inizializzarla a false
/* iterare sugli elementi di v fino a che found diventa true o si è iterato su tutto l'array
    - se il valore alla pos corrente (i) e' uguale a item
    -- assegnare true a found e il valore di i a loc
*/
// se trovato, scrivere su output: ``Trovato in posizione ...''
// altrimenti scrivere ``Non trovato''


main(){

  const int N = 15;

  int item;
  std::cout << "Inserisci un numero intero da cercare: ";
  std::cin >> item;

  int v[N];

  for (int i = 0; i < N; ++i) {
    int val;
    std::cout << "Valore n." << i << ": ";
    std::cin >> val;

    v[i] = val;
  }

  int loc = -1;
  bool found = false;

  for (int i = 0; i < N; ++i) {
    if(v[i] == item){
      found = true;
      loc = i;
    }
  }

  if(found)
    std::cout << "Trovato in posizione " << loc;
  else
    std::cout << "Non trovato";

  return 0;
}
