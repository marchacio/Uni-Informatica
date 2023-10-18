#include <iostream>
#include <string>

#include "menu.h"

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
  cout << endl;
}

int use_menu(string choice1, string choice2, string choice3, string choice4){
  print_menu(choice1, choice2, choice3, choice4);

  int n = get_choice(4);

  print_choice(n, choice1, choice2, choice3, choice4);

  return n;
}
