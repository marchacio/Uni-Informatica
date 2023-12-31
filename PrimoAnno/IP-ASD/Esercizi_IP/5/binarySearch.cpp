#include <iostream>

/*
Scrivere un programma che effettui la ricerca dell’elemento item (un intero) nell’array v (array di 15 interi ORDINATI letti da input).
[ File binarySearch.cpp ]
NOTA. Per l’algoritmo di binarySearch vi rimandiamo alle slides presentate a lezione.
[SUGGERIMENTO: Ricordate che il metodo di Ricerca Binaria opera su sequenze ordinate!]
*/

main(){

  const int N = 15;

  int v[N];

  //Ottieni input
  for (int i = 0; i < N; ++i) {
    int val;

    std::cout << "Valore n." << i << " (intero): ";
    std::cin >> val;

    v[i] = val;
  }

  //Ottieni item da ricercare in v
  int item;
  std::cout << "Inserisci un numero intero da cercare: ";
  std::cin >> item;

  //Ordina l'array
  for(int i = 0; i < N-1; ++i){
    int smallestIndex = i;
    for(int mini = i+1; mini < N; ++mini)
      if(v[mini] < v[smallestIndex])
        smallestIndex = mini;

    int temp = v[smallestIndex];
    v[smallestIndex] = v[i];
    v[i] = temp;
  }

  //Effettua la ricerca binaria
  int first = 0;
  int last = N-1;
  int mid;
  bool trovato = false;

  while(first <= last && !trovato){
    mid = (first + last) / 2;
    if(v[mid] == item)
      trovato = true;
    else {
      if(v[mid] > item)
        last = mid-1;
      else
        first = mid+1;
    }
  }

  //stampa il risultato
  if (trovato)
    std::cout << item << " e' presente nell'array\n";
  else
    std::cout << item << " non e' presente nell'array\n";

  return 0;
}
