#include "myvector.h"

#include <string>
#include <iostream>


int main() {

  myvector vec;

  create(vec, 5);

  push_back(vec, 1);
  push_back(vec, 3);
  push_back(vec, 4);

  pop_back(vec);

  print(vec);

  return 0;
}
