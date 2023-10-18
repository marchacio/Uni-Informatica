#include <iostream>
#include <string>

using namespace std;

int fact(const int& n) {
  // se n < 0 solleva eccezione
  const string err = "Fattoriale non valido";
  if(n < 0) throw err;

  if(n == 0) return 1;
  else return n*fact(n-1);
}


int fibonacci(const int& n){
  if(n == 0 || n == 1) return 1;

  return fibonacci(n-1) + fibonacci(n-2);
}


int MCD(const int& m, const int& n) {

  if(m == n) return m;
  if(m > n) return MCD(m-n, n);
  if(n > m) return MCD(m, n-m);

  return 0;
}


int main() {

  cout << MCD(3, 10);

  return 0;
}
