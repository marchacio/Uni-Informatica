#include <iostream>
#include <string>

using namespace std;

void print_menu(string choice1, string choice2, string choice3, string choice4){
  cout << "1\t" << choice1 << "\n";
  cout << "2\t" << choice2 << "\n";
  cout << "3\t" << choice3 << "\n";
  cout << "4\t" << choice4 << "\n";
}

int get_choice(int max){
  int scelta = 0;

  while(scelta < 1 || scelta > max){
    cout << "Inserisci una scelta fra 1 e " << max << endl;
    cin >> scelta;
  }

  return scelta;
}

void print_choice(int n, string ch1, string ch2, string ch3, string ch4){
  cout << "\nScelta effettuata: ";

  switch(n){
    case 1:
      cout << ch1;
      break;
    case 2:
      cout << ch2;
      break;
    case 3:
      cout << ch3;
      break;
    case 4:
      cout << ch4;
      break;
  }
}

// Chiamare print_menu su choice1, choice2, choice3, choice4
// Dichiarare una variabile n di tipo int inizializzata con il risultato della chiamata di get_choice su 4
// Chiamare print_choice su n, choice1, choice2, choice3, choice4
// Restituire n
int use_menu(string choice1, string choice2, string choice3, string choice4){
  print_menu(choice1, choice2, choice3, choice4);

  int n = get_choice(4);

  print_choice(n, choice1, choice2, choice3, choice4);

  return n;
}


int main() {

  // dichiarare una costante s1 di tipo string inizializzata con "Prima scelta"
  // dichiarare una costante s2 di tipo string inizializzata con "Seconda scelta"
  // dichiarare una costante s3 di tipo string inizializzata con "Terza scelta"
  // dichiarare una costante s4 di tipo string inizializzata con "Quarta scelta"
  // chiamare use_menu su s1, s2, s3, s4

  const string s1 = "Prima scelta";
  const string s2 = "Seconda scelta";
  const string s3 = "Terza scelta";
  const string s4 = "Quarta scelta";

  use_menu(s1, s2, s3, s4);

  return 0;
}
