#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "List.hpp"

namespace ft {
  template <class T, class Container = ft::List<T> >
  class Queue {
   public:
    typedef T         value_type;
    typedef Container container_type;
    typedef size_t    size_type;

    explicit Queue(const container_type& ctnr = container_type()) {
      c_ = ctnr;
    };

    Queue(const Queue& other) {
      c_ = other.c_;
    }

    Queue& operator = (const Queue& other) {
      c_ = other.c_;
      return *this;
    };

    ~Queue() {};

    bool              empty() const               { return c_.empty(); };
    size_type         size() const                { return c_.size(); };
    value_type&       front()                     { return c_.front(); };
    const value_type& front() const               { return c_.front(); };
    value_type&       back()                      { return c_.back(); };
    const value_type& back() const                { return c_.back(); };
    void              push(const value_type& val) { c_.push_back(val); };
    void              pop()                       { c_.pop_front(); };

    template <class T1, class C1>
    friend bool operator== (const Queue<T1, C1>& lhs, const Queue<T1, C1>& rhs);

    template <class T1, class C1>
    friend bool operator< (const Queue<T1, C1>& lhs, const Queue<T1, C1>& rhs);

   protected:
    container_type c_;
  };

  template <class T, class Ctnr>
  bool operator== (const Queue<T, Ctnr>& lhs, const Queue<T, Ctnr>& rhs) {
    return lhs.c_ == rhs.c_;
  };

  template <class T, class Ctnr>
  bool operator< (const Queue<T, Ctnr>& lhs, const Queue<T, Ctnr>& rhs) {
    return lhs.c_ < rhs.c_;
  };

  template <class T, class Ctnr>
  bool operator!= (const Queue<T, Ctnr>& lhs, const Queue<T, Ctnr>& rhs) {
    return !(lhs == rhs);
  };

  template <class T, class Ctnr>
  bool operator<= (const Queue<T, Ctnr>& lhs, const Queue<T, Ctnr>& rhs) {
    return !(rhs < lhs);
  };

  template <class T, class Ctnr>
  bool operator>  (const Queue<T, Ctnr>& lhs, const Queue<T, Ctnr>& rhs) {
    return rhs < lhs;
  };

  template <class T, class Ctnr>
  bool operator>= (const Queue<T, Ctnr>& lhs, const Queue<T, Ctnr>& rhs) {
    return !(lhs < rhs);
  };
};

#endif