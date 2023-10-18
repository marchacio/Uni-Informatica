#include <iostream>

/*
Scrivere un programma che chiede all’utente di inserire e leggere numeri interi e poi chiede all’utente se vuole continuare
e legge la risposta finché l’utente non risponde di no. Finito il ciclo di lettura stampa la media dei numeri letti. [ File
mediainterattiva.cpp ]
*/

int main() {

  //dichiarazione variabili
  int sommaNumeri = 0;
  int conteggioNumeri = 0;
  char continuaProgramma = 's';

  //Ciclo di vita del programma
  while (continuaProgramma == 's' || continuaProgramma == 'S') {
    int tempInput;

    std::cout << "Inserisci il " << conteggioNumeri + 1 << "' numero intero: ";
    std::cin >> tempInput;

    //Aggiorna le variabili del main
    sommaNumeri += tempInput;
    conteggioNumeri++;

    //Chiedi all'utente se continuare il calcolo della media. In caso negativo, stampa la media
    std::cout << "Vuoi aggiungere altri numeri (s = si, n = no)? ";
    std::cin >> continuaProgramma;
    std::cout << std::endl;
  }

  //Stampa la media
  float media = (float)sommaNumeri/conteggioNumeri;
  std::cout << "La media dei tuoi numeri e': " << media << " (" << sommaNumeri << "/" << conteggioNumeri << ")";

  return 0;
}
