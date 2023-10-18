#include <iostream>

/*
Scrivere un programma che definisce un valore costante, N pari a 10.
Dichiara poi un array bidimensionale tavolaPitagorica di dimensioni N×N, e lo riempie dei valori della tavola pitagorica,
dove l’elemento (i, j) contiene il prodotto tra i+1 e j+1 (perché?).
Infine chiede all’utente una coppia di valori tra 1 e 10, e restituisce il loro prodotto – ottenuto consultando la tavola
pitagorica come una look-up table, e non eseguendo la moltiplicazione
*/

int main() {

  //Dichiarazione variabili
  const int N = 10;
  int tavolaPitagorica[N][N];

  //Calcolo della tavola pitagorica tramite 2 cicli for
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      tavolaPitagorica[i][j] = (i+1)*(j+1);

  //Coppia di valori da chiedere all'utente
  int a, b;
  std::cout << "Inserisci due numeri tra 1 e 10: ";
  std::cin >> a >> b;

  if(a > 0 && a <= N && b > 0 && b <= N)
    std::cout << "Il risultato e': " << tavolaPitagorica[a-1][b-1];
  else
    std::cout << "Valori non ammessi";

  return 0;
}
