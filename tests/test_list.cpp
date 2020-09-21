#include "tests.h"

void list_constructors() {
  std::list<int> real;
  ft::List<int> mine;
  ITERATE(real, mine);

  std::list<int> real6(5);
  ft::List<int> mine6(5);

  std::list<int> real5(4, 100);
  ft::List<int> mine5(4, 100);
  ITERATE(real5, mine5);

  std::list<std::string> real2(12, "test");
  ft::List<std::string> mine2(12, "test");
  ITERATE(real2, mine2);

  std::list<int> ww(55, 68);
  std::list<int> real3(ww.begin(), ww.end());
  ft::List<int> mine3(ww.begin(), ww.end());
  ITERATE(real3, mine3);

  std::list<std::string> ww2(55, "test");
  std::list<std::string> real4(ww2.begin(), ww2.end());
  ft::List<std::string> mine4(ww2.begin(), ww2.end());
  ITERATE(real4, mine4);
}

void list_push_front() {
  std::list<std::string> real;
  ft::List<std::string> mine;

  PUSH_FRONT(real, mine, "test");
  TEST(real.front(), mine.front());
  TEST(real.back(), mine.back());
  PUSH_FRONT(real, mine, "mdr");
  PUSH_FRONT(real, mine, "lol");
  PUSH_FRONT(real, mine, "wtf");
  TEST(real.front(), mine.front());
  TEST(real.back(), mine.back());
  ITERATE(real, mine);
  ITERATE_REV(real, mine);
}

void list_push_back() {
  std::list<std::string> real;
  ft::List<std::string> mine;

  PUSH_BACK(real, mine, "test");
  TEST(real.front(), mine.front());
  TEST(real.back(), mine.back());
  PUSH_BACK(real, mine, "mdr");
  PUSH_BACK(real, mine, "lol");
  PUSH_BACK(real, mine, "wtf");
  TEST(real.front(), mine.front());
  TEST(real.back(), mine.back());
  ITERATE(real, mine);
  ITERATE_REV(real, mine);
}

void list_size() {
  std::list<int> real;
  ft::List<int> mine;

  TEST(real.size(), mine.size());
  PUSH_BACK(real, mine, 12);
  PUSH_BACK(real, mine, 24);
  PUSH_FRONT(real, mine, 16);
  PUSH_BACK(real, mine, 5);
  real.pop_back();
  mine.pop_back();
  TEST(real.size(), mine.size());
  real.clear();
  mine.clear();
  TEST(real.size(), mine.size());
  PUSH_BACK(real, mine, 5);
  TEST(real.size(), mine.size());
}

void list_empty() {
  std::list<int> real;
  ft::List<int> mine;

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
  ft::List<int> mine;

  TEST(real.max_size(), mine.max_size());

  std::list<std::string> real2;
  ft::List<std::string> mine2;
  TEST(real2.max_size(), mine2.max_size());

  std::list<std::list<int> > real3;
  ft::List<std::list<int> > mine3;
  TEST(real3.max_size(), mine3.max_size());

  std::list<char> real4;
  ft::List<char> mine4;
  TEST(real4.max_size(), mine4.max_size());
}

void list_erase() {
  std::list<int> real;
  ft::List<int> mine;
  std::list<int>::iterator real_it;
  ft::List<int>::iterator my_it;

  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 3);
  real_it = real.erase(real.begin());
  my_it = mine.erase(mine.begin());
  TEST(*real_it, *my_it);
  real_it = real.erase(real.begin());
  my_it = mine.erase(mine.begin());
  TEST(*real_it, *my_it);
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
  ft::List<int> mine;

  PUSH_BACK(real, mine, 36);

  real.sort();
  mine.sort();
  ITERATE(real, mine);

  PUSH_BACK(real, mine, 0);
  PUSH_BACK(real, mine, 1);
  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 0);

  real.sort();
  mine.sort();
  ITERATE(real, mine);

  PUSH_BACK(real, mine, 36);
  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 0);
  PUSH_BACK(real, mine, 18);
  PUSH_BACK(real, mine, 17);

  real.sort();
  mine.sort();

  ITERATE(real, mine);

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

  ITERATE(real, mine);

  std::list<std::string> real2;
  ft::List<std::string> mine2;
  PUSH_BACK(real2, mine2, "test");
  PUSH_BACK(real2, mine2, "Test");
  PUSH_BACK(real2, mine2, "LOL");
  PUSH_BACK(real2, mine2, "Lol");
  PUSH_BACK(real2, mine2, "LOL");

  real2.sort(compare_nocase);
  mine2.sort(compare_nocase);
  ITERATE(real2, mine2);
}

