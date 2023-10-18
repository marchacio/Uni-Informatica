#include "myvector.h"

#include <string>
#include <iostream>


int main() {

  myvector vec;

  create(vec, 10);

  push_back(vec, 1);
  push_back(vec, 3);
  push_back(vec, 14);
  push_back(vec, 6);
  push_back(vec, 2);
  push_back(vec, 8);
  push_back(vec, 3);
  push_back(vec, 87);
  push_back(vec, 34);

  selectionSort(vec);

  print(vec);

  return 0;
}
