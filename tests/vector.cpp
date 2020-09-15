#include "tests.h"

void vector_constructors() {
  std::vector<int> real;
  ft::vector<int> mine;

}

void vector_reserve() {
  std::vector<int> real;
  ft::vector<int> mine;

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
}

void vector_push_back() {
  std::vector<int> real;
  ft::vector<int> mine;

  PUSH_BACK(real, mine, 23);
  TEST(real.capacity(), mine.capacity());
  PUSH_BACK(real, mine, 18);
  // PUSH_BACK(real, mine, 32);
  // PUSH_BACK(real, mine, 54);
  TEST(real.capacity(), mine.capacity());
  // PUSH_BACK(real, mine, 43);
  TEST(real.capacity(), mine.capacity());
  // PUSH_BACK(real, mine, 7);
  // PUSH_BACK(real, mine, 2);
  // PUSH_BACK(real, mine, 8);
  // PUSH_BACK(real, mine, 14);
  // PUSH_BACK(real, mine, 13);
  // PUSH_BACK(real, mine, 65);
  // PUSH_BACK(real, mine, 78);
  // PUSH_BACK(real, mine, 14);
  // PUSH_BACK(real, mine, 0);
  TEST(real.capacity(), mine.capacity());
  TEST(real.size(), mine.size());
  TEST(real.back(), mine.back());
  TEST(real.front(), mine.front());
  TEST(real[1], mine[1]);
  // TEST(real.at(5), mine.at(5));

  ITERATE(real, mine);

  // mine.insert(mine.begin(), 12);
  // real.insert(real.begin(), 12);
  // ITERATE(real, mine);
  // mine.insert(mine.end(), 4);
  // real.insert(real.end(), 4);
  // ITERATE(real, mine);
  mine.insert(mine.end(), 15);
  real.insert(real.end(), 15);
  mine.insert(mine.end(), 15);
  real.insert(real.end(), 15);
  // mine.erase(mine.begin(), --mine.end());
  // real.erase(real.begin(), --real.end());

  TEST(real.capacity(), mine.capacity());
  TEST(real.size(), mine.size());

  int myint[] = {0, 1, 2, 3, 4};
  std::vector<int> three(myint, myint + 3); // three ints with a value of 100
  std::vector<int> four(myint, myint + 4);  // two ints with a value of 200
  ft::vector<int> three1(myint, myint + 3); // three ints with a value of 100
  ft::vector<int> four1(myint, myint + 4);  // two ints with a value of 200

  // EXPECT_FALSE(foo == bar);
  // EXPECT_TRUE(foo != bar);
  // EXPECT_FALSE(foo > bar);
  // EXPECT_TRUE(foo < bar);
  // EXPECT_FALSE(foo >= bar);
  // EXPECT_TRUE(foo <= bar);
  PRINT_LIST(three);
  PRINT_LIST(four);
  TEST(three < four, three1 < four1);
  three.reserve(50);
  three.clear();
  std::cout << three.capacity() << std::endl;
  // TEST(three > four, three1 > four1);
  // EXPECT_FALSE(three == four);
  // EXPECT_TRUE(three != four);
  // EXPECT_FALSE(three > four);
  // EXPECT_TRUE(three < four);
  // EXPECT_FALSE(three >= four);
  // EXPECT_TRUE(three <= four);

}

int main() {
  std::cout << "Vector " << std::endl;

  // FCT_TEST("constructors");
  // vector_constructors();

  FCT_TEST("reserve");
  vector_reserve();

  FCT_TEST("push_back");
  vector_push_back();

  std::cout << std::endl;
}