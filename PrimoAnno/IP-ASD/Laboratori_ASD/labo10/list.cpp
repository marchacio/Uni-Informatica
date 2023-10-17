#include "list.h"

using namespace list;

//"attacca" l2 in coda ad l1;
//Quindi l'unica lista che verrà modificata sarà l1, mentre l2 rimarrà inveriata
//
//Consiglio: se possibile, inserisci come l1 la lista piu corta, in quanto sarà quella 
//che verrà letta totalmente per arrivare all'ultimo elemento e attaccarci l2
void list::compose(List& l1, const List& l2){
  //caso in cui la compose non serve a niente
  if(isEmpty(l2))
    return;
  
  //Altro caso che produrrebbe errore
  if(isEmpty(l1) && !isEmpty(l2)){
    l1 = l2;
    return;
  }

  List scroller = l1;
  while(scroller->next != emptyList)
    scroller = scroller->next;
  
  //a questo punto, scroller punta all'ultimo elemento della lista l1
  //e ci attacchiamo l2
  scroller->next = l2;
}

/****************************************************************/
void list::clear(List& l){
  //caso di lista vuota, non fare nulla
  if(isEmpty(l))
    return;
  //caso in cui c'è solo un elemento nella lista
  if(isEmpty(l->next)){
    delete l;
    return;
  }

  //tutti gli altri casi: 
  List prev = l;
  List aux = l->next;

  while(aux != nullptr){
    delete prev;
    prev = aux;
    aux = aux->next;
  }
  delete prev;
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
void list::addBack(Elem e, List& l) // aggiunge in coda e CONTROLLA CHE NON CI SIANO DUPLICATI
{
  List nuova = new listNode;
  nuova->elem = e;
  nuova->next = emptyList;

  List aux = l;
  if(!isEmpty(aux)){
    while(aux->next != emptyList){
      if(aux->elem == e)
        return; //evita i duplicati

      aux = aux->next;
    }
      
    aux->next = nuova;
  }else {
    l = nuova;
  }  
}


/****************************************************************/
void list::addFront(Elem e, List& l) // aggiunge
{
  List aux = new listNode;
  aux->elem = e;
  aux->next = l;

  l = aux;
}

/****************************************************************/
void list::removePos(int pos, List& l)
{
  
}


List list::createEmptyList()
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
  int counter = 0;
  List aux = l;
  
  while (aux != emptyList){
    counter++;
    aux = aux->next;
  }

  return counter;
}


/****************************************************************/
void printList(const List& l){
  List aux = l;
  
  while (aux != emptyList){
    cout<< aux->elem << ", ";
    aux = aux->next;
  }
}
