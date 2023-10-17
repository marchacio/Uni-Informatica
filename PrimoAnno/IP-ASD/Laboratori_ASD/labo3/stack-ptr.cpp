#include "stack-ptr.h"
#include <iostream>

using namespace stack;


struct stack::cell {
    Elem	elem;
    cell	*next;
};


/****************************************************************/
bool stack::isEmpty(const Stack& s)
{
  return s == EMPTYSTACK;
}


/****************************************************************/
void stack::push(const Elem x, Stack& s)
{
  //inserisci in testa un elemento
  Stack aux = new cell;
  aux->elem = x;

  if(isEmpty(s))
    aux->next = EMPTYSTACK;
  else
    aux->next = s;

  s = aux;
}

/****************************************************************/
Elem stack::pop(Stack& s)
{
  if(isEmpty(s))
    return EMPTYELEM;

  //rimuovi la testa dello stack
  Elem e = s->elem;

  Stack aux = s;

  s = s->next;
  delete aux;

  return e;
}


/****************************************************************/
Elem stack::top(Stack& s)
{
  if(isEmpty(s))
    return EMPTYELEM;

  Elem e = s->elem;
  return e;
}



Stack readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return readFromStream(ifs);
}



Stack readFromStdin()
{
    cout << endl << "inserire una sequenza di numeri separati da spazi seguiti da " <<  FINEINPUT
        << " per terminare" << endl;
    return readFromStream((std::cin));
}



Stack readFromStream(istream& is)
{
    Stack s = EMPTYSTACK;
    Elem e;
    while (is >> e) {
        if (e == FINEINPUT) // il segnale di fine input nel file è il numero FINEINPUT
            return s;
        push(e, s);
    }
    throw runtime_error("errore inserimento dati");
}



void print(const Stack& s)
{
    cell* c = s;
    while (c != EMPTYSTACK) {
        cout << c->elem << "; ";
        c = c->next;
    }
    cout << endl;
}
