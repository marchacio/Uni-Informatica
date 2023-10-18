#include <iostream>
#include <string>


// stampare `1' seguito da un carattere tab seguito da choice1
// stampare su una nuova riga `2' seguito da un tab seguito da choice2
// stampare su una nuova riga `3' seguito da un tab seguito da choice3
// stampare su una nuova riga `4' seguito da un tab seguito da choice4
void print_menu(std::string choice1, std::string choice2, std::string choice3, std::string choice4){
  std::cout << "1\t" << choice1 << "\n";
  std::cout << "2\t" << choice2 << "\n";
  std::cout << "3\t" << choice3 << "\n";
  std::cout << "4\t" << choice4 << "\n";
}

int main() {

  // dichiarare una costante s1 di tipo string inizializzata con "Prima scelta"
  // dichiarare una costante s2 di tipo string inizializzata con "Seconda scelta"
  // dichiarare una costante s3 di tipo string inizializzata con "Terza scelta"
  // dichiarare una costante s4 di tipo string inizializzata con "Quarta scelta"
  // chiamare print_menu su s1, s2, s3, s4
  std::string s1 = "Prima scelta";
  std::string s2 = "Seconda scelta";
  std::string s3 = "Terza scelta";
  std::string s4 = "Quarta scelta";

  print_menu(s1, s2, s3, s4);

  return 0;
}
