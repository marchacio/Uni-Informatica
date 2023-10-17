#include "ll.h"

// dichiarare una variabile tmp di tipo puntatore a elem
// allocare elem
// assegnare il valore di s all 'elemento next di temp
// assegnare il valore di c all 'elemento c di temp
// assegnare il valore di temp a s
void addhead(ll& s, char & c)
{
  elem* tmp;
  tmp = new elem;

  tmp->next = s;
  tmp->c = c;

  s = tmp;
}

bool removehead(ll &s, char& c)
{
  if(s == nullptr)
    return false;

  //assegna a c il valore dell'elemento che verrà cancellato
  c = s->c;
  //punta all'elemento successivo per poter eliminare correttamente la testa
  ll tmp = s->next;
  delete s;
  //riallaccia la lista
  s = tmp;
  return true;
}

int size(ll s)
{
  int counter = 0;

  ll tmp = s;
  while(tmp->next != nullptr){
    counter++;
    tmp = tmp->next;
  }

  return counter;
}
