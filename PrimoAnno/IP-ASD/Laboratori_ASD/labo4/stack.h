#include <cstddef> // serve per il NULL
#include <iostream>
#include <stdexcept>

#include "token.h"

using namespace std;

// Implementa STACK

namespace stack {
    // Gli elementi dello STACK sono token
    typedef token Elem;

    //questo è il valore del token nullo
    const Elem EMPTYELEM = {"", TOKEN::kind::SCONOSCIUTO};


    struct cell{
        Elem elem;
        cell* next;
    };
    typedef cell* Stack;

    
    //Questo è il valore del puntatore nullo
    const Stack EMPTYSTACK = NULL;

    bool isEmpty(const Stack&);
    void push(const Elem, Stack&);	/* aggiunge elem in cima (operazione safe, si può sempre fare) */
    Elem pop(Stack&);	/* toglie dallo stack l'ultimo elemento e lo restituisce; se lo stack è vuoto 
                            viene sollevata un'eccezione) */
}
