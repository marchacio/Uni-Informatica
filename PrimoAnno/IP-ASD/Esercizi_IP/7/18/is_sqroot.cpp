#include <cmath>
#include "is_root.h"

bool funct(float x, float sqrt_x){
  return std::fabs(sqrt_x*sqrt_x - x) < 0.0001;
}
