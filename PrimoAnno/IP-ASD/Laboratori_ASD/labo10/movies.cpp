#include "movies.h"
#include <iostream>

using namespace movies;

/*
--------------------------------------------------------------------------------------------------

Definizione delle funzioni e struct che servono per gestire le liste di puntatori per le relazioni;

--------------------------------------------------------------------------------------------------
*/
struct listPuntatoriElem{
    Node punt;
    listPuntatoriElem* next;
};
typedef listPuntatoriElem* ListPuntatori;
const ListPuntatori EMPTY_LIST_P = nullptr;

//aggiunge un puntatore in testa alla lista
//non esegue il controllo se è gia presente nella lista in quanto verrà già eseguito dalla funzione addEdge 
void addFrontListP(ListPuntatori& l, Node p){
    ListPuntatori nuovo = new listPuntatoriElem;
    nuovo->punt = p;
    nuovo->next = l;

    l = nuovo;
}

//restituisce true se p è gia in l
bool contains(const ListPuntatori& l, Node p){
    ListPuntatori scorr = l; //var ausiliaria per scorrere la lista

    while(scorr != EMPTY_LIST_P){
        if(scorr->punt == p)
            return true;

        scorr = scorr->next;
    }

    return false;
}

bool isEmptyP(const ListPuntatori& l){
    return l == EMPTY_LIST_P;
}

//restituisce la grandezza della lista di puntatori
int sizeListP(const ListPuntatori& l){
    ListPuntatori scorr = l; //var ausiliaria per scorrere la lista
    int counter = 0;

    while(scorr != EMPTY_LIST_P){
        counter++;
        scorr = scorr->next;
    }

    return counter;
}


/*
--------------------------------------------------------------------------------------------------

DEFINIZIONE DI STRUCT E FUNZIONI PER MOVIES.H;

Per evitare ripetizioni inutili, sono state inserite anche diverse funzioni ausiliarie come find, isEmpty, HashF e primoNodo. 

--------------------------------------------------------------------------------------------------

Ogni nodo delle liste di collisione sarà una struct composta da diversi elementi:
un puntatore al nodo precedente ed uno al successivo;
un NodeType che specifica di che tipo è il nodo (PERSON o MOVIE)
un Label contenente il nome della persona o del film;
una lista semplice per ogni tipo di relazione possibile che contenga i puntatori ai nodi con cui si ha una relazione.

In questo modo, i nodi tra loro collegati da una relazione potranno “raggiungersi” immediatamente tramite un puntatore: 
grazie a questa implementazione, molte delle funzioni di ispezione come “stampare gli attori che hanno recitato in almeno un film con un attore/produttore/regista” 
avranno una complessità pari alla ricerca della persona in questione, evitando calcoli ulteriori.
*/
struct movies::node{
    node* prev;
    node* next;

    NodeType tipo;
    Label nome;
    bool visto;

    ListPuntatori act;
    ListPuntatori dir;
    ListPuntatori prod;
};


// crea un database vuoto
MovieDB movies::createEmpty() {
    MovieDB database = (Node*)malloc(sizeof(Node) * DIM_HASH_TABLE); //alloca la memoria necessaria al database

    for (int i = 0; i < DIM_HASH_TABLE; i++)
        database[i] = EMPTY_NODE; //inizializza tutti gli elementi del database a vuoti
    
    return database; //ritorna l'indirizzo iniziale del database
}

//funz ausiliaria per vedere se una lista di nodi è vuota
bool isEmpty(const Node& lista){
    return lista == EMPTY_NODE;
}

