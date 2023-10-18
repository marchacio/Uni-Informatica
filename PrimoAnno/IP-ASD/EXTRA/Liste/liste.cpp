#include <iostream>

typedef struct cell{
  int info;
  cell* next;
  cell* prev;
}* list;

int main() {

  list lista = new cell;

  lista->info = 1;
  lista->next = nullptr;
  lista->prev = nullptr;

  //Aggiungi una cella in testa alla lista
  list aux = new cell;

  aux->info = 2;
  aux->next = lista;
  aux->prev = nullptr;

  lista->prev = aux;
  lista = aux;


  //Aggiungi una cella in coda alla lista
  list aux2 = new cell;
  list last_cell = lista;

  while(last_cell->next != nullptr){
    last_cell = last_cell->next;
  }

  aux2->info = 3;
  aux2->next = nullptr;
  aux2->prev = last_cell;

  last_cell->next = aux2;


  //stampa lista
  while(lista != nullptr){
    std::cout << lista->info << " ";
    lista = lista->next;
  }

  return 0;
}
