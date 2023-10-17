#include <iostream>
using namespace std;

int main() {

  //Assegno un valore di input ad a
  cout << "Inserisci il valore che vuoi dare al primo numero: ";
  //Dichiarazione variabili
  int a;
  cin >> a;

  //Assegno un valore di input a b
  cout << "Inserisci il valore che vuoi dare al secondo numero: ";
  //Dichiarazione variabili
  int b;
  cin >> b;

  // stampare un a capo seguito dalla stringa "a vale " e dal valore di a
  cout << endl << "a vale: " << a;
  // stampare un a capo seguito dalla stringa "b vale " e dal valore di b
  cout << endl << "b vale: " << b;

  // dichiarare una variabile c di tipo int inizializzata con il valore di a
  int c = a;
  // assegnare ad a il valore di b
  a = b;
  // assegnare a b il valore di c, ovvero il valore iniziale di a
  b = c;

  // stampare un a capo seguito dalla stringa "a vale " e dal valore di a
  cout << endl << "a vale: " << a;
  // stampare un a capo seguito dalla stringa "b vale " e dal valore di b
  cout << endl << "b vale: " << b;

  return 0;
}
