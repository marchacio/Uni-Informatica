#include <iostream>

/*
  CONSEGNA: Scrivere un programma che legge un numero intero e ne stampa il valore assoluto (ovvero il numero senza segno, ad esempio
    se leggo −7 devo stampare 7).
*/

int main() {

  //Dichiarazione variabili
  int numero;

  //Assegnazione variabili
  std::cout << "Scrivi un numero: ";
  std::cin >> numero;

  //Condizione logica che restituisce il valore assoluto della varaibile numero
  if(numero < 0)
    std::cout << "Il valore assoluto del numero e': " << -numero;
  else
    std::cout << "Il valore assoluto del numero e': " << numero;

  return 0;
}
