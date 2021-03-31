# include "tests.h"

int main() {
  NAMESPACE::list<int> list;
  NAMESPACE::list<int> list2(5);
  NAMESPACE::list<int> list3(4, 100);
  NAMESPACE::list<std::string> list4(12, "test");
  std::list<int> ww(13, 68);
  NAMESPACE::list<int> list5(ww.begin(), ww.end());
  std::list<std::string> ww2(13, "test");
  NAMESPACE::list<std::string> list6(ww2.begin(), ww2.end());

  // constructors used in the same order as described above:
  NAMESPACE::list<int> first;                                // empty list of ints
  NAMESPACE::list<int> second (4,100);                       // four ints with value 100
  NAMESPACE::list<int> third (second.begin(),second.end());  // iterating through second
  NAMESPACE::list<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  NAMESPACE::list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  TEST_LIST(list);
  TEST_LIST(list2);
  TEST_LIST(list3);
  TEST_LIST(list4);
  TEST_LIST(list5);
  TEST_LIST(list6);
  TEST_LIST(fifth);
  return 0;
}