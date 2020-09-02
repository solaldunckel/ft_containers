#ifndef STACK_HPP
# define STACK_HPP

# include "List.hpp"

namespace ft {
  template <class T, class Container = ft::List<T> >
  class Stack {
   public:
    typedef T         value_type;
    typedef Container container_type;
    typedef size_t    size_type;

    explicit Stack(const container_type& ctnr = container_type()) {
      ctnr_ = ctnr;
    };

    ~Stack() {};

    bool              empty() const               { return ctnr_.empty(); };
    size_type         size() const                { return ctnr_.size(); };
    value_type&       top()                       { return ctnr_.back(); };
    const value_type& top() const                 { return ctnr_.back(); };
    void              push(const value_type& val) { ctnr_.push_back(val); };
    void              pop()                       { ctnr_.pop_back(); };

   private:
    Container ctnr_;

  };

  template <class T, class Container>
  bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return lhs == rhs;
  };

  template <class T, class Container>
  bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return lhs != rhs;
  };

  template <class T, class Container>
  bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return lhs < rhs;
  };

  template <class T, class Container>
  bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return lhs <= rhs;
  };

  template <class T, class Container>
  bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return lhs > rhs;
  };

  template <class T, class Container>
  bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return lhs >= rhs;
  };
};

#endif