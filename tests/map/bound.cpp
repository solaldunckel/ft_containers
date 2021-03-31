#include "tests.h"

int	main() {
  NAMESPACE::map<char,int> mymap;
  NAMESPACE::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  mymap.erase(itlow,itup);        // erases [itlow,itup)

  NAMESPACE::map<char,int> mymap2;

  mymap2['a']=10;
  mymap2['b']=20;
  mymap2['c']=30;

  NAMESPACE::pair<NAMESPACE::map<char,int>::iterator, NAMESPACE::map<char,int>::iterator> ret;
  ret = mymap2.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';
  TEST_MAP(mymap);
  TEST_MAP(mymap2);
	return (0);
}