#include <iostream>

/*
  CONSEGNA: Scrivere un programma che legge da input un numero intero Temp e stampa:
    • “Freddo dannato” se Temp è compreso fra −20 e 0
    • “Freddo” se Temp è compreso fra 1 e 15
    • “Normale” se Temp è compreso fra 16 e 23
    • “Caldo” se Temp è compreso fra 24 e 30
    14
    • “Caldo da morire” se Temp è compreso fra 31 e 40
    • “Non ci credo, il termometro deve essere rotto” se Temp è superiore a 40 o inferiore a −20
*/

int main() {

  //Dichiarazione variabili
  int temp;

  //Assegnazione variabili
  std::cout << "Inserisci la temperatura: ";
  std::cin >> temp;

  //condizione logica
  if(temp <= 0 && temp >= -20)
    std::cout << "Freddo dannato";
  else if(temp <= 15 && temp >= 1)
    std::cout << "Freddo";
  else if(temp <= 23 && temp >= 16)
      std::cout << "Normale";
  else if(temp <= 30 && temp >= 24)
    std::cout << "Caldo";
  else if(temp <= 40 && temp >= 31)
    std::cout << "Caldo da morire";
  else
    std::cout << "Non ci credo, il termometro deve essere rotto";
}
