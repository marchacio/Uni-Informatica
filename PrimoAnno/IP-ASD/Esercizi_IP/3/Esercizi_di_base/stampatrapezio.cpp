#include <iostream>

/*. Scrivere un programma che legge due numeri interi strettamente positivi e stampa il trapezio rettangolo
fatto di 'x' con le
basi lunghe quanto i numeri letti, e l’altezza pari alla differenza fra le basi più uno.
[ File stampatrapezio.cpp ]
*/

int main() {
  //Dichiarazione variabili
  int b1, b2;

  //Assegnazione variabili
  std::cout << "Digita due numeri interi positivi: ";
  std::cin >> b1 >> b2;

  //Controllo integrità variabili
  while (b1 <= 0 || b2 <= 0 || b1 == b2) {
    std::cout << "I due numeri devono essere positivi e diversi: ";
    std::cin >> b1 >> b2;
  }

  //se i numeri sono invertiti rispetto al ciclo
  if(b1 > b2){
    int temp = b1;
    b1 = b2;
    b2 = temp;
  }

  //Creazione trapezio
  for(int n = b1; n < b2; ++n){
    for(int i = 0; i < n; ++i)
      std::cout << "*";

    std::cout << std::endl;
  }

  return 0;
}
