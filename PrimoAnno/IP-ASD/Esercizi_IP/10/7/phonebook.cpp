#include "phonebook.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//aggiunge un contatto C in coda alla rubrica B
void add(PhoneBook& B, string surname, string name, int phoneNumber) {
  Contact_Str cntc = {name, surname, phoneNumber};

  B.push_back(cntc);
}

//stampare il contenuto della rubrica B
void print(const PhoneBook& B){
  for(unsigned int i = 0; i < B.size(); ++i)
    cout << B.at(i).name << " " << B.at(i).surname << " " << B.at(i).phonenumber << "\n";
}

//data una rubrica ordini alfabeticamente gli elementi in
//essa contenuti rispetto al campo Surname
void sortSurnames(PhoneBook& B){
  for(unsigned int i = 0; i < B.size(); ++i){
    unsigned int minIndex = i;

    for(unsigned int j = i+1; j < B.size(); ++j){
      if(B.at(minIndex).surname > B.at(j).surname){
        minIndex = j;
      }
    }

    if(minIndex != i){
      Contact_Str tmp = B.at(minIndex);
      B.at(minIndex) = B.at(i);
      B.at(i) = tmp;
    }

  }
}


/*
utilizzando la ricerca binaria, abbia il seguente comportamento:
• Se nella rubrica esiste un contatto C il cui campo C.Surname è uguale all’argomento S, allora restituisca l’indice di
tale contatto nella rubrica (ossia nel vettore)
• Se nella rubrica non esiste un contatto C il cui campo C.Surname è uguale all’argomento S, allora restituisca l’indice
del contatto che sarebbe quello immediatamente precedente in ordine alfabetico.
[SUGGERIMENTO: Ricordate che la ricerca binaria assume che il vettore sia ordinato]
*/
int FindPos(const PhoneBook& r, string S){
  int medio = r.size()/2;
  int max = (int)r.size()-1;
  int min = 0;

  bool trovato = false;

  while (trovato == false) {
    if(S > r.at(medio).surname && S < r.at(medio+1).surname){
      trovato = true;
    }else if(S < r.at(medio).surname){
      max = medio;
      medio = max /2;

    }else if(S > r.at(medio).surname){
      min = medio;
      float mid = ((float)max+(float)min)/2+0.5;
      medio = (int)mid;

      //cout << S << ">" << r.at(medio).surname << "    max: " << max << "   medio: " << medio << "  min: " << min << "\n";
    }else if(S == r.at(medio).surname){
      trovato = true;
    }
  }

  return medio;
}

//incrementa di un elemento la dimensione
//del vettore B e poi sposta a destra di un elemento
//tutti gli elementi a partire dalla posizione pos+1.
void Shift_PhoneBook(PhoneBook& B, int pos){
  
}
