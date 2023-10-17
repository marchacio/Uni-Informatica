#include <iostream>

/*
Leggi un array di float da tastiera. Scrivere un programma uguale al precedente, ma che lavora su array di float.
[ File leggiArrayFloat.cpp ]
*/

main() {

  const int N = 10;

  float v[N];

  for (int i = 0; i < N; ++i) {
    float val;
    std::cout << "Valore n." << i << ": ";
    std::cin >> val;

    v[i] = val;
  }

  return 0;
}
