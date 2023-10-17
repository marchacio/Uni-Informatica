////////////////////////////////////////////////////
//
//  Questa serve per realizzare le liste che vengono fuori come risultato di
//  operazioni quali il percorso tra due citta' (che viene rappresentato come
//  lista di nomi di citta') e l'elenco delle citta' adiacenti a una certa
//  citta' (anch'esso rappresentato come lista di nomi di citta').
//  Non serve invece per le liste dei vertici nel grafo, ne' per le liste di
//  adiacenza di ciascun vertice.
//
////////////////////////////////////////////////////

#include "list.h"

using namespace list;

//struct
struct list::list 
{
  Elem elem;
  list *next;  
};


/****************************************************************/
void list::clear(List& l){
   
}


/****************************************************************/
void list::set(int pos, Elem e, List& l) // "set" nel senso di "assegna un valore", non nel senso di "insieme"! E' una terminologia standard, non fate confusione con gli insiemi
{
   
}


/****************************************************************/
void list::add(int pos, Elem e, List& l) // aggiunge e nella posizione pos
{
  
}

/****************************************************************/
void list::addBack(Elem e, List& l) // aggiunge e in coda
{
  List nuova = new list;
  nuova->elem = e;
  nuova->next = emptyList;

  List aux = l;
  if(!isEmpty(aux)){
    while(aux->next != emptyList)
      aux = aux->next;

    aux->next = nuova;
  }else {
    l = nuova;
  }  
}


/****************************************************************/
void list::addFront(Elem e, List& l) // aggiunge
{
  List aux = new list;
  aux->elem = e;
  aux->next = l;

  l = aux;
}

/****************************************************************/
void list::removePos(int pos, List& l)
{
  
}


List list::createEmpty()
{
  return emptyList; 
}

/****************************************************************/
//ausiliaria
//Restituisce true se nella lista esiste una cella con elemento e, restituisce false altrimenti
bool list::get(Elem e, const List& l)
{
  if (isEmpty(l)) return false;
  List aux = l;
  while (!isEmpty(aux)){
    if(aux->elem == e) return true;
    aux = aux->next;
  }
  return false;
}


/****************************************************************/
bool list::isEmpty(const List& l)
{
   return (l == emptyList);
}

/****************************************************************/
int list::size(const List& l)
{
   return 0;
}


/****************************************************************/
void printList(const List& l)
{
  List aux = l;
  
  while (aux != emptyList){
    cout<< aux->elem << " ";
    aux = aux->next;
  }

  aux = emptyList;
  delete aux;
}
