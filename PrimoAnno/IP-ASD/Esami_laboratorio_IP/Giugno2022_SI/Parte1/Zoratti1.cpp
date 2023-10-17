#include "hist.h"


// Aggiunge
void add(Hist& h, const int v)
{
  int indexFound = -1;
  for(unsigned int i = 0; i < h.size() && indexFound == -1; ++i)
    if(h.at(i).value == v)
      indexFound = i;


  if(indexFound != -1){
    //Vuol dire che ha trovato il Bin
    h.at(indexFound).num++; //CONTROLLA
  } else {
    //Non ha trovato un bin esistente, ne crea uno nuovo
    Bin nuova = {v, 1};
    h.push_back(nuova);
  }
}

// ordina h in modo crescente secondo "value"
void sort(Hist& h)
{
  for(unsigned int i = 0; i < h.size(); ++i){
    unsigned int indexMin = i;
    for(unsigned int j = i+1; j < h.size(); ++j)
      if(h.at(j).value < h.at(indexMin).value)
        indexMin = j;

    if(i != indexMin){
      Bin tmp = h.at(i);
      h.at(i) = h.at(indexMin);
      h.at(indexMin) = tmp;
    }
  }
}

// Cerca, restituisce conteggio
int count(const Hist & h, int v)
{
  for(unsigned int i = 0; i < h.size(); ++i)
    if(h.at(i).value == v)
      return h.at(i).num;

  return 0;
}
