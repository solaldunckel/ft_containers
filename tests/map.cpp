#include "tests.h"

int main() {
  std::cout << "Map " << std::endl;

  ft::Map<int, int> test;

  // ft::pair<int, int> p1 = ft::make_pair("solal", 24);

  test[5] = 2;
  test[122] = 4;
  test[99] = 4;
  test[3] = 4;
  test[102] = 4;
  test[3] = 8;
  // test.insert_test(5, 2);
	// test.insert_test(122, 4);
	// test.insert_test(99, 0);
  // test.insert_test(3, 0);
	// test.insert_test(102, 0);
  // test.insert_test(-4, 0);
  // test.insert_test(-7, 0);
	// test.insert_test(135, 0);
	// test.insert_test(104, 0);
	// test.insert_test(101, 0);
	// test.insert_test(148, 0);
	// test.insert_test(123, 0);
	// test.insert_test(702, 0);
	// test.insert_test(12, 0);

  ft::Map<int, int>::iterator my_it = test.begin();

 for (; my_it != test.end(); my_it++) {
    std::cout << my_it->first << "\n";
  }

  // test["hava"] = 25;

  // std::cout << "The value of p1 is "
  //             << "(" << p1.first << ", " << p1.second << ")\n";

  // std::cout << test.size() << std::endl;

  // ft::Map<std::string, int>::iterator it = test.begin();

  // std::cout << it->first << std::endl;
  

  // test[1] = 42;
  // test[122] = 42;
  // test[99] = 12;
  // test[102] = 33;
  // test[135] = 18;
  // test[104] = 12;
  // test[101] = 53;
  // test[148] = 18;
  // test[123] = 18;
  // test[702] = 18;
  // test[12] = 18;

  // ft::Map<int, int> test3;
  // ft::Map<int, int>::iterator it3 = test3.begin();

  // std::cout << it3->first << std::endl;
  // std::cout << "equal to end : " << (it3 == test3.end()) << std::endl;

  std::map<int, int> test2;

  test2[23] = 5;

  std::map<int, int>::iterator it = test2.begin();
  --it;
  std::cout << it->first << std::endl;
  std::cout << (it == test2.end()) << std::endl;
  // std::map<int, int>::iterator it2 = test2.begin();

  // std::cout << it2->first << std::endl;
  // std::cout << "equal to end : " << (it2 == test2.end()) << std::endl;
  // for (; it != test.end(); it++) {
  //   std::cout << it->first << " = " << it->second << "\n";
  // }

  std::cout << std::endl;
}