#include "selectvarfn.h"

int selectvarfn(int lenght, char v[]){
  char *punt = v;

  int n_cifre = 0;

  for(int i=0; i<lenght; ++i)
    if(isNumber(*(punt+i)))
      n_cifre++;

  return n_cifre;
}

bool isNumber(char c){
  return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5'
  || c == '6' || c == '7' || c == '8' || c == '9';
}
