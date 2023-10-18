#include <iostream>
#include <vector>

using namespace std;

bool funzione_m(vector<int> v){
  bool is_esponenziale = true;

  for(unsigned int i = 1; i < v.size() -1; ++i)
    if(is_esponenziale && v.at(i+1) != (v.at(i-1)*v.at(i)))
      is_esponenziale = false;

  return is_esponenziale;
}

bool funzione_anna(vector<int> v){
   unsigned int i = 1;

   while ((v[i] % v[i-1] == 0)&&(i != v.size ())) ++i;

   return (i == v.size());

}

int main() {

  vector<int> v = {2, 4, 8};

  cout << boolalpha << funzione_anna(v);

}
