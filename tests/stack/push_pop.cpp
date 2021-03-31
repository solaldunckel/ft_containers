# include "tests.h"

int main() {
  NAMESPACE::stack<int> st;

  st.push(18);
  TEST_STACK_QUEUE(st);
  std::cout << st.top() << std::endl;

  int i = 0;
  while (i < 12) {
    st.push(i*i);
    i++;
  }

  st.top() = 5;
  std::cout << st.top() << std::endl;

  TEST_STACK_QUEUE(st);
  while (!st.empty()) {
    std::cout << st.top() << std::endl;
    TEST_STACK_QUEUE(st);
    st.pop();
  }
  return 0;
}