#include "tests.hpp"

template <class L1, class L2>
bool ITERATE_MAP(L1 &lhs, L2 &rhs) {
  typename L1::iterator lit = lhs.begin();
  typename L2::iterator rit = rhs.begin();

  while (lit != lhs.end() || rit != rhs.end()) {
    if (lit->second != rit->second)
      return false;
    lit++;
    rit++;
  }
  if (lit != lhs.end() || rit != rhs.end())
    return false;
  return true;
}

template <class L1, class L2>
bool ITERATE_MAP_REV(L1 &lhs, L2 &rhs) {
  typename L1::reverse_iterator lit = lhs.rbegin();
  typename L2::reverse_iterator rit = rhs.rbegin();

  while (lit != lhs.rend() || rit != rhs.rend()) {
    if (lit->second != rit->second)
      return false;
    lit++;
    rit++;
  }
  if (lit != lhs.rend() || rit != rhs.rend())
    return false;
  return true;
}

template <class L1, class L2>
void TEST_MAP(L1 &lhs, L2 &rhs, bool rev = false) {
  bool empty = lhs.empty() == rhs.empty();
  bool size = lhs.size() == rhs.size();
  bool max_size = lhs.max_size() == rhs.max_size();
  bool content = false;

  if (rev)
    content = ITERATE_MAP_REV(lhs, rhs);
  else
    content = ITERATE_MAP(lhs, rhs);

  if (!empty) {
    KO;
  }
  else if (!size) {
    KO;
  }
  else if (!max_size) {
    KO;
  }
  else if (!content) {
    KO;
  }
  else
    OK;
}

void map_constructors() {
  std::map<char, int> real;
  ft::map<char, int> mine;

  real['a'] = 10;
  real['b'] = 30;
  real['c'] = 50;
  real['d'] = 70;

  mine['a'] = 10;
  mine['b'] = 30;
  mine['c'] = 50;
  mine['d'] = 70;

  std::map<char, int> real2(real.begin(), real.end());
  ft::map<char, int> mine2(mine.begin(), mine.end());

  std::map<char, int> real3(real2);
  ft::map<char, int> mine3(mine2);

  TEST(real.size(), mine.size());
  TEST(real2.size(), mine2.size());
  TEST(real3.size(), mine3.size());
}

void map_capacity() {
  std::map<char, int> real;
  ft::map<char, int> mine;

  TEST(real.empty(), mine.empty());
  real['a'] = 10;
  real['b'] = 30;
  real['c'] = 50;
  real['d'] = 70;

  mine['a'] = 10;
  mine['b'] = 30;
  mine['c'] = 50;
  mine['d'] = 70;
  TEST(real.empty(), mine.empty());
  TEST(real.size(), mine.size());
  TEST(real.max_size(), mine.max_size());

  std::map<std::string, int> real2;
  ft::map<std::string, int> mine2;
  TEST(real2.max_size(), mine2.max_size());
  std::map<std::string, size_t> real3;
  ft::map<std::string, size_t> mine3;
  TEST(real3.max_size(), mine3.max_size());
}

void map_access() {
  std::map<char, int> real;
  ft::map<char, int> mine;

  real['a'] = 10;
  real['b'] = 30;
  real['c'] = 50;
  real['d'] = 70;
  real['e'] = real['b'];

  mine['a'] = 10;
  mine['b'] = 30;
  mine['c'] = 50;
  mine['d'] = 70;
  mine['e'] = mine['b'];
  TEST(real['a'], mine['a']);
  TEST(real['b'], mine['b']);
  TEST(real['e'], mine['e']);
  TEST(real['g'], mine['g']);
  TEST(real.size(), mine.size());
}

void map_modifiers() {
  std::map<char, int> real;
  std::map<char, int> real2;
  ft::map<char, int> mine;
  ft::map<char, int> mine2;

  real.insert(std::pair<char, int>('a', 100));
  mine.insert(ft::pair<char, int>('a', 100));
  real.insert(std::pair<char, int>('z', 200));
  mine.insert(ft::pair<char, int>('z', 200));

  std::pair<std::map<char, int>::iterator, bool> ret;
  ret = real.insert(std::pair<char, int>('z', 500));

  ft::pair<ft::map<char, int>::iterator, bool> ret2;
  ret2 = mine.insert(ft::pair<char, int>('z', 500));

  std::map<char, int>::iterator it = real.begin();
  real.insert(it, std::pair<char, int>('b', 300));
  real.insert(it, std::pair<char, int>('c', 400));

  ft::map<char, int>::iterator it2 = mine.begin();
  mine.insert(it2, ft::pair<char, int>('b', 300));
  mine.insert(it2, ft::pair<char, int>('c', 400));

  real2.insert(real.begin(), real.find('c'));
  mine2.insert(mine.begin(), mine.find('c'));
  TEST_MAP(real, mine);
  TEST_MAP(real2, mine2);

  it = real.find('b');
  it2 = mine.find('b');
  real.erase(it);
  mine.erase(it2);

  real.erase('c');
  mine.erase('c');
  TEST_MAP(real, mine);

  it = real.find('e');
  it2 = mine.find('e');

  real.erase(it, real.end());
  mine.erase(it2, mine.end());
  TEST_MAP(real, mine);

  real.swap(real2);
  mine.swap(mine2);
  TEST_MAP(real, mine);

  real.clear();
  mine.clear();
  TEST(real.size(), mine.size());
}

int test_map() {
  std::cout << "Map " << std::endl;

  FCT_TEST("constructors");
  map_constructors();

  FCT_TEST("capacity");
  map_capacity();

  FCT_TEST("access");
  map_access();

  FCT_TEST("modifiers");
  map_modifiers();

  std::cout << "\n" << std::endl;
  return 0;
}