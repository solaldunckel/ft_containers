#ifndef TESTS_H
# define TESTS_H

# define PRINT(x) (std::cout << x << std::endl)
# define FCT_TEST(str) (printf("\n%-25s : ", "> " str))

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"

# include <iostream>
# include <stack>
# include <list>
# include <stdio.h>

# include "../List.hpp"

template <typename T>
void test(T first, T second) {
  if (first == second) {
    printf(GREEN "[OK] " RESET);
  }
  else
    printf(RED "[KO] " RESET);
}

template <typename MyIterator, typename ListIterator >
int test_iterate(ListIterator begin_real, ListIterator end_real, MyIterator begin_mine, MyIterator end_mine) {
  int count = 0;

  while (begin_real != end_real && begin_mine != end_mine) {
    if (*begin_real != *begin_mine)
      return printf(RED "[KO] " RESET);
    begin_real++;
    begin_mine++;
    count++;
  }
  return printf(GREEN "[OK] " RESET);;
}

template <typename T>
void test_debug(T first, T second) {
  if (first == second) {
    printf(GREEN "[OK] " RESET);
  }
  else {
    printf(RED "[KO] " RESET);
    std::cout << "real : " << first << " / mine : " << second;
  }
    
}

// LIST
void test_list();

#endif