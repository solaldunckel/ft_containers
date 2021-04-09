#include "tests.hpp"

template <class L1, class L2>
bool ITERATE_LIST(L1 &lhs, L2 &rhs) {
  typename L1::iterator lit = lhs.begin();
  typename L2::iterator rit = rhs.begin();

  while (lit != lhs.end() || rit != rhs.end()) {
    if (*lit != *rit)
      return false;
    lit++;
    rit++;
  }
  if (lit != lhs.end() || rit != rhs.end())
    return false;
  return true;
}

template <class L1, class L2>
bool ITERATE_LIST_REV(L1 &lhs, L2 &rhs) {
  typename L1::reverse_iterator lit = lhs.rbegin();
  typename L2::reverse_iterator rit = rhs.rbegin();

  while (lit != lhs.rend() || rit != rhs.rend()) {
    if (*lit != *rit)
      return false;
    lit++;
    rit++;
  }
  if (lit != lhs.rend() || rit != rhs.rend())
    return false;
  return true;
}

template <class L1, class L2>
void TEST_LIST(L1 &lhs, L2 &rhs, bool rev = false) {
  bool empty = lhs.empty() == rhs.empty();
  bool size = lhs.size() == rhs.size();
  bool max_size = lhs.max_size() == rhs.max_size();
  bool content = false;

  if (rev)
    content = ITERATE_LIST_REV(lhs, rhs);
  else
    content = ITERATE_LIST(lhs, rhs);

  if (empty && size && max_size && content)
    OK;
  else
    KO;
}

void list_constructors() {
  std::list<int> real;
  ft::list<int> mine;
  TEST_LIST(real, mine);

  std::list<int> real6(5);
  ft::list<int> mine6(5);

  std::list<int> real5(4, 100);
  ft::list<int> mine5(4, 100);
  TEST_LIST(real5, mine5);

  std::list<std::string> real2(12, "test");
  ft::list<std::string> mine2(12, "test");
  TEST_LIST(real2, mine2);

  std::list<int> ww(55, 68);
  std::list<int> real3(ww.begin(), ww.end());
  ft::list<int> mine3(ww.begin(), ww.end());
  TEST_LIST(real3, mine3);

  std::list<std::string> ww2(55, "test");
  std::list<std::string> real4(ww2.begin(), ww2.end());
  ft::list<std::string> mine4(ww2.begin(), ww2.end());
  TEST_LIST(real4, mine4);
}

void list_push_front() {
  std::list<std::string> real;
  ft::list<std::string> mine;

  PUSH_FRONT(real, mine, "test");
  TEST(real.front(), mine.front());
  TEST(real.back(), mine.back());
  PUSH_FRONT(real, mine, "mdr");
  PUSH_FRONT(real, mine, "lol");
  PUSH_FRONT(real, mine, "wtf");
  TEST(real.front(), mine.front());
  TEST(real.back(), mine.back());
  TEST_LIST(real, mine);
  TEST_LIST(real, mine, true);
}

void list_push_back() {
  std::list<std::string> real;
  ft::list<std::string> mine;

  PUSH_BACK(real, mine, "test");
  TEST(real.front(), mine.front());
  TEST(real.back(), mine.back());
  PUSH_BACK(real, mine, "mdr");
  PUSH_BACK(real, mine, "lol");
  PUSH_BACK(real, mine, "wtf");
  TEST(real.front(), mine.front());
  TEST(real.back(), mine.back());
  TEST_LIST(real, mine);
  TEST_LIST(real, mine, true);
}

void list_size() {
  std::list<int> real;
  ft::list<int> mine;

  TEST(real.size(), mine.size());
  PUSH_BACK(real, mine, 12);
  PUSH_BACK(real, mine, 24);
  PUSH_FRONT(real, mine, 16);
  PUSH_BACK(real, mine, 5);
  real.pop_back();
  mine.pop_back();
  TEST(real.size(), mine.size());
  int i = 8;
  while (i < 102) {
    PUSH_BACK(real, mine, i);
    i += 2;
  }
  PUSH_BACK(real, mine, 5);
  TEST(real.size(), mine.size());
  real.clear();
  mine.clear();
  TEST(real.size(), mine.size());
  PUSH_BACK(real, mine, 5);
  TEST(real.size(), mine.size());
}

void list_empty() {
  std::list<int> real;
  ft::list<int> mine;

  TEST(real.empty(), mine.empty());
  PUSH_BACK(real, mine, 12);
  real.pop_back();
  mine.pop_back();
  TEST(real.empty(), mine.empty());
  PUSH_BACK(real, mine, 12);
  PUSH_BACK(real, mine, 12);
  TEST(real.empty(), mine.empty());
  real.clear();
  mine.clear();
  TEST(real.empty(), mine.empty());
}

