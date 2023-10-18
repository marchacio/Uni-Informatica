#include "insert.h"

#include <vector>
#include <iostream>

int main() {

  //(a) Inserimento in v vuoto
  std::vector<int> v1;
  try{
    v1 = insert(v1, 0, 3);

    //Stampa risultato
    std::cout << std::endl << "Test a passato: ";
    for(unsigned int i = 0; i < v1.size(); ++i)
      std::cout << v1.at(i) << " ";

  } catch(int err) {
    std::cout << "\nTest a: Errore " << err;
  }


  //(b) Inserimento in testa (in posizione 0) a v non vuoto
  std::vector<int> v2;

  //Inserisci valori di test nel vector
  for(int i = 0; i < 3; ++i)
    v2.push_back(i);

  try{
    v2 = insert(v2, 0, 100);

    //Stampa risultato
    std::cout << std::endl << "Test b passato: ";
    for(unsigned int i = 0; i < v2.size(); ++i)
      std::cout << v2.at(i) << " ";

  } catch(int err) {
    std::cout << "\nTest b: Errore " << err;
  }


  //(c) Inserimento in coda (dopo l’ultima posizione) a v non vuoto
  std::vector<int> v3;

  //Inserisci valori di test nel vector
  for(int i = 0; i < 3; ++i)
    v3.push_back(i);

  try{
    v3 = insert(v3, v3.size(), 100);

    //Stampa risultato
    std::cout << std::endl << "Test c passato: ";
    for(unsigned int i = 0; i < v3.size(); ++i)
      std::cout << v3.at(i) << " ";

  } catch(int err) {
    std::cout << "\nTest c: Errore " << err;
  }



  //(d) Inserimento in posizione generica (non testa, non coda) in v non vuoto
  std::vector<int> v4;

  //Inserisci valori di test nel vector
  for(int i = 0; i < 3; ++i)
    v4.push_back(i);

  try{
    v4 = insert(v4, 1, 100);

    //Stampa risultato
    std::cout << std::endl << "Test d passato: ";
    for(unsigned int i = 0; i < v4.size(); ++i)
      std::cout << v4.at(i) << " ";

  } catch(int err) {
    std::cout << "\nTest d: Errore " << err;
  }


  //(e) Inserimento in posizione non valida (usare try . . . catch per trattare l’eccezione).
  std::vector<int> v5;

  //Inserisci valori di test nel vector
  for(int i = 0; i < 3; ++i)
    v5.push_back(i);

  try{
    v5 = insert(v5, 10, 100);

    //Stampa risultato
    std::cout << std::endl << "Test e passato: ";
    for(unsigned int i = 0; i < v5.size(); ++i)
      std::cout << v5.at(i) << " ";

  } catch(int err) {
    std::cout << "\nTest e: Errore " << err;
  }

  return 0;
}
