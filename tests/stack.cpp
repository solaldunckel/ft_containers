#include "tests.h"

void stack_constructors() {
  std::stack<int> real;
  ft::Stack<int> mine;
}

void stack_size() {
  std::stack<int> real;
  ft::Stack<int> mine;

  PUSH(real, mine, 15);
  TEST(real.size(), mine.size());
}

int main() {
  std::cout << "Stack " << std::endl;

  FCT_TEST("constructors");
  stack_constructors();

  FCT_TEST("size");
  stack_size();
  std::cout << std::endl;
}