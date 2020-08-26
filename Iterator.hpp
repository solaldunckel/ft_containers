#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {
  template <typename T>
  struct DoubleLinkedList {
    DoubleLinkedList *prev_;
    DoubleLinkedList *next_;
    T value_;

    DoubleLinkedList(DoubleLinkedList *prev, DoubleLinkedList *next, const T &val)
      : prev_(prev), next_(next), value_(val) {};
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

  template <class Iterator>
  class ReverseIterator {
   public:
    typedef Iterator iterator_type;
    typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;

    ReverseIterator() {};
    ReverseIterator(Iterator ptr) : ptr_(ptr) {};
    ReverseIterator(ReverseIterator<Iterator> &copy) : ptr_(copy.ptr_) {};
    ~ReverseIterator() {};

    iterator_type base() const {
      return ptr_;
    };

    reference operator*() const {
      Iterator copy(ptr_);
      ptr_--;
      return *copy;
    };

    ReverseIterator<Iterator>& operator++() {
      ptr_--;
      return *this;
    };

    ReverseIterator<Iterator>& operator++(int) {
      ReverseIterator<Iterator> tmp = *this;
      ++(*this);
      return tmp;
    };

    ReverseIterator<Iterator>& operator--() {
      ptr_++;
      return *this;
    };

    ReverseIterator<Iterator>& operator--(int) {
      ReverseIterator<Iterator> tmp = *this;
      --(*this);
      return tmp;
    };

    pointer operator->() const {
      return &(operator*());
    };

   private:
    Iterator ptr_;
  };
}

#endif