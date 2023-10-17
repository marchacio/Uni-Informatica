#include <iostream>
using namespace std;

/*
  CONSEGNA: Scrivere un programma che calcola perimetro e area di un triangolo, dopo aver chiesto e letto i dati necessari. Il programma
    deve essere scritto in un file chiamato triangle.cpp
*/

int main() {

  //Supponendo che il triangolo sia un tri. equilatero, dichiaro variabile
  int lato;

  //Richiesta dati all'utente
  cout << "Quanto e' lungo in lato? ";
  cin >> lato;

  //calcolo area e perimetro
  float area = lato * lato / 2.;
  int perimetro = lato * 3;

  //Stampo i risultati
  cout << "L'area del triangolo e': " << area << endl;
  cout << "Il perimetro del triangolo e': " << perimetro << endl;

  return 0;
}
