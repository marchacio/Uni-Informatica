#include <iostream>

/*
  CONSEGNA: Scrivere un programma che legge tre numeri reali
    e li stampa in ordine decrescente
*/

int main() {

  //Dichiarazione variabili
  int a, b, c;

  //Assegnazione variabili
  std::cout << "Digita tre numeri da ordinare in ordine decrescente: ";
  std::cin >> a;
  std::cin >> b;
  std::cin >> c;

  //condizione logica
  //Se a è il numero maggiore:
  if(a > b && a > c){
    //Se b è maggiore di c
    if(b > c)
      std::cout << a << ", " << b << ", " << c;
    //Se c è maggiore di b
    else
      std::cout << a << ", " << c << ", " << b;

  //Se b è il numero maggiore:
  } else if(b > a && b > c) {
    //Se a è maggiore di c
    if(a > c)
      std::cout << b << ", " << a << ", " << c;
    //Se c è maggiore di a
    else
      std::cout << b << ", " << c << ", " << a;

  //Se c è il numero maggiore:
  } else {
    //Se a è maggiore di b
    if(a > b)
      std::cout << c << ", " << a << ", " << b;
    //Se b è maggiore di a
    else
      std::cout << c << ", " << b << ", " << a;
  }

  return 0;
}
