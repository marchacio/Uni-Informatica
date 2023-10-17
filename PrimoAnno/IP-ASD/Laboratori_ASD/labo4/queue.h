#include <iostream>
#include <stdexcept>

#include "token.h"

using namespace std;

// Implementa QUEUE
namespace queue {
    // Gli elementi della QUEUE sono token
    typedef token Elem;

    const int BLOCKDIM = 1000;
    const Elem EMPTYELEM = {"", TOKEN::kind::SCONOSCIUTO};

    typedef struct {
        Elem* queue;
        int size;
        int maxsize;
    } Queue;

    bool isEmpty(const Queue&);
    void enqueue(Elem, Queue&);  /* inserisce l'elemento alla fine della lista */
    Elem dequeue(Queue&);        /* cancella l'elemento in prima posizione (se esiste) e lo restituisce */

    Queue createEmpty();
}