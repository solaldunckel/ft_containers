#include "tests.h"

void vector_constructors() {
  std::vector<int> real;
  ft::Vector<int> mine;
  ITERATE(real, mine);

  std::vector<int> real6(5);
  ft::Vector<int> mine6(5);

  std::vector<int> real5(4, 100);
  ft::Vector<int> mine5(4, 100);
  ITERATE(real5, mine5);

  std::vector<std::string> real2(12, "test");
  ft::Vector<std::string> mine2(12, "test");
  ITERATE(real2, mine2);

  std::vector<int> ww(55, 68);
  std::vector<int> real3(ww.begin(), ww.end());
  ft::Vector<int> mine3(ww.begin(), ww.end());
  ITERATE(real3, mine3);

  std::vector<std::string> ww2(55, "test");
  std::vector<std::string> real4(ww2.begin(), ww2.end());
  ft::Vector<std::string> mine4(ww2.begin(), ww2.end());
  ITERATE(real4, mine4);

  int myint[] = {0, 1, 2, 3, 4};
  std::vector<int> three(myint, myint + 3); // three ints with a value of 100
  std::vector<int> four(myint, myint + 4);  // two ints with a value of 200
  ft::Vector<int> three1(myint, myint + 3); // three ints with a value of 100
  ft::Vector<int> four1(myint, myint + 4);  // two ints with a value of 200
  ITERATE(three, three1);
  ITERATE(four, four1);
}

void vector_size() {
  std::vector<int> real;
  ft::Vector<int> mine;

  TEST(real.size(), mine.size());
  PUSH_BACK(real, mine, 12);
  PUSH_BACK(real, mine, 24);
  TEST(real.size(), mine.size());
  PUSH_BACK(real, mine, 12);
  PUSH_BACK(real, mine, 24);
  PUSH_BACK(real, mine, 12);
  PUSH_BACK(real, mine, 24);
  TEST(real.size(), mine.size());
}

void vector_max_size() {
  std::vector<int> real;
  ft::Vector<int> mine;

  TEST(real.max_size(), mine.max_size());

  std::vector<std::string> real2;
  ft::Vector<std::string> mine2;

  TEST(real2.max_size(), mine2.max_size());

  std::vector<long int> real3;
  ft::Vector<long int> mine3;

  TEST(real3.max_size(), mine3.max_size());
}

void vector_resize() {
  std::vector<int> real;
  ft::Vector<int> mine;

  real.resize(32, 12);
  mine.resize(32, 12);

  ITERATE(real, mine);

  real.resize(12, 24);
  mine.resize(12, 24);

  ITERATE(real, mine);

  std::vector<int> real2;
  ft::Vector<int> mine2;

  for (int i=1;i<10;i++) {
    real2.push_back(i);
    mine2.push_back(i);
  }

  real2.resize(5);
  real2.resize(8,100);
  real2.resize(12);
  mine2.resize(5);
  mine2.resize(8,100);
  mine2.resize(12);

  ITERATE(real2, mine2);
}

void vector_capacity() {
  std::vector<int> real;
  ft::Vector<int> mine;

  TEST(real.capacity(), mine.capacity());

  for (int i=1;i<100;i++) {
    real.push_back(i);
    mine.push_back(i);
  }

  TEST(real.capacity(), mine.capacity());

  for (int i=1;i<100;i++) {
    real.push_back(i);
    mine.push_back(i);
  }

  TEST(real.capacity(), mine.capacity());
}

void vector_empty() {
  std::vector<int> real;
  ft::Vector<int> mine;

  TEST(real.empty(), mine.empty());

  for (int i=1;i<100;i++) {
    real.push_back(i);
    mine.push_back(i);
  }

  TEST(real.empty(), mine.empty());
}

void vector_reserve() {
  std::vector<int> real;
  ft::Vector<int> mine;

  TEST(real.capacity(), mine.capacity());

  real.reserve(2);
  mine.reserve(2);

  TEST(real.capacity(), mine.capacity());

  real.reserve(125);
  mine.reserve(125);

  TEST(real.capacity(), mine.capacity());

  real.reserve(128);
  mine.reserve(128);

  TEST(real.capacity(), mine.capacity());

  real.reserve(122);
  mine.reserve(122);

  TEST(real.capacity(), mine.capacity());
}

void vector_access() {
  std::vector<int> real;
  ft::Vector<int> mine;

  for (int i=1;i<100;i++) {
    real.push_back(i);
    mine.push_back(i);
  }
  TEST(real[12], mine[12]);
  TEST(real.at(23), mine.at(23));
  TEST(real.front(), mine.front());
  TEST(real.back(), mine.back());
}

void vector_modifiers() {
  std::vector<int> real;
  ft::Vector<int> mine;
  std::vector<int> real2;
  ft::Vector<int> mine2;

  PUSH_BACK(real, mine, 33);
  PUSH_BACK(real, mine, 42);
  PUSH_BACK(real, mine, 63);
  PUSH_BACK(real, mine, 73);
  PUSH_BACK(real, mine, 12);

  TEST(real.back(), mine.back());

  POP_BACK(real, mine);

  TEST(real.back(), mine.back());

  for (int i=1;i<100;i++) {
    PUSH_BACK(real2, mine2, i);
  }
  real.assign(real2.begin(), --real2.end());
  mine.assign(real2.begin(), --real2.end());
  ITERATE(real, mine);
  real.erase(real.begin() + 15, real.end());
  mine.erase(mine.begin() + 15, mine.end());
  ITERATE(real, mine);
  real.erase(real.begin() + 5);
  mine.erase(mine.begin() + 5);
  ITERATE(real, mine);
  real.swap(real2);
  mine.swap(mine2);
  ITERATE(real, mine);
  swap(real, real2);
  swap(mine, mine2);
  ITERATE(real, mine);
  real.clear();
  mine.clear();
  TEST(real.size(), mine.size());
  ITERATE(real, mine);
}

void vector_operators() {
  std::vector<int> real;
  std::vector<int> real2;
  ft::Vector<int> mine;
  ft::Vector<int> mine2;

  PUSH_BACK(real, real2, 15);
  PUSH_BACK(mine, mine2, 15);
  TEST(real == real2, mine == mine2);

  PUSH_BACK(real, mine, 10);
  PUSH_BACK(real2, mine2, 38);
  TEST(real == real2, mine == mine2);
  TEST(real < real2, mine < mine2);

  PUSH_BACK(real, mine, 63);
  PUSH_BACK(real2, mine2, 35);
  TEST(real == real2, mine == mine2);
  TEST(real <= real2, mine <= mine2);
  TEST(real >= real2, mine >= mine2);
  TEST(real != real2, mine != mine2);

  real = real2;
  mine = mine2;
  ITERATE(real, mine);
}

int main() {
  std::cout << "Vector " << std::endl;

  FCT_TEST("constructors");
  vector_constructors();

  FCT_TEST("size");
  vector_size();

  FCT_TEST("max_size");
  vector_max_size();

  FCT_TEST("resize");
  vector_resize();

  FCT_TEST("empty");
  vector_empty();

  FCT_TEST("reserve");
  vector_reserve();

  FCT_TEST("access");
  vector_access();

  FCT_TEST("modifiers");
  vector_modifiers();

  FCT_TEST("operators");
  vector_operators();

  std::cout << std::endl;
}