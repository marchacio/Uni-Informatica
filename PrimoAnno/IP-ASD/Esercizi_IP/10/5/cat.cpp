#include "cat.h"

#include <vector>

std::vector<int> cat(std::vector<int> v1, std::vector<int> v2) {

  std::vector<int> v12;

  for(unsigned int i = 0; i < v1.size(); ++i)
    v12.push_back(v1.at(i));

  for(unsigned int i = 0; i < v2.size(); ++i)
    v12.push_back(v2.at(i));

  return v12;
}
