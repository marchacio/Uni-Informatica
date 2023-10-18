#include "ndigits.h"

int n_cifre(int num){
  int cifre = 0;

  //distingui i casi possibili
  if(num >= 0){
    while(num > 0) {
      num /= 10;
      cifre++;
    }
  } else {
    while(num < 0) {
      num /= 10;
      cifre++;
    }
  }

  return cifre;
}
