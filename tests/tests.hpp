#ifndef TESTS_H
# define TESTS_H

# include <iostream>
# include <list>
# include <stack>
# include <queue>
# include <vector>
# include <map>
# include <utility>
# include <sys/types.h>

# include <stdio.h>

# include "vector.hpp"
# include "map.hpp"
# include "list.hpp"
# include "stack.hpp"
# include "queue.hpp"

// static std::queue<std::string> g_errors;
// static int g_test = 0;

// # define TESTING_VAR true

# define PUSH(l, r, x)        (l.push(x), r.push(x))
# define PUSH_FRONT(l, r, x)  (l.push_front(x), r.push_front(x))
# define PUSH_BACK(l, r, x)   (l.push_back(x), r.push_back(x))

# define POP(l, r) (l.pop(), r.pop())
# define POP_BACK(l, r)   (l.pop_back(), r.pop_back())

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"

# define OK (printf(GREEN "[OK] " RESET))
# define KO (printf(RED "[KO] " RESET))

# define FCT_TEST(str) (printf("\n%-4s%-15s%-4s", ">", str, ":"))

template <typename T>
void TEST(T first, T second) {
  if (first == second)
    OK;
  else
    KO;
}

int test_vector();
int test_map();
int test_list();
int test_stack();
int test_queue();

#endif