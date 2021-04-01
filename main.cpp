# include "list.hpp"
# include "tests.h"

int test_std() {
  std::list<int> lst(5);
	std::list<int>::iterator it = lst.begin(), ite = lst.end();
	for (int i = 0; it != ite; ++it)
		*it = ++i;

	it = lst.begin();
	std::list<int> lst_range(it, --(--ite));
  std::cout << "IT = " << *it << std::endl;
  std::cout << "ITE = " << *ite << std::endl;
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;


    TEST_LIST(lst);
	// it = lst.begin();
	// std::list<int> lst_copy(lst);
	// for (int i = 0; it != ite; ++it)
	// 	*it = ++i * 7;
	// lst_copy.push_back(42);
	// lst_copy.push_back(21);

	// std::cout << "\t-- PART ONE --" << std::endl;
	// TEST_LIST(lst);
	// TEST_LIST(lst_range);
	// TEST_LIST(lst_copy);

	// lst = lst_copy;
	// lst_copy = lst_range;
	// lst_range.clear();

	// std::cout << "\t-- PART TWO --" << std::endl;
	// TEST_LIST(lst);
	// TEST_LIST(lst_range);
	// TEST_LIST(lst_copy);
  return 0;
}

int test_ft() {
  ft::list<int> lst(5);
	ft::list<int>::iterator it = lst.begin();
  ft::list<int>::const_iterator ite = lst.end();

	for (int i = 0; it != ite; ++it)
		*it = ++i;

	// it = lst.begin();
	// ft::list<int> lst_range(it, --(--ite));
  // std::cout << "IT = " << *it << std::endl;
  // std::cout << "ITE = " << *ite << std::endl;
	// for (int i = 0; it != ite; ++it)
	// 	*it = ++i * 5;

  // std::cout << *ite << std::endl;
  // TEST_LIST(lst);
	// it = lst.begin();
	// ft::list<int> lst_copy(lst);
	// for (int i = 0; it != ite; ++it)
	// 	*it = ++i * 7;
	// lst_copy.push_back(42);
	// lst_copy.push_back(21);

	// std::cout << "\t-- PART ONE --" << std::endl;
	// TEST_LIST(lst);
	// TEST_LIST(lst_range);
	// TEST_LIST(lst_copy);

	// lst = lst_copy;
	// lst_copy = lst_range;
	// lst_range.clear();

	// std::cout << "\t-- PART TWO --" << std::endl;
	// TEST_LIST(lst);
	// TEST_LIST(lst_range);
	// TEST_LIST(lst_copy);
  return 0;
}

int main() {
  ft::list<int> mylist1, mylist2;
  ft::list<int>::iterator it;

  // set some initial values:
  for (int i=1; i<=4; ++i)
     mylist1.push_back(i);      // mylist1: 1 2 3 4

  for (int i=1; i<=3; ++i)
     mylist2.push_back(i*10);   // mylist2: 10 20 30

  it = mylist1.begin();
  ++it;                         // points to 2

  mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
                                // mylist2 (empty)
                                // "it" still points to 2 (the 5th element)
                                          
  mylist2.splice (mylist2.begin(),mylist1, it);
                                // mylist1: 1 10 20 30 3 4
                                // mylist2: 2
                                // "it" is now invalid.
  it = mylist1.begin();
  std::advance(it,3);           // "it" points now to 30

  mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
                                // mylist1: 30 3 4 1 10 20

  std::cout << "mylist1 contains:";
  for (it=mylist1.begin(); it!=mylist1.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "mylist2 contains:";
  for (it=mylist2.begin(); it!=mylist2.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
  // test_std();
  // test_ft();
  return 0;
}