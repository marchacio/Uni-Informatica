#include <iostream>
using namespace std;

/*
  CONSEGNA: Scrivere un programma che calcola circonferenza e area di un cerchio, dopo aver chiesto e letto i dati necessari. Il programma
    deve essere scritto in un file chiamato circle.cpp*/

  //Circonferenza: 2*PI*r
  //Area: PI*r*r

int main() {

  //Definire Pi Greco
  const float PI = 3.14;

  //Dichiarazione e assegnazione variabile raggio
  int raggio;
  cout << "Qual'e' il valore del raggio? ";
  cin >> raggio;

  //Calcolo area e circonferenza
  double area = PI*raggio*raggio;
  double circonferenza = 2*PI*raggio;

  //Stampo i risultati
  cout << "L'area vale " << area << endl;
  cout << "La circonferenza vale " << circonferenza;

  return 0;
}
