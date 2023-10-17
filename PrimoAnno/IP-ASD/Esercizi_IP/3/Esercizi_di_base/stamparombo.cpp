#include <iostream>

/*
Scrivere un programma che chiede all’utente un numero intero positivo n e stampa un rombo di asterischi che sulla diagonale
ha 2 ∗ n + 1 caratteri. Ad esempio su 8 stampa

che sulla diagonale ha 17 caratteri. [ File stamparombo.cpp ]
[SUGGERIMENTO: È più facile stampare il rombo con due cicli, il primo per le righe in cui il numero di asterischi cresce e il
secondo per le righe in cui il numero di asterischi diminuisce.]
*/

int main() {

  int moltiplicatore = 0;

  //Controlla che l'utente inserisca valori positivi
  while(moltiplicatore <= 0){
    std::cout << "Inserisci un numero intero positivo: ";
    std::cin >> moltiplicatore;

    if(moltiplicatore <= 0) {
      std::cout << "Devi inserire un numero positivo!\n";
    }
  }

  std::cout << std::endl;

  //Per moltiplicatore volte gli asterischi cresceranno e diminuiranno, mentre
  //ci sarà una riga centrale comune:
  //CICLO CHE GENERA DA 0 A META' + 1 DEL ROMBO:
  for(int i = 0; i < moltiplicatore; i++){
    for(int n = 0; n < (2*moltiplicatore + 1); n++){
      if (n < moltiplicatore-i || n > moltiplicatore+i)
        std::cout << " ";
      else
        std::cout << "*";
    }
    std::cout << std::endl;
  }

  //CICLO CHE GENERA DA META' - 1 A FINE DEL ROMBO:
  for(int i = moltiplicatore; i >= 0; i--){
    for(int n = 0; n < (2*moltiplicatore +1); n++){
      if (n < moltiplicatore-i || n > moltiplicatore+i)
        std::cout << " ";
      else
        std::cout << "*";
    }

    std::cout << std::endl;
  }

  return 0;
}
