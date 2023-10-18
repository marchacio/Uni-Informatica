#include "string_list.h"

#include <string>
#include <iostream>

using namespace std;

//stampa gli elementi della lista
void print(const list l){
  list aux = l;

  while(aux->next != nullptr){
    cout << aux->value << " ";
    aux = aux->next;
  }
}

//inserisce un elemento in testa alla lista
void headInsert(list& l, string s){
  list aux = new cell;
  aux->value = s;
  aux->next = l;

  l = aux;
}

//legge valori da input e li inserisce in coda alla lista
void read(list& l){
  cout << "Inserisci tutti le stringhe che vuoi aggiungere alla lista;\nInserisci 0 per confermare\n";

  string inserimento;
  while(inserimento != "0"){
    cin >> inserimento;

    list nuovaCella = new cell;
    nuovaCella->next = nullptr;
    nuovaCella->value = inserimento;

    //Crea una cella ausiliaria per arrivare all'ultima cella disponibile
    list aux = l;
    while(aux->next != nullptr)
      aux = aux->next;

    //attacca l'ultima cella a quella creata precedentemente
    aux->next = nuovaCella;
  }
}

//Ritorna il valore all'index
string getElem(const list l, int index){
  list aux = l;
  int count = 0;
  while(aux->next != nullptr && index > count){
    aux = aux->next;
    count++;
  }

  //cout << aux->value;
  return aux->value;
}

//inserimento in posizione fissata
void insertAt(list& l, string s, int index){
  if(index == 0){
    headInsert(l, s);
    return;
  }

  list aux = l;

  list nuova = new cell;
  nuova->value = s;

  int count = 1;
  while(aux->next != nullptr && index > count){
    aux = aux->next;
    count++;
  }

  nuova->next = aux->next;
  aux->next = nuova;
}


void deleteAt(list& l, int index){
  
}
