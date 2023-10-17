#include "graph.h"

using namespace graph;


/*******************************************************************************************************/
// Grafo
/*******************************************************************************************************/

struct halfEdgeVertex {
  vertexNode* vertice; // puntatore al vertice cosiderato
  Weight weight; // peso dell'arco
  halfEdgeVertex* nextEdge; // puntatore al mezzo arco successivo
};

struct graph::vertexNode {
  Label label; //etichetta
  vertexNode* next; // puntatore al prossimo vertice nella lista di vertici
  halfEdgeVertex* adiacenti; // puntatore alla lista dei “mezzi archi” adiacenti
  bool visto; // booleano che dice se il vertice è stato marcato oppure no 
};

halfEdgeVertex* emptyEdge = nullptr; 

//GRAFICAMENTE:
/*
******************************************************************************************************
NODO1 -> {nodoAdiacente1} -> {nodoAdiacente2}
  |
NODO2 -> {nodoAdiacente1} -> {nodoAdiacente2} -> {nodoAdiacente3}
  |
NODO3 -> null
  |
NODO4 -> {nodoAdiacente1}
  |
 null
*******************************************************************************************************
*/

//FUNZIONE AUSILIARIA PER TROVARE DUE NODI IN UN SOLO CICLO:
//n1 e n2 = nodi da cercare passati per riferimento
//l1 e l2 = label per identificare n1 e n2
//g = grafo passato per riferimento
void cercaDueNodi(const Graph& g, Graph& n1, Graph& n2, Label l1, Label l2){

  Graph aux = g;

  //scorri fino alla fine dei vertici
  while(!isEmpty(aux)){
    if(aux->label == l1)
      n1 = aux;
      
    if(aux->label == l2)
      n2 = aux;
      

    //ottimizzazione: se entrambi sono gia stati inizializzati, esci dalla funzione
    if(!isEmpty(n1) && !isEmpty(n2))
      return;

    aux = aux->next;
  }

  aux = emptyGraph;
  delete aux;
}

//FUNZIONE AUSILIARIA per trovare un singolo nodo
Graph cercaNodo(const Label l, const Graph& g) {
  Graph aux = g;
  while(!isEmpty(aux)){
    if(aux->label == l)
      return aux;
    
    aux = aux->next;
  }
	
	return emptyGraph;
}

//FUNZ AUSILIARIA: Restituisce true se l'arco e' vuoto, false altrimenti
bool isEmptyEdge(halfEdgeVertex* h){
  return h == emptyEdge;
}

// Restituisce il grafo vuoto
Graph graph::createEmptyGraph()
{
  return emptyGraph;
}

// Aggiunge nuovo vertice con etichetta la stringa. Fallisce se gia' presente
bool graph::addVertex(Label l, Graph& g) {

  Graph nuovoVertice = new vertexNode;

  //inizializza tutti i campi
  nuovoVertice->adiacenti = emptyEdge;
  nuovoVertice->label = l;
  nuovoVertice->visto = false;
  nuovoVertice->next = emptyGraph;

  //controlla che il grafo non sia vuoto
  if(!isEmpty(g)){

    //controlla che non esista gia il vertice da aggiungere
    Graph aux = g;
    while(!isEmpty(aux->next)){
      if(aux->label == l || aux->next->label == l)
        return false;
      
      aux = aux->next;
    }

    //a questo punto fai un inserimento in coda grazie ad aux
    aux->next = nuovoVertice;
    
  } else {
    //caso in cui bisogna aggiungere un vertice in un grafo vuoto
    g = nuovoVertice;
  }

  return true;
}

// Aggiunge un arco di peso "w" tra i nodi con etichetta "f" e "t". 
// Fallisce se esiste gia' l'arco,
// se i nodi non esistono nel grafo e se si tenta di inserire un arco tra un nodo ed esso stesso
bool graph::addEdge(Label from, Label to, Weight w, Graph& g) {
  //ERRORE: si tenta di inserire un arco tra un nodo ed esso stesso
  if(from == to)
    return false;  

  //scorri finche non becchi il vertice a cui aggiungere un arco
  Graph _from = emptyGraph;
  Graph _to = emptyGraph;
  cercaDueNodi(g, _from, _to, from, to);

  //ERRORE: i nodi non esistono nel grafo
  if(isEmpty(_from) || isEmpty(_to))
    return false;

  //ERROE: esiste gia' l'arco
  //controlla se c'è gia _to tra gli archi di _from
  //non controllare il viceversa perche è un grafo non orientato, quindi un arco se esiste in un vertice esisterà per forza anche nell'altro
  //(questo controllo è garantito da questa funzione di inserimento degli archi)
  halfEdgeVertex* auxTO = _from->adiacenti;
  if(!isEmptyEdge(auxTO))
    while(!isEmptyEdge(auxTO->nextEdge)){
      if(auxTO->vertice->label == to)
        return false;

      auxTO = auxTO->nextEdge;
    }
    

  //aggiunta vera e propria dell'arco sia in from sia in to:
  halfEdgeVertex* nuovoArcoVersoTO = new halfEdgeVertex;
  nuovoArcoVersoTO->vertice = _to;
  nuovoArcoVersoTO->weight = w;
  nuovoArcoVersoTO->nextEdge = _from->adiacenti;
  _from->adiacenti = nuovoArcoVersoTO;
  
  halfEdgeVertex* nuovoArcoVersoFROM = new halfEdgeVertex;
  nuovoArcoVersoFROM->vertice = _from;
  nuovoArcoVersoFROM->weight = w;
  nuovoArcoVersoFROM->nextEdge = _to->adiacenti;
  _to->adiacenti = nuovoArcoVersoFROM;
  
  return true;
}

