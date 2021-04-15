# ft_containers

![containers](https://i.imgur.com/gfVBbX5.png)

## Description

ft_containers is a project written in C++ that ask you to reimplement a few containers from the STL.

They must have all public member functions from C++98.

## Containers

### List

Unordered container with constant time for inserting/deleting elements. Searching an element is O(n).

Implemented as a linked-list.

### Vector

Unordered container with fast access time with `[]`.

Implemented as an array, similar to standard C arrays.
  
### Map

Stores pairs `key = value` and is sorted by `key` (custom function for sorting can be templated).

Implemented as a Binary Search Tree (BST)

### Stack

Last In First Out (LIFO). Basic functionnality such as `push_back` / `pop_back` / `accessing last element`. 

Can be templated with any container supporting `push_back` `pop_back` `back` `empty` `size`.

### Queue

First In First Out (FIFO). Basic functionnality such as `push_back` / `pop_front` / `accessing first/last element`.

Can be templated with any container supporting `push_back` `pop_front` `back` `front` `empty` `size`.

## Usage

* Include :
```c++
#include "includes/list.hpp"
#include "includes/vector.hpp"
#include "includes/map.hpp"
#include "includes/stack.hpp"
#include "includes/queue.hpp"

// Containers are in the 'ft' namespace

ft::list<int> list;
ft::vector<int> vector;
ft::map<int, std::string> map;
ft:stack<int> stack;
ft::queue<int> queue;
```

* Test :
```shell
# Compile the sources
make

# Run the tester
./ft_containers_test [container_name] ..
```

## Sources
- [C++ Reference](https://www.cplusplus.com/reference/stl/)
- [Iterators](https://www.cs.helsinki.fi/u/tpkarkka/alglib/k06/lectures/iterators.html)
- [Const Iterators](https://www.drdobbs.com/the-standard-librarian-defining-iterato/184401331)
- [Reverse Iterator Reference](http://www.cplusplus.com/reference/iterator/reverse_iterator/)

## Unit Tests
- [mli42](https://github.com/mli42/containers_test)
- [llefranc](https://github.com/llefranc/42_Containator)
- [Mazoise](https://github.com/Mazoise/FT_CONTAINERS_TESTER)
