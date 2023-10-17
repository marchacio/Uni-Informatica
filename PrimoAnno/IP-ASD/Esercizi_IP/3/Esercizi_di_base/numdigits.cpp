#include <iostream>

/*. Scrivere un programma che chiede all’utente un numero intero positivo e ne stampa il numero di cifre (in base 10). Ad
    esempio su 27458 stampa 5. [ File numdigits.cpp ]
*/

int main() {
  //dichiarazione variabili
  int numero;

  //Assegnazione
  std::cout << "Digita un numero intero positivo: ";
  std::cin >> numero;

  //calcolo cifre
  int cifre = 0;
  while (numero > 0) {
    ++cifre;
    numero = numero / 10;
  }

  //Stampo risultato
  std::cout << "Numero di cifre: " << cifre;

  return 0;
}
