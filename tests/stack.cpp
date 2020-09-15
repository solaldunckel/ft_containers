#include "tests.h"

void stack_constructors() {
  std::stack<int> real;
  ft::stack<int> mine;

  std::stack<std::string> real2;
  ft::stack<std::string> mine2;
}

void stack_empty() {
  std::stack<int> real;
  ft::stack<int> mine;

  TEST(real.empty(), mine.empty());

  PUSH(real, mine, 18);
  TEST(real.empty(), mine.empty());
}

void stack_size() {
  std::stack<int> real;
  ft::stack<int> mine;

  PUSH(real, mine, 15);
  TEST(real.size(), mine.size());

  PUSH(real, mine, 18);
  PUSH(real, mine, 18);
  TEST(real.size(), mine.size());
}

void stack_top() {
  std::stack<int> real;
  ft::stack<int> mine;

  PUSH(real, mine, 15);
  TEST(real.top(), mine.top());

  PUSH(real, mine, 18);
  TEST(real.top(), mine.top());
}

void stack_pop() {
  std::stack<int> real;
  ft::stack<int> mine;

  PUSH(real, mine, 15);
  POP(real, mine);
  TEST(real.empty(), mine.empty());
}

void stack_operators() {

}

int main() {
  std::cout << "stack " << std::endl;

  FCT_TEST("constructors");
  stack_constructors();

  FCT_TEST("empty");
  stack_empty();

  FCT_TEST("size");
  stack_size();

  FCT_TEST("top");
  stack_top();

  FCT_TEST("pop");
  stack_pop();

  FCT_TEST("operators");
  stack_operators();
  std::cout << std::endl;
}