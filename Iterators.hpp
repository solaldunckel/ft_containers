#ifndef ITERATORS_HPP
# define ITERATORS_HPP

namespace ft {
  template <typename Iterator>
  class ReverseIterator {
   public:
    typedef ReverseIterator    self_;

    typedef typename Iterator::value_type       value_type;
    typedef typename Iterator::pointer          pointer;
    typedef typename Iterator::reference        reference;
    typedef typename Iterator::difference_type  difference_type;

    ReverseIterator() : it_() {};
    ReverseIterator(const Iterator &copy) : it_(copy) {};
    ReverseIterator(const self_ &copy) : it_(copy.it_) {};

    template <typename It>
    ReverseIterator(const ReverseIterator<It> &copy) : it_(copy.getIt()) {};

    virtual ~ReverseIterator() {};

    self_ &operator=(self_ const &other) {
      this->ptr_ = other.ptr_;
      return (*this);
    }

    self_     operator ++ () {
      --it_;
      return *this;
    };
    self_     operator ++ (int) {
      self_ tmp = *this;
      --it_;
      return tmp;
    };
    self_     operator -- () {
      ++it_;
      return *this;
    };
    self_     operator -- (int) {
      self_ tmp = *this;
      ++it_;
      return tmp;
    };

    reference operator * () {
      Iterator tmp = it_;
      return *--tmp;
    };
    pointer   operator -> () {
      Iterator tmp = it_;
      return &*--tmp;
    };
    const reference operator * () const {
      Iterator tmp = it_;
      return *--tmp;
    };
    const pointer   operator ->() const {
      Iterator tmp = it_;
      return &*--tmp;
    };

    Iterator getIt() const { return it_; }

   private:
    Iterator it_;
  };

  template<typename Iterator>
  bool operator==(const ReverseIterator<Iterator> &x,
                    const ReverseIterator<Iterator> &y) {
    return x.getIt() == y.getIt();
  }

  template<typename Iterator>
  bool operator!=(const ReverseIterator<Iterator> &x,
                    const ReverseIterator<Iterator> &y) {
    return !(x == y);
  }

  template<typename Iterator>
  bool operator<(const ReverseIterator<Iterator> &x,
                    const ReverseIterator<Iterator> &y) {
    return x.getIt() < y.getIt();
  }

  template<typename Iterator>
  bool operator>(const ReverseIterator<Iterator> &x,
                    const ReverseIterator<Iterator> &y) {
    return y < x;
  }

  template<typename Iterator>
  bool operator<=(const ReverseIterator<Iterator> &x,
                    const ReverseIterator<Iterator> &y) {
    return !(x < y);
  }

  template<typename Iterator>
  bool operator>=(const ReverseIterator<Iterator> &x,
                    const ReverseIterator<Iterator> &y) {
    return !(x > y);
  }

};

#endif