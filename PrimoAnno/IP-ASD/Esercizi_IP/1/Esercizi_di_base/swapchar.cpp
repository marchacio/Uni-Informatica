#include <iostream>
using namespace std;

int main() {

  /*CONSEGNA: Scrivere un programma che scambia i valori di due variabili di tipo char, lette da input, e stampa i valori prima e dopo lo
    scambio. Il programma deve essere scritto in un file chiamato swapchar.cpp*/

  //Dichiara la variabile char a e assegnale il valore di input
  cout << "Digita la prima lettera: ";
  char a;
  cin >> a;

  //Dichiara la variabile char b e assegnale il valore di input
  cout << "Digita la seconda lettera: ";
  char b;
  cin >> b;

  //stampa i valori prima dello scambio
  cout << "Il valore di a: " << a << endl;
  cout << "Il valore di b: " << b << endl;

  //Scambia i valori tramite una variabile d'appoggio c
  char c = a;
  a = b;
  b = c;

  //stampa i valori dopo lo scambio
  cout << "Il valore di a: " << a << endl;
  cout << "Il valore di b: " << b << endl;

  return 0;
}
