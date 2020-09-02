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

    Stack(const container_type& ctnr = container_type()) {
      ctnr_ = ctnr;
    };

    ~Stack() {};
    
    bool empty() const { return ctnr_.empty(); };

    size_type size() const { return ctnr_.size(); };

    value_type& top() { return ctnr_.back(); };

    const value_type& top() const { return top(); };

    void push (const value_type& val) { ctnr_.push_back(val); };

    void pop() { ctnr_.pop_back(); };

   private:
    Container ctnr_;

  };
};

#endif