void list_max_size() {
  std::list<int> real;
  ft::list<int> mine;

  TEST(real.max_size(), mine.max_size());

  std::list<std::string> real2;
  ft::list<std::string> mine2;
  TEST(real2.max_size(), mine2.max_size());

  std::list<std::list<int> > real3;
  ft::list<std::list<int> > mine3;
  TEST(real3.max_size(), mine3.max_size());

  std::list<char> real4;
  ft::list<char> mine4;
  TEST(real4.max_size(), mine4.max_size());

  std::list<size_t> real5;
  ft::list<size_t> mine5;
  TEST(real5.max_size(), mine5.max_size());

  std::list<u_char> real6;
  ft::list<u_char> mine6;
  TEST(real6.max_size(), mine6.max_size());
}

void list_erase() {
  std::list<int> real;
  ft::list<int> mine;
  std::list<int>::iterator real_it;
  ft::list<int>::iterator my_it;

  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 3);
  real_it = real.erase(real.begin());
  my_it = mine.erase(mine.begin());
  TEST(*real_it, *my_it);
  real_it = real.erase(real.begin());
  my_it = mine.erase(mine.begin());
  TEST(my_it, mine.end());
}

bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

bool less_than(int &a, int &b) {
	return (a < b);
}

void list_sort() {
  std::list<int> real;
  ft::list<int> mine;

  PUSH_BACK(real, mine, 36);

  real.sort();
  mine.sort();
  TEST_LIST(real, mine);

  PUSH_BACK(real, mine, 0);
  PUSH_BACK(real, mine, 1);
  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 0);

  real.sort();
  mine.sort();
  TEST_LIST(real, mine);

  PUSH_BACK(real, mine, 36);
  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 0);
  PUSH_BACK(real, mine, 18);
  PUSH_BACK(real, mine, 17);

  real.sort();
  mine.sort();

  TEST_LIST(real, mine);

  real.clear();
  mine.clear();

  PUSH_BACK(real, mine, 36);
  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 0);
  PUSH_BACK(real, mine, 18);
  PUSH_BACK(real, mine, 17);

  real.sort(less_than);
  mine.sort(less_than);

  TEST_LIST(real, mine);

  std::list<std::string> real2;
  ft::list<std::string> mine2;
  PUSH_BACK(real2, mine2, "test");
  PUSH_BACK(real2, mine2, "Test");
  PUSH_BACK(real2, mine2, "LOL");
  PUSH_BACK(real2, mine2, "Lol");
  PUSH_BACK(real2, mine2, "LOL");

  real2.sort(compare_nocase);
  mine2.sort(compare_nocase);
  TEST_LIST(real2, mine2);
}

void list_remove() {
  std::list<int> real;
  ft::list<int> mine;

  PUSH_BACK(real, mine, 5);
  real.remove(3);
  mine.remove(3);

  real.remove(5);
  mine.remove(5);

  TEST_LIST(real, mine);

  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 12);
  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 5);

  real.remove(5);
  mine.remove(5);

  TEST_LIST(real, mine);

  PUSH_FRONT(real, mine, 5);
  PUSH_BACK(real, mine, 4);
  PUSH_BACK(real, mine, 17);
  PUSH_BACK(real, mine, 20);
  PUSH_BACK(real, mine, 5);

  real.remove(5);
  mine.remove(5);

  TEST_LIST(real, mine);
}

void list_unique() {
  std::list<int> real;
  ft::list<int> mine;

  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 5);

  real.unique();
  mine.unique();

  TEST_LIST(real, mine);

  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 5);

  real.unique();
  mine.unique();

  TEST_LIST(real, mine);

  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 12);
  PUSH_BACK(real, mine, 15);
  PUSH_BACK(real, mine, 25);
  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 23);
  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 5);

  real.unique();
  mine.unique();

  TEST_LIST(real, mine);
}

void list_splice() {
  std::list<int> real;
  ft::list<int> mine;

  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 4);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 16);
  PUSH_BACK(real, mine, 32);

  std::list<int> real_sp(real.begin(), real.end());
  ft::list<int> mine_sp(mine.begin(), mine.end());

  real.splice(--real.end(), real_sp);
  mine.splice(--mine.end(), mine_sp);

  if (real_sp.size() == mine_sp.size())
    TEST_LIST(real, mine);
  else
    KO;
}

void list_reverse() {
  std::list<int> real;
  ft::list<int> mine;

  int i = 0;

  PUSH_BACK(real, mine, 1);
  PUSH_BACK(real, mine, 2);
  real.reverse();
  mine.reverse();
  TEST_LIST(real, mine);

  while (i < 100) {
    PUSH_BACK(real, mine, i);
    i++;
  }
  real.reverse();
  mine.reverse();

  TEST_LIST(real, mine);
  TEST_LIST(real, mine, true);

  real.reverse();
  mine.reverse();

  TEST_LIST(real, mine);
  TEST_LIST(real, mine, true);
}

void list_merge() {
  std::list<int> real;
  std::list<int> real2;
  ft::list<int> mine;
  ft::list<int> mine2;

  real.push_back(3);
  real.push_back(5);
  real.push_back(8);
  real.push_back(12);

  real2.push_back(7);
  real2.push_back(4);
  real2.push_back(7);
  real2.push_back(13);

  mine.push_back(3);
  mine.push_back(5);
  mine.push_back(8);
  mine.push_back(12);

  mine2.push_back(7);
  mine2.push_back(4);
  mine2.push_back(7);
  mine2.push_back(13);

  real.merge(real2);
  mine.merge(mine2);

  TEST_LIST(real, mine);

  real.clear();
  mine.clear();

  real.push_back(2);
  real2.push_back(3);

  mine.push_back(2);
  mine2.push_back(3);

  real.merge(real2);
  mine.merge(mine2);

  TEST_LIST(real, mine);
}

