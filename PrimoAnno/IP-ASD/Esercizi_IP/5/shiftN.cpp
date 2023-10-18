#include <iostream>

/*
Modificare shiftLeft.cpp e rotateRight.cpp in modo da ottenere programmi che leggano un numero intero N, positivo o
negativo, ed eseguano rispettivamente la traslazione e la rotazione verso sinistra (se N negativo) o verso destra (se N positivo)
di |N| posizioni.
[ File shiftN.cpp ] [ File rotateN.cpp ]
NOTA. Se |N| ≥ lunghezza array, shift creerà un vettore vuoto. Se |N| > lunghezza array, rotate si comporterà come se |N|
fosse sostituito da |N % lunghezza array|. In particolare, se |N| == k×lunghezza array (k intero), rotate creerà un vettore
uguale a quello dato, ovvero nessuna modifica.
*/


main(){

  const int LENGHT = 5;
  int numeri[LENGHT];

  //richiedi numeri all'utente
  for(int i = 0; i < LENGHT; i++){
    std::cout << "Inserisci il valore n. "  << i+1 << ": ";
    std::cin >> numeri[i];
  }

  //richiedi di quante posizioni bisogna shiftare l'array
  int N;
  std::cout << "Di quante posizioni vuoi traslare l'array (intero positivo = destra; intero negativo = sinistra)? ";
  std::cin >> N;

  //Evita di fare calcoli inutili: se LENGHT è divisore di N,
  //il risultato sarà sempre quello di partenza
  if((N % LENGHT) != 0){
    //Distingui i casi possibili
    if(N < 0){
      //Bisogna traslare l'array verso sinistra per N volte

      for (int j = 0; j < -N; ++j)
        for (int i = 1; i < LENGHT; ++i) {
          numeri[i-1] = numeri[i];

          if(i == LENGHT-1)
            numeri[LENGHT-1] = 0;
        }

    } else if(N > 0){
      //Bisogna traslare l'array verso destra per N volte

      for (int j = 0; j < N; ++j)
        for (int i = LENGHT-1; i >= 0; --i) {
          numeri[i+1] = numeri[i];

          if(i == 0)
            numeri[0] = 0;
        }
    }
    //se N==0, non modificare l'array
  }

  //Stampa risultato
  std::cout << "\nL'array traslato di " << N << " posizioni e': ";
  for(int i = 0; i < LENGHT; ++i)
    std::cout << numeri[i] << " ";

  return 0;
}
