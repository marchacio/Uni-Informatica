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
    count += 5;
  }

  //Effettua la ricerca binaria
  int first = 0;
  int last = N-1;
  int mid;
  bool trovato = false;

  while(first <= last && !trovato){
    mid = (first + last) / 2;
    if(v[mid] == item){
      trovato = true;
      count++;
    }
    else {
      if(v[mid] > item){
        last = mid-1;
        count++;
      }
      else
        first = mid+1;
    }
  }

  //stampa il risultato
  if (trovato)
    std::cout << item << " e' presente nell'array\n";
  else
    std::cout << item << " non e' presente nell'array\n";

  std::cout << "\nNumero di accessi: " << count;

  return 0;
}
