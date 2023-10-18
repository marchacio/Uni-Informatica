#include "plist.h"
#include <iostream>

void PList_insert(PList &L, int val) {
  // dichiara una variabile cur di tipo puntatore a Elem e inizializzala a L
  Elem* cur = L;
  // se L non è il puntatore nullo:
  //  verifica che val sia presente:
  // fintanto che il campo next di cur non è il puntatore nullo
  // se il campo cont di cur è uguale a val
  // esci dalla funzione /* val già presente */
  // aggiorna cur assegnandogli il suo campo next
  if(L != nullptr){
    while(cur->next != nullptr){
      if(cur->cont == val)
        return;
      cur = cur->next;
    }
  }

  // dichiara una variabile aux di tipo puntatore a Elem e allocala
  Elem* aux = new Elem;
  // assegna val al campo cont di aux
  aux->cont = val;
  // assegna L al campo next di aux
  aux->next = L;
  // assegna aux a L
  L = aux;
  // alloca (nuovamente) aux
  aux = new Elem;
  // assegna (nuovamente) val al campo cont di aux
  aux->cont = val;
  // assegna il puntatore nullo al campo next di aux
  aux->next = nullptr;
  // se cur è nullo assegna L a cur
  if(cur == nullptr)
    cur = L;
  // assegna aux al campo next di cur
  cur->next = aux;
}




/*
  --Cancellazione di un elemento da lista vuota
• Cancellazione di un elemento che si trova all’inizio (e quindi anche alla fine). . .
. . . in lista di soli due elementi
. . . in lista di quattro o più elementi
• Cancellazione di un elemento che si trova in posizione generica
  --Cancellazione di un elemento che non è presente nella lista
*/
void PList_delete(PList &L, int val) {

  //Caso della lista vuota
  if(L == nullptr)
    return;

  //Inizializzazione variabili utili
  int length = 0;
  int lastValueIndex = -1;
  int firstValueIndex;

  //assegnazione
  PList tmp = L;
  while(tmp != nullptr){
    if(tmp->cont == val)
      lastValueIndex = length;

    length++;
    tmp = tmp->next;
  }

  //Il value non è stato trovato nella lista
  if(lastValueIndex == -1)
    //throw -1;
    return;
  else{
    firstValueIndex = length-lastValueIndex-1;
  }

  std::cout << "FIRST: " << firstValueIndex << "   LAST: " << lastValueIndex << "\n";


  //Cancellazione dalla testa e dalla coda
  if(firstValueIndex == 0){
    tmp = L->next;
    delete L;
    L = tmp;

    while(tmp->next->next != nullptr)
      tmp = tmp->next;

    delete tmp->next;
    tmp->next = nullptr;

    return;
  }

  //Rimozione generica
  PList curr = L->next;
  PList prev = L;
  while(curr->next != nullptr){
    if(curr->cont == val){
      prev->next = curr->next;
      delete curr;
      curr = prev->next;
    }

    curr = curr->next;
    prev = prev->next;

  }
}
