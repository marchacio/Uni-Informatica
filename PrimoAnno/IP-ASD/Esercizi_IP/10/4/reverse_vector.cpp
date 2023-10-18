#include "reverse_vector.h"

#include <vector>
#include <iostream>

//Scrivere una funzione std::vector<int> reverse(std::vector<int> v) che
//prende in ingresso un std::vector<int> v e restituisce un std::vector<int>
//contenente il contenuto di v in ordine inverso.
std::vector<int> reverse(std::vector<int> v){
  std::vector<int> reversed;

  for(int i = (int)v.size()-1; i >= 0; i--)
    reversed.push_back(v.at(i));

  return reversed;
}


void printVector(const std::vector<int>& v) {
  for(unsigned int i = 0; i < v.size(); ++i)
    std::cout << v.at(i) << " ";
}
