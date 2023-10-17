#include <iostream>

// Stampare "Inserire le coordinate del punto P1: "
// Dichiarare una variabile P1 di tipo Point
// Leggere da input le coordinate e memorizzarle in P1.x e P1.y
// Stampare "Inserire le coordinate del punto P2: "
// Dichiarare una variabile P2 di tipo Point
// Leggere da input le coordinate e memorizzarle in P2.x e P2.y
//
// Se P1 e P2 sono lo stesso punto (ossia se hanno le stesse coordinate)
// - Stampare "I punti sono uguali" seguito da un a capo
// Altrimenti
// - Stampare "Il secondo punto è "
// - Se P2.y > P1.y
// -- Stampare "in alto "
// - Altrimenti
// -- Stampare "in basso "
// - Se P2.x > P1.x
// -- Stampare "a destra "
// - Altrimenti
// -- Stampare "a sinistra "
// - Stampare " rispetto al primo" seguito da un a capo

struct Point {
  double x;
  double y;
};

int main() {
  Point p1, p2;

  std::cout << "Inserire le coordinate del punto P1: ";
  std::cin >> p1.x >> p1.y;

  std::cout << "Inserire le coordinate del punto P2: ";
  std::cin >> p2.x >> p2.y;

  if(p1.x == p2.x && p1.y == p2.y)
    std::cout << "I punti sono uguali\n";
  else {
    std::cout << "Il secondo punto e' ";

    if(p2.y > p1.y){
      std::cout << "in alto";
    } else {
      std::cout << "in basso";
    }

    if(p2.x > p1.x){
      std::cout << " a destra";
    } else {
      std::cout << " a sinistra";
    }

    std::cout << " rispetto al primo\n";
  }

  return 0;
}
