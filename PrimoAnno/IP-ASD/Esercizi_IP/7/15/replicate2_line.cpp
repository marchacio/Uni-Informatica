#include <iostream>
#include "replicate2_line.h"

void replicate2_line(int f, char f_c, int s, char s_c){
  for(int i = 0; i < f; ++i)
    std::cout << f_c;

  for(int i = 0; i < s; ++i)
    std::cout << s_c;
}
