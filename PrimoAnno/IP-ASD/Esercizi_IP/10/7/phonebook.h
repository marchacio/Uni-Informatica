#include <string>
#include <vector>

struct Contact_Str {
  std::string name;
  std::string surname;
  int phonenumber;
};

typedef std::vector<Contact_Str> PhoneBook;


//aggiunge un contatto C in coda alla rubrica B
void add(PhoneBook& B, std::string surname, std::string name, int phoneNumber);

//stampare il contenuto della rubrica B
void print(const PhoneBook& B);

// data una rubrica ordini alfabeticamente gli elementi in
//essa contenuti rispetto al campo Surname
void sortSurnames(PhoneBook& B);


int FindPos(const PhoneBook& r, std::string S);


void Shift_PhoneBook(PhoneBook& B, int pos);
