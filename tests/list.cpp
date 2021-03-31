#include "tests.h"

# define PRINT_TEST(str) (std::cout << "\r\n#### " << str << " ####\r\n" << std::endl)

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

void list_constructor() {
  PRINT_TEST("CONSTRUCTORS");

  NAMESPACE::list<int> list;
  NAMESPACE::list<int> list2(5);
  NAMESPACE::list<int> list3(4, 100);
  NAMESPACE::list<std::string> list4(12, "test");
  std::list<int> ww(13, 68);
  NAMESPACE::list<int> list5(ww.begin(), ww.end());
  std::list<std::string> ww2(13, "test");
  NAMESPACE::list<std::string> list6(ww2.begin(), ww2.end());

  // constructors used in the same order as described above:
  NAMESPACE::list<int> first;                                // empty list of ints
  NAMESPACE::list<int> second (4,100);                       // four ints with value 100
  NAMESPACE::list<int> third (second.begin(),second.end());  // iterating through second
  NAMESPACE::list<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  NAMESPACE::list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  TEST_LIST(list);
  TEST_LIST(list2);
  TEST_LIST(list3);
  TEST_LIST(list4);
  TEST_LIST(list5);
  TEST_LIST(list6);
  TEST_LIST(fifth);
}

void list_push_front() {
  PRINT_TEST("PUSH_FRONT");

  NAMESPACE::list<std::string> list;

  list.push_front("test");
  TEST_LIST(list);
  list.push_front("");
  TEST_LIST(list);
  list.push_front("mdr");
  list.push_front("yo");
  TEST_LIST(list);
}

void list_push_back() {
  PRINT_TEST("PUSH_BACK");

  NAMESPACE::list<std::string> list;

  list.push_back("test");
  TEST_LIST(list);
  list.push_back("");
  TEST_LIST(list);
  list.push_back("mdr");
  list.push_back("yo");
  TEST_LIST(list);
}

void list_size() {
  PRINT_TEST("SIZE");
}

int main() {
  list_constructor();
  list_push_front();
  list_push_back();
  list_size();
}