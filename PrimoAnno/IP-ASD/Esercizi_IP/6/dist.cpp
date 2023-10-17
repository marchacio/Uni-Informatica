#include <iostream>
#include <cmath>

// Stampare "Inserire le coordinate del punto P1: "
// Dichiarare una variabile P1 di tipo Point
// Leggere da input le coordinate e memorizzarle in P1.x e P1.y
// Stampare "Inserire le coordinate del punto P2: "
// Dichiarare una variabile P2 di tipo Point
// Leggere da input le coordinate e memorizzarle in P2.x e P2.y
// Calcolare e stampare la distanza tra i due punti

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

  double distanza = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));

  std::cout << "La distanza fra i due punti e': " << distanza;

  return 0;
}
