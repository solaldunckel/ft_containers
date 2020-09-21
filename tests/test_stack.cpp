#include "tests.h"

void stack_constructors() {
  ft::Stack<int> mine;

  mine.push(12);
  mine.push(24);

  ft::Stack<int> mine2(mine);

  TEST(mine2.size(), size_t(2));
  TEST(mine2.top(), 24);
}

void stack_empty() {
  ft::Stack<int> mine;

  TEST(mine.empty(), true);

  mine.push(12);
  TEST(mine.empty(), false);
}

void stack_size() {
  ft::Stack<int> mine;

  mine.push(15);
  TEST(mine.size(), size_t(1));

  mine.push(15);
  mine.push(15);
  mine.push(15);
  mine.push(15);
  TEST(mine.size(), size_t(5));
}

void stack_top() {
  ft::Stack<int> mine;

  mine.push(15);
  TEST(mine.top(), 15);

  mine.push(18);
  mine.push(24);
  TEST(mine.top(), 24);
}

void stack_pop() {
  ft::Stack<int> mine;

  mine.push(15);
  mine.push(24);
  mine.pop();
  TEST(mine.top(), 15);
  mine.pop();
  TEST(mine.empty(), true);
}

void stack_operators() {
  std::stack<int> real;
  std::stack<int> real2;

  ft::Stack<int> mine;
  ft::Stack<int> mine2;

  PUSH(real, real2, 12);
  PUSH(real, real2, 24);
  PUSH(real, real2, 36);

  PUSH(mine, mine2, 12);
  PUSH(mine, mine2, 24);
  PUSH(mine, mine2, 36);

  TEST(real == real2, mine == mine2);
  real2.push(37);
  mine2.push(37);
  TEST(real == real2, mine == mine2);
  TEST(real < real2, mine < mine2);
  TEST(real > real2, mine > mine2);
  TEST(real != real2, mine != mine2);
  TEST(real <= real2, mine <= mine2);
  TEST(real >= real2, mine >= mine2);
}

int main() {
  std::cout << "Stack " << std::endl;

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