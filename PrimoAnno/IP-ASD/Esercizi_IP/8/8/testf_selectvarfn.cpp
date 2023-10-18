#include <iostream>
#include "selectvarfn.h"

int main() {

  const int N = 5;

  char v[N] = {'a', 'b', '2', '5', '6'};
  int n_cifre = selectvarfn(N, v);
  
  std::cout << "Numero di cifre: " << n_cifre;

  return 0;
}
