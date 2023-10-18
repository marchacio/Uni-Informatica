#include <iostream>

/*
  CONSEGNA: Scrivere un programma che legge un numero intero da input
    e stampa se è o no divisibile per 13
*/

int main() {

  //Dichiarazione variabili
  int numero;

  //Assegnazione variabili
  std::cout << "Digita un numero: ";
  std::cin >> numero;

  //condizione logica che restituisce se il numero è divisibile per 13
  if((numero % 13) == 0) {
    std::cout << "Il numero " << numero << " e' divisibile per 13";
  } else {
    std::cout << "Il numero " << numero << " NON e' divisibile per 13";
  }
}
