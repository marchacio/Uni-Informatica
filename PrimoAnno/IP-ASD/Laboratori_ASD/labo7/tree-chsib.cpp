#include "tree-chsib.h"

using namespace tree;

/* Nota: nei commenti usiamo "albero" e "puntatore a un nodo" come sinonimi, scegliendo di volta in volta
la formulazione più adatta a dare la specifica di una funzione.
Dal punto di vista tecnico, usiamo sempre il tipo Tree sia quando operiamo su un albero, sia quando operiamo,
a livello concettuale, su un puntatore a un nodo dell'albero.
Questo approccio e' corretto in quanto un albero (o sottoalbero) è un puntatore a una struct di tipo treeNode:
un albero è identificato univocamente dal puntatore alla sua radice */


/*******************************************************************************************************/
// il nodo di un albero è caratterizzato dall'etichetta, il puntatore al primo figlio e il puntatore al prossimo fratello
// NON manteniamo il puntatore al padre, anche se sarebbe comodo per alcune funzioni (ma del tutto inutile per altre)
struct tree::treeNode {
    Label label;
    treeNode *firstChild;
    treeNode *nextSibling;
};


/*******************************************************************************************************/
// isEmpty restituisce true se l'albero t e' vuoto, false altrimenti
bool tree::isEmpty(const Tree& t)
{
  return (t == emptyTree);
}



/*******************************************************************************************************/
//funzione ausiliaria ad addElem che restituisce il puntatore all'elemento con etichetta l
Tree getNode (const Label l, const Tree& t)
{
  //se l'albero é vuoto o l'etichetta é vuota ritorno emptyTree
  if(isEmpty(t) || l == emptyLabel) return emptyTree;
  //se l'etichetta di t é == l ritorno t
  if(t->label == l) return t;
  //altrimenti effettuo la ricorsione finché non ricevo un valore diverso da emptyTree
  Tree auxT = t->firstChild;
  //creo una variabile node che terrá il puntatore del padre se esiste
  Tree node;
  while (auxT != emptyTree)
   {
     //effettuo una chiamata di getNode su node
     node = getNode (l,auxT);
     //se restituisce emptyTree non ho trovato l'etichetta giusta
     if (node == emptyTree)
          //proseguo quindi con il fratello  di aux
          auxT = auxT->nextSibling;
    else //altrimenti
       //se ho trovato l'etichetta corretta restituisco node
       return node;
   }

  return emptyTree;
}

//Funzione ausiliaria per creare un nuovo nodo con etichetta l
Tree createNode(const Label l)
{
    Tree t = new treeNode;
    t->label = l;
    t->firstChild = t->nextSibling = emptyTree;
    return t;
}

// addElem aggiunge il nodo etichettato con labelOfNodeToAdd come
// figlio del nodo etichettato con labelOfNodeInTree.
// Caso particolare: aggiunta della radice, che si ottiene
// con labelOfNodeInTree uguale a emptyLabel (= nessun padre), e ha successo
// solo se l'albero e' vuoto (in caso contrario restituisce FAIL
// e non aggiunge nulla).
// Restituisce FAIL se non esiste un nodo nell'albero etichettato
// con labelOfNodeInTree oppure se nell'albero esiste gia' un nodo
// etichettato con labelOfNodeToAdd; aggiunge e restituisce OK altrimenti
Error tree::addElem(const Label labelOfNodeInTree, const Label labelOfNodeToAdd, Tree& t)
{
  //se l'albero é vuoto e l'etichetta del padre é vuota aggiungo l'elemento come radice
  if (isEmpty(t) && (labelOfNodeInTree == emptyLabel)){
      //creo un nodo e lo assegno a t
      t = createNode (labelOfNodeToAdd);
      return OK;
    } else {//altrimenti 
      //se l'etichetta da aggiungere esiste giá ritorno FAIL
      if (member(labelOfNodeToAdd,t)) return FAIL;

      //altrimenti creo una varibile aux e le chiamo getNode per assegnarle il puntatore del padre
      Tree auxT = getNode(labelOfNodeInTree,t);
      //se restituisce emptyTree ritorno FAIL (etichetta padre non presente)
      if (auxT == emptyTree) return FAIL;

      else //altrimenti
      {
        //creo un nuovo nodo che sará quello da aggiungere
        Tree add = createNode (labelOfNodeToAdd);
        //se il padre non ha figli:
        if (auxT->firstChild == emptyTree)
            //lo inserisco come firstChild
            auxT->firstChild = add;
        else //altrimenti
            //inserisco in testa il nuovo figlio e il precedente lo inserisco come fratello
          add->nextSibling = auxT->firstChild;
          
        auxT->firstChild = add;
      }
    return OK;
  }
}


