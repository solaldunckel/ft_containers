#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "utils_iterator.hpp"

namespace ft {
  template <class T>
  struct node_list {
    node_list  *prev_;
    node_list  *next_;
    T           value_;
  };

  template <class T, bool isconst = false>
  struct list_iterator {
    typedef list_iterator<T, isconst>        self;

    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;

    typedef typename choose_type<isconst, const T&, T&>::type                         reference;
    typedef typename choose_type<isconst, const T*, T*>::type                         pointer;
    typedef typename choose_type<isconst, const node_list<T>*, node_list<T>*>::type   nodeptr;

    list_iterator() : ptr_(NULL) {};
    list_iterator(nodeptr ptr) : ptr_(ptr) {};
    list_iterator(const list_iterator<T, true> &copy) : ptr_(copy.ptr_) {};
    list_iterator(const list_iterator<T, false> &copy) : ptr_(copy.ptr_) {};

    virtual ~list_iterator() {};

    self   &operator = (const self &rhs)   {
      ptr_ = rhs.ptr_;
      return *this;
    };

    self     operator ++ () {
      ptr_ = ptr_->next_;
      return *this;
    };
    self     operator ++ (int) {
      self tmp = *this;
      ++(*this);
      return tmp;
    };
    self     &operator -- () {
      ptr_ = ptr_->prev_;
      return *this;
    };
    self     operator -- (int) {
      self tmp = *this;
      --(*this);
      return tmp;
    };

    bool      operator == (const list_iterator<T, true> &rhs) const { return ptr_ == rhs.ptr_; };
    bool      operator != (const list_iterator<T, true> &rhs) const { return ptr_ != rhs.ptr_; };
    reference operator *  () const                { return ptr_->value_; };
    pointer   operator -> () const                { return &ptr_->value_; };

    nodeptr ptr_;
  };
}

#endif