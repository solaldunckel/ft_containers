#include "tests.hpp"

void error(std::string type) {
  std::stringstream ss;

  // ss << "TEST " << g_test << ": error on " << type;
  // g_errors.push(ss.str());
  KO;
  std::cout << "error: " << type;
  
}

template <class T1, class T2>
bool vector_error(T1 &l, T2 &r) {
  std::cerr << "error: got " << r << " expected " << l << std::endl;
  return false;
}

template <class L1, class L2>
bool ITERATE_VECTOR(L1 &lhs, L2 &rhs) {
  typename L1::iterator lit = lhs.begin();
  typename L2::iterator rit = rhs.begin();

  while (lit != lhs.end() || rit != rhs.end()) {
    if (*lit != *rit)
      return vector_error(*lit, *rit);
    lit++;
    rit++;
  }
  if (lit != lhs.end() || rit != rhs.end())
    return false;
  return true;
}

template <class L1, class L2>
bool ITERATE_VECTOR_REV(L1 &lhs, L2 &rhs) {
  typename L1::reverse_iterator lit = lhs.rbegin();
  typename L2::reverse_iterator rit = rhs.rbegin();

  while (lit != lhs.rend() || rit != rhs.rend()) {
    if (*lit != *rit)
      return vector_error(*lit, *rit);
    lit++;
    rit++;
  }
  if (lit != lhs.rend() || rit != rhs.rend())
    return false;
  return true;
}

template <class L1, class L2>
void TEST_VECTOR(L1 &lhs, L2 &rhs, bool rev = false) {
  bool empty = (lhs.empty() == rhs.empty());
  bool size = (lhs.size() == rhs.size());
  bool max_size = (lhs.max_size() == rhs.max_size());
  bool content = false;

  if (rev)
    content = ITERATE_VECTOR_REV(lhs, rhs);
  else
    content = ITERATE_VECTOR(lhs, rhs);

  if (!empty) {
    error("empty");
  }
  else if (!size) {
    error("size");
  }
  else if (!max_size) {
    error("max_size");
  }
  else if (!content) {
    error("content");
  }
  else
    OK;
}

void vector_constructors() {
  std::vector<int> real;
  ft::vector<int> mine;
  TEST_VECTOR(real, mine);

  std::vector<int> real6(5);
  ft::vector<int> mine6(5);

  std::vector<int> real5(4, 100);
  ft::vector<int> mine5(4, 100);
  TEST_VECTOR(real5, mine5);

  std::vector<std::string> real2(12, "test");
  ft::vector<std::string> mine2(12, "test");
  TEST_VECTOR(real2, mine2);

  std::vector<int> ww(55, 68);
  std::vector<int> real3(ww.begin(), ww.end());
  ft::vector<int> mine3(ww.begin(), ww.end());
  TEST_VECTOR(real3, mine3);

  std::vector<std::string> ww2(55, "test");
  std::vector<std::string> real4(ww2.begin(), ww2.end());
  ft::vector<std::string> mine4(ww2.begin(), ww2.end());
  TEST_VECTOR(real4, mine4);

  int myint[] = {0, 1, 2, 3, 4};
  std::vector<int> three(myint, myint + 3); // three ints with a value of 100
  std::vector<int> four(myint, myint + 4);  // two ints with a value of 200
  ft::vector<int> three1(myint, myint + 3); // three ints with a value of 100
  ft::vector<int> four1(myint, myint + 4);  // two ints with a value of 200
  TEST_VECTOR(three, three1);
  TEST_VECTOR(four, four1);
}

void vector_size() {
  std::vector<int> real;
  ft::vector<int> mine;

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
  ft::vector<int> mine;

  TEST(real.max_size(), mine.max_size());

  std::vector<std::string> real2;
  ft::vector<std::string> mine2;

  TEST(real2.max_size(), mine2.max_size());

  std::vector<long int> real3;
  ft::vector<long int> mine3;

  TEST(real3.max_size(), mine3.max_size());
}

void vector_resize() {
  std::vector<int> real;
  ft::vector<int> mine;

  real.resize(32, 12);
  mine.resize(32, 12);

  TEST_VECTOR(real, mine);

  real.resize(12, 24);
  mine.resize(12, 24);

  TEST_VECTOR(real, mine);

  std::vector<int> real2;
  ft::vector<int> mine2;

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

  TEST_VECTOR(real2, mine2);
}

void vector_empty() {
  std::vector<int> real;
  ft::vector<int> mine;

  TEST(real.empty(), mine.empty());

  for (int i=1;i<100;i++) {
    real.push_back(i);
    mine.push_back(i);
  }

  TEST(real.empty(), mine.empty());
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

  real.reserve(122);
  mine.reserve(122);

  TEST(real.capacity(), mine.capacity());
}

void vector_capacity() {
  vector_size();
  vector_max_size();
  vector_resize();
  vector_empty();
  vector_reserve();

  std::vector<int> real;
  ft::vector<int> mine;

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

void vector_access() {
  std::vector<int> real;
  ft::vector<int> mine;

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
  ft::vector<int> mine;
  std::vector<int> real2;
  ft::vector<int> mine2;

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
  TEST_VECTOR(real, mine);
  real.erase(real.begin() + 15, real.end());
  mine.erase(mine.begin() + 15, mine.end());
  TEST_VECTOR(real, mine);
  real.erase(real.begin() + 5);
  mine.erase(mine.begin() + 5);
  TEST_VECTOR(real, mine);
  real.swap(real2);
  mine.swap(mine2);
  TEST_VECTOR(real, mine);
  swap(real, real2);
  swap(mine, mine2);
  TEST_VECTOR(real, mine);
  real.clear();
  mine.clear();
  TEST(real.size(), mine.size());
  TEST_VECTOR(real, mine);
}

void vector_operators() {
  std::vector<int> real;
  std::vector<int> real2;
  ft::vector<int> mine;
  ft::vector<int> mine2;

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
  TEST_VECTOR(real, mine);
}

int test_vector() {
  std::cout << "Vector " << std::endl;

  FCT_TEST("constructors");
  vector_constructors();

  FCT_TEST("capacity");
  vector_capacity();

  FCT_TEST("access");
  vector_access();

  FCT_TEST("modifiers");
  vector_modifiers();

  FCT_TEST("operators");
  vector_operators();

  std::cout << "\n" << std::endl;
  return 0;
}