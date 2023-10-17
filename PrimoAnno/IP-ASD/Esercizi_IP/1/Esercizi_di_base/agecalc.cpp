#include <iostream>
using namespace std;

/*
  CONSEGNA: Scrivere un programma che chiede all’utente in che anno è nato e stampa quanti anni ha. Il programma deve essere scritto
    in un file chiamato agecalc.cpp.
*/

int main() {

  //Dichiarazione anno di nascita utente
  int anno_nascita;

  //Dichiarazione costante anno attuale
  int anno_attuale = 2022;

  //Richiesta all'utente
  cout << "Inserisci il tuo anno di nascita: ";
  cin >> anno_nascita;

  //Calcola gli anni dell'utente tramite una sottrazione
  int anni = anno_attuale - anno_nascita;

  //stampa risultato
  cout << "Hai " << anni << " anni";
}
