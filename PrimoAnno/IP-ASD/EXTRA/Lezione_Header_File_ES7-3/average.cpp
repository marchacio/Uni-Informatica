#include <iostream>
#include "average.h"

float average(int hm){

  //Controllo la positività di hm
  if(hm <= 0) throw 666;

  float sum = 0.0;

  for(int i = 0; i < hm; ++i){
    std::cout << "Inserisci un numero float: ";
    float x;
    std::cin >> x;

    sum += x;
  }

  return sum / hm;
}
