#include "isupper.h"

bool isUpper(int size1, int size2, int *arr){

  //Secondo la tabella ascii, le lettere maiuscole sono tra il numero
  //65 (A) e 90 (Z)
  for(int i = 0; i < (size1 * size2); ++i)
    if(*(arr+i) < 65 || *(arr+i) > 90) return false;

  return true;
}
