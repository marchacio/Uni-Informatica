#include <iostream>
#include "d_array.h"

//Crea un array leggendo valori da input
void read_d_array(dynamic_array& d) {
  int s = -1;

  while(s <= 0){
    std::cout << "Inserisci la dimensione del vettore:\n";
    std::cin >> s;
  }

  d.size = s;
  d.store = new int[s];

  for(int i = 0; i < s; ++i){
    std::cout << "Inserisci un valore: ";
    std::cin >> d.store[i];
  }
}

//Stampa tutti gli elementi dell'array
void print_d_array(const dynamic_array& d) {
  int* p = d.store;

  for(unsigned int i = 0; i < d.size; ++i)
    std::cout << p[i] << "\t";

  std::cout << "\n";
}

//Svuota un array: array.size verrà impostata su 0 e verrà cancellato il riferimento in memoria
void delete_d_array(dynamic_array& d) {
  //Controlla che l'array dinamico sia cancellabile
  const std::string err = "Dimensione dell'array troppo piccola per poterlo cancellare";
  if(d.size <= 0) throw err;

  d.size = 0;
  delete [] d.store;
}

//int s = size dell'array;
//int v = valore
//
//inizializza d in modo che la sua size sia == s e tutti gli elementi siano v;
void create_d_array(dynamic_array& d, int s, int v) {
  //controlla che il array dinamico d sia vuoto; nel caso non lo fosse, cancellalo
  if(d.size != 0) delete_d_array(d);

  const std::string ERR = "La nuova dimensione dell'array dev'essere strettamente positiva";
  if(s <= 0) throw ERR;

  d.size = s;

  int* punt = new int[s];
  for(int i = 0; i < s; ++i)
    punt[i] = v;

  d.store = punt;
}


//Assegna value al index del array dinamico d;
void set(dynamic_array& d, int index, int value) {

  //controlla che index sia un valore corretto, cioe non crei errori o.o.b.
  const std::string err = "Valore di index non valido";
  if(index < 0 || index > (int)d.size) throw err;

  d.store[index] = value;
}


//Ritorna il valore di un elemento dell'array d in posizione index
int get(const dynamic_array& d, int index) {
  //controlla che index sia valido
  const std::string err = "Valore di index non valido";
  if(index < 0 || index > (int)d.size) throw err;

  int value = d.store[index];
  return value;
}


//Ordina l’array secondo l’algoritmo SelectionSort
void SelectionSort(dynamic_array& d) {

  for(int i = 0; i < (int)d.size-1; i++){

  	int min=i;

    for(int j = i+1; j < (int)d.size; j++)
    	if (d.store[j] < d.store[min])
         min = j;

      int temp = d.store[min];
      d.store[min] = d.store[i];
      d.store[i] = temp;
  }
}
