#include <iostream>

/*. Scrivere un programma che chiede all’utente un numero intero maggiore di 1 e ne stampa
  la scomposizione in fattori primi.
  Ad esempio su 392 stampa "392 = 2^3 * 7^2", usando il carattere '^' per rappresentare l’elevamento a potenza.
  [ File primefactors.cpp ]
*/

int main() {

  //dichiarazione variabili
  int numero;
  int divisore;

  //Assegnazione
  std::cout << "Digita un numero intero positivo maggiore di 1: ";
  std::cin >> numero;

  int n = numero;
  //Valore booleano per stampare o no l'* nella stampa finale
  bool primaStampa = true;

  //Logica
  for(divisore = 2; divisore < numero; divisore++){
    //variabile che contiene il numero di volte in cui viene usato il divisore
    int numeroUtilizzoDivisore = 0;

    //Calcolo della potenza
    while((n % divisore) == 0 && numero > 0){
      numeroUtilizzoDivisore++;
      n = n/divisore;
    }

    //Stampa solo i numeri che vengono usati almeno una volta
    if(numeroUtilizzoDivisore > 0){
      if(!primaStampa)
        std::cout << " * ";
      std::cout << divisore << "^" << numeroUtilizzoDivisore;
      primaStampa = false;
    }
  }

  std::cout << std::endl;

  return 0;
}
