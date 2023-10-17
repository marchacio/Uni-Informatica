#include <iostream>


// Dichiarare una variabile scelta di tipo int
/* Ripetere
- Stampare "Inserisci una scelta fra 1 e " seguito da max
- Stampare un a capo
- Leggere scelta
finché scelta minore di uno o maggiore di max
*/
// Restituire scelta
int get_choice(int max){
  int scelta = 0;

  while(scelta < 1 || scelta > max){
    std::cout << "Inserisci una scelta fra 1 e " << max << std::endl;
    std::cin >> scelta;
  }

  return scelta;
}

int main() {

  // stampare il risultato della chiamata di get_choice su 7
  int val = get_choice(7);
  std::cout << val;

  return 0;
}
