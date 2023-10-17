#include "AlbumLibrary.h"
#include <iostream>

void sortAlbumLibrary(AlbumLibrary& AL) {
  // dichiara una variabile greatestIndex di tipo unsigned int
  unsigned int gratestIndex;
  for(unsigned int i = 0; i < AL.size(); i++){
    gratestIndex = i;
    for(unsigned int j = i+1; j < AL.size(); j++){
      if(AL.at(j).year < AL.at(gratestIndex).year
        || (AL.at(j).year == AL.at(gratestIndex).year && AL.at(j).title < AL.at(gratestIndex).title))
        gratestIndex= j;
    }

    if(i != gratestIndex){
      Album tmp = AL.at(i);
      AL.at(i) = AL.at(gratestIndex);
      AL.at(gratestIndex) = tmp;
    }
  }
  /* per tutti gli elementi di AL
    memorizza in greatestIndex la posizione corrente (sia i)
      per gli elementi di AL dalla posizione successiva a quella corrente, ossia da i+1
        se il campo year alla posizione corrente (sia j) è minore di quello alla...
        ... alla posizione greatestIndex OPPURE il valore di year è lo stesso ma...
        ... il titolo alla posizione j precede alfabeticamente quello alla...
        ... posizione greatestIndex
        memorizza j in greatestIndex
      */
    // se i è diverso da greatestIndex, scambia il contenuto alla posizione i...
    // ... con quello alla posizione greatestIndex
}


void insertAlbum(const Album& A, AlbumLibrary& AL){
  //trova l'index in cui mettere l'album
  unsigned int index = 0;
  for(unsigned int i = 0; i < AL.size(); ++i){
    if(AL.at(i).year < A.year
      || (AL.at(i).year == A.year && AL.at(i).title < A.title))
      index = i;
  }
  std::cout << index;
  AL.push_back(AL.back());

  for(unsigned int i = AL.size()-2; i >= index; i--){
    std::cout<< i << " ";
    AL.at(i+1) = AL.at(i);
  }

  AL.at(index) = A;
}
