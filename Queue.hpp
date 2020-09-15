#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "list.hpp"

namespace ft {
  template <class T, class Container = ft::list<T> >
  class queue {
   public:
    typedef T         value_type;
    typedef Container container_type;
    typedef size_t    size_type;

    explicit queue(const container_type& ctnr = container_type()) {
      c_ = ctnr;
    };

    queue(const queue& other) {
      c_ = other.c_;
      return *this;
    }

    queue& operator = (const queue& other) {
      c_ = other.c_;
      return *this;
    };

    ~queue() {};

    bool              empty() const               { return c_.empty(); };
    size_type         size() const                { return c_.size(); };
    value_type&       front()                     { return c_.front(); };
    const value_type& front() const               { return c_.front(); };
    value_type&       back()                      { return c_.back(); };
    const value_type& back() const                { return c_.back(); };
    void              push(const value_type& val) { c_.push_back(val); };
    void              pop()                       { c_.pop_front(); };

    template <class T1, class C1>
    friend bool operator== (const queue<T1,C1>& lhs, const queue<T1,C1>& rhs) {
      return lhs.c_ == rhs.c_;
    };

    template <class T1, class C1>
    friend bool operator< (const queue<T1,C1>& lhs, const queue<T1,C1>& rhs) {
      return lhs.c_ < rhs.c_;
    };

    template <class T1, class C1>
    friend bool operator!= (const queue<T1,C1>& lhs, const queue<T1,C1>& rhs) {
      return !(lhs == rhs);
    };

    template <class T1, class C1>
    friend bool operator<= (const queue<T1,C1>& lhs, const queue<T1,C1>& rhs) {
      return !(rhs < lhs);
    };

    template <class T1, class C1>
    friend bool operator>  (const queue<T1,C1>& lhs, const queue<T1,C1>& rhs) {
      return rhs < lhs;
    };

    template <class T1, class C1>
    friend bool operator>= (const queue<T1,C1>& lhs, const queue<T1,C1>& rhs) {
      return !(lhs < rhs);
    };

   protected:
    container_type c_;
  };
};

#endif