/*******************************************************************************************************/
//funzione ausiliaria lastChild che restituisce l'ultimo figlio del puntatore scelto
Tree lastChild (const Tree& t)
{
  //se il nodo non ha figli o se é vuoto restituisco emptyTree
  if(t->firstChild == emptyTree || isEmpty(t)) return emptyTree;
  //altrimenti creo una variabile ausiliaria per scorrere la lista dei figli
  Tree auxT = t->firstChild;
  //finché il fratello di aux non é vuoto
  while (!isEmpty(auxT->nextSibling)){
      //passo al fratello
      auxT = auxT->nextSibling;
    }
  //restituisco auxT che corrisponderá all'ultimo figlio di t
  return auxT;
}

// funzione ausiliaria: dato un albero t e un'etichetta l, restituisce il puntatore al fratello precedente
// (ovvero più a sinistra) a quello con l'etichetta data, se esiste nell'albero
// Serve nella deleteElem
Tree prevSibling(const Label l, const Tree& t)
{
    // se l'albero e' vuoto oppure non ha figli restituisce il nodo vuoto
    if (isEmpty(t) || isEmpty(t->firstChild) || l==emptyLabel)
      return emptyTree;
    //se l'etichetta del firstChild di t é uguale ad l restituisco emptyTree (non ho un fratello precedente)
    if ((t->firstChild)->label == l)
      return emptyTree;
    //altrimenti
    else
       {
         //creo:
         //una variabile per tenere conto del precedente (all'inizio il firstChild di t )
         Tree prevChild = t->firstChild;
         //una variabile per tenere conto del corrente (all'inizio il primo fratello)
         Tree currentChild = prevChild->nextSibling;
         Tree auxT;
         //finché il corrente non é vuoto e non ho raggiunto il nodo con etichetta l
         while (!isEmpty(currentChild) && currentChild->label != l)
            {
              //scorro in avanti il prev e il curr
              prevChild = currentChild;  // avanzo finché currentChild diventa vuoto
              currentChild = currentChild->nextSibling;
            }
          //se sono uscito dal while perché ho trovato l'etichetta, restituisco il prev
          if (!isEmpty(currentChild) && currentChild->label == l)
            return prevChild;
          //altrimenti
          else
            {
              currentChild = t->firstChild;
              while (!isEmpty(currentChild))
                {
                  auxT = prevSibling(l, currentChild);
                  if (!isEmpty(auxT))
                  return auxT;
                  else
                    currentChild = currentChild->nextSibling;
                }
            }
       }
return emptyTree;
}


// deleteElem (versione iterativa) rimuove dall'albero il nodo etichettato con la Label l
// e collega al padre di tale nodo tutti i suoi figli
// Restituisce FAIL se si tenta di cancellare la radice e questa ha
// dei figli (non si saprebbe a che padre attaccarli) oppure se non esiste
// un nodo nell'albero etichettato con la Label; cancella e restituisce OK altrimenti
Error tree::deleteElemI(const Label l, Tree& t)
{
  if(isEmpty(t) || !member(l,t)) return FAIL;

  Tree nodesFather = getNode(father(l,t),t);
  if(nodesFather == emptyTree)
    {
      if(degree(l,t) == 0)
        {
          delete t;
          t = emptyTree;
        }
      else
        return FAIL;
    }
  else
    {
      Tree nodeToDelete = getNode(l,t);
      Tree lastSibling = lastChild (nodesFather);
      lastSibling->nextSibling = nodeToDelete->firstChild;
      Tree prev = prevSibling(l,t);
      if(isEmpty(prev))
        nodesFather->firstChild = (nodesFather->firstChild)->nextSibling;
      else
        prev->nextSibling = nodeToDelete->nextSibling;

      delete nodeToDelete;
      return OK;
    }
   return FAIL;
}



/*******************************************************************************************************/

//funzione ausiliaria per controllare se ha un figlio con l'etichetta l
bool HasChildrenL (const Label l,const Tree& t)
{
  //se l'albero é vuoto ritorno false
  if (isEmpty(t)) return false;
  //creo una variabile ausiliaria = al figlio di t
  Tree auxT = t->firstChild;
  //finché auxT non é vuota
  while (!isEmpty(auxT))
    {
      //se l'etichetta di auxT é = ad l ritorno true
      if (auxT->label == l) return true;
      //altrimenti passo al fratello
      auxT = auxT->nextSibling;
    }
  //se arrivo fino a qui non esiste un figlio con quella etichetta
  return false;
}


//Funzioni ausiliaria per deleteElem:
void deleteChild (const Label l, Tree& t)
{
  //creo una variabile ausiliaria = al firstChild di t
  Tree auxT = t->firstChild;
  //e un precedente inizialmente vuoto
  Tree  prev = createEmpty();
  //finché l'etichetta di auxT != da quella da eliminare
  while (auxT->label != l)
    {
      //il precedente é uguale ad auxT
      prev = auxT;
      //auxT passa al fratello
      auxT = auxT->nextSibling;
    }
  //quando esco da questo while auxT punta al nodo da eliminare
  //creo una variabile = ad auxT che useró per raggiungere l'ultimo fratello del nodo da eliminare
  Tree lastSibling = auxT;
  //scorro tra i fratelli finché non arrivo all'ultimo
  while(!isEmpty(lastSibling->nextSibling))
        lastSibling = lastSibling->nextSibling;

  //dopo aver raggiunto l'ultimo fratello ci attacco il firstChild del nodo da eliminare
  lastSibling->nextSibling = auxT->firstChild;
  //se non c'é nessun prev vuol dire che devo eliminare il primo
  if(isEmpty(prev))
    //quindi il fratello dell'elemento da eliminare diventa il firstChild
    t->firstChild = (t->firstChild)->nextSibling;
  else
      //altrimenti elimino un fratello nel mezzo e quindi sistemo i puntatori con prev
      prev->nextSibling = auxT->nextSibling;
  //alla fine in ogni caso elimino auxT
  delete auxT;
}

Error deleteElemAux(const Label l,Tree& t)
{
  //se l'albero é vuoto non ho nulla da eliminare
  if (isEmpty(t)) return FAIL;
  //se t ha un figlio con l'etichetta l
  if(HasChildrenL(l,t))
    {
      //elimino il figlio di t con quella etichetta
      deleteChild(l,t);
      return OK;
    }
  //altrimenti scorro la lista fino a che non raggiungo l'elemento con quella etichetta o non finisco di scorrere fino alla fine
  Tree auxT = t->firstChild;
  while(!isEmpty(auxT))
     {
       //chiamo ricorsivamente la funzione e se mi restituisce OK ha trovato l'elemento e lo ha eliminato
       //posso quindi restituire OK
       if(deleteElemAux(l,auxT) == OK) return OK;
       //altrimenti passo al fratello
       else
          auxT = auxT->nextSibling;
     }
  //se arrivo fino a qui ho visitato tutto l'albero senza trovare l'elemento con etichetta l
  return FAIL;
}

// deleteElem (versione ricorsiva): stesso comportamento della versione iterativa, ma implementata ricorsivamente
// (può anche non essere ricorsiva la deleteElemR, ma deve fare uso di funzioni ausiliarie ricorsive)
Error tree::deleteElemR(const Label l, Tree& t)
{
  //se l'albero é vuoto non posso eliminare nulla
  if(isEmpty(t)) return FAIL;
  //se invece non é vuoto e l'elemento da eliminare corrisponde alla radice
  if(!isEmpty(t) && t->label == l)
    {
      //se t non ha figli
      if(t->firstChild == emptyTree)
         {
           //dealloco t e lo rendo un emptyTree
           delete t;
           t = emptyTree;
         }
      //altrimenti restituisco FAIL poiché posso eliminare la radice solo se non ha figli
      else return FAIL;
    }
  //se arrivo fino a qui l'elemento da eliminare non é la radice e chiamo quindi la funzione ausiliaria
  //per trovare l'elemento (se esiste) ed eliminarlo
  return deleteElemAux(l,t);
}



/*******************************************************************************************************/

// father restituisce l'etichetta del padre del nodo con etichetta l se il nodo esiste nell'albero
// (o sottoalbero) t e se il padre esiste.
// Restituisce la costante emptyLabel altrimenti
Label tree::father(const Label l, const Tree& t)
{
   //se l'albero é vuoto restituisco emptyLabel
   if (isEmpty(t)) return emptyLabel;
   //se t ha un figlio con l'etichetta l restituisce il label di t
   if (HasChildrenL(l,t)) return t->label;
   //altrimenti creo una variabile aux albero = al firstChild di t
   Tree auxT = t->firstChild;
   //e creo una variabile label aux
   Label auxL;
   //finché aux non é vuota
   while (!isEmpty(auxT))
      {
        //effettuo la chiamata father su auxT assegnado il valore alla label aux
        auxL = father(l,auxT);
        //se ritorna un valore diverso da emptyLabel restituisco l'etichetta
        if (auxL != emptyLabel) return auxL;
        //altrimenti
        else
          //passo al fratello
          auxT = auxT->nextSibling;
      }
  //se sono arrivato qui non ho trovato nessun padre del nodo con etichetta l
  return emptyLabel;
}



/*******************************************************************************************************/
//funzione ausiliaria a children
bool childrenAux (const Label l, list::List& lst,const Tree& t)
{
  //se la lista é vuota esco e non faccio nulla
  if(isEmpty(t)) return false;
  //raggiungo il nodo padre etichettato con l
  Tree node = getNode(l,t);
  //se il nodo non ha figli esco senza fare nulla
  if(node->firstChild == emptyTree) return false;
  //altrimenti creo una variabile ausiliaria = al figlio di node
  Tree auxT = node->firstChild;
  //finché non raggiungo l'ultimo fratello
  while (auxT != emptyTree)
    {
      //aggiungo auxT alla lista
      list::addFront (auxT->label,lst);
      //passo poi al fratello
      auxT = auxT->nextSibling;
    }
  //esco dalla funzione
  return false;
}

// children restituisce una lista di Label, contenente le etichette
// di tutti i figli nell'albero t del nodo etichettato con l
// La lista può essere implementata usando una qualunque delle strutture dati viste a lezione
// (non un Vector!!!): si riusi una implementazione del TDD list, adattandola
// a elementi di tipo string (nelle precedenti esercitazioni gli elementi erano int)
list::List tree::children(const Label l, const Tree& t)
{
   //creo una lista vuota
   list::List lst = list::createEmpty();
   //chiamo la funzione ausiliaria childrenAux
   childrenAux(l,lst,t);
   //restituisco la lista
   return lst;
}



/*******************************************************************************************************/
// degree restituisce il numero di archi uscenti dal nodo etichettato con l; restituisce -1 se non esiste
// nessuna etichetta l nell'albero
int tree::degree(const Label l, const Tree& t)
{
  //se l'albero é vuoto ritorno -1
  if (isEmpty(t)) return -1;
  //creo una variabile ausiliaria e chiamo la funzione getNode per recuperare il nodo con etichetta l
  Tree auxT = getNode(l,t);
  //se il nodo con etichetta l non esiste ritorno -1
  if (auxT == emptyTree) return -1;
  //altrimenti creo una variavile intera come contatore = 0
  int cont = 0;
  //creo una variabile Tree per scorrere tutti i figli/fratelli
  Tree arcs = auxT->firstChild;
  //finché non raggiungo l'ultimo fratello
  while (arcs != emptyTree)
       {
         //aumento il contatore
         cont++;
         //passo al fratello successivo
         arcs = arcs->nextSibling;
       }
  //restituisco il numero finale di archi
  return cont;
}



/*******************************************************************************************************/
//Funzione ausiliaria per ancestorsR
bool ancestorsAux (const Label l, list::List& lst, const Tree& t)
{
  //se esiste un figlio di t con l'etichetta l
  if (HasChildrenL(l,t))
    {
      //aggiungo t alla lista -> il primo elemento aggiunto sará la radice
      list::addFront (t->label,lst);
      //restituisco true
      return true;
    }
  //altrimenti creo una variabile ausiliaria per scorrere l'albero
  Tree auxT = t->firstChild;
  //finché auxT non é vuoto
  while(!isEmpty(auxT))
    {
      //chiamo ricorsivamente la funzione ancestorsAux su auxT
      if (ancestorsAux(l,lst,auxT))
         {
           //se restituisce true aggiungo l'elemento alla lista
           list::addFront (t->label,lst);
           //restituisco true
           return true;
         }
      else
         //altrimenti passo al fratello
         auxT = auxT->nextSibling;
    }
  return false;
}

// ancestors (versione ricorsiva) restituisce una lista di Label, contenente le etichette
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
// (può anche non essere ricorsiva la ancestorsR, ma deve fare uso di funzioni ausiliarie ricorsive)
list::List tree::ancestorsR(const Label l, const Tree& t)
{
   //creo una lista vuota
   list::List lst = list::createEmpty();
   //chiamo la funzione ausiliaria ancestorsAux per riempire la lista
   ancestorsAux (l,lst,t);
   //restituisco la lista
   return lst;
}



/*******************************************************************************************************/
// ancestors (versione iterativa) restituisce una lista di Label, contenente le etichette
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
list::List tree::ancestorsI(const Label l, const Tree& t)
{
   list::List lst = list::createEmpty();
   //se ho solo la radice o l'albero é vuoto restituisco la lista
   if(father(l,t) == emptyLabel || isEmpty(t)) return lst;
   //inserisco nella lista in modo che la radice sia sempre il primo elemento e scorro
   //la lista dei padri fino a che non arrivo alla radice
   //creo una variabile Label per tenere l'etichetta della radice
   Label radice = t->label;
   Label auxL = l;
   //finché auxL é diversa dalla radice
   while(auxL != radice)
       {
         //risalgo ogni volta al padre di auxL, lo inserisco nella lista e auxL = al padre
         auxL = father(auxL,t);
         list::addFront(auxL,lst);
       }
   //restituisco la radice
   return lst;
}



/*******************************************************************************************************/
// leastCommonAncestor restituisce l'etichetta del minimo antenato comune
// ai nodi etichettati con label1 e label2
Label tree::leastCommonAncestor(const Label label1, const Label label2, const Tree& t)
{
  //utilizzo la funzione ancestorsR per crearmi due liste con gli antenati di label1 e label2
  list::List lst1 = ancestorsR(label1,t);
  list::List lst2 = ancestorsR(label2,t);
  //se una delle due liste é vuota restituisco emptyLabel
  if(list::isEmpty(lst1) || list::isEmpty(lst2)) return emptyLabel;

  // altrimenti inizio a scandire le liste dal primo elemento, che deve esistere e deve per forza essere la radice
  // e mi fermo quando i due elementi della lista sono diversi, o quando una delle due liste finisce
  int index = 0;
  while (list::get(index, lst1) == list::get(index, lst2) && index<list::size(lst1) && index<list::size(lst2))
     index++;

  // restituisco l'elemento in posizione precedente a quello del primo elemento diverso
  return get(index-1,lst1);
}



/*******************************************************************************************************/
// member restituisce true se il nodo etichettato con la label l appartiene all'albero t e false altrimenti
bool tree::member(const Label l, const Tree& t)
{
  //se l'albero é vuoto ritorno false
  if (isEmpty(t)) return false;
  //se l'etichetta é quella cercarta restituisco true
  if (t->label == l) return true;
  //chiamate ricorsive sui figli fino a che una non restituisce un valore diverso da false
  //creo una variabile ausiliaria come firstChild di t
  Tree auxT = t->firstChild;
  //fino a che auxT é diverso da emptyTree
  while (auxT != emptyTree)
   {
     if (!member(l,auxT))
         auxT = auxT->nextSibling;
     /*//se isMember é false passo al fratello
     if(!member(l,auxT)) auxT = auxT->nextSibling;*/
     //altrimenti ritorno true
     else return true;
   }
   return false;

   /*versione alternativa usando la getNode
   Tree auxT = getNode (l,t);
   if (auxT == emptyTree) return false;
   return true;*/
}



/*******************************************************************************************************/
// numNodes restituisce il numero di nodi nell'albero t mediante una visita ricorsiva in depthfirst
int tree::numNodes(const Tree& t)
{
  //se l'albero é vuoto non faccio niente
  if (isEmpty(t)) return 0;
  //creo una variabile ausiliaria come firstChild di t
 Tree auxT = t->firstChild;
 //creo una variabile cont da usare come contatore per i nodi
 int cont = 0;
 //finché auxT é diversa da emptyTree
 while (auxT != emptyTree)
     {
       //aumento il contatore chiamando ricorsivamente numNodes su auxTS
       cont += numNodes(auxT);
       //passo poi al fratello
       auxT = auxT->nextSibling;
     }
  //restituisco cont + 1 (radice)
  return cont+1;
}



/*******************************************************************************************************/
// createEmptyTree restituisce l'albero vuoto
Tree tree::createEmpty()
{
  Tree t = emptyTree;
  return t;
}



/*******************************************************************************************************/
//funzione ausiliaria per stampare
void visit(const Tree& t, int level)
{
  /* se l'albero e' vuoto non c'é niente da visitare */
  if (isEmpty(t)) return;
  //preparo una stringa composta da 2 trattini
  string frecce = "--";
  //itero tante volte in base al livello a cui sono
  for(int i = 0; i < level; ++i)
    //stampo i trattini
    cout<<frecce;

  //stampo il valore in fondo
  cout<<t->label<<endl;

  //effettuo le chiamate riscorsive come nelle funzioni precedenti
  Tree auxT = t->firstChild;
  while (!isEmpty(auxT)) {
    visit(auxT,level+1);
    auxT=auxT->nextSibling;
  }
}
// Visualizzazione possibilmente strutturata come visto a lezione
void printTree(const Tree& t)
{
  visit(t,0);
}



/****************************************************************/
// Questa funzione NON richiede di conoscere come e' fatta la struttura dati che implementa l'albero: usa solo addElem e quindi e' ad
// un alto livello di astrazione
// Vantaggi: codice compatto, leggibile, riutilizzabile per qualunque implementazione del TDD Tree
// Svantaggi: inefficiente: la addElem cerca ogni volta il nodo con etichetta fatherLabel, mentre basterebbe una chiamata sola per
// trovarlo e poi si potrebbero attaccare tutti i figli a esso, senza ripetere la dispendiosa ricerca nell'albero; per renderla
// efficiente dovrei pero' accedere direttamente alla struttura dati chiamando qualche funzione ausiliaria che operi
// sui nodi dell'albero, rinunciando a scrivere codice modulare, chiaro e ad un ragionevole livello di astrazione...
// Non esiste un'opzione migliore tra le due: se il codice deve essere efficiente, è opportuno scrivere una funzione ad hoc per
// una determinata implementazione; se il codice deve essere riutilizzabile, bisogna limitarsi a usare le funzioni offerte dall'
// interfaccia del TDD in modo che la funzione continui ad andare bene anche se cambia l'implementazione
Tree readFromStream(istream& str)
{
    Tree t = createEmpty();
    string line;
    Label rootLabel, fatherLabel, childLabel;
    getline(str, line);
    istringstream instream;            // uso una variabile di tipo istringstream per poter scandire i pezzi di ogni riga usando >>
    instream.clear();
    instream.str(line);
    instream >> rootLabel;             // il primo elemento che si incontra nel file e' l'etichetta della radice, per convenzione su come deve essere fatto il file
    addElem(emptyLabel, rootLabel, t); // la si inserisce nell'albero vuoto, indicando che il padre non c'e' (primo argomento emptyLabel)
    getline(str, line);                // poi si iniziano a scansionare le righe seguenti
    instream.clear();
    instream.str(line);
    while (!str.eof())
        {
	instream >> fatherLabel; // in ogni riga del file, il primo elemento e' l'etichetta del nodo padre e gli altri sono le etichette dei figli
        normalize(fatherLabel); // normalizzo l'etichetta del padre
        while (!instream.eof())            // finche' la riga corrente non e' terminata
            {
            instream >> childLabel;              // leggo la prossima etichetta
            normalize(childLabel);    // la normalizzo
            addElem(fatherLabel, childLabel, t); // e la attacco al padre
            }
        getline(str, line);
        instream.clear();
        instream.str(line);
        }
    str.clear();
    return t;
}



/****************************************************************/
Tree readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmpty();}
    return readFromStream(ifs);
}
