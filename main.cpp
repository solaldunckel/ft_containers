# include "tests.hpp"

typedef int (*test_func)(void);
typedef std::map<std::string, test_func> test_map_fct;

int test_all() {
  test_vector();
  test_map();
  test_list();
  test_stack();
  test_queue();
  return 0;
}

int main(int argc, char **argv) {
  test_map_fct TESTS;

  TESTS["vector"] = &test_vector;
  TESTS["map"] = &test_map;
  TESTS["list"] = &test_list;
  TESTS["stack"] = &test_stack;
  TESTS["queue"] = &test_queue;

  if (argc < 2)
    return test_all();
  for (int i = 1; i < argc; i++)
    TESTS[argv[i]]();
  return 0;
}