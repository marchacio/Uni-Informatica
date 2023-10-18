#include "insert.h"

#include <vector>


//La funzione aggiunge a v il valore di val in posizione i
std::vector<int> insert(std::vector<int> v, int i, int val) {
  //Controlla che i sia corretto
  if(i < 0 || i > (int)v.size()) throw -1;

  v.resize(v.size() + 1);

  for(int j = (int)v.size()-1; j >= i; --j){
    if(j > i)
      v.at(j) = v.at(j-1);
    else if(j == i)
      v.at(j) = val;
  }

  return v;
}
