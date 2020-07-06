#ifndef STACK_HPP
# define STACK_HPP

#include <string>

template <typename T>
struct Node {
  T content;
  Node *next;
};

namespace ft {
  template <typename T, class Container = Node<T> >
  class stack {
   public:
    typedef T value_type;
    typedef size_t size_type;
    typedef Container container_type;

    stack() {};
    ~stack() {};

    bool empty() { return size() == 0; };

    size_type size() {
      Container *tmp = &container_;
      size_type size = 0;
      while (tmp->next) {
        size++;
        tmp = tmp->next;
      }
      return size;
    };

    value_type& top() {
      Container *tmp = &container_;
      while (tmp->next)
        tmp = tmp->next;
      return tmp->content;
    };

    void push(value_type val) {
      Container *tmp = &container_;
      Container *new_node = new Container;
      while (tmp->next)
        tmp = tmp->next;
      new_node->content = val;
      new_node->next = nullptr;
      tmp->next = new_node;
    };

    void pop() {
      Container *tmp = &container_;
      Container *tmp2;
      while (tmp->next) {
        tmp2 = tmp;
        tmp = tmp->next;
      }
      // delete tmp->content;
      delete tmp;
      tmp2->next = nullptr;
    };

   private:
    Container container_;
  };

  template <class T, class Container>
  bool operator == (const stack<T, Container>& lhs,
                    const stack<T, Container>& rhs) { return lhs == rhs; };
  template <class T, class Container>
  bool operator != (const stack<T, Container>& lhs,
                    const stack<T, Container>& rhs) { return lhs != rhs; };
  template <class T, class Container>
  bool operator < (const stack<T, Container>& lhs,
                    const stack<T, Container>& rhs) { return lhs < rhs; };
  template <class T, class Container>
  bool operator <= (const stack<T, Container>& lhs,
                    const stack<T, Container>& rhs) { return lhs <= rhs; };
  template <class T, class Container>
  bool operator > (const stack<T, Container>& lhs,
                    const stack<T, Container>& rhs) { return lhs > rhs; };
  template <class T, class Container>
  bool operator >= (const stack<T, Container>& lhs,
                    const stack<T, Container>& rhs) { return lhs >= rhs; };
}

#endif