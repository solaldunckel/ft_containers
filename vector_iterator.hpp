#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "utils_iterator.hpp"

namespace ft {
  template <class T, bool isconst = false>
  struct vector_iterator {
    typedef vector_iterator<T, isconst>      self;

    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef typename choose_type<isconst, const T&, T&>::type  reference;
    typedef typename choose_type<isconst, const T*, T*>::type  pointer;

    vector_iterator() : ptr_(NULL) {};
    vector_iterator(value_type *ptr) : ptr_(ptr) {};
    vector_iterator(const vector_iterator<T, false> &copy) : ptr_(copy.ptr_) {};
    // vector_iterator(const vector_iterator<T>  &copy) : ptr_(copy.ptr_) {};

    virtual ~vector_iterator() {};

    self   &operator = (const self &rhs) {
      ptr_ = rhs.ptr_;
      return *this;
    };

    self     &operator ++ () {
      ptr_++;
      return *this;
    };
    self     operator ++ (int) {
      self tmp = *this;
      ++(*this);
      return tmp;
    };
    self     &operator -- () {
      ptr_--;
      return *this;
    };
    self     operator -- (int) {
      self tmp = *this;
      --(*this);
      return tmp;
    };
    self     operator += (int n) {
      ptr_ += n;
      return *this;
    };
    self     operator -= (int n) {
      ptr_ -= n;
      return *this;
    };
    self     operator + (int n) const {
      self  tmp(*this);
      return tmp += n;
    };
    self     operator - (int n) const {
      self  tmp(*this);
      return tmp -= n;
    };
    difference_type     operator - (vector_iterator<T, true> it) const {
      return ptr_ - it.ptr_;
    };
    reference operator[] (size_t n) const {
      return ptr_[n];
    };

    bool      operator < (const vector_iterator<T, true> &rhs) const   { return ptr_ < rhs.ptr_; };
    bool      operator > (const vector_iterator<T, true> &rhs) const   { return ptr_ > rhs.ptr_; };
    bool      operator <= (const vector_iterator<T, true> &rhs) const  { return ptr_ <= rhs.ptr_; };
    bool      operator >= (const vector_iterator<T, true> &rhs) const  { return ptr_ >= rhs.ptr_; };

    bool      operator == (const vector_iterator<T, true> &rhs) const  { return ptr_ == rhs.ptr_; };
    bool      operator != (const vector_iterator<T, true> &rhs) const  { return ptr_ != rhs.ptr_; };
    reference operator *  () const                 { return *ptr_; };
    pointer   operator -> () const                 { return ptr_; };

    friend self operator + (int n, self it) { return it += n; };
    friend self operator - (int n, self it) { return it -= n; };

    pointer ptr_;
  };
}

#endif