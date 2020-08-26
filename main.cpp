#include "List.hpp"

#include <iostream>
#include <stack>
#include <list>

#define PRINT(x) (std::cout << x << std::endl)

int main() {
  ft::List<int> test;

  test.push_back(21);
  test.push_back(42);
  test.push_back(42);
  test.push_back(42);
  test.push_back(42);
  test.push_back(42);
  test.push_back(42);
  test.push_back(33);
  int i = 0;
  for (ft::List<int>::iterator it = test.begin(); it != test.end(); it++) {
    if (i > 50)
      break;
    i++;
    PRINT(*it);
  }

}