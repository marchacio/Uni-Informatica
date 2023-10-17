#include "num.h"
#include <iostream>

num* int2list(int inum)
{
  num* list = nullptr;

  //Questo è il caso in cui il inum abbia una sola cifra
  if(inum%10 == 0){
    list = new num;
    list->next = nullptr;
    list->digit = inum;

    return list;
  }

  while(inum%10 != 0){
    int cifra = inum % 10;
    //std::cout << "cifra: " << cifra;

    if(list == nullptr){
      list = new num;
      list->next = nullptr;
      list->digit = cifra;
    } else {
      num* coda = new num;
      coda->next = nullptr;
      coda->digit = cifra;

      //attacca la coda alla lista
      num* aux = list;
      while(aux->next != nullptr)
        aux = aux->next;

      aux->next = coda;
    }

    inum = inum/10;
  }

  return list;
}

num * sum(num* n1, num* n2){
  int num1 = 0;
  int moltiplicatore = 1;
  num* aux = n1;
  while(aux != nullptr){
    num1 += aux->digit*moltiplicatore;

    moltiplicatore *= 10;
    aux = aux->next;
  }

  int num2 = 0;
  moltiplicatore = 1;
  aux = n2;
  while(aux != nullptr){
    num2 += aux->digit*moltiplicatore;

    moltiplicatore *= 10;
    aux = aux->next;
  }

  //std::cout << "-1: " << num1 << " -2: " << num2 << "    ";

  return int2list(num1+num2);
}

/*
num * sum(num* n1, num* n2)
{
  num* risultato = nullptr;

  num* aux1 = n1;
  num* aux2 = n2;

  bool riporto = false;
  while(aux1 != nullptr || aux2 != nullptr){
    int num1;
    if(aux1 == nullptr)
      num1 = 0;
    else
      num1 = aux1->digit;

    int num2;
    if(aux2 == nullptr)
      num2 = 0;
    else
      num2 = aux2->digit;

    int somma = num1 + num2;

    //Se c'è il riporto dall'operazione precedente
    if(riporto){
      somma++;
      riporto = false;
    }

    if(somma >= 10){
      riporto = true;
      somma /= 10;
    }

    num* cell = new num;
    cell->digit = somma;
    cell->next = risultato;

    risultato = cell;
  }


  return risultato;
}

*/
