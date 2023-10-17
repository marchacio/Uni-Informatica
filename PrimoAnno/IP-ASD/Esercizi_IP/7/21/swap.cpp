#include "swap.h"

void swap(double& a, double& b){
  double tmp = a;

  a = b;
  b = tmp;
}
