#include "d_array.h"
#include <iostream>


int main() {

  dynamic_array dynm;

  try{
    create_d_array(dynm, 5, 1);

    print_d_array(dynm);
  } catch (std::string err) {
    std::cout << err;
  }


  return 0;
}