void list_remove() {
  std::list<int> real;
  ft::List<int> mine;

  PUSH_BACK(real, mine, 5);
  real.remove(3);
  mine.remove(3);

  real.remove(5);
  mine.remove(5);

  ITERATE(real, mine);

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

  ITERATE(real, mine);

  PUSH_FRONT(real, mine, 5);
  PUSH_BACK(real, mine, 4);
  PUSH_BACK(real, mine, 17);
  PUSH_BACK(real, mine, 20);
  PUSH_BACK(real, mine, 5);

  real.remove(5);
  mine.remove(5);

  ITERATE(real, mine);
}

void list_unique() {
  std::list<int> real;
  ft::List<int> mine;

  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 5);

  real.unique();
  mine.unique();

  ITERATE(real, mine);

  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 5);
  PUSH_BACK(real, mine, 5);

  real.unique();
  mine.unique();

  ITERATE(real, mine);

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

  ITERATE(real, mine);
}

void list_splice() {
  std::list<int> real;
  ft::List<int> mine;

  PUSH_BACK(real, mine, 2);
  PUSH_BACK(real, mine, 4);
  PUSH_BACK(real, mine, 8);
  PUSH_BACK(real, mine, 16);
  PUSH_BACK(real, mine, 32);

  std::list<int> real_sp(real.begin(), real.end());
  ft::List<int> mine_sp(mine.begin(), mine.end());

  real.splice(--real.end(), real_sp);
  mine.splice(--mine.end(), mine_sp);

  if (real_sp.size() == mine_sp.size())
    ITERATE(real, mine);
  else
    KO;
}

void list_reverse() {
  std::list<int> real;
  ft::List<int> mine;

  int i = 0;

  PUSH_BACK(real, mine, 1);
  PUSH_BACK(real, mine, 2);
  real.reverse();
  mine.reverse();
  ITERATE(real, mine);

  while (i < 100) {
    PUSH_BACK(real, mine, i);
    i++;
  }
  real.reverse();
  mine.reverse();

  ITERATE(real, mine);
  ITERATE_REV(real, mine);

  real.reverse();
  mine.reverse();

  ITERATE(real, mine);
  ITERATE_REV(real, mine);
}

void list_merge() {
  std::list<int> real;
  std::list<int> real2;
  ft::List<int> mine;
  ft::List<int> mine2;

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

  ITERATE(real, mine);

  real.clear();
  mine.clear();

  real.push_back(2);
  real2.push_back(3);

  mine.push_back(2);
  mine2.push_back(3);

  real.merge(real2);
  mine.merge(mine2);

  ITERATE(real, mine);
}

void list_swap() {
  std::list<int> real;
  std::list<int> real2;
  ft::List<int> mine;
  ft::List<int> mine2;

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

  ITERATE(real, mine);
  ITERATE(real2, mine2);

  real.clear();
  mine.clear();

  real.push_back(2);
  real2.push_back(3);

  mine.push_back(2);
  mine2.push_back(3);

  swap(real, real2);
  swap(mine, mine2);

  ITERATE(real, mine);
  ITERATE(real2, mine2);
}

void list_iterators() {
  std::list<int> real;
  ft::List<int> mine;
  std::list<int>::iterator it_real;
  ft::List<int>::iterator it_mine;

  TEST(*real.begin(), *mine.begin());
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
  ft::List<int> mine_sp(mine.begin(), mine.end());

  it_real = real_sp.begin();
  it_mine = mine.begin();

  real.splice(++real.begin(), real_sp);
  mine.splice(++mine.begin(), mine_sp);

  TEST(*it_real, *it_mine);

  std::list<int>::const_iterator cit_real = real.begin();
  ft::List<int>::const_iterator cit_mine = mine.begin();
  TEST(*(++cit_real), *(++cit_mine));
}

void list_operators() {
  std::list<int> real;
  std::list<int> real2;
  ft::List<int> mine;
  ft::List<int> mine2;

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
  std::cout << "List " << std::endl;

  FCT_TEST("constructors");
  list_constructors();

  FCT_TEST("push_front");
  list_push_front();

  FCT_TEST("push_back");
  list_push_back();

  FCT_TEST("size");
  list_size();

  FCT_TEST("empty");
  list_empty();

  FCT_TEST("max_size");
  list_max_size();

  FCT_TEST("erase");
  list_erase();

  FCT_TEST("sort");
  list_sort();

  FCT_TEST("remove");
  list_remove();

  FCT_TEST("unique");
  list_unique();

  FCT_TEST("splice");
  list_splice();

  FCT_TEST("reverse");
  list_reverse();

  FCT_TEST("merge");
  list_merge();

  FCT_TEST("swap");
  list_swap();

  FCT_TEST("iterators");
  list_iterators();

  FCT_TEST("operators");
  list_operators();

  std::cout << std::endl;
}