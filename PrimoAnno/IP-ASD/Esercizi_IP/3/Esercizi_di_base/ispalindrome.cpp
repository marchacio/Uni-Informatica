#include <iostream>

/*.
Scrivere un programma che chiede all’utente un numero intero e verifica se è palindromo, ovvero se le sue cifre (in base 10)
lette da destra a sinistra corrispondono alle cifre lette da sinistra a destra (ad esempio 165373561 è palindromo). Dopo la
verifica stampa il risultato all’utente. [ File ispalindrome.cpp ]
*/

int main() {
  //dichiarazione variabili
  int numero;
  int numeroRibaltato = 0;

  //Assegnazione
  std::cout << "Digita un numero intero: ";
  std::cin >> numero;

  int divnum = numero;

  while (divnum > 0) {
    int cifra = divnum % 10;
    numeroRibaltato = numeroRibaltato * 10 + cifra;
    divnum = divnum / 10;
  }

  if(numero != numeroRibaltato)
    std::cout << "Non e' palindromo";
  else
    std::cout << "E' palindromo";

  return 0;
}
