#include <iostream>

/*
Fissata una costante intera positiva N, scrivere un programma che, preso in ingresso un numero intero positivo minore di 2^N
, memorizzi la sua rappresentazione binaria su un vettore di lunghezza N. Quindi stampi il contenuto del vettore.
[ File dec2bin.cpp ]
L’algoritmo per il calcolo della rappresentazione binaria è il seguente: si divide il numero in ingresso per 2 fino a che il
risultato non è 0. La rappresentazione binaria è data dai resti delle divisioni nell’ordine inverso in cui sono stati calcolati.
Quindi basta eseguire le divisioni finché non si arriva a 0 e memorizzare a ogni iterazione i resti della divisione intera in un
array partendo dall’ultima posizione.
*/

main() {

  const int N = 5;

  int numeroBinario[N];

  //Definizione del limite massimo dell'input (elevazione di potenza senza librerie esterne)
  int max_input = 1;
  for (int i = 0; i < N; ++i)
    max_input *= 2;

  //Ingresso input da utente
  int input;
  std::cout << "Inserisci un numero intero < " << max_input << ": ";
  std::cin >> input;

  //Controllo input utente
  if(input < max_input){

    //Calcolo il binario

    //Dichiaro e inizializzo array contenente il binario
    int resti[N];
    for (int i = 0; i < N; i++)
      resti[i] = 0;

    int index = 0;
    while(input > 0){
      resti[index] = input % 2;
      index++;

      input /= 2;
    }

    //stampo il vettore al contrario
    std::cout << "In codice binario e': ";
    for (int i = N-1; i >= 0; --i) {
      std::cout << resti[i];
    }

  } else {
    std::cout << "Dev'essere minore di " << max_input;
  }

  return 0;
}
