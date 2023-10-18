#include <iostream>
#include "is_root.h"

/*
Scrivere una funzione con due argomenti reali x e sqrt_x che restituisce un valore booleano, true se sqrt_x è la radice
quadrata di x, ovvero se il quadrato di sqrt_x coincide con x.
Per testare la funzione usate come dati 25.3268614564 la cui radice quadrata è 5.03258
  (se preferite altri valori, vi conviene partire da un numero con cifre decimali e farne il quadrato,
  in modo da evitare errori di approssimazione dovuti ai troncamenti).
*/

int main() {

  std::cout << std::boolalpha << funct(25.3268614564, 5.03258);

  return 0;
}