/*
funzione si Hash ausiliaria basata sulla tavola ascii:

La funzione di Hash ritornerà il numero 0 per il carattere ‘a’, 1 per ‘b’, 2 per ‘c’ …
…25 per ‘z’, 26 per tutti i film che iniziano con un numero (es. “300” diretto da Zack Snyder) 
e 27 per tutti i film/persone il cui nome inizia con un carattere diverso dai casi precedenti 
(es. “È stata la mano di Dio” diretto da Paolo Sorrentino).

In questo modo, l’array avrà una dimensione costante (28 celle di puntatori) che non varierà 
con l’aggiunta o la rimozione di uno o più nodi nel database.

Riferimento: https://docs.google.com/document/d/1mwiqJ3No_HdR-3Uxe7SwCjFwH7bkS13iQcSRiZWzgy0/edit?usp=sharing
*/
int hashF(char c){
    if(c >= 48 && c <= 57) //è un numero
        return 26;
    else if(c >= 65 && c <= 90) //è una lettera (maiuscola)
        return c-65;
    else if(c >= 97 && c <= 122) //è una lettera (minuscola)
        return c-97;
    else
        return 27; //è un carattere non numero e non lettera
}

//funz ausiliaria per ritornare il primo nodo della lista corrispondente al carattere l[0]
Node primoNodo(const MovieDB &mdb, const Label l){
    return mdb[hashF(l[0])];
}

//funzione ausiliaria per trovare il nodo ricercato dal label;
//ritorna EMPTY_NODE il nodo non è stato trovato
Node find(const MovieDB &mdb, const Label l) {

    if(isEmpty(primoNodo(mdb, l)))
        return EMPTY_NODE;

    //questo è il primo nodo della lista
    Node nodoIniziale = primoNodo(mdb, l);

    Node finderStart = nodoIniziale; //ricerca partendo dalla testa
    Node finderEnd = nodoIniziale->prev; //ricerca partendo dalla coda

    if(finderEnd == nodoIniziale){ //questo vuol dire che c'è solo un nodo nella lista
        if(nodoIniziale->nome == l)
            return nodoIniziale;
        else
            return EMPTY_NODE;
    }

    //inizia a scandire tutta la lista sia dalla testa sia dalla coda verso la metà
    while(finderEnd != nodoIniziale){

        if(finderStart->nome == l)
            return finderStart;
        else if(finderEnd->nome == l)
            return finderEnd;
            
        finderStart = finderStart->next;
        finderEnd = finderEnd->prev;

        //caso in cui entrambi i puntatori siano arrivati allo stesso momento sullo 
        //stesso nodo (capita se la lista ha lunghezza dispari)
        if(finderStart == finderEnd){
            if(finderStart->nome == l)
                return finderStart;
            else
                return EMPTY_NODE;
        }

        //ferma il ciclo e ritorna EMPTY_NODE se i due puntatori si 
        //sono superati (capita se la lista ha lunghezza pari);
        //questo vuol dire che il nodo cercato nn è nella lista
        if(finderStart == finderEnd->next){
            return EMPTY_NODE;
        }
    }

    return EMPTY_NODE;
}


//resetta tutti i flag "visto" su false;
//utilizza due puntatori per dimezzare il tempo nella lista di collisione:
//complessità: T(lunghezza tab hash * (lunghezza lista di collisione / 2))
void resetVisto(const MovieDB &mdb){
    for (int i = 0; i < DIM_HASH_TABLE; i++){
        Node nodoIniziale = mdb[i];

        //controlla che ci sia almeno un nodo, altrimenti passa alla prossima iterata
        if(!isEmpty(nodoIniziale)){
            Node finderStart = nodoIniziale; //partendo dalla testa
            Node finderEnd = nodoIniziale->prev; //partendo dalla coda

            if(finderEnd == nodoIniziale){ //questo vuol dire che c'è solo un nodo nella lista
                nodoIniziale->visto = false;
            } else {
                //inizia a scandire tutta la lista sia dalla testa sia dalla coda verso la metà
                while(finderEnd != nodoIniziale){

                    finderStart->visto = false;
                    finderEnd->visto = false;
                        
                    finderStart = finderStart->next;
                    finderEnd = finderEnd->prev;

                    //caso in cui entrambi i puntatori siano arrivati allo stesso momento sullo 
                    //stesso nodo (capita se la lista ha lunghezza dispari)
                    if(finderStart == finderEnd)
                        finderStart->visto = false;

                    //ferma il ciclo se i due puntatori si sono superati (capita se la lista è di lunghezza pari)
                    if(finderStart == finderEnd->next)
                        break;
                }
            }
        }
    }
}

