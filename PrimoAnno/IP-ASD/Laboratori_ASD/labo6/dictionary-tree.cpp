// trucchetto per fare contento l'editor, che altrimenti si lamenta che le strutture dati non sono definite
#ifndef USE_TREE
#define USE_TREE
#endif

#include "dictionary.h"

#include <math.h> // sqrt()

using namespace dict;

struct dict::bstNode {
    Elem elem;
    bstNode* leftChild;
    bstNode* rightChild;
};

//funz ausiliaria per determinare se un dictionary è vuoto o no
bool isEmpty(const Dictionary& s){
    return s == emptyNode;
}

/****************************************************************/
/* Ritorna OK se la chiave non esisteva già e se l'inserimento  */
/* ha avuto successo.							    */
/* Ritorna FAIL se la chiave esisteva già o se l'inserimento    */
/* non ha avuto successo.
*****************************************************************/
Error dict::insertElem(const Key k, const Value v,  Dictionary& s){
    try {

        //caso particolare in cui è inserito il primo elemento
        //in tal caso, crea il nuovo nodo (la radice)
        if(isEmpty(s)){
            s = new bstNode;
            s->elem.key = k;
            s->elem.value = v;
            s->leftChild = emptyNode;
            s->rightChild = emptyNode;

            return Error::OK;
        }

        //caso in cui k esiste già
        if(s->elem.key == k)
            return Error::FAIL;
        //caso in cui k è piu piccolo del nodo
        else if(k < s->elem.key){
            if(s->leftChild == emptyNode){
                bstNode* nuovo = new bstNode;
                nuovo->elem = {k, v};
                nuovo->leftChild = emptyNode;
                nuovo->rightChild = emptyNode;

                s->leftChild = nuovo;

                return Error::OK;
            }
            return insertElem(k, v, s->leftChild);
        }
        //caso in cui k è piu grande del nodo
        else if(k > s->elem.key) {
            if(s->rightChild == emptyNode){
                bstNode* nuovo = new bstNode;
                nuovo->elem = {k, v};
                nuovo->leftChild = emptyNode;
                nuovo->rightChild = emptyNode;

                s->rightChild = nuovo;

                return Error::OK;
            }
            return insertElem(k, v, s->rightChild);
        }
        
        //c'è qualche problema...
        return Error::FAIL;
    } catch (...) {
        return Error::FAIL;
    }
}

/****************************************************************/
/* Ritorna il Value v associato alla Key k, se questa esiste    */
/* Ritorna emptyValue altrimenti					    */
/****************************************************************/
Value dict::search(const Key k, const Dictionary& s){
    if(s->elem.key == k)
        return s->elem.value;

    else if(k < s->elem.key){
        if(s->leftChild == emptyNode)
            return emptyValue;

        return search(k, s->leftChild);
    } else if(k > s->elem.key){
        if(s->rightChild == emptyNode)
            return emptyValue;
        
        return search(k, s->rightChild);
    }
    
    return emptyValue;
}

/****************************************************************/
/* Ritorna OK se la chiave esiste nel dizionario e se la 	    */
/* cancellazione ha avuto successo					    */
/* Ritorna FAIL se la chiave non esisteva nel dizionaio o se la */
/* cancellazione non ha avuto successo				    */
/****************************************************************/
//funzione ausiliaria
Elem deleteMin(Dictionary& s){
    bstNode* aux = s->leftChild;
    bstNode* prev = s;

    //trovo il figlio piu piccolo (piu a sinistra)
    while(aux->leftChild != emptyNode){
        prev = prev->leftChild;
        aux = aux->leftChild;
    }
    
    //se il filgio piu a sinistra ha figli a destra, sostituiscilo con il primo destro
    //altrimenti, cancellalo e basta
    if(aux->rightChild != emptyNode){
        prev->leftChild = aux->rightChild;    
    } else {
        prev->leftChild = emptyNode;
    }

    return aux->elem;  
}

Error dict::deleteElem(const Key k, Dictionary& s){
    if(isEmpty(s))
        return Error::FAIL;
    
    else if(k < s->elem.key)
        return deleteElem(k, s->leftChild);
    else if(k > s->elem.key)
        return deleteElem(k, s->rightChild);
    else if(k == s->elem.key){
        
        //se s non ha figli, lo cancello
        if(s->leftChild == emptyNode && s->rightChild == emptyNode)
            s = emptyNode;
        //se s ha solo il figlio destro, lo cancello e sostituisco s con il figlio destro
        else if(s->leftChild == emptyNode && s->rightChild != emptyNode)
            s = s->rightChild;
        //se s ha solo il figlio sinistro, lo cancello e sostituisco s con il figlio sinistro
        else if(s->leftChild != emptyNode && s->rightChild == emptyNode) 
            s = s->leftChild;
        else {
            //ha entrambi i figli
            Elem e = deleteMin(s->rightChild);
            s->elem = e;
        }

        return Error::OK;
    }

    return Error::FAIL;
}

//crea un dizionario vuoto
Dictionary dict::createEmptyDict(){
    bstNode* radice = emptyNode;

    return radice;
}

Dictionary readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmptyDict();}  
    return readFromStream(ifs);
}


/****************************************************************/
Dictionary readFromStdin()
{
    cout << "\nInserire una sequenza di linee che rispettano la sintassi key: value.<enter>\nDigitare CTRL^ D per terminare l'inserimento\n";
    Dictionary d = readFromStream((std::cin));
// Questa serve per aggirare un bug di alcune versioni attuali di glibc.
    clearerr(stdin);
    return d;
}


/****************************************************************/
Dictionary readFromStream(istream& str)
{
    Dictionary d = createEmptyDict();     
    string key, kcopy;
    string value;
    getline (str, key, ':'); 
    getline (str, value); 
    while (!str.eof())  
        {     
        kcopy = key;
        removeBlanksAndLower(kcopy);   
        insertElem(kcopy, value, d); // FINCHE' NON IMPLEMENTATE LA INSERTELEM, NON PUO' FUNZIONARE CORRETTAMENTE: la insertElem e' la prima funzione che dovete implementare
        getline (str, key, ':'); 
        getline (str, value); 
        }
    str.clear();
    return d;
}


/****************************************************************/
int printBucket(const Dictionary& b) // stampa il contenuto dell'albero secondo la stampa DFS simmetrica
{  
    int counter = 0;

    //se b non è vuoto, inizia il print
    if(!isEmpty(b)){
        if(b->leftChild != emptyNode)
            counter += printBucket(b->leftChild);

        cout << (b->elem).key << ": " << (b->elem).value << "\n"; 
        counter++;
        
        if(b->rightChild != emptyNode)
            counter += printBucket(b->rightChild);

        
    }

    return counter;	
}


/****************************************************************/
void print(const Dictionary& s)
// stampa il contenuto del dizionario ed anche informazioni su come sono stati organizzati gli elementi
{
int totalElem = printBucket(s);

cout << "\n===STATISTICHE SULL'ORGANIZZAZIONE DEL DIZIONARIO===";
cout << "\nIl numero totale di elementi memorizzati e' " << totalElem;
}

