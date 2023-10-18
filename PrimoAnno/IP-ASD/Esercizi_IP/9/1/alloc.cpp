// dichiarare una costante N intera inizializzandola a un valore moderato (es. 5 o 10)
// dichiarare una variabile v di tipo puntatore a int
// allocare una quantità di memoria pari a N int, assegnandola a v
// scrivere nella memoria puntata da v la sequenza di valori 1, 3, 5, ... , 2*N-1 (i primi N dispari)
// stampare v usando l'aritmetica dei puntatori
// deallocare v
// allocare una quantità di memoria pari a 2*N int, assegnandola a v
// scrivere nella memoria puntata da v la sequenza di valori...
// ...1, 3, 5, ... , 4*N-1 (i primi 2*N dispari)
// stampare v usando l'aritmetica dei puntatori
// deallocare v

#include <iostream>

int main() {

  const int N = 5;

  int *v = new int[N];

  for(int i = 0; i< N; ++i)
    v[i] = 2*(i+1)-1;

  std::cout << "Stampa 1 di v: ";
  for(int i = 0; i< N; ++i)
    std::cout << v[i] << " ";

  delete [] v;


  v = new int[2*N];

  for(int i = 0; i< 2*N; ++i)
    v[i] = 2*(i+1)-1;

  std::cout << "\nStampa 2 di v: ";
  for(int i = 0; i< 2*N; ++i)
    std::cout << v[i] << " ";

  delete [] v;

  return 0;
}
