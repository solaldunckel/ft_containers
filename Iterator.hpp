#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {
  template <class T>
  struct DoubleLinkedList {
    DoubleLinkedList *prev_;
    DoubleLinkedList *next_;
    T value_;

    DoubleLinkedList() : prev_(NULL), next_(NULL) {};
    DoubleLinkedList(DoubleLinkedList *prev, DoubleLinkedList *next)
      : prev_(prev), next_(next) {};
  };

  template <typename T>
  class ListIterator {
   public:
    typedef ListIterator<T> self_type;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    ListIterator() : ptr_(NULL) {};
    ListIterator(DoubleLinkedList<T> *ptr) : ptr_(ptr) {};
    ListIterator(const self_type &copy) : ptr_(copy.ptr_) {};

    ~ListIterator() {};

    self_type operator ++ () {
			ptr_ = ptr_->next_;
      return *this;
    };

    self_type operator ++ (int rhs) {
      self_type tmp(*this);
      ++(*this);
      return tmp;
    };

    self_type operator -- () {
      self_type i = *this;
      ptr_--;
      return i;
    };

    self_type operator -- (int rhs) {
      ptr_--;
      return *this;
    };

    reference operator *  () {
      return ptr_->value_;
    };

    pointer   operator -> () {
      return &ptr_->value_;
    };

    bool      operator == (const self_type &rhs) {
      return ptr_ == rhs.ptr_;
    };

    bool      operator != (const self_type &rhs) {
      return ptr_ != rhs.ptr_;
    };

    void      operator =  (const self_type &rhs) {
      ptr_ = rhs;
    };

    DoubleLinkedList<T>* getPtr() { return ptr_; }

   private:
    DoubleLinkedList<T> *ptr_;
  };

  template <typename T>
  class ReverseIterator {
   public:
    typedef ReverseIterator<T> self_type;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    ReverseIterator() : ptr_(NULL) {};
    ReverseIterator(DoubleLinkedList<T> *ptr) : ptr_(ptr) {};
    ReverseIterator(const self_type &copy) : ptr_(copy.ptr_) {};

    ~ReverseIterator() {};

    self_type operator ++ () {
			ptr_ = ptr_->prev_;
      return *this;
    };

    self_type operator ++ (int rhs) {
      self_type tmp(*this);
      ptr_ = ptr_->prev_;
      return tmp;
    };

    self_type operator -- () {
      self_type i = *this;
      ptr_ = ptr_->next_;
      return i;
    };

    self_type operator -- (int rhs) {
      ptr_ = ptr_->next_;
      return *this;
    };

    reference operator *  () {
      return ptr_->value_;
    };

    pointer   operator -> () {
      return &ptr_->value_;
    };

    bool      operator == (const self_type &rhs) {
      return ptr_ == rhs.ptr_;
    };

    bool      operator != (const self_type &rhs) {
      return ptr_ != rhs.ptr_;
    };

    void      operator =  (const self_type &rhs) {
      ptr_ = rhs;
    };

    DoubleLinkedList<T>* getPtr() { return ptr_; }

   private:
    DoubleLinkedList<T> *ptr_;
  };
}

#endif