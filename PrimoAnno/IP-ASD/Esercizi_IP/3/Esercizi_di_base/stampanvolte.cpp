#include <iostream>

/*
Scrivere un programma che legge un numero intero n strettamente positivo ed un carattere, e stampa il carattere n volte. [
File stampanvolte.cpp ]
*/

int main() {

  //Dichiarazione variabili
  //numeroVolte dev'essere strettamente positivo
  int numeroVolte;
  char carattere;

  //Assegnazione variabile numeroVolte
  std::cout << "Inserisci il numero di volte che vuoi replicare un carattere (strettamente maggiore di zero): ";
  std::cin >> numeroVolte;

  if(numeroVolte <= 0){
    std::cout << "Avevo detto positivo...";
    return 1;
  }

  //Assegnazione variabile carattere
  std::cout << "Inserisci il carattere da replicare: ";
  std::cin >> carattere;

  //Stampa numeroVolte carattere
  for(int i = 0; i < numeroVolte; ++i){
    std::cout << carattere;
  }

  return 0;
}
