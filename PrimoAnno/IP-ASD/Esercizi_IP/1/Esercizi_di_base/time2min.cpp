#include <iostream>
using namespace std;

/*
  CONSEGNA: Scrivere un programma che prende in input il numero di ore (compreso fra 0 e 23) e di minuti (compreso fra 0 e 59) e
    stampa in output il numero di minuti totali. Il programma deve essere scritto in un file chiamato time2min.cpp.
*/

int main() {

  //Dichiaro le variabili
  int ore, minuti;

  //Assegno valori alle variabili
  cout << "Digita il numero di ore (compreso tra 0 e 23): ";
  cin >> ore;

  cout << "Digita il numero di minuti: ";
  cin >> minuti;

  //Calcolo il numero di minuti totali
  int totale = ore * 60 + minuti;

  //Stampo il risultato
  cout << "I minuti totali sono: " << totale;

  return 0;
}
