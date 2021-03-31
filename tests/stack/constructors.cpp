# include "tests.h"

int main() {
  NAMESPACE::stack<int> st;

  TEST_STACK_QUEUE(st);

  const NAMESPACE::stack<size_t> st2;

  TEST_STACK_QUEUE(st2);

  NAMESPACE::stack<const std::string> st3;

  TEST_STACK_QUEUE(st3);

  NAMESPACE::stack<int> st4;

  st4.push(12);
  st4.push(24);

  NAMESPACE::stack<int> st5(st4);

  std::cout << st5.top() << std::endl;

  TEST_STACK_QUEUE(st5);
  return 0;
}