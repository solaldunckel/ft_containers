# include "tests.h"

int	main() {
	NAMESPACE::list<int> lst(7);
	NAMESPACE::list<int>::iterator it = lst.begin();

	for (unsigned long int i = 0; i < lst.size(); ++i)
		*it++ = (lst.size() - i) * 3;
	TEST_LIST(lst);

	NAMESPACE::list<int> const lst_c(lst);

	std::cout << "front(): " << lst.front() << " " << lst_c.front() << std::endl;
	std::cout << "back(): " << lst.back() << " " <<  lst_c.back() << std::endl;

	lst.front() = 42;
	lst.back() = 404;
	TEST_LIST(lst);
	return (0);
}