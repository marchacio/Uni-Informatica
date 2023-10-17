#include "d_array.h"

int main() {

  dynamic_array dynm;
  create_d_array(dynm, 5, 1);

  set(dynm, 0, 7);

  print_d_array(dynm);

  return 0;
}
