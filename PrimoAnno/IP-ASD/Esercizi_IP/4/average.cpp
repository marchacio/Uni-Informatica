#include <iostream>

/*
Scrivere un programma che legge N valori reali, li memorizza in un array di lunghezza N, e ne stampa la media.
[ File average.cpp ]

// copiare qui il codice del programma ``leggiArrayFloat''
// dichiarare una variabile sum di tipo float e inizializzarla a zero
/* iterare su i a partire da 0 e fino a N-1
    - sommare il contenuto dell'i-esimo elemento di v a sum
*/
// stampare la divisione di sum per N


main() {

  const int N = 10;

  float v[N];

  for (int i = 0; i < N; ++i) {
    float val;
    std::cout << "Valore n." << i << ": ";
    std::cin >> val;

    v[i] = val;
  }

  float sum = 0.0;
  for (int i = 0; i < N; ++i) {
    sum += v[i];
  }

  std::cout << "La media dei " << N << " input e': " << sum/N;

  return 0;
}