// aggiunge un nodo di tipo PERSON o MOVIE con nome l, fallisce se un nodo con quell'etichetta è già presente
// restituisce true se l'inserimento ha avuto successo
bool movies::addVertex(MovieDB &mdb, const Label l, const NodeType t){

    Node nuovoNodo = new node;
    nuovoNodo->nome = l;
    nuovoNodo->tipo = t;
    nuovoNodo->visto = false;
    //inizializza le relazioni come tutte vuote:
    nuovoNodo->act = EMPTY_LIST_P;
    nuovoNodo->dir = EMPTY_LIST_P;
    nuovoNodo->prod = EMPTY_LIST_P;


    if(isEmpty(primoNodo(mdb, l))){
        //in caso la lista di nodi sia vuota, inserisci un nodo particolare:
        //punta a se stesso sia next che prev

        nuovoNodo->prev = nuovoNodo;
        nuovoNodo->next = nuovoNodo;
        
        mdb[hashF(l[0])] = nuovoNodo;

        return true;
    }

    //Prova a cercare un nodo con label l;
    //se esiste, ritorna falso.
    Node possibileNodoEsistente = find(mdb, l);
    if(possibileNodoEsistente == EMPTY_NODE){
        //a questo punto puoi aggiungere in lista il nodo nuovo

        Node primoNodoLista = primoNodo(mdb, l); //questo è il primo nodo della lista di collisione corrispondente a l

        //aggiusta i puntatori
        nuovoNodo->prev = primoNodoLista->prev;
        primoNodoLista->prev->next = nuovoNodo;
        primoNodoLista->prev = nuovoNodo;
        nuovoNodo->next = primoNodoLista;

        mdb[hashF(l[0])] = nuovoNodo;
        return true;
    }

    return false;
}

// aggiunge un arco tra `person` e `movie` con tipo t (ACTED, DIRECTED o PRODUCED)
// fallisce se i nodi non hanno tipo appropriato o se un arco identico (stessa persona, film e tipo) esiste già
bool movies::addEdge(MovieDB &mdb, const Label person, const Label movie, const EdgeType t){
    Node persona = find(mdb, person);
    Node film = find(mdb, movie);

    //prima di tutto, controlla che i due nodi esistano e che abbiano tipo opposto
    if(film == EMPTY_NODE || persona == EMPTY_NODE || film->tipo == persona->tipo){
        return false;
    }


    
    
    
    //se è una relazione di tipo ACTED:
    if(t == EdgeType::ACTED){
        //controlla che la relazione non esista gia;
        //il controllo viene effettuato solo sulla 
        //persona perche le relazioni sono bilaterali
        if(contains(persona->act, film))
            return false;

        //aggiungi la nuova relazione alla lista di relazioni act della persona
        addFrontListP(persona->act, film);
        //fai lo stesso al contrario in quanto le relazioni sono bilaterali
        addFrontListP(film->act, persona);

        return true;
    }
    //se è una relazione di tipo DIRECTED:
    else if(t == EdgeType::DIRECTED){
        //controlla che la relazione non esista gia
        if(contains(persona->dir, film))
            return false;

        //aggiungi la nuova relazione alla lista di relazioni dir della persona
        addFrontListP(persona->dir, film);
        //fai lo stesso al contrario in quanto le relazioni sono bilaterali
        addFrontListP(film->dir, persona);

        return true;
    }
    //se è una relazione di tipo PRODUCED:
    else if(t == EdgeType::PRODUCED){
        //controlla che la relazione non esista gia
        if(contains(persona->prod, film))
            return false;

        //aggiungi la nuova relazione alla lista di relazioni prod della persona
        addFrontListP(persona->prod, film);
        //fai lo stesso al contrario in quanto le relazioni sono bilaterali
        addFrontListP(film->prod, persona);

        return true;
    } else 
        return false;
}

