#include <iostream>

//Con la seguente riga, includo nel mio file attuale un file header esterno (average.h)
//Per eseguire correttamente il programma, bisogna compilare anche il file contenente il corpo della funzione:
//in questo caso average.cpp
//Si fa con il comando c++ -Wall -std=c++14 .\testf_average.cpp .\average.cpp
#include "average.h"

int main() {

  int n = 2;

  try{
    float media = average(n);
    std::cout << "La media dei " << n << " numeri e': " << media;
  } catch(int err) {
    std::cout << "Mi spiace, ma " << n << " non e' un valore valido";
  }
}
