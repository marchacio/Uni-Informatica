#include "myvector.h"

#include <iostream>
#include <string>

//stampa il myvector
void print(myvector& v){
  std::cout << "Capacity: " << v.capacity << std::endl;
  std::cout << "Size: " << v.size << std::endl;
  std::cout << "Store: ";
  for(int i = 0; i < v.size; ++i)
    std::cout << v.store[i] << " ";
}

//Scrivere la funzione void create(myvector& v, int capacity); che dato per riferimento un myvector v non ancora inizializzato,
//fa l’allocazione di v.store con lunghezza capacity, assegna v.capacity = capacity, e assegna v.size = 0.
void create(myvector& v, int capacity) {
  v.store = new int[capacity];
  v.capacity = capacity;
  v.size = 0;
}

//Scrivere la funzione push_back che riceve due argomenti, un riferimento a un myvector v inizializzato e un intero x.
//Se v.size è minore di v.capacity, la funzione inserisce x in v.store all’indice v.size e incrementa di uno v.size.
//Se v è già completamente pieno (cioè v.size == v.capacity), la funzione solleva un’eccezione di tipo opportuno.
//Valore restituito: nessuno.
void push_back(myvector& v, int x){
  if(v.size < v.capacity){
    v.store[v.size] = x;
    v.size++;
  }

  if(v.size >= v.capacity){
    const std::string err = "La size non può essere >= alla capacity";
    throw err;
  }
}

//Scrivere la funzione pop_back che riceve un argoment, un riferimento a un myvector v inizializzato.
//Se v è vuoto (cioè 0 == v.size), la funzione solleva un’eccezione di tipo opportuno.
//Se v.size è positivo, la funzione restituisce il valore memorizzato in v.store all’indice v.size-1 e decrementa di uno v.size.
int pop_back(myvector& v){
  if(v.size <= 0){
    const std::string err = "Il vector è vuoto!";
    throw err;
  }

  int to_delete = v.store[v.size-1];
  v.size--;

  return to_delete;
}

//Scrivere la funzione void set(myvector& v, int value, int index); che assegna value all’elemento con indice index di
//v.store. Solleva una eccezione (di tipo opportuno) se index non è un valore corretto, ovvero se non è compreso fra 0 e
//v.size.
void set(myvector& v, int value, int index){
  if(index < 0 || index >= v.size){
    const std::string err = "Index out of bound";
    throw err;
  }

  v.store[index] = value;
}

//La funzione ordina il suo argomento secondo l’algoritmo SelectionSort.
void selectionSort(myvector& v){
  for(int i = 0; i < v.size; ++i){
    int index_numero_minore = i;
    for(int j = i+1; j < v.size; ++j)
      if(v.store[j] < v.store[i])
        index_numero_minore = j;

    int tmp = v.store[i];
    v.store[i] = v.store[index_numero_minore];
    v.store[index_numero_minore] = tmp;
  }
}
