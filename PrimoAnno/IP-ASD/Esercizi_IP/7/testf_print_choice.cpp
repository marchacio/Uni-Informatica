#include <iostream>
#include <string>

// Stampare un a capo seguito da "Scelta effettuata: "
// A seconda del valore di n
// Nel caso 1:
// - stampare ch1
// Nel caso 2:
// - stampare ch2
// Nel caso 3:
// - stampare ch3
// Nel caso 4:
// - stampare ch4
void print_choice(int n, std::string ch1, std::string ch2, std::string ch3, std::string ch4){
  std::cout << "\nScelta effettuata: ";

  switch(n){
    case 1:
      std::cout << ch1;
      break;
    case 2:
      std::cout << ch2;
      break;
    case 3:
      std::cout << ch3;
      break;
    case 4:
      std::cout << ch4;
      break;
  }
}

int main() {

  // dichiarare una costante s1 di tipo string inizializzata con "Prima scelta"
  // dichiarare una costante s2 di tipo string inizializzata con "Seconda scelta"
  // dichiarare una costante s3 di tipo string inizializzata con "Terza scelta"
  // dichiarare una costante s4 di tipo string inizializzata con "Quarta scelta"
  // chiamare print_choice su 1, s1, s2, s3, s4
  // chiamare print_choice su 2, s1, s2, s3, s4
  // chiamare print_choice su 3, s1, s2, s3, s4
  // chiamare print_choice su 4, s1, s2, s3, s4

  const std::string s1 = "Prima scelta";
  const std::string s2 = "Seconda scelta";
  const std::string s3 = "Terza scelta";
  const std::string s4 = "Quarta scelta";

  print_choice(1, s1, s2, s3, s4);
  print_choice(2, s1, s2, s3, s4);
  print_choice(3, s1, s2, s3, s4);
  print_choice(4, s1, s2, s3, s4);

  return 0;
}
