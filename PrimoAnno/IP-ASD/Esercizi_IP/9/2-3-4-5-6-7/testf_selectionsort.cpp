#include "d_array.h"

int main() {

  dynamic_array dynm;

  read_d_array(dynm);

  SelectionSort(dynm);

  print_d_array(dynm);

  return 0;
}
