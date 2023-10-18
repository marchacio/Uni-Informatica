#include "iovector.h"
#include <vector>

int main() {

  // dichiarare un std::vector vect di interi
  // chiamare la funzione readVector su vect
  // chiamare la funzione printVector su vect

  std::vector<int> vect;

  readVector(vect);
  printVector(vect);

  return 0;
}
