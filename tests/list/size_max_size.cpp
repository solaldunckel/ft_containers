# include "tests.h"

int main() {
  NAMESPACE::list<size_t> list;
  NAMESPACE::list<char>   list2;
  NAMESPACE::list<long long>   list3;

  TEST_LIST(list);
  TEST_LIST(list2);
  TEST_LIST(list3);
  return 0;
}