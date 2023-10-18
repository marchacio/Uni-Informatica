#include <iostream>
using namespace std;

int main() {

  /*
  CONSEGNA: Scrivere un programma che scambia in maniera circolare “verso sinistra” i valori di tre variabili di tipo float, lette da input,
    e stampa i valori prima e dopo lo scambio. Il programma deve essere scritto in un file chiamato rotleft.cpp.

    Situazione iniziale:
    a contiene il valore x b contiene il valore y c contiene il valore z
    Risultato finale:
    a contiene il valore y b contiene il valore z c contiene il valore x
    Ad esempio se vengono inseriti i valori 3.5, 4.7 e −8.978 li assegna a variabili a, b e c (nell’ordine) e stampa 3.5, 4.7 e
    −8.978. Poi assegna 4.7 ad a, −8.978 a b e 3.5 a c e stampa 4.7, −8.978 e 3.5.
  */

  //Dichiarazione variabili
  float a, b, c;

  //Assegnazione valore ad a
  cout << "Digita il valore float di a: ";
  cin >> a;

  //Assegnazione valore ad b
  cout << "Digita il valore float di b: ";
  cin >> b;

  //Assegnazione valore ad c
  cout << "Digita il valore float di c: ";
  cin >> c;

  //Stampa il risultato dell'assegnazione
  cout << "Valore di a: " << a << endl;
  cout << "Valore di b: " << b << endl;
  cout << "Valore di c: " << c << endl;

  //Scambia i valori tra le variabili
  //Dichiara e inizializza una variabile d'appoggio app con valore di a
  float app = a;

  //Scambia i valori
  a = b;
  b = c;
  c = app;

  //Stampa il risultato dello scambio
  cout << "Valore di a: " << a << endl;
  cout << "Valore di b: " << b << endl;
  cout << "Valore di c: " << c << endl;

  return 0;
}
