#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string> 

using namespace std; 
 
namespace list{
    /**************************** Tipi e costanti *********************************************/
    typedef string Elem;      // tipo base, compatibile con il tipo Label dell'grafo 

    const Elem emptyElem = "$#$#$";

    struct listNode{
        Elem elem;
        listNode* next;
    };
    typedef listNode* List;

    const List emptyList = nullptr;

    void clear(List& l);          /* "smantella" la lista */
    void set(int pos, Elem e, List& l); /* modifica l'elemento in posizione pos */
    void add(int pos, Elem e, List& l); /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
    void addBack(Elem e, List& l);  /* aggiunge in coda e CONTROLLA CHE NON CI SIANO DUPLICATI*/
    void addFront(Elem e, List& l); /* inserisce l'elemento all'inizio della lista */
    void removePos(int pos, List& l); /* cancella l'elemento in posizione pos dalla lista  */
    List createEmptyList();         /* crea la lista vuota e la restituisce */
    bool get(Elem e, const List& l);	/* restituisce l'elemento in posizione pos */
    bool isEmpty(const List& l);
    int size(const List& l);

    void compose(List& l1, const List& l2); //Unisce due liste
}

void printList(const list::List& l);