#include <iostream>
#include <string>

#include "menu.h"

using namespace std;

int main() {

  // dichiarare una costante s1 di tipo string inizializzata con "Prima scelta"
  // dichiarare una costante s2 di tipo string inizializzata con "Seconda scelta"
  // dichiarare una costante s3 di tipo string inizializzata con "Terza scelta"
  // dichiarare una costante s4 di tipo string inizializzata con "Basta!"
  /* ripetere
  - dichiarare una variabile intera answer inizializzata con use_menu su s1, s2, s3, s4
    finché answer è diverso da quattro
  */

  const string s1 = "Prima scelta";
  const string s2 = "Seconda scelta";
  const string s3 = "Terza scelta";
  const string s4 = "Quarta scelta";

  int tmp = 0;
  while(tmp != 4){
    int answer = use_menu(s1, s2, s3, s4);
    tmp = answer;
  }

  return 0;
}
