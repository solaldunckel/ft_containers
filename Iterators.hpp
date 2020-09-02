#ifndef ITERATORS_HPP
# define ITERATORS_HPP

namespace ft {
  template <typename Iterator>
  class ReverseIterator : public Iterator {
   public:
    ReverseIterator() : Iterator() {};
    ReverseIterator(const Iterator &copy) : Iterator(copy) {};
    ReverseIterator(const ReverseIterator &copy) : Iterator(copy.ptr_) {};

    ~ReverseIterator() {};

    ReverseIterator     operator ++ () {
      this->ptr_ = this->ptr_->prev_;
      return *this;
    };
    ReverseIterator     operator ++ (int) {
      ReverseIterator tmp = *this;
      ++(*this);
      return tmp;
    };
    ReverseIterator     operator -- () {
      this->ptr_ = this->ptr_->next_;
      return *this;
    };
    ReverseIterator     operator -- (int) {
      ReverseIterator tmp = *this;
      --(*this);
      return tmp;
    };
  };
};

#endif