#include <iostream>
#include <vector>

using namespace std;

void dequeue(vector<int> &v){
  if(v.size() <= 1){
    v.clear();
    return;
  }

  vector<int> temp;
  for(unsigned int i = 1; i < v.size(); ++i)
    temp.push_back(v.at(i));

  v = temp;
}

int main() {

  vector<int> vect = {1, 2, 3, 4, 5};

  dequeue(vect);

  for(unsigned int i = 0; i < vect.size(); ++i)
    cout << vect.at(i) << " ";

  return 0;
}
