#include <iostream>

/*
Scrivere un programma che legge lettere maiuscole finché l’utente non inserisce un carattere che non è una lettera maiuscola
e stampa la prima in ordine alfabetico. [ File alphafirst.cpp ]
[SUGGERIMENTO: Le lettere maiuscole vengono rappresentate con numeri consecutivi, quindi per sapere se un carattere
rappresenta una lettera maiuscola basta verificare che sia maggiore o uguale del carattere ‘A’ e minore o uguale al carattere
‘Z’.]
*/

int main() {

  //Dichiarazione variabili
  char carattere;

  do {
    //Assegna variabile
    std::cout << "Inserisci una lettera maiuscola: ";
    std::cin >> carattere;

  } while(!(carattere >= 'A' && carattere <= 'Z'));

  //a questo punto carattere è maiuscola

  //Dichiarazione variabile temporanea
  char c = 'Z';

  //Finche c è una lettera maiuscola esegui il ciclo;
  //Se c non è lettera maiuscola, esci dal ciclo e stampa la lettera piu piccola
  while(c >= 'A' && c <= 'Z') {
    //Se c è minore di carattere vuol dire che l'utente ha inserito la lettera piu piccola fino ad ora
    if(c < carattere)
      carattere = c;

    //Ripeti la richiesta
    std::cout << "Inserisci una lettera maiuscola (o altro carattere per terminare): ";
    std::cin >> c;
  }

  //Stampa risultato
  std::cout << "La lettera piu' piccola e': " << carattere;

  return 0;
}
