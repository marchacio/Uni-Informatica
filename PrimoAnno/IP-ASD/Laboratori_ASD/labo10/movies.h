#include <string>
#include "list.h"

namespace movies {

    typedef std::string Label;

    enum NodeType {PERSON, MOVIE};
    enum EdgeType {ACTED, DIRECTED, PRODUCED};

/*
La funzione di Hash ritornerà il numero 0 per il carattere ‘a’, 1 per ‘b’, 2 per ‘c’ …
…25 per ‘z’, 26 per tutti i film che iniziano con un numero (es. “300” diretto da Zack Snyder) 
e 27 per tutti i film/persone il cui nome inizia con un carattere diverso dai casi precedenti 
(es. “È stata la mano di Dio” diretto da Paolo Sorrentino).

In questo modo, l’array avrà una dimensione costante (28 celle di puntatori) che non varierà 
con l’aggiunta o la rimozione di uno o più nodi nel database.

Riferimento: https://docs.google.com/document/d/1mwiqJ3No_HdR-3Uxe7SwCjFwH7bkS13iQcSRiZWzgy0/edit?usp=sharing
*/
    const int DIM_HASH_TABLE = 28;

    //questa è la struct che definisce le componenti di un nodo
    struct node;

    typedef node* Node;

    //MovieDB è un array di puntatori ai nodi iniziali
    typedef Node* MovieDB;

    const Node EMPTY_NODE = nullptr;

    const int NO_BACON_NUMBER = -1;

    // crea un database vuoto
    MovieDB createEmpty();

    // aggiunge un nodo di tipo PERSON o MOVIE con nome l, fallisce se un nodo con quell'etichetta è già presente
    // restituisce true se l'inserimento ha avuto successo
    bool addVertex(MovieDB &mdb, const Label l, const NodeType t);

    // aggiunge un arco tra `person` e `movie` con tipo t (ACTED, DIRECTED o PRODUCED)
    // fallisce se i nodi non hanno tipo appropriato o se un arco identico (stessa persona, film e tipo) esiste già
    bool addEdge(MovieDB &mdb, const Label person, const Label movie, const EdgeType t);

    // numero di nodi con tipo t
    int numNodesPerType(const MovieDB &mdb, NodeType t);

    // numero di archi con tipo t
    int numEdgesPerType(const MovieDB &mdb, EdgeType t);

    // lista, senza ripetizioni, di attori che hanno interpretato un film con l'attore con etichetta l
    // restituisce una lista vuota se l non è una persona o non appartiene al grafo
    list::List coActors(const MovieDB &mdb, Label l);

    // lista, senza ripetizioni, di attori che hanno interpretato un film prodotto da l
    // restituisce una lista vuota se l non è una persona o non appartiene al grafo
    list::List actorsProducedBy(const MovieDB &mdb, Label l);

    // lista, senza ripetizioni, di attori che hanno interpretato un film diretto da l
    // restituisce una lista vuota se l non è una persona o non appartiene al grafo
    list::List actorsDirectedBy(const MovieDB &mdb, Label l);

    // numero di Bacon di l (vedi testo); restituisce NO_BACON_NUMBER se l non è una persona o non ha un numero di Bacon
    int BaconNumber(const MovieDB &mdb, Label l);
}

// stampa il contenuto del database; siete liberi di scegliere il formato, ma pensatelo in modo che sia comprensibile per un umano
void printDB(const movies::MovieDB &mdb);