#include <iostream>
using namespace std;

/*
  CONSEGNA: Scrivere un programma che legge due interi e ne stampa la media (come numero reale). Ad esempio sull’input 1 e 2 stampa
    1.5. Il programma deve essere scritto in un file chiamato mean.cpp.
*/

int main() {

  //Dichiarazione variabili
  int a, b;

  //Assegnazione valore alle variabili
  cout << "Valore primo numero: ";
  cin >> a;

  cout << "Valore secondo numero: ";
  cin >> b;

  //Calcolo media
  double media = (a + b) / 2.;

  //Stampo risultato
  cout << "La media dei due numeri vale: " << media;

  return 0;
}
