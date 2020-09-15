#include "tests.h"

void queue_constructors() {
  std::queue<int> real;
  ft::queue<int> mine;

  std::queue<std::string> real2;
  ft::queue<std::string> mine2;
}

void queue_empty() {
  std::queue<int> real;
  ft::queue<int> mine;

  TEST(real.empty(), mine.empty());

  PUSH(real, mine, 18);
  TEST(real.empty(), mine.empty());
}

void queue_size() {
  std::queue<int> real;
  ft::queue<int> mine;

  PUSH(real, mine, 15);
  TEST(real.size(), mine.size());

  PUSH(real, mine, 18);
  PUSH(real, mine, 18);
  TEST(real.size(), mine.size());
}

void queue_back() {
  std::queue<int> real;
  ft::queue<int> mine;

  PUSH(real, mine, 15);
  TEST(real.back(), mine.back());

  PUSH(real, mine, 18);
  TEST(real.back(), mine.back());
}

void queue_pop() {
  std::queue<int> real;
  ft::queue<int> mine;

  PUSH(real, mine, 15);
  POP(real, mine);
  TEST(real.empty(), mine.empty());
}

void queue_operators() {
  std::queue<int> real;
  std::queue<int> real1;
  ft::queue<int> mine;
  ft::queue<int> mine1;

  PUSH(real, real1, 15);
  real.push(22);
  real1.push(23);

  PUSH(mine, mine1, 15);
  mine.push(22);
  mine1.push(23);

  TEST(real == real1, mine == mine1);
  TEST(real != real1, mine != mine1);
  TEST(real < real1, mine < mine1);
  TEST(real > real1, mine > mine1);
  TEST(real <= real1, mine <= mine1);
  TEST(real >= real1, mine >= mine1);
}

int main() {
  std::cout << "queue " << std::endl;

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