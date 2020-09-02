#include "tests.h"

void vector_constructors() {
  std::vector<int> real;
  ft::Vector<int> mine;

}

void vector_reserve() {
  std::vector<int> real;
  ft::Vector<int> mine;

  real.reserve(0);
  mine.reserve(0);

  TEST(real.capacity(), mine.capacity());

  real.reserve(2);
  mine.reserve(2);

  TEST(real.capacity(), mine.capacity());

  real.reserve(125);
  mine.reserve(125);

  TEST(real.capacity(), mine.capacity());

  real.reserve(3333);
  mine.reserve(3333);

  TEST(real.capacity(), mine.capacity());

}

int main() {
  std::cout << "Vector " << std::endl;

  FCT_TEST("constructors");
  vector_constructors();

  FCT_TEST("reserve");
  vector_reserve();

  std::cout << std::endl;
}