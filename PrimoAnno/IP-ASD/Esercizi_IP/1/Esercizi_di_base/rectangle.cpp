#include <iostream>
using namespace std;

/*
  CONSEGNA: Scrivere un programma che calcola perimetro e area di un rettangolo, dopo aver chiesto e letto i dati necessari. Il programma
    deve essere scritto in un file chiamato rectangle.cpp.
*/

int main() {

  //Dichiara le variabili
  int lato_lungo, lato_corto;

  //Richiedi il lato corto
  cout << "Digita il valore del lato corto: ";
  cin >> lato_corto;

  //Richiedi il lato lungo
  cout << "Digita il valore del lato lungo: ";
  cin >> lato_lungo;

  //Calcolo area e perimetro
  int perimetro = (lato_corto * 2) + (lato_lungo * 2);
  int area = lato_lungo * lato_corto;

  //Stampa i risultati
  cout << "Area: " << area << endl;
  cout << "Perimetro: " << perimetro;
}
