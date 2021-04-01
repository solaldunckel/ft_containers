#ifndef ITERATORS_HPP
# define ITERATORS_HPP

namespace ft {
  template <class Iterator>
  struct iterator_traits {
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
  };

	template <class T>
	struct iterator_traits <T*> {
	  typedef T                               value_type;
	  typedef ptrdiff_t                       difference_type;
	  typedef T*                              pointer;
	  typedef T&                              reference;
	  typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits <const T*> {
	  typedef T                               value_type;
	  typedef ptrdiff_t                       difference_type;
	  typedef const T*                        pointer;
	  typedef const T&                        reference;
	  typedef std::random_access_iterator_tag iterator_category;
	};

  template <bool flag, class const_type, class normal_type>
  struct choose_type;

  template <class const_type, class normal_type>
  struct choose_type<true, const_type, normal_type> {
    typedef const_type type;
  };

  template <class const_type, class normal_type>
  struct choose_type<false, const_type, normal_type> {
    typedef normal_type type;
  };

  template <typename Iterator>
  class reverse_iterator : public Iterator {
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
			this->it_ = other.it_;
			return *this;
		}

    iterator_type base() const {
      return it_;
    }

    self     operator ++ () {
      --it_;
      return *this;
    };
    self     operator ++ (int) {
      self tmp = *this;
      --it_;
      return tmp;
    };
    self     operator -- () {
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

    template<typename It>
    friend bool operator==(const reverse_iterator<It> &x,
                            const reverse_iterator<It> &y) {
      return x.it_ == y.it_;
    }

    template<typename It>
    friend bool operator!=(const reverse_iterator<It> &x,
                            const reverse_iterator<It> &y) {
      return !(x == y);
    }

    template<typename It>
    friend bool operator<(const reverse_iterator<It> &x,
                            const reverse_iterator<It> &y) {
      return x.it_ > y.it_;
    }

    template<typename It>
    friend bool operator>(const reverse_iterator<It> &x,
                            const reverse_iterator<It> &y) {
      return y < x;
    }

    template<typename It>
    friend bool operator<=(const reverse_iterator<It> &x,
                            const reverse_iterator<It> &y) {
      return !(x < y);
    }

    template<typename It>
    friend bool operator>=(const reverse_iterator<It> &x,
                            const reverse_iterator<It> &y) {
      return !(x > y);
    }

    iterator_type it_;
  };
};

#endif