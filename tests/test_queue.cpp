#include "tests.h"

void queue_constructors() {
  ft::Queue<int> mine;

  mine.push(12);
  mine.push(24);

  ft::Queue<int> mine2(mine);

  TEST(mine2.size(), size_t(2));
  TEST(mine2.back(), 24);
}

void queue_empty() {
  ft::Queue<int> mine;

  TEST(mine.empty(), true);

  mine.push(12);
  TEST(mine.empty(), false);
}

void queue_size() {
  ft::Queue<int> mine;

  mine.push(15);
  TEST(mine.size(), size_t(1));

  mine.push(15);
  mine.push(15);
  mine.push(15);
  mine.push(15);
  TEST(mine.size(), size_t(5));
}

void queue_back() {
  ft::Queue<int> mine;

  mine.push(15);
  TEST(mine.back(), 15);

  mine.push(18);
  mine.push(24);
  TEST(mine.back(), 24);
}

void queue_pop() {
  ft::Queue<int> mine;

  mine.push(15);
  mine.push(24);
  mine.pop();
  TEST(mine.back(), 24);
  mine.pop();
  TEST(mine.empty(), true);
}

void queue_operators() {
  std::queue<int> real;
  std::queue<int> real2;

  ft::Queue<int> mine;
  ft::Queue<int> mine2;

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
  std::cout << "Queue " << std::endl;

  FCT_TEST("constructors");
  queue_constructors();

  FCT_TEST("empty");
  queue_empty();

  FCT_TEST("size");
  queue_size();

  FCT_TEST("back");
  queue_back();

  FCT_TEST("pop");
  queue_pop();

  FCT_TEST("operators");
  queue_operators();
  std::cout << std::endl;
}