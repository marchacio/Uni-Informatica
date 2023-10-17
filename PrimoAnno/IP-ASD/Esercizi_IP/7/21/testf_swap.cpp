#include <iostream>
#include "swap.h"

/*
Scrivere una funzione di nome swap che prende due argomenti a e b di tipo double,
quando viene chiamata ne scambia i valori, e restituisce void.
All’uscita, a e b devono avere i loro valori scambiati.
*/

int main() {

  double a = 0.3, b = 0.5;

  std::cout << "Valore di a: " << a << ". Valore di b: " << b << std::endl;

  swap(a, b);

  std::cout << "Nuovo valore di a: " << a << ". Nuovo valore di b: " << b;

}
