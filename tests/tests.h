#ifndef TESTS_H
# define TESTS_H

# include <iostream>
# include <stack>
# include <list>
# include <vector>
# include <stdio.h>

# include "../List.hpp"
# include "../Stack.hpp"
# include "../Queue.hpp"
# include "../Vector.hpp"

# define FCT_TEST(str) (printf("\n%-4s%-15s%-4s", ">", str, ":"))

# define PUSH(l, r, x)        (l.push(x), r.push(x))
# define PUSH_FRONT(l, r, x)  (l.push_front(x), r.push_front(x))
# define PUSH_BACK(l, r, x)   (l.push_back(x), r.push_back(x))

# define POP(l, r) (l.pop(), r.pop())

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"

# define OK (printf(GREEN "[OK] " RESET))
# define KO (printf(RED "[KO] " RESET))

template <typename T>
void TEST(T first, T second) {
  if (first == second)
    OK;
  else
    KO;
}

template <typename T>
void TEST_DEBUG(T first, T second) {
  if (first != second)
    std::cout << "real : " << first << " / mine : " << second << std::endl;
}

template <class list>
void PRINT_LIST(list &l) {
	for (typename list::iterator it = l.begin(); it != l.end(); ++it)
    std::cout << *it << " ";
	std::cout << std::endl;
}

template <class list>
void PRINT_REV(list l) {
	for (typename list::reverse_iterator it = l.rbegin(); it != l.rend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template <class list1, class list2>
void ITERATE(list1 &real, list2 &mine) {
  typename list1::iterator it1 = real.begin();
  typename list2::iterator it2 = mine.begin();

  while (it1 != real.end()) {
    if (*it1 != *it2) {
      KO;
      return ;
    }
    it1++;
    it2++;
  }
  OK;
}

template <class list1, class list2>
void ITERATE_REV(list1 &real, list2 &mine) {
  typename list1::reverse_iterator it1 = real.rbegin();
  typename list2::reverse_iterator it2 = mine.rbegin();

  while (it1 != real.rend() && it2 != mine.rend()) {
    if (*it1 != *it2) {
      KO;
      return ;
    }
    it1++;
    it2++;
  }
  OK;;
}

#endif