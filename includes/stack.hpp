#ifndef STACK_HPP
# define STACK_HPP

# include "list.hpp"

namespace ft {
  template <class T, class Container = ft::list<T> >
  class stack {
   public:
    typedef T           value_type;
    typedef Container   container_type;
    typedef std::size_t size_type;

    explicit stack(const container_type& ctnr = container_type()) {
      c_ = ctnr;
    };

    stack(const stack& other) {
      c_ = other.c_;
    }

    stack& operator = (const stack& other) {
      c_ = other.c_;
      return *this;
    };

    ~stack() {};

    bool              empty() const               { return c_.empty(); };
    size_type         size() const                { return c_.size(); };
    value_type&       top()                       { return c_.back(); };
    const value_type& top() const                 { return c_.back(); };
    void              push(const value_type& val) { c_.push_back(val); };
    void              pop()                       { c_.pop_back(); };

    template <class T1, class C1>
    friend bool operator== (const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

    template <class T1, class C1>
    friend bool operator< (const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

   protected:
    container_type c_;
  };

  template <class T, class Ctnr>
  bool operator== (const stack<T, Ctnr>& lhs, const stack<T, Ctnr>& rhs) {
    return lhs.c_ == rhs.c_;
  };

  template <class T, class Ctnr>
  bool operator< (const stack<T, Ctnr>& lhs, const stack<T, Ctnr>& rhs) {
    return lhs.c_ < rhs.c_;
  };

  template <class T, class Ctnr>
  bool operator!= (const stack<T, Ctnr>& lhs, const stack<T, Ctnr>& rhs) {
    return !(lhs == rhs);
  };

  template <class T, class Ctnr>
  bool operator<= (const stack<T, Ctnr>& lhs, const stack<T, Ctnr>& rhs) {
    return !(rhs < lhs);
  };

  template <class T, class Ctnr>
  bool operator>  (const stack<T, Ctnr>& lhs, const stack<T, Ctnr>& rhs) {
    return rhs < lhs;
  };

  template <class T, class Ctnr>
  bool operator>= (const stack<T, Ctnr>& lhs, const stack<T, Ctnr>& rhs) {
    return !(lhs < rhs);
  };
};

#endif