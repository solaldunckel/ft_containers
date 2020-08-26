#include "tests.h"

void list_constructors() {
  std::list<int> real;
  ft::List<int> mine;
  test(real.size(), mine.size());
  real.push_front(2);
  mine.push_front(2);
  test(real.front(), mine.front());

  std::list<std::string> real2(12, "test");
  ft::List<std::string> mine2(12, "test");
  // printf("test\n");
  test_debug(real2.size(), mine2.size());
  test_debug(real2.front(), mine2.front());

  std::list<int> ww(55, 68);
  std::list<int> real3(ww.begin(), ww.end());
  ft::List<int> mine3(ww.begin(), ww.end());
  test(real3.size(), mine3.size());
  test(real3.back(), mine3.back());

  // std::list<std::string> ww2(55, "test");
  // std::list<std::string> real4(ww2.begin(), ww2.end());
  // ft::List<std::string> mine4(ww2.begin(), ww2.end());
  // test(real4.size(), mine4.size());
  // test(real4.back(), mine4.back());
}

void list_size() {
  std::list<int> real;
  ft::List<int> mine;

  test(real.size(), mine.size());
  real.push_back(12);
  real.push_back(24);
  real.push_front(16);
  real.push_back(5);
  real.pop_back();
  mine.push_back(12);
  mine.push_back(24);
  mine.push_front(16);
  mine.push_back(5);
  mine.pop_back();
  test(real.size(), mine.size());
  real.clear();
  mine.clear();
  test(real.size(), mine.size());
  real.push_back(5);
  mine.push_back(5);
  test(real.size(), mine.size());
}

void list_empty() {
  std::list<int> real;
  ft::List<int> mine;

  test(real.empty(), mine.empty());
  real.push_back(12);
  real.pop_back();
  mine.push_back(12);
  mine.pop_back();
  test(real.empty(), mine.empty());
  real.push_back(12);
  mine.push_back(12);
  real.push_back(12);
  mine.push_back(12);
  test(real.empty(), mine.empty());
  real.clear();
  mine.clear();
  test(real.empty(), mine.empty());
}

void list_push_front() {
  std::list<int> real;
  ft::List<int> mine;

  real.push_front(12);
  real.push_front(24);
  mine.push_front(12);
  mine.push_front(24);
  // test(real.front(), mine.front());
  // real.push_front(12);
  // real.push_front(24);
  // mine.push_front(12);
  // mine.push_front(24);
  // real.push_front(12);
  // real.push_front(36);
  // mine.push_front(12);
  // mine.push_front(36);
  test_debug(real.front(), mine.front());
  // for (ft::List<int>::iterator it = mine.begin(); it != mine.end(); it++) {
  //   PRINT(*it);
  // }
  // for (std::list<int>::iterator it = real.begin(); it != real.end(); it++) {
  //   PRINT(*it);
  // }
  test_iterate(real.rbegin(), real.rend(), mine.rbegin(), mine.rend());
}

void list_push_back() {
  std::list<int> real;
  ft::List<int> mine;

  real.push_back(12);
  real.push_back(24);
  mine.push_back(12);
  mine.push_back(24);
  test(real.back(), mine.back());
  real.push_back(12);
  real.push_back(24);
  mine.push_back(12);
  mine.push_back(24);
  real.push_back(12);
  real.push_back(36);
  mine.push_back(12);
  mine.push_back(36);
  test(real.back(), mine.back());
  // test_iterate(real, mine);
}

void list_max_size() {
  std::list<int> real;
  ft::List<int> mine;

  test(real.max_size(), mine.max_size());

  std::list<std::string> real2;
  ft::List<std::string> mine2;
  test(real2.max_size(), mine2.max_size());

  std::list<std::list<int> > real3;
  ft::List<std::list<int> > mine3;
  test(real3.max_size(), mine3.max_size());
}

void test_list() {
  std::cout << "List " << std::endl;

  // FCT_TEST("constructors");
  // list_constructors();
  FCT_TEST("push_front / pop_front");
  list_push_front();
  // FCT_TEST("push_back / pop_back");
  // list_push_front();
  // FCT_TEST("size");
  // list_size();
  // FCT_TEST("empty");
  // list_empty();
  // FCT_TEST("max_size");
  // list_max_size();
  std::cout << std::endl;
}