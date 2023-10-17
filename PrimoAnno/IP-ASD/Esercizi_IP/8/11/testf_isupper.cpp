#include <iostream>
#include "isupper.h"

/*
Scrivere una funzione isUpper che presa una matrice quadrata di caratteri
restituisce true se tutti gli elementi contenuti sono
lettere maiuscole, cioè caratteri nell’intervallo ['A','Z'], false
altrimenti usando l’aritmetica dei puntatori per scorrere la matrice.
*/

int main() {

  const int N1 = 3;
  const int N2 = 5;

  int car[N1][N2] = {
    {'A', 'B', 'C', 'D', 'E'},
    {'A', 'B', 'C', 'D', 'E'},
    {'A', 'B', 'C', 'D', 'E'},
  };

  std::cout << std::boolalpha << "L'array contiene sono lettere maiuscole? " << isUpper(N1, N2, car[0]);

  return 0;
}
