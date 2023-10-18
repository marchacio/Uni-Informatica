#include "reverse_vector.h"

#include <vector>
#include <iostream>


int main(){

  std::vector<int> source;

  std::cout << "Inserisci gli elementi positivi del vector (inseriscine uno negativo per terminare): ";

  int elem = 1;
  while(elem > 0){
    std::cin >> elem;

    if(elem > 0) source.push_back(elem);
  }

  std::vector<int> dest = reverse(source);

  printVector(source);
  std::cout << std::endl;
  printVector(dest);

}
