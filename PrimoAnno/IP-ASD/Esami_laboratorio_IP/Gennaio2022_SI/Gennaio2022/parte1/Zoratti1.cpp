#include <iostream>
#include "bow.h"

// Aggiunge
void add(BagOfWords & b, const std::string w)
{
  for(unsigned int i = 0; i < b.size(); ++i)
    if(b.at(i).word == w){
      b.at(i).num++;
      return;
    }

  std::cout << "AGGIUNGO " << w << std::endl;
  Entry added = {w, 1};
  b.push_back(added);
}

// Cancella
void del(BagOfWords & b, const std::string w)
{
  for(unsigned int i = 0; i < b.size(); ++i)
    if(b.at(i).word == w){
      if(b.at(i).num > 1)
        b.at(i).num--;
      else if(b.at(i).num == 1){
        for(unsigned int j = i; j < b.size()-1; ++j)
          b.at(i) = b.at(i+1);

        b.resize(b.size()-1);
      }
    }
}

// Restituisce conteggio
int count(const BagOfWords & b, std::string w)
{
  for(unsigned int i = 0; i < b.size(); ++i)
    if(b.at(i).word == w)
      return b.at(i).num;

  return 0;
}
