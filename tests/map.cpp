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

void map_iterators() {
  std::map<char, int> real;
  ft::map<char, int> mine;
  std::map<char, int>::iterator it_real;
  ft::map<char, int>::iterator it_mine;

  real['a'] = 10;
  real['d'] = 30;
  real['f'] = 50;

  mine['a'] = 10;
  mine['d'] = 30;
  mine['f'] = 50;

  it_real = real.begin();
  it_mine = mine.begin();

  TEST(it_real->first, it_mine->first);

  real['c'] = 20;
  mine['c'] = 20;

  TEST((++it_real)->first, (++it_mine)->first);
  TEST((++(++it_real))->first, (++(++it_mine))->first);

  it_real = real.end();
  it_mine = mine.end();
  TEST((--it_real)->first, (--it_mine)->first);

  std::map<char, int>::reverse_iterator rit_real;
  ft::map<char, int>::reverse_iterator rit_mine;

  rit_real = real.rbegin();
  rit_mine = mine.rbegin();

  TEST((++rit_real)->first, (++rit_mine)->first);
  TEST((++rit_real)->first, (++rit_mine)->first);

  std::map<char, int>::const_iterator cit_real;
  ft::map<char, int>::const_iterator cit_mine;

  cit_real = real.begin();
  cit_mine = mine.begin();

  TEST(cit_real == real.begin(), cit_mine == mine.begin());
  TEST(cit_real != real.begin(), cit_mine != mine.begin());
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

void map_observers() {
  std::map<char,int> real;
  std::map<char,int>::key_compare realcomp = real.key_comp();

  real['a']=100;
  real['b']=200;
  real['c']=300;

  ft::map<char,int> mine;
  ft::map<char,int>::key_compare minecomp = mine.key_comp();

  mine['a']=100;
  mine['b']=200;
  mine['c']=300;

  char realhighest = real.rbegin()->first;
  char myhighest = mine.rbegin()->first;

  std::map<char,int>::iterator realit = real.begin();
  ft::map<char,int>::iterator myit = mine.begin();
  TEST(realcomp((*realit++).first, realhighest), minecomp((*myit++).first, myhighest));
  TEST(realcomp((*realit++).first, realhighest), minecomp((*myit++).first, myhighest));
  TEST(realcomp((*realit++).first, realhighest), minecomp((*myit++).first, myhighest));
}

void map_operations() {
  std::map<char,int> real;
  std::map<char,int>::iterator it_real;

  real['a']=50;
  real['b']=100;
  real['c']=150;
  real['d']=200;

  it_real = real.find('b');
  if (it_real != real.end())
    real.erase (it_real);

  ft::map<char,int> mine;
  ft::map<char,int>::iterator it_mine;

  mine['a']=50;
  mine['b']=100;
  mine['c']=150;
  mine['d']=200;

  it_mine = mine.find('b');
  if (it_mine != mine.end())
    mine.erase (it_mine);

  TEST_MAP(real, mine);

  std::map<char,int> real2;

  real2['a']=101;
  real2['c']=202;
  real2['f']=303;

  ft::map<char,int> mine2;

  mine2['a']=101;
  mine2['c']=202;
  mine2['f']=303;

  TEST(real2.count('a'), mine2.count('a'));
  TEST(real2.count('b'), mine2.count('b'));
  TEST(real2.count('e'), mine2.count('e'));
  TEST(real2.count('f'), mine2.count('f'));

  std::map<char,int> real3;
  std::map<char,int>::iterator itlow_real, itup_real;

  real3['a']=20;
  real3['b']=40;
  real3['c']=60;
  real3['d']=80;
  real3['e']=100;

  itlow_real=real3.lower_bound ('b');
  itup_real=real3.upper_bound ('d');

  real3.erase(itlow_real,itup_real);

  ft::map<char,int> mine3;
  ft::map<char,int>::iterator itlow_mine, itup_mine;

  mine3['a']=20;
  mine3['b']=40;
  mine3['c']=60;
  mine3['d']=80;
  mine3['e']=100;

  itlow_mine=mine3.lower_bound ('b');
  itup_mine=mine3.upper_bound ('d');

  mine3.erase(itlow_mine,itup_mine);

  TEST_MAP(real3, mine3);

  std::map<char,int> real4;
  std::map<char,int>::iterator itlow_real2,itup_real2;

  real4['a']=20;
  real4['b']=40;
  real4['c']=60;
  real4['d']=80;
  real4['e']=100;

  itlow_real2=real4.lower_bound ('b');
  itup_real2=real4.upper_bound ('d');

  real4.erase(itlow_real2,itup_real2);

  ft::map<char,int> mine4;
  ft::map<char,int>::iterator itlow_mine2,itup_mine2;

  mine4['a']=20;
  mine4['b']=40;
  mine4['c']=60;
  mine4['d']=80;
  mine4['e']=100;

  itlow_mine2=mine4.lower_bound ('b');
  itup_mine2=mine4.upper_bound ('d');

  mine4.erase(itlow_mine2,itup_mine2);

  TEST_MAP(real4, mine4);

  std::map<char,int> real5;

  real5['a']=10;
  real5['b']=20;
  real5['c']=30;

  std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
  ret = real5.equal_range('b');

  ft::map<char,int> mine5;

  mine5['a']=10;
  mine5['b']=20;
  mine5['c']=30;

  ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret2;
  ret2 = mine5.equal_range('b');

  TEST(ret.first->first, ret2.first->first);
  TEST(ret.first->second, ret2.first->second);
  TEST(ret.second->first, ret2.second->first);
  TEST(ret.second->second, ret2.second->second);
}

void map_operators() {
  std::map<int, char> realalice;

  realalice[1] = 'a';
  realalice[2] = 'b';
  realalice[3] = 'c';

  std::map<int, char> realbob;

  realbob[7] = 'Z';
  realbob[8] = 'Y';
  realbob[9] = 'X';
  realbob[10] = 'W';

  std::map<int, char> realeve;

  realeve[1] = 'a';
  realeve[2] = 'b';
  realeve[3] = 'c';

  ft::map<int, char> minealice;

  minealice[1] = 'a';
  minealice[2] = 'b';
  minealice[3] = 'c';

  ft::map<int, char> minebob;

  minebob[7] = 'Z';
  minebob[8] = 'Y';
  minebob[9] = 'X';
  minebob[10] = 'W';

  ft::map<int, char> mineeve;

  mineeve[1] = 'a';
  mineeve[2] = 'b';
  mineeve[3] = 'c';

  TEST(realalice == realbob, minealice == minebob);
  TEST(realalice != realbob, minealice != minebob);
  TEST(realalice < realbob, minealice < minebob);
  TEST(realalice <= realbob, minealice <= minebob);
  TEST(realalice > realbob, minealice > minebob);
  TEST(realalice >= realbob, minealice >= minebob);

  TEST(realalice == realeve, minealice == mineeve);
  TEST(realalice != realeve, minealice != mineeve);
  TEST(realalice < realeve, minealice < mineeve);
  TEST(realalice <= realeve, minealice <= mineeve);
  TEST(realalice > realeve, minealice > mineeve);
  TEST(realalice >= realeve, minealice >= mineeve);
}

int test_map() {
  std::cout << "Map " << std::endl;

  FCT_TEST("constructors");
  map_constructors();

  FCT_TEST("iterators");
  map_iterators();

  FCT_TEST("capacity");
  map_capacity();

  FCT_TEST("access");
  map_access();

  FCT_TEST("modifiers");
  map_modifiers();

  FCT_TEST("observers");
  map_observers();

  FCT_TEST("operations");
  map_operations();

  FCT_TEST("operators");
  map_operators();

  std::cout << "\n" << std::endl;
  return 0;
}