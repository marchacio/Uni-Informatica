#include <iostream>

/*
Scrivere un programma che gioca più mani di morra cinese. Alla fine di ogni mano deve chiedere all’utente se vuole
continuare;
se l’utente risponde ’S’ o ’s’ prosegue con un’altra mano, altrimenti termina. [ File partitamorra.cpp ]
*/

int main() {

  //Dichiarazione variabili
  char continuaPartita = 's';

  //Le mosse possono essere:
  //c = carta, f = forbice, s = sasso
  char mossa1, mossa2;

  //Ripeti il codice finche l'utente non decide di chiudere il programma
  while (continuaPartita == 's' || continuaPartita == 'S') {

    std::cout << "Mosse possibili: s = sasso, f = forbice, c = carta.\n\n";

    //Assegnazione variabili
    std::cout << "Mossa del giocatore 1: ";
    std::cin >> mossa1;
    std::cout << "Mossa del giocatore 2: ";
    std::cin >> mossa2;

    //Controlla integrità delle mosse
    if((mossa1 == 'c' || mossa1 == 'f' || mossa1 == 's') && (mossa2 == 'c' || mossa2 == 'f' || mossa2 == 's')){

      //Logica della morra cinese
      if(mossa1 == mossa2)
        std::cout << "Pareggio" << std::endl;

      //Tutti i casi in cui vince mossa1
      else if((mossa1 == 'c' && mossa2 == 's') || (mossa1 == 'f' && mossa2 == 'c') || (mossa1 == 's' && mossa2 == 'f'))
        std::cout << "Vince giocatore 1" << std::endl;
      else if((mossa2 == 'c' && mossa1 == 's') || (mossa2 == 'f' && mossa1 == 'c') || (mossa2 == 's' && mossa1 == 'f'))
        std::cout << "Vince giocatore 2" << std::endl;

      std::cout << "\nVuoi giocare ancora?\nS = un'altra partita\nN = Chiudi" << std::endl;
      std::cin >> continuaPartita;
      std::cout << std::endl;

    } else {
      //Mostra questo messaggio se una delle mosse in input non vanno bene
      std::cout << "Mossa non valida!\nRiprova\n\n\n";
    }
  }

  return 0;
}
