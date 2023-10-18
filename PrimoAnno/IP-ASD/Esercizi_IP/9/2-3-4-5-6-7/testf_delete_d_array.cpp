#include "d_array.h"
#include <iostream>

int main() {

  dynamic_array dynm;
  read_d_array(dynm);

  try{
    delete_d_array(dynm);
    delete_d_array(dynm);
  } catch (std::string err) {
    std::cout << err;
  }

  return 0;
}
