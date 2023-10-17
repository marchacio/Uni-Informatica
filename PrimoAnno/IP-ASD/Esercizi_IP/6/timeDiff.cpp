#include <iostream>

/*
Definire una struct Time per mantenere informazioni orarie come terne ora, minuti, secondi (memorizzabili con degli interi senza segno).
Scrivere un programma che legge le informazioni relative a due variabili T1, T2 di tipo Time, ne verifica la correttezza e
calcola il tempo trascorso tra i due orari, assumendo che si riferiscano allo stesso giorno. [ File timeDiff.cpp ]
*/

struct Time {
  unsigned int ora;
  unsigned int minuti;
  unsigned int secondi;
};


int main(){

  Time t1, t2, tempoTrascorso;

  std::cout << "Inserisci ora (0-23), minuti(0-59) e secondi(0-59) del primo giorno: ";
  std::cin >> t1.ora >> t1.minuti >> t1.secondi;

  std::cout << "Inserisci ora (0-23), minuti(0-59) e secondi(0-59) del secondo giorno: ";
  std::cin >> t2.ora >> t2.minuti >> t2.secondi;

  //verifica correttezza delle due variabili
  if(
    t1.ora < 24 && t1.ora >= 0 && t1.minuti < 60 && t1.minuti >= 0 && t1.secondi < 60 && t1.secondi >= 0 &&
    t2.ora < 24 && t2.ora >= 0 && t2.minuti < 60 && t2.minuti >= 0 && t2.secondi < 60 && t2.secondi >= 0
  ){
    //t1 dev'essere il tempo maggiore tra i due
    //Per capire se effettuare uno switch tra i due tempi, effettua calcoli in secondi
    int secondiT1 = (t1.ora * 60 * 60 + t1.minuti * 60 + t1.secondi);
    int secondiT2 = (t2.ora * 60 * 60 + t2.minuti * 60 + t2.secondi);
    if(secondiT2 > secondiT1) {
      int temp = secondiT1;
      secondiT1 = secondiT2;
      secondiT2 = temp;
    }

    //calcola il tempo trascorso tra t1 e t2 in secondi
    int secondiDiff = secondiT1 - secondiT2;

    //converti i secondi in time
    tempoTrascorso.ora = secondiDiff / 60 / 60;
    secondiDiff -= tempoTrascorso.ora * 60 * 60;

    tempoTrascorso.minuti = secondiDiff / 60;
    secondiDiff -= tempoTrascorso.minuti * 60;

    tempoTrascorso.secondi = secondiDiff;

    std::cout << "\nLa differenza e': " << tempoTrascorso.ora << " ore, " << tempoTrascorso.minuti << " minuti e " << tempoTrascorso.secondi << " secondi";

  } else
    std::cout << "I dati inseriti non vanno bene";

  return 0;
}
