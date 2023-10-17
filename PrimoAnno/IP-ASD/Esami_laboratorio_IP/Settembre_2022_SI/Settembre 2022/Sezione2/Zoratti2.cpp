#include <cmath>
#include "boomerang.h"
#include <iostream>

int contaBoomerang(std::vector<punto> punti)
{
  if(punti.size() < 3)
    throw -1;

  int counter = 0;

  for(unsigned int i = 0; i < punti.size()-2; ++i){

    float distanza1 = sqrt(((punti.at(i).x-punti.at(i+1).x) * (punti.at(i).x-punti.at(i+1).x)) + ((punti.at(i).y-punti.at(i+1).y) * (punti.at(i).y-punti.at(i+1).y)));
    float distanza2 = sqrt(((punti.at(i+1).x-punti.at(i+2).x) * (punti.at(i+1).x-punti.at(i+2).x)) + ((punti.at(i+1).y-punti.at(i+2).y) * (punti.at(i+1).y-punti.at(i+2).y)));

    if(equals(distanza1, distanza2))
      counter++;
  }

  return counter;
}

bool equals(float a, float b)
{
  float eps = 1e-5;
  return fabs(a-b) < eps;
}
