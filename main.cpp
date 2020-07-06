#include "Stack.hpp"

#include <iostream>
#include <stack>

int main() {
  std::stack<std::string> real_stack;
  ft::stack<std::string> my_stack;

  std::cout << real_stack.size() << std::endl;
  std::cout << my_stack.size() << std::endl;

  real_stack.push("Hello");
  my_stack.push("Hello");

  std::cout << real_stack.top() << std::endl;
  std::cout << my_stack.top() << std::endl;

  real_stack.push("World");
  my_stack.push("World");

  std::cout << real_stack.top() << std::endl;
  std::cout << my_stack.top() << std::endl;

  std::cout << real_stack.size() << std::endl;
  std::cout << my_stack.size() << std::endl;

  real_stack.pop();
  my_stack.pop();

  std::cout << real_stack.top() << std::endl;
  std::cout << my_stack.top() << std::endl;

  std::cout << real_stack.empty() << std::endl;
  std::cout << my_stack.empty() << std::endl;

  real_stack.pop();
  my_stack.pop();

  std::cout << real_stack.empty() << std::endl;
  std::cout << my_stack.empty() << std::endl;
}