// numero di nodi con tipo t
int movies::numNodesPerType(const MovieDB &mdb, NodeType t){
    int counter = 0;

    //scannerizza tutto il database utilizzando due puntatori che partono dalla testa 
    //e dalla coda verso il centro della lista
    for (int i = 0; i < DIM_HASH_TABLE; i++){
        Node nodoIniziale = mdb[i];

        //controlla che ci sia almeno un nodo, altrimenti passa alla prossima iterata
        if(!isEmpty(nodoIniziale)){
            Node finderStart = nodoIniziale; //ricerca partendo dalla testa
            Node finderEnd = nodoIniziale->prev; //ricerca partendo dalla coda

            if(finderEnd == nodoIniziale){ //questo vuol dire che c'è solo un nodo nella lista
                if(nodoIniziale->tipo == t)
                    counter++;
            } else {
                //inizia a scandire tutta la lista sia dalla testa sia dalla coda verso la metà
                while(finderEnd != nodoIniziale){

                    if(finderStart->tipo == t)
                        counter++;
                    if(finderEnd->tipo == t)
                        counter++;
                        
                    finderStart = finderStart->next;
                    finderEnd = finderEnd->prev;

                    //caso in cui entrambi i puntatori siano arrivati allo stesso momento sullo 
                    //stesso nodo (capita se la lista ha lunghezza dispari)
                    if(finderStart == finderEnd){
                        if(finderStart->tipo == t){
                            counter++;
                            break;
                        }
                        else
                            break;
                    }

                    //ferma il ciclo se i due puntatori si sono superati (capita se la lista è di lunghezza pari)
                    if(finderStart == finderEnd->next)
                        break;
                }
            }
        }
    }
    
    return counter;
}


//Funzione ausiliaria per contare i nodi di un certo tipo
int contatoreRelazioniAux(const Node& node, EdgeType t){
    int counter = 0;

    if(t == EdgeType::ACTED)
        counter += sizeListP(node->act);
    else if(t == EdgeType::DIRECTED)
        counter += sizeListP(node->dir);
    else if(t == EdgeType::PRODUCED)
        counter += sizeListP(node->prod);
    
    return counter;
}

// numero di archi con tipo t
int movies::numEdgesPerType(const MovieDB &mdb, EdgeType t){
    int counter = 0;

    //dato che le relazioni sono bidirezionali, per non contare due volte ogni relazione,
    //possiamo prendere solo le relazioni partendo dai film:
    NodeType tipoNodoPredefinito = NodeType::MOVIE;

    //scannerizza tutto il database utilizzando due puntatori che partono dalla testa 
    //e dalla coda verso il centro della lista
    for (int i = 0; i < DIM_HASH_TABLE; i++){
        Node nodoIniziale = mdb[i];

        //controlla che ci sia almeno un nodo, altrimenti passa alla prossima iterata
        if(!isEmpty(nodoIniziale)){
            Node finderStart = nodoIniziale; //ricerca partendo dalla testa
            Node finderEnd = nodoIniziale->prev; //ricerca partendo dalla coda

            if(finderEnd == nodoIniziale){ //questo vuol dire che c'è solo un nodo nella lista
                if(nodoIniziale->tipo == tipoNodoPredefinito)
                    counter += contatoreRelazioniAux(nodoIniziale, t); //aggiungi il numero di relazioni di tipo t
            } else {
                //inizia a scandire tutta la lista sia dalla testa sia dalla coda verso la metà
                while(finderEnd != nodoIniziale){

                    if(finderStart->tipo == tipoNodoPredefinito)
                        counter += contatoreRelazioniAux(finderStart, t); //aggiungi il numero di relazioni di tipo t
                    if(finderEnd->tipo == tipoNodoPredefinito)
                        counter += contatoreRelazioniAux(finderEnd, t); //aggiungi il numero di relazioni di tipo t
                        
                    finderStart = finderStart->next;
                    finderEnd = finderEnd->prev;

                    //caso in cui entrambi i puntatori siano arrivati allo stesso momento sullo 
                    //stesso nodo (capita se la lista ha lunghezza dispari)
                    if(finderStart == finderEnd){
                        if(finderStart->tipo == tipoNodoPredefinito){
                            counter += contatoreRelazioniAux(finderStart, t); //aggiungi il numero di relazioni di tipo t
                            break;
                        }
                        else
                            break;
                    }

                    //ferma il ciclo se i due puntatori si sono superati (capita se la lista è di lunghezza pari)
                    if(finderStart == finderEnd->next)
                        break;
                }
            }
        }
    }

    return counter;
}


//Funzione ausiliaria per ritornare la lista di attori che hanno lavorato ("Colleghi") con l
//dove l era di tipo t (cioè o attore o prod o reg).
//
//ricercaNumeroBacon è un valore booleano per evidenziare se questa funzione è usata
//durante la ricerca del numero di bacon; in tal caso, non si deve fare il resetVisto perchè
//crea problemi nella ricerca del numero di bacon.
list::List attoriColleghiDi(const MovieDB &mdb, Label l, EdgeType t, bool ricercaNumeroBacon){
    list::List lista = list::createEmptyList();

    //trova il nodo vero e proprio che corrisponde alla persona cercato
    Node persona = find(mdb, l);

    if(!isEmpty(persona) && (persona->tipo == NodeType::PERSON)){ //controlla eventuali errori
        //(se non stiamo facendo la ricerca di bacon) aggiorna il bit di controllo per evitare
        //di scrivere piu volte la persona all'interno della lista
        if(!ricercaNumeroBacon)
            persona->visto = true;

        //scorri tutti i film in cui ha recitato/diretto/prodotto la persona 
        //e inserisci nella lista tutti gli attori di quei film (senza la persona in questione e senza ripetizioni)
        ListPuntatori films;

        //inizializza la lista di film da cui prendere gli attori
        if(t == EdgeType::ACTED)
            films = persona->act;
        else if(t == EdgeType::DIRECTED)
            films = persona->dir;
        else if(t == EdgeType::PRODUCED)
            films = persona->prod;

        while(films != EMPTY_LIST_P){
            //scorri tutti gli attori di quel film
            ListPuntatori attori = films->punt->act;
            while(attori != EMPTY_LIST_P){
                //non aggiungere due volte la stessa persona
                if(!attori->punt->visto){
                    //inserisci nella lista
                    list::addFront(attori->punt->nome, lista);
                    
                    //(se non stiamo facendo la ricerca di bacon) modifica il suo flag "visto" 
                    if(!ricercaNumeroBacon)
                        attori->punt->visto = true;
                }
                
                attori = attori->next;
            }

            films = films->next;
        }

        //se non stiamo facendo la ricerca del numero di bacon,
        //fai tornare tutti i flag "visto" su false
        if(!ricercaNumeroBacon)
            resetVisto(mdb);

        return lista;
    } 

    return list::emptyList;
}

// lista, senza ripetizioni, di attori che hanno interpretato un film con l'attore con etichetta l
// restituisce una lista vuota se l non è una persona o non appartiene al grafo
list::List movies::coActors(const MovieDB &mdb, Label l){
    return attoriColleghiDi(mdb, l, EdgeType::ACTED, false);
}

// lista, senza ripetizioni, di attori che hanno interpretato un film prodotto da l
// restituisce una lista vuota se l non è una persona o non appartiene al grafo
list::List movies::actorsProducedBy(const MovieDB &mdb, Label l){
    return attoriColleghiDi(mdb, l, EdgeType::PRODUCED, false);
}

// lista, senza ripetizioni, di attori che hanno interpretato un film diretto da l
// restituisce una lista vuota se l non è una persona o non appartiene al grafo
list::List movies::actorsDirectedBy(const MovieDB &mdb, Label l){
    return attoriColleghiDi(mdb, l, EdgeType::DIRECTED, false);
}