void list_swap() {
  std::list<int> real;
  std::list<int> real2;
  ft::list<int> mine;
  ft::list<int> mine2;

  real.push_back(3);
  real.push_back(5);
  real.push_back(8);
  real.push_back(12);

  real2.push_back(7);
  real2.push_back(4);
  real2.push_back(7);
  real2.push_back(13);

  mine.push_back(3);
  mine.push_back(5);
  mine.push_back(8);
  mine.push_back(12);

  mine2.push_back(7);
  mine2.push_back(4);
  mine2.push_back(7);
  mine2.push_back(13);

  real.swap(real2);
  mine.swap(mine2);

  TEST_LIST(real, mine);
  TEST_LIST(real2, mine2);

  real.clear();
  mine.clear();

  real.push_back(2);
  real2.push_back(3);

  mine.push_back(2);
  mine2.push_back(3);

  swap(real, real2);
  swap(mine, mine2);

  TEST_LIST(real, mine);
  TEST_LIST(real2, mine2);
}

void list_iterators() {
  std::list<int> real;
  ft::list<int> mine;
  std::list<int>::iterator it_real;
  ft::list<int>::iterator it_mine;

  PUSH_BACK(real, mine, 7);
  TEST(*(++real.end()), *(++mine.end()));
  TEST(*(--real.rend()), *(--mine.rend()));

  PUSH_BACK(real, mine, 9);
  PUSH_BACK(real, mine, 12);
  PUSH_BACK(real, mine, 3);
  it_real = real.begin();
  it_mine = mine.begin();
  real.sort();
  mine.sort();

  TEST(*it_real, *it_mine);

  std::list<int> real_sp(real.begin(), real.end());
  ft::list<int> mine_sp(mine.begin(), mine.end());

  it_real = real_sp.begin();
  it_mine = mine.begin();

  real.splice(++real.begin(), real_sp);
  mine.splice(++mine.begin(), mine_sp);

  TEST(*it_real, *it_mine);

  std::list<int>::const_iterator cit_real = real.begin();
  ft::list<int>::const_iterator cit_mine = mine.begin();
  TEST(*(++cit_real), *(++cit_mine));
}

void list_operators() {
  std::list<int> real;
  std::list<int> real2;
  ft::list<int> mine;
  ft::list<int> mine2;

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
  TEST_LIST(real, mine);
}

template <typename T>
inline bool binaryPredicateTest(const T& a, const T& b) { return a < b; } // Inline keywork to avoid duplicate symbol error

int test_list() {
  std::cout << "List " << std::endl;

  const int arrInt[20] = {58966, 2147483647, 256, -2147483648, 0, 
                            -1, 2, 3, 4, 5, 6, 7, 7, 8, 54634152, 9, 
                            10, 11, 56, 56465};

  ft::list<int> test;

  for (int i = 0; i < 20; i++) {
    test.push_back(arrInt[i]);
  }

  std::cout << "\nBEFORE" << std::endl;
  for (ft::list<int>::iterator it = test.begin(); it != test.end(); it++) {
    std::cout << *it << std::endl;
  }

  test.unique();

  std::cout << "\nAFTER" << std::endl;

  for (ft::list<int>::iterator it = test.begin(); it != test.end(); it++) {
    std::cout << *it << std::endl;
  }

  std::list<int> test2;

  for (int i = 0; i < 20; i++) {
    test2.push_back(arrInt[i]);
  }

  std::cout << "\nBEFORE" << std::endl;

  for (std::list<int>::iterator it = test2.begin(); it != test2.end(); it++) {
    std::cout << *it << std::endl;
  }

  test2.unique();

  std::cout << "\nAFTER" << std::endl;

  for (std::list<int>::iterator it = test2.begin(); it != test2.end(); it++) {
    std::cout << *it << std::endl;
  }

  // FCT_TEST("constructors");
  // list_constructors();

  // FCT_TEST("push_front");
  // list_push_front();

  // FCT_TEST("push_back");
  // list_push_back();

  // FCT_TEST("size");
  // list_size();

  // FCT_TEST("empty");
  // list_empty();

  // FCT_TEST("max_size");
  // list_max_size();

  // FCT_TEST("erase");
  // list_erase();

  // FCT_TEST("sort");
  // list_sort();

  // FCT_TEST("remove");
  // list_remove();

  // FCT_TEST("unique");
  // list_unique();

  // FCT_TEST("splice");
  // list_splice();

  // FCT_TEST("reverse");
  // list_reverse();

  // FCT_TEST("merge");
  // list_merge();

  // FCT_TEST("swap");
  // list_swap();

  // FCT_TEST("iterators");
  // list_iterators();

  // FCT_TEST("operators");
  // list_operators();

  std::cout << "\n" << std::endl;
  return 1;
}