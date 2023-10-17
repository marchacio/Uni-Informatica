#include <iostream>
#include "d_array.h"

int main() {

  dynamic_array dynm;
  create_d_array(dynm, 5, 2);

  std::cout << get(dynm, 0);

}
