#include <vector>
#include <iostream>

/*
Ancora sul Crivello di Eratostene: scrivere la funzione std::vector<int> primes(int n) che dato un intero positivo n restituisce un std::vector<int>
che contiene tutti e soli i numeri primi compresi tra 2 e n, che quindi deve essere un vettore vuoto se n<2.
*/
bool isPrime(int n){
  for (int i = 2; i < n; i++)
    if(n%i == 0)
      return false;
  return true;
}

std::vector<int> primes(int n) {
  std::vector<int> v;

  for(int i = 1; i < n; ++i)
    if(isPrime(i))
      v.push_back(i);

  return v;
}


int main() {
  std::vector<int> v = primes(100000);

  for(unsigned int i = 0; i < v.size(); ++i)
    std::cout << v.at(i) << " ";
}
