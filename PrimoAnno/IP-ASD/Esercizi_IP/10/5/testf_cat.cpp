#include "cat.h"

#include <vector>
#include <iostream>

int main() {

  std::vector<int> v1;
  std::vector<int> v2;

  //Inserimento dei valori del primo vector:
  std::cout << "Inserisci i valori del primo vector (strettamente positivi, altrimenti passa al prossimo vector): ";
  int val = 1;
  while(val > 0){
    std::cin >> val;

    if(val > 0) v1.push_back(val);
  }

  //Inserimento dei valori del secondo vector:
  std::cout << "Inserisci i valori del secondo vector (strettamente positivi, altrimenti termina): ";
  val = 1;
  while(val > 0){
    std::cin >> val;

    if(val > 0) v2.push_back(val);
  }

  std::vector<int> total = cat(v1, v2);

  //Stampa tutto
  std::cout << std::endl << "v1: ";

  for(unsigned int i = 0; i < v1.size(); ++i)
    std::cout << v1.at(i) << " ";

  std::cout << std::endl << "v2: ";

  for(unsigned int i = 0; i < v2.size(); ++i)
    std::cout << v2.at(i) << " ";

  std::cout << std::endl << "total: ";

  for(unsigned int i = 0; i < total.size(); ++i)
    std::cout << total.at(i) << " ";

}
