# include "tests.h"

int main() {
  NAMESPACE::queue<int> st;

  TEST_STACK_QUEUE(st);

  const NAMESPACE::queue<size_t> st2;

  TEST_STACK_QUEUE(st2);

  NAMESPACE::queue<const std::string> st3;

  TEST_STACK_QUEUE(st3);

  NAMESPACE::queue<int> st4;

  st4.push(12);
  st4.push(24);

  NAMESPACE::queue<int> st5(st4);

  std::cout << st5.back() << std::endl;

  TEST_STACK_QUEUE(st5);
  return 0;
}