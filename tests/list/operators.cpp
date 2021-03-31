# include "tests.h"

int main() {
  NAMESPACE::list<int> list1;
  NAMESPACE::list<int> list2;

  TEST_OP(list1, list2);
  list1.push_back(18);
  TEST_OP(list1, list2);
  list2.push_back(12);
  list2.pop_back();
  list2.push_back(19);
  TEST_OP(list1, list2);
  list2.pop_back();
  list2.push_back(18);
  TEST_OP(list1, list2);
  return 0;
}