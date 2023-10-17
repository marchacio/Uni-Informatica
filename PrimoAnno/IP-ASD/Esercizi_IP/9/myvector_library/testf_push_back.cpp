#include "myvector.h"

#include <string>
#include <iostream>


int main() {

  myvector vec;

  create(vec, 5);

  try {
    push_back(vec, 1);
    push_back(vec, 3);
    push_back(vec, 4);
    push_back(vec, 4);
    push_back(vec, 4);
    push_back(vec, 4);
  } catch(std::string err) {
    std::cout << err;
  }


  print(vec);

  return 0;
}
