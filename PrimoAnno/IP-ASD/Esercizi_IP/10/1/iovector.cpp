#include "iovector.h"
#include <iostream>
#include <vector>

void readVector(std::vector<int>& v) {
// Stampare "Inserisci la dimensione della sequenza: "
// Dichiarare una variabile intera N
// Leggere N
// iterare finchÃ N non Ã¨ positivo
    //- segnalare che N deve essere positivo
    //- leggere N
/* iterare N volte
    - leggere un valore intero
    - memorizzare il valore letto in v
*/

  std::cout << "Inserisci la dimensione della sequenza: ";

  int N = 0;
  std::cin >> N;

  while(N <= 0){
    std::cout << "Inserire un numero POSITIVO: ";
    std::cin >> N;
  }

  for(int i = 0; i < N; ++i){
    std::cout << "Inserisci il " << i+1 << "o intero: ";
    int elem;
    std::cin >> elem;

    v.push_back(elem);
  }
}

void printVector(const std::vector<int>& v) {
  /* iterare v.size() volte
    - stampare l'elemento corrente di v
  */

  for(unsigned int i = 0; i < v.size(); ++i)
    std::cout << v.at(i) << " ";
}
