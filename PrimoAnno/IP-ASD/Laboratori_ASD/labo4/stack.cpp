#include "stack.h"

using namespace stack;

//struct stack::;


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

