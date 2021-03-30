#include "tests.h"

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
  ITERATE_MAP(real, mine);
  ITERATE_MAP(real2, mine2);

  it = real.find('b');
  it2 = mine.find('b');
  real.erase(it);
  mine.erase(it2);

  real.erase('c');
  mine.erase('c');
  ITERATE_MAP(real, mine);

  it = real.find('e');
  it2 = mine.find('e');

  real.erase(it, real.end());
  mine.erase(it2, mine.end());
  ITERATE_MAP(real, mine);

  real.swap(real2);
  mine.swap(mine2);
  ITERATE_MAP(real, mine);

  real.clear();
  mine.clear();
  TEST(real.size(), mine.size());
}

int main() {
  std::cout << "Map " << std::endl;

  FCT_TEST("constructors");
  map_constructors();

  FCT_TEST("capacity");
  map_capacity();

  FCT_TEST("access");
  map_access();

  FCT_TEST("modifiers");
  map_modifiers();

  std::cout << std::endl;
}