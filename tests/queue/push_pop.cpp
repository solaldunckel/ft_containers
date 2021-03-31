# include "tests.h"

int main() {
  NAMESPACE::queue<int> st;

  st.push(18);
  TEST_STACK_QUEUE(st);
  std::cout << st.front() << std::endl;
  std::cout << st.back() << std::endl;

  int i = 0;
  while (i < 12) {
    st.push(i*i+2);
    i++;
  }

  st.front() = 5;
  std::cout << st.front() << std::endl;
  std::cout << st.back() << std::endl;

  TEST_STACK_QUEUE(st);
  while (!st.empty()) {
    std::cout << st.front() << std::endl;
    std::cout << st.back() << std::endl;
    TEST_STACK_QUEUE(st);
    st.pop();
  }
  return 0;
}