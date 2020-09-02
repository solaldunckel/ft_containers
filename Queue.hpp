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
      ctnr_ = ctnr;
    };

    ~Queue() {};

    bool              empty() const               { return ctnr_.empty(); };
    size_type         size() const                { return ctnr_.size(); };
    value_type&       front()                     { return ctnr_.front(); };
    const value_type& front() const               { return ctnr_.front(); };
    value_type&       back()                      { return ctnr_.back(); };
    const value_type& back() const                { return ctnr_.back(); };
    void              push(const value_type& val) { ctnr_.push_back(val); };
    void              pop()                       { ctnr_.pop_front(); };

   private:
    Container ctnr_;

  };

  template <class T, class Container>
  bool operator== (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
    return lhs == rhs;
  };

  template <class T, class Container>
  bool operator!= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
    return lhs != rhs;
  };

  template <class T, class Container>
  bool operator<  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
    return lhs < rhs;
  };

  template <class T, class Container>
  bool operator<= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
    return lhs <= rhs;
  };

  template <class T, class Container>
  bool operator>  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
    return lhs > rhs;
  };

  template <class T, class Container>
  bool operator>= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
    return lhs >= rhs;
  };
};

#endif