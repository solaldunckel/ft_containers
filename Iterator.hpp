#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {
  template <typename T>
  class Iterator {
   public:
    typedef iterator self_type;
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;

    Iterator(pointer ptr) : ptr_(ptr) {};

    self_type operator ++ () { self_type i = *this; ptr_++; return i };
    self_type operator ++ (int rhs) { ptr_++; return *this };
    reference operator *  () { return *ptr_; };
    pointer   operator -> () { return ptr_; };
    bool      operator == (const self_type &rhs) { return ptr_ == rhs.ptr_; };
    bool      operator != (const self_type &rhs) { return ptr_ != rhs.ptr_; };
    void      operator =  (const self_type &rhs) { rhs = ptr_; };

   private:
    pointer ptr_;
  };
}

#endif