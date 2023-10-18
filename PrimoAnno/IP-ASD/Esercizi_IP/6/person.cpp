#include <iostream>

struct Person {
  std::string name;
  std::string surname;
  int birthYear;
};

int main() {

  Person me, you;

  me.name = "Bruce";
  me.surname = "Wayne";
  me.birthYear = 1939;

  you.name = "Clark";
  you.surname = "Kent";
  you.birthYear = 1933;

  me = you;

  std::cout << "My name is " << me.name << " " << me.surname << std::endl;
  std::cout << "I was born in " << me.birthYear << std::endl;

  return 0;
}
