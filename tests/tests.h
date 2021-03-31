#ifndef TESTS_H
# define TESTS_H

# ifndef NAMESPACE
#  define NAMESPACE ft
# endif

# include <iostream>
# include <list>
# include <stack>
# include <queue>
# include <vector>
# include <map>
# include <stdio.h>

# include "Iterators.hpp"
# include "Utility.hpp"

# include "list.hpp"
# include "stack.hpp"
# include "queue.hpp"
# include "vector.hpp"
# include "map.hpp"

template <class Container>
void PRINT(Container &l) {
	for (typename Container::iterator it = l.begin(); it != l.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

template <class Container>
void PRINT_MAP(Container &l) {
	for (typename Container::iterator it = l.begin(); it != l.end(); ++it) {
    std::cout << it->first << " -> " << it->second << std::endl;
  }
}

template<class T1, class T2>
void TEST_OP(T1 &lhs, T2 &rhs) {
  std::cout << (lhs == rhs) << std::endl;
  std::cout << (lhs != rhs) << std::endl;
  std::cout << (lhs > rhs) << std::endl;
  std::cout << (lhs >= rhs) << std::endl;
  std::cout << (lhs < rhs) << std::endl;
  std::cout << (lhs <= rhs) << std::endl;
  std::cout << "##########################" << std::endl;
}

template<class T>
void TEST_STACK_QUEUE(T &stack) {
  std::cout << "empty: " << stack.empty() << std::endl;
  std::cout << "size: " << stack.size() << std::endl;
  std::cout << "##########################" << std::endl;
}

template<class T>
void TEST_LIST(T &list) {
  std::cout << "empty: " << list.empty() << std::endl;
  std::cout << "size: " << list.size() << std::endl;
  std::cout << "max_size: " << list.max_size() << std::endl;
  std::cout << "content:" << std::endl;
  std::cout << "-" << std::endl;
  PRINT(list);
  std::cout << "-" << std::endl;
  std::cout << "##########################" << std::endl;
}

template<class T>
void TEST_MAP(T &map) {
  std::cout << "empty: " << map.empty() << std::endl;
  std::cout << "size: " << map.size() << std::endl;
  std::cout << "max_size: " << map.max_size() << std::endl;
  std::cout << "content:" << std::endl;
  std::cout << "-" << std::endl;
  PRINT_MAP(map);
  std::cout << "-" << std::endl;
  std::cout << "##########################" << std::endl;
}

#endif