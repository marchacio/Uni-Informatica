#include <iostream>

int main() {

  int a;

  std::cout << "Inserisci un numero intero: ";
  std::cin >> a;

  if(a%2 == 0)
    std::cout << "\nPIPPO";
  else
    std::cout << "\nPLUTO";

  return 0;
}
