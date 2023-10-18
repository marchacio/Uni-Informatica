#include <iostream>
#include "divide.h"

/*
Scrivere una funzione di nome divide che prende quattro argomenti interi a, b, q e r,
restituisce void, quando viene chiamata
assegna a q il quoziente tra a e b (risultato della divisione intera) e a r il resto.
*/

int main() {
  int a = 10, b = 7, q, r;

  divide(a, b, q, r);

  std::cout << "Divisione tra " << a << " e " << b << ": " << q << ", resto " << r;
}
