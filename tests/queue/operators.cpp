# include "tests.h"

int main() {
  NAMESPACE::queue<int> st1;
  NAMESPACE::queue<int> st2;

  TEST_OP(st1, st2);
  st1.push(18);
  TEST_OP(st1, st2);
  st2.push(12);
  st2.pop();
  st2.push(19);
  TEST_OP(st1, st2);
  st2.pop();
  st2.push(18);
  TEST_OP(st1, st2);
  return 0;
}