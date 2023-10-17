#include "phonebook.h"

#include <iostream>

int main() {

  PhoneBook phonebook;

  add(phonebook, "Angelo", "Giovanni", 546);
  add(phonebook, "Corti", "Michele", 9789897);
  add(phonebook, "Gionta", "Francesca", 476);
  add(phonebook, "Merello", "Piero", 476);
  add(phonebook, "Zora", "Marco", 34567890);

  sortSurnames(phonebook);

  print(phonebook);

  std::cout << "\n\n" << FindPos(phonebook, "ZZZZZZZZZ");

  return 0;
}