// Restituisce true se il grafo e' vuoto, false altrimenti
bool graph::isEmpty(const Graph& g)
{ 
 return g == emptyGraph;
}

// Ritorna il numero di vertici del grafo
int graph::numVertices(const Graph& g){
  int counter = 0;

  Graph aux = g;
  while(!isEmpty(aux)){
    counter++;
    aux = aux->next;
  }

  return counter;
}

// Ritorna il numero di archi del grafo
int graph::numEdges(const Graph& g){
  int counter = 0;

  Graph aux = g;
  while(!isEmpty(aux)){
    halfEdgeVertex* aux2 = aux->adiacenti;
    while(!isEmptyEdge(aux2)){
      counter++;
      aux2 = aux2->nextEdge;
    }
    aux = aux->next;
  }

  //dividi per due perche è un grafo non orientato 
  return counter/2;
}

// Calcola e ritorna (nel secondo parametro) il grado del nodo. Fallisce
// se il nodo non esiste
bool graph::nodeDegree(Label l, int& degree, const Graph& g) {
  Graph aux = cercaNodo(l, g);
  
  if(!isEmpty(aux)){
    //conta tutti i nodi adiacenti (il grado del nodo)
    int counter = 0;
    halfEdgeVertex* aux2 = aux->adiacenti;
    if(!isEmptyEdge(aux2))
      while(!isEmptyEdge(aux2)){
        counter++;
        aux2 = aux2->nextEdge;
      }

    //e ritorna
    degree = counter;
    return true;
  }
  
  //in caso non sia stato trovato il label:
  return false;
}

// Verifica se i due vertici v1 e v2 sono adiacenti (ovvero se esiste un arco)
bool graph::areAdjacent(Label v1, Label v2, const Graph& g) {
  Graph n1 = emptyGraph;
  Graph n2 = emptyGraph;
  cercaDueNodi(g, n1, n2, v1, v2);

  if(v1 == v2 || isEmpty(n1) || isEmpty(n2))
    return false; //errore
  
  //controlla solo n1 perche il grafo non è orientato e quindi non possono esistere archi unidirezionali
  halfEdgeVertex* aux = n1->adiacenti;
  while(!isEmptyEdge(aux)){
    if(aux->vertice->label == v2)
      return true;

    aux = aux->nextEdge;
  }

  return false;
}

// Restituisce la lista di adiacenza di un vertice
list::List graph::adjacentList(Label v1, const Graph& g) {
  list::List lst = list::createEmpty();

  //trova il nodo v1
  Graph aux = cercaNodo(v1, g);
  
  if(!isEmpty(aux)){
    //a sto punto aggiungi tutti i vertici adiacenti alla lista
    halfEdgeVertex* aux2 = aux->adiacenti;
    while(!isEmptyEdge(aux2)){
      list::addFront(aux2->vertice->label, lst);
      aux2 = aux2->nextEdge;
    }

    aux2 = emptyEdge;
    delete aux2;
  }
  
  aux = emptyGraph;
  delete aux;

  return lst;
}



// Ritorna un cammino tra una citta' ed un altra
// Il cammino da "v1" a "v2" alla fine sara' in "path"
// e la lunghezza sara' in "len".
// Si assume che il chiamante fornisca inizialmente un cammino vuoto.
//
// La funzione rappresenta una variante della visita DFS
bool pathAux(Label destinazione, list::List &path, int &len, const Graph& g){
  //non considerare i vertici gia visti
  if(g->visto) 
    return false;

  //setta il vertice su visto
	g->visto = true;

  //caso in cui è stata trovata la destinazione
	if(g->label == destinazione)
    return true;

  //scorri tutti i vertici adiacenti a g
	halfEdgeVertex* adiacenti = g->adiacenti;
  while(!isEmptyEdge(adiacenti)){
    
    if(pathAux(destinazione, path, len, adiacenti->vertice)) {
      //caso in cui il prossimo vertice abbia visto == false;
      len += adiacenti->weight;
      list::addFront(adiacenti->vertice->label, path);
      return true;
    }

    adiacenti = adiacenti->nextEdge;
  }

  //caso default:
	return false;

}

void graph::findPath(Label v1, Label v2, list::List &path, int &len, const Graph& g) {

  //Inizializzazione delle veriabili
  path = list::createEmpty();
	len = 0;

	//Evita errori vari:
	if(v1 == v2)
    return;
  Graph n1 = emptyGraph;
  Graph n2 = emptyGraph;
  cercaDueNodi(g, n1, n2, v1, v2);
  if(v1 == v2 || isEmpty(n1) || isEmpty(n2))
    return;
  

	//azzera tutti i "visto" dei nodi
	Graph aux = g;
  while(!isEmpty(aux)){
    aux->visto = false;

    aux = aux->next;
  }
  
  Graph from = cercaNodo(v1, g);
  if(isEmpty(from)) //caso in cui non è stato trovato v1 per qualche motivo
    return;
  
	pathAux(v2, path, len, from);
}


// opzionale: svuota il grafo;
// l'implementazione data soffre di memory leak perché il grafo corrente non viene deallocato
void graph::clear(graph::Graph& g)
{
  g = createEmptyGraph();
}


/*******************************************************************************************************/
// Stampa il grafo
void printGraph(const graph::Graph& g) {
  //per ogni nodo, stampa i suoi adiacenti
  Graph aux = g;

  while(aux != emptyGraph){
    cout << aux->label << ": ";

    halfEdgeVertex* aux2 = aux->adiacenti;
    while(!isEmptyEdge(aux2)){
      cout << aux2->vertice->label << "(" << aux2->weight << ") --> ";

      aux2 = aux2->nextEdge;
    }
    delete aux2;

    cout << "NULL\n";

    aux = aux->next;
  }
  delete aux;

}

