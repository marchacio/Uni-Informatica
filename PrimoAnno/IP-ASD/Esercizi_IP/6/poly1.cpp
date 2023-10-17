#include <iostream>
#include <cmath>

/*
Scrivere un programma che, dato un valore di N preimpostato ma modificabile, legge le coordinate di N punti in un array di
Point (che rappresenta una spezzata o “polilinea”), e:
• calcola e stampa la lunghezza totale della spezzata
• verifica se i lati hanno tutti la stessa lunghezza
• verifica se la spezzata è chiusa, e se lo è scrive un messaggio: “La linea è chiusa e quindi definisce un poligono”. Se i
lati hanno tutti la stessa lunghezza, aggiungere: “regolare”.
[ File poly1.cpp ]
*/

struct Point {
  double x;
  double y;
};

int main() {

  int N = 5;

  //Questo perche almeno tre lati devono esistere per essere definito poligono
  std::cout << "Inserisci la lunghezza dell'array (minimo 4): ";
  std::cin >> N;

  if(N >= 4){
    Point points[N];

    //Popula l'array di Point
    for(int i = 0; i < N; ++i){
      Point point;

      std::cout << "Inserire le coordinate del punto P" << i+1 << ": ";
      std::cin >> point.x >> point.y;

      points[i] = point;
    }

    //Calcola la lunghezza totale della spezzata sommando tutti i lati
    double lunghezzaSpezzata = 0;
    for (int i = 0; i < N-1; ++i)
      lunghezzaSpezzata += sqrt(pow((points[i + 1].x - points[i].x), 2) + pow((points[i + 1].y - points[i].y), 2));
    std::cout << "\nComplessivamente, la spezzata e' lunga " << lunghezzaSpezzata << std::endl;

    //verifica se tutti i lati hanno la stessa lunghezza
    bool lunghiUguali = true;
    double lunghezzaPrimoLato = sqrt(pow((points[1].x - points[0].x), 2) + pow((points[1].y - points[0].y), 2));

    for (int i = 1; i < N-1; i++){
      double lunghezzaLatoN = sqrt(pow((points[i + 1].x - points[i].x), 2) + pow((points[i + 1].y - points[i].y), 2));
      if(lunghezzaPrimoLato != lunghezzaLatoN)
        lunghiUguali = false;
    }
    if(lunghiUguali)
      std::cout << "I lati sono tutti della stessa lunghezza" << std::endl;
    else
      std::cout << "I lati non hanno tutti la stessa lunghezza" << std::endl;

    //verifica se la spezzata è chiusa
    if(points[0].x == points[N-1].x && points[0].y == points[N-1].y){
      std::cout << "La linea e' chiusa e quindi definisce un poligono";
      if(lunghiUguali)
        std::cout << " regolare";
    }

  } else
    std::cout << "\nLa lunghezza dev'essere almeno 2!";

  return 0;
}
