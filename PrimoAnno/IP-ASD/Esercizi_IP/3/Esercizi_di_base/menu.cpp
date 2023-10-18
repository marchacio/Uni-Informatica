#include <iostream>

/*
Scrivere un programma che propone all’utente un menu con quattro alternative, ne legge la scelta e seleziona l’alternativa
corrispondente. [ File menu.cpp ]
*/

int main() {

  //Dichiarazione variabili
  int scelta = 1;

  //Ripeti il codice finche l'utente non sceglie qualcosa
  while (scelta != 0) {

    //Print delle possibili opzioni
    std::cout << "1 Prima scelta" << std::endl;
    std::cout << "2 Seconda scelta" << std::endl;
    std::cout << "3 Terza scelta" << std::endl;
    std::cout << "0 Uscita dal programma" << std::endl  << std::endl;

    //Assegna input
    std::cout << "Fai una scelta: ";
    std::cin >> scelta;

    //Condizioni logiche
    if(scelta == 1)
      std::cout << "Hai fatto la prima scelta" << std::endl << std::endl;
    else if(scelta == 2)
      std::cout << "1Hai fatto la seconda scelta" << std::endl << std::endl;
    else if(scelta == 3)
      std::cout << "Hai fatto la terza scelta" << std::endl << std::endl;
    else if(scelta == 0){
      std::cout << "Hai deciso di uscire dal programma" << std::endl;
      return 0;
    }
    else
      std::cout << "Scelta non valida" << std::endl << std::endl;
  }

  return 0;
}
