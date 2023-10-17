#include <iostream>
#include <string>

/*
  CONSEGNA: Scrivere un programma che implementa un turno di gioco di forbice carta sasso,
    ovvero che legge in input la mossa dei due
    giocatori e restituisce in output chi ha vinto. [ File morra.cpp ]

*/

int main() {

  //Dichiarazione variabili
  std::string mossa1, mossa2;

  //Assegnazione variabili
  std::cout << "Digitare le due mosse: " << std::endl;

  std::cout << "Giocatore 1: ";
  std::cin >> mossa1;

  std::cout << "Giocatore 2: ";
  std::cin >> mossa2;

  //Condizione logica
  //CARTA
  if(mossa1 == "carta"){
    //carta vince su sasso
    if(mossa2 == "sasso")
      std::cout << "Ha vinto giocatore 1";
    //carta perde su forbice
    else if(mossa2 == "forbice")
      std::cout << "Ha vinto giocatore 2";
    //pareggio
    else if(mossa2 == "carta")
      std::cout << "Pareggio";
    //Mossa non riconosciuta dal programma
    else
      std::cout << "Mossa sconosciuta";

  //FORBICE
  } else if(mossa1 == "forbice"){
    //forbice vince su carta
    if(mossa2 == "carta")
      std::cout << "Ha vinto giocatore 1";
    //forbice perde su sasso
    else if(mossa2 == "sasso")
      std::cout << "Ha vinto giocatore 2";
    //pareggio
    else if(mossa2 == "forbice")
      std::cout << "Pareggio";
    //Mossa non riconosciuta dal programma
    else
      std::cout << "Mossa sconosciuta";

  //SASSO
  } else if(mossa1 == "sasso"){
    //sasso vince su forbice
    if(mossa2 == "forbice")
      std::cout << "Ha vinto giocatore 1";
    //sasso perde su carta
    else if(mossa2 == "carta")
      std::cout << "Ha vinto giocatore 2";
    //pareggio
    else if(mossa2 == "sasso")
      std::cout << "Pareggio";
    //Mossa non riconosciuta dal programma
    else
      std::cout << "Mossa sconosciuta";
  } else {
    std::cout << "Mossa sconosciuta";
  }

  return 0;
}