//funzione ausiliaria ricorsiva per trovare il numero di bacon di l
//
//listaAttori è una lista di label contenente i nomi degli attori che hanno collaborato 
//con l'attore del livello di ricorsione precedente;
//
//Sia che restituisca un errore, sia che restituisca un int valido, alla fine della ricorsione
//resetta tutti i "visto" su false.
int baconAux(const MovieDB &mdb, const list::List& listaAttori, const Label l) {

    list::List scroller = listaAttori;

    //crea e inizializza la lista di attori che verrà passata al prossimo livello di ricorsione
    //(se non vuota)
    list::List listaAttoriR = list::createEmptyList();

    //per ogni attore nella lista di attori
    while(scroller != list::emptyList){

        //Controlla se l è presente nella lista di attori 
        //(questo è il caso base dove è stato trovato l'attore ricercato)
        if(scroller->elem == l){
            resetVisto(mdb);
            return 1;
        } else {
            //Cerca il nodo di "attore" in poco tempo grazie alle ottimizzazioni di find;
            //una volta trovato, controlla che non sia gia stato visto
            Node attore = find(mdb, scroller->elem);

            if(!attore->visto){//se l'attore non è ancora mai stato visto:
                //inserisci in listaAttoriR tutti i "colleghi" dell'attore appena analizzato 
                //tramite la funzione "compose" che unisce due liste di label;
                //Per altre info e tips su compose, si guardi il suo commento in "list.cpp".
                list::List colleghi = attoriColleghiDi(mdb, attore->nome, EdgeType::ACTED, true);
                list::compose(listaAttoriR, colleghi);

                //fai in modo che l'attore appena scansionato non venga scansionato nuovamente
                attore->visto = true;
            }
        }
        scroller = scroller->next; //passa al prossimo attore
    }

    //caso in cui è stato esplorato tutto il database e non è stato trovato un risultato
    //(questo può avvenire ad esempio se si cerca il numero di bacon di un non-attore):
    if(list::isEmpty(listaAttoriR)){
        resetVisto(mdb);
        return NO_BACON_NUMBER;
    }

    //trova il numero di bacon ricorsivamente
    int baconR = baconAux(mdb, listaAttoriR, l);

    //controlla che gli errori siano passati correttamente 
    if(baconR == NO_BACON_NUMBER)
        return NO_BACON_NUMBER;
    else
        return 1 + baconR;
}

// numero di Bacon di l; restituisce NO_BACON_NUMBER se l non è una persona o non ha un numero di Bacon calcolabile
int movies::BaconNumber(const MovieDB &mdb, Label l){
    
    if(l == "Kevin Bacon") //l'attore è Bacon
        return 0;

    Node attore = find(mdb, l);
    if(!isEmpty(attore) && (attore->tipo == NodeType::PERSON)){ //fai controlli sulla persona cercata e poi trova il numero di bacon
        list::List colleghiBacon = coActors(mdb, "Kevin Bacon");

        //inizia la ricorsione con tutti gli attori colleghi di bacon
        return baconAux(mdb, colleghiBacon, l);
    }

    return NO_BACON_NUMBER;
}


/*Stampa il database in ordine alfabetico nel seguente modo:
A:
- Film:
-- Nome Film 1, Nome Film 2 ...

- Persone:
-- Nome Persona 1, Nome Persona 2...
*/
void printDB(const movies::MovieDB &mdb){
    //per ogni cella della hash table, stampa il contenuto
    for (int i = 0; i < DIM_HASH_TABLE; i++){

        //gruppo è il nome del gruppo, cioè A, B, C...
        string gruppo;
        if(i == 26)
            gruppo = "Numeri";
        else if(i == 27)
            gruppo = "Altro";
        else {
            char c = i + 65;
            gruppo = c;
        }
            
        cout << gruppo << ": ";

        //stampa il contenuto
        if(isEmpty(mdb[i])){
            cout << "vuoto\n";
        } else {
            if(mdb[i]->next == mdb[i]){ 
                //vuol dire che c'è solo un elemento
                cout << mdb[i]->nome;
            } else { 
                //stampa tutti i nodi della lista di collisione
                Node printer = mdb[i]->next;
                
                cout << mdb[i]->nome; //stampa il primo della lista che sennò non verrebbe stampato
                while(printer != mdb[i]){
                    cout << ", " << printer->nome;
                    printer = printer->next;
                }
            }
            cout << "\n";
        }
    }
}
