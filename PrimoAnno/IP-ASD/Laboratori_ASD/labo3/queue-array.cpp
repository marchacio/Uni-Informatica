#include "queue-array.h"
#include <iostream>

using namespace queue;


/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

/****************************************************************/
Queue queue::createEmpty()
{
   Queue q;

   q.queue = new Elem[BLOCKDIM];
   q.size = 0;
   q.maxsize = BLOCKDIM;
   return q;
}

void ridimensiona(int newDim, Queue& l){
  //controlla che newdim sia maggiore di size
  if(newDim < l.size) return;

  //alloca un nuovo array dinamico in memoria e fai la copia profonda
  Elem* aux = new Elem[newDim];
  for(int i = 0; i < l.size; ++i)
    aux[i] = l.queue[i];

  //scambia l'array dinamico:
  //cancella l'array precedente
  delete[] l.queue;
  //linka quello nuovo
  l.queue = aux;
}

/****************************************************************/
void queue::enqueue(Elem e, Queue& l) // aggiunge e in coda
{
  //L'array è pieno, bisogna aumentare la maxsize
  if(l.size == l.maxsize)
    ridimensiona(l.maxsize*2, l);

  l.queue[l.size] = e;
  l.size++;
  std::cout << l.size << " ";
  return;
}


/****************************************************************/
Elem queue::dequeue(Queue& l) // rimuove il primo elemento e lo restituisce
{
  //rimuovi tutti i casi estremi (size == 0 o size == 1)
  if(isEmpty(l)) return EMPTYELEM;

  Elem dequeued = l.queue[0];

  if(l.size == 1){
    l = createEmpty();
    return dequeued;
  }

   for(int i = 0; i < l.size-1; ++i)
     l.queue[i] = l.queue[i+1];

   //cancella l'ultimo elemento (è gia stato traslato a size-1)
   l.queue[l.size-1] = EMPTYELEM;
   l.size--;

   //se lo spazio non utilizzato è troppo, ridimensiona
   if((l.maxsize - l.size) >= BLOCKDIM)
     ridimensiona(l.size+1, l);

   return dequeued;
}


/****************************************************************/
Elem queue::first(Queue& l) // restituisce il primo elemento
{
  if(isEmpty(l)) return EMPTYELEM;

   return l.queue[0];
}


/****************************************************************/
bool queue::isEmpty(const Queue& l)
{
   return l.size == 0;
}



/****************************************************************/
Queue readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // stream associato a un file, in lettura
    return readFromStream(ifs);
}



Queue readFromStdin()
{
    cout << endl << "inserire una sequenza di numeri separati da spazi seguiti da "
      <<  FINEINPUT << " per terminare" << endl;
    return readFromStream((std::cin));
}



Queue readFromStream(istream& is)
{
   Queue l = createEmpty();
   Elem e;
   while (is >> e) {
      if (e == FINEINPUT) // il segnale di fine input è FINEINPUT
         return l;
      enqueue(e, l);
   }
   throw runtime_error("errore inserimento dati");
}



void print(const Queue& l)
{
   for (int i=0; i<l.size; ++i)
      cout << l.queue[i] << "; ";
   cout << endl;
}
