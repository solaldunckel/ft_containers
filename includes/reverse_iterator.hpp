#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "utils_iterator.hpp"

namespace ft {
  template <typename Iterator>
  class reverse_iterator {
   public:
    typedef reverse_iterator    self;
    typedef Iterator            iterator_type;

    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::reference         reference;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;

    reverse_iterator() : it_() {};
    reverse_iterator(const iterator_type copy) : it_(copy) {};

    template <typename It>
    reverse_iterator(const reverse_iterator<It> &copy) : it_(copy.base()) {};

    virtual ~reverse_iterator() {};

    template <class It>
		self &operator=(const reverse_iterator<It>& other) {
			this->it_ = other.base();
			return *this;
		}

    iterator_type base() const {
      return it_;
    }

    self     &operator ++ () {
      --it_;
      return *this;
    };
    self     operator ++ (int) {
      self tmp = *this;
      --it_;
      return tmp;
    };
    self     &operator -- () {
      ++it_;
      return *this;
    };
    self     operator -- (int) {
      self tmp = *this;
      ++it_;
      return tmp;
    };
    self     operator + (difference_type n) const {
      reverse_iterator tmp(*this);
      tmp.it_ -= n;
      return tmp;
    };
    self     operator += (difference_type n) {
      it_ = it_ - n;
      return *this;
    };
    self     operator - (difference_type n) const {
      reverse_iterator tmp(*this);
      tmp.it_ += n;
      return tmp;
    };
    self     operator -= (difference_type n) {
      it_ = it_ + n;
      return *this;
    };
    reference     operator [] (difference_type n) const {
      return *(*this + n);
    };

    reference operator * () const {
      iterator_type tmp = it_;
      return *--tmp;
    };
    pointer   operator -> () const {
      iterator_type tmp = it_;
      return &*--tmp;
    };

    template <class It>
    difference_type     operator - (const reverse_iterator<It> &x) {
      return x.base().operator-(it_);;
    };

    friend reverse_iterator	operator+(difference_type n, const reverse_iterator &rhs) {
      return rhs + n;
    };

    template <class It>
    bool	operator==(const reverse_iterator<It> &rhs) const { return it_ == rhs.base(); };

    template <class It>
    bool	operator!=(const reverse_iterator<It> &rhs) const { return it_ != rhs.base(); };

    template <class It>
    bool	operator<(const reverse_iterator<It> &rhs) const { return it_ > rhs.base(); };

    template <class It>
    bool	operator>(const reverse_iterator<It> &rhs) const { return it_ < rhs.base(); };

    template <class It>
    bool	operator<=(const reverse_iterator<It> &rhs) const { return it_ >= rhs.base(); };

    template <class It>
    bool	operator>=(const reverse_iterator<It> &rhs) const { return it_ <= rhs.base(); };

   private:
    iterator_type it_;
  };
}
#endif