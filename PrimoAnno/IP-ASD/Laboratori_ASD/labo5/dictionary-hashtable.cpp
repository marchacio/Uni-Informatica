// trucchetto per fare contento l'editor, che altrimenti si lamenta che le strutture dati non sono definite
#ifndef USE_HASH_TABLE
#define USE_HASH_TABLE
#endif

#include "dictionary.h"

#include <math.h> // sqrt()

using namespace dict;

struct dict::cell {
      Elem	elem;
 	   cell	*next;
};


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
int h1(Key s) // funzione di hash che considera unicamente il valore ascii del primo carattere della chiave (se esiste) e restituisce il resto della divisione di tale valore per tableDim 
{
   // implementare la funzione richiesta e modificare il return 

   // ricavo il codice ASCII di una lettera 
   int val_ascii = (int)(s[0]);
   
   return val_ascii % tableDim;
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
int h2(Key s) // funzione di hash che somma il codice ascii di ogni carattere nella chiave e restituisce il resto della divisione di tale somma per tableDim 
{
   // implementare la funzione richiesta e modificare il return 
 
   int somma_ascii = 0;
   for(unsigned int i = 0; i < s.size(); ++i)
      somma_ascii += (int)(s[i]);

   return somma_ascii % tableDim;
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
int h3(Key s) // funzione di hash diversa da h1 ed h2, che progettate e implementate voi seguendo qualche criterio che vi sembra ragionevole
{
   int somma_ascii = 0;
   for(unsigned int i = 0; i < s.size(); ++i)
      somma_ascii += (int)(s[i]);

   somma_ascii *= (5/s.size());

   return somma_ascii % tableDim;
}

/****************************************************************/
/*    FUNZIONE DA MODIFICARE PER FARE ESPERIMENTI DIVERSI       */
/****************************************************************/
int h(Key s)
{
   return h1(s); // modificare questa chiamata per sperimentare l'utilizzo delle funzioni di hash h1, h2, h3, definite prima
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/* Ritorna OK se la chiave non esisteva già e se l'inserimento  */
/* ha avuto successo.							    */
/* Ritorna FAIL se la chiave esisteva già o se l'inserimento    */
/* non ha avuto successo.
*****************************************************************/
Error dict::insertElem(const Key k, const Value v,  Dictionary& s)
{
   try{

      Bucket nuovoBucket = new cell;
      Elem e = {k, v};
      nuovoBucket->elem = e;

      //controlla se il dizionario è vuoto in posizione h(k)
      if(s[h(k)] == emptyBucket){
         //Nel caso, inserisci in testa l'elemento
         nuovoBucket->next = emptyBucket;
      } else {
         //Altrimenti inserisci in testa ma controlla i puntatori
         //e che non esista gia un elemento con quella chiave
         Bucket aux = new cell;
         aux->next = s[h(k)];
         while(aux->next != emptyBucket){
            if(aux->next->elem.key == k)
               return FAIL;
            aux = aux->next;
         }
         //nel caso k non sia stato trovato, elimina l'aux e aggiungi il nuovo elemento
         //delete aux;

         nuovoBucket->next = s[h(k)];
      }
      s[h(k)] = nuovoBucket;

      return OK;
   }
   catch(...){
      return FAIL;
   }
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/* Ritorna il Value v associato alla Key k, se questa esiste    */
/* Ritorna emptyValue altrimenti					    */
/****************************************************************/
Value dict::search(const Key k, const Dictionary& s)
{	
   Bucket lista = s[h(k)];

   while(lista != emptyBucket){
      if(lista->elem.key == k)
         return lista->elem.value;
      
      lista = lista->next;
   }
   return emptyValue;
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/* Ritorna OK se la chiave esiste nel dizionario e se la 	    */
/* cancellazione ha avuto successo					    */
/* Ritorna FAIL se la chiave non esisteva nel dizionaio o se la */
/* cancellazione non ha avuto successo				    */
/****************************************************************/
Error dict::deleteElem(const Key k, Dictionary& s)
{
   try{
      if(s[h(k)] != emptyBucket){
         //Crea un bucket ausiliario per scorrere la lista e cercare l'elemento da eliminare:
         //aux fa il controllo e prev serve per modificare il puntatore precedente
         Bucket aux = s[h(k)]->next;
         Bucket prev = s[h(k)];

         //se c'è un solo elemento o l'elemento da cercare è il primo della lista:
         if(prev->elem.key == k){
            delete prev;

            if(aux == emptyBucket)
               s[h(k)] = emptyBucket;
            else
               s[h(k)] = aux;

            return OK;
         }

         while(aux != emptyBucket){
            if(aux->elem.key == k){
               if(aux->next == emptyBucket)
                  prev->next = emptyBucket;
               else
                  prev->next = aux->next;

               delete aux;
               return OK;
            }

            aux = aux->next;
            prev = prev->next;
         }
      }
      return FAIL;
   }
   catch(...){
      return FAIL;
   }   
}


/****************************************************************/
Dictionary dict::createEmptyDict()
{
   Bucket* d = new Bucket[tableDim];
   for (int i=0; i < tableDim; ++i)
      d[i]=emptyBucket;
   return d;
}


/****************************************************************/
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
int printBucket(Bucket b) // stampa il contenuto di un bucket e restituisce il numero di elementi contenuti nel bucket stesso
{  
   int counter = 0;
   while(b!=emptyBucket) {
        counter++;
        cout << (b->elem).key << ": " << (b->elem).value << "\n"; 
	b=b->next;
	}
   return counter;	
}


/****************************************************************/
void print(const Dictionary& s)
// stampa il contenuto del dizionario ed anche informazioni su come sono stati organizzati gli elementi
{
int bucketDim[tableDim];
int totalElem = 0;
for (unsigned int i=0; i<tableDim; ++i)
   {
    cout << "\nBucket " << i << "\n\n";
    bucketDim[i] = printBucket(s[i]);
    totalElem += bucketDim[i]; 
   }
float means = totalElem/(float)tableDim;
float standardDevSum = 0;
for (unsigned int i=0; i<tableDim; ++i)
     standardDevSum += (bucketDim[i]-means)*(bucketDim[i]-means);
   
/* Lo scarto tipo, deviazione standard, o scarto quadratico medio e' un indice di dispersione statistico, vale a dire una stima della variabilita' di una popolazione di dati o di una variabile casuale.
Lo scarto tipo e' uno dei modi per esprimere la dispersione dei dati intorno ad un indice di posizione, quale puo' essere, ad esempio, la media aritmetica. */

cout << "\n===STATISTICHE SULL'ORGANIZZAZIONE DEL DIZIONARIO===\n";

for (unsigned int i=0; i<tableDim; ++i)
   cout << "\nBucket " << i << ": " << bucketDim[i] << " elementi";

cout << "\nIl numero totale di elementi memorizzati e' " << totalElem;
cout << "\nIl numero di bucket nel dizionario e' " << tableDim;
if (tableDim != 0) cout << "\nIl numero atteso di elementi per bucket e' " << means << "\nLa deviazione standard e' " << sqrt(standardDevSum/tableDim);
}



