#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <limits>
# include <type_traits>

# include "Iterators.hpp"

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

    list_iterator() : ptr_(nullptr) {};
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
    self     operator -- () {
      ptr_ = ptr_->prev_;
      return *this;
    };
    self     operator -- (int) {
      self tmp = *this;
      --(*this);
      return tmp;
    };

    bool      operator == (const self &rhs) const { return ptr_ == rhs.ptr_; };
    bool      operator != (const self &rhs) const { return ptr_ != rhs.ptr_; };
    reference operator *  () const                { return ptr_->value_; };
    pointer   operator -> () const                { return &ptr_->value_; };

    nodeptr ptr_;
  };

  template <class T, class Alloc = std::allocator<T> >
  class list {
   public:
    typedef T           value_type;
    typedef size_t      size_type;
    typedef Alloc       allocator_type;

    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;

    typedef ft::list_iterator<T>                   iterator;
		typedef ft::list_iterator<T, true>             const_iterator;
		typedef ft::reverse_iterator<iterator>         reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>   const_reverse_iterator;

    typedef typename iterator::difference_type     difference_type;

    explicit list(const allocator_type& alloc = allocator_type()) {
      alloc_ = alloc;
      size_ = 0;

      elem_ = alloc_node_.allocate(1);
      elem_->prev_ = elem_;
      elem_->next_ = elem_;
      alloc_.construct(&elem_->value_, value_type());
    };

    explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
      alloc_ = alloc;
      size_ = 0;

      elem_ = alloc_node_.allocate(1);
      elem_->prev_ = elem_;
      elem_->next_ = elem_;
      alloc_.construct(&elem_->value_, value_type());

      insert(end(), n, val);
    };

    template <class InputIterator>
    list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
          typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
      alloc_ = alloc;
      size_ = 0;

      elem_ = alloc_node_.allocate(1);
      elem_->prev_ = elem_;
      elem_->next_ = elem_;
      alloc_.construct(&elem_->value_, value_type());

      insert(end(), first, last);
    };

    list(list &x) {
      alloc_ = x.alloc_;
      size_ = 0;

      elem_ = alloc_node_.allocate(1);
      elem_->prev_ = elem_;
      elem_->next_ = elem_;
      alloc_.construct(&elem_->value_, value_type());

      assign(x.begin(), x.end());
    };

    ~list() {
      clear();
      alloc_.destroy(&elem_->value_);
      alloc_node_.deallocate(elem_, 1);
    };

    list& operator = (const list& x) {
      assign(x.begin(), x.end());
      return *this;
    };

    iterator begin() { return iterator(elem_->next_); };
    iterator end() { return iterator(elem_); };
    const_iterator begin() const { return const_iterator(elem_->next_); };
    const_iterator end() const { return const_iterator(elem_); };

    reverse_iterator rbegin() { return reverse_iterator(end()); };
    reverse_iterator rend() { return reverse_iterator(begin()); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

    bool empty() const { return size_ == 0; };
    size_type size() const { return size_; };
    size_type max_size() const { return alloc_node_.max_size(); };

    reference front() { return elem_->next_->value_; };
    const_reference front() const { return elem_->next_->value_; };

    reference back() { return elem_->prev_->value_; };
    const_reference back() const { return elem_->prev_->value_; };

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last) {
      clear();
      insert(end(), first, last);
    };

    void assign (size_type n, const value_type& val) {
      clear();
      insert(end(), n, val);
    };

    void push_front (const value_type& val) { insert(begin(), val); };
    void pop_front ()                       { erase(begin()); };
    void push_back (const value_type& val)  { insert(end(), val); };
    void pop_back()                         { erase(--end()); };

    iterator insert (iterator position, const value_type& val) {
      node *tmp = alloc_node_.allocate(1);

      tmp->prev_ = position.ptr_->prev_;
      tmp->next_ = position.ptr_;
      alloc_.construct(&tmp->value_, val);

      tmp->prev_->next_ = tmp;
      tmp->next_->prev_ = tmp;
      size_++;
      return iterator(tmp);
    };

    void insert (iterator position, size_type n, const value_type& val) {
      while (n) {
        insert(position, val);
        n--;
      }
    };

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last,
                  typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
      while (first != last) {
        insert(position, *first);
        first++;
      }
    };

    iterator erase (iterator position) {
      node *elem = position.ptr_;
      node *next = position.ptr_->next_;

      elem->prev_->next_ = next;
      next->prev_ = elem->prev_;

      alloc_.destroy(&elem->value_);
      alloc_node_.deallocate(elem, 1);

      size_--;
      return iterator(next);
    };

    iterator erase (iterator first, iterator last) {
      while (first != last) {
        first = erase(first);
      }
      return last;
    };

    void swap (list& x) {
      node *tmp;
      size_type size_tmp;

      size_tmp = size_;
      size_ = x.size_;
      x.size_ = size_tmp;

      tmp = elem_;
      elem_ = x.elem_;
      x.elem_ = tmp;
    };

    void resize (size_type n, value_type val = value_type()) {
      if (size_ < n) {
        insert(end(), n, val);
      };
      while (size_ > n) {
        pop_back();
      };
    };

    void clear() {
      erase(begin(), end());
    };

    void splice (iterator position, list& x) {
      splice(position, x, x.begin(), x.end());
    }

    void splice (iterator position, list& x, iterator i) {
      node *old = i.ptr_;
      node *frsh = position.ptr_;

      old->prev_->next_ = old->next_;
      old->next_->prev_ = old->prev_;

      old->prev_ = frsh->prev_;
      old->next_ = frsh;

      frsh->prev_->next_ = old;
      frsh->prev_ = old;

      size_++;
      x.size_--;
    }

    void splice (iterator position, list& x, iterator first, iterator last) {
      while (first != last) {
        insert(position, *first);
        first = x.erase(first);
      }
    }

    void remove(const value_type& val) {
      iterator it = begin();

      while (it != end())
      {
        if (*it == val)
          it = erase(it);
        else
          it++;
      }
    };

    template <class Predicate>
    void remove_if(Predicate pred) {
      iterator it = begin();

      while (it != end())
      {
        if (pred(*it))
          it = erase(it);
        else
          it++;
      }
    };

    void unique() {
      iterator it1 = begin();

      while (it1 != end())
      {
        if (it1.ptr_->prev_ != end().ptr_ && *it1 == it1.ptr_->prev_->value_)
          it1 = erase(it1);
        else
          it1++;
      }
    };

    template <class BinaryPredicate>
    void unique(BinaryPredicate binary_pred) {
      iterator it1 = begin();

      while (it1 != end())
      {
        if (it1.ptr_->prev_ != end().ptr_ && binary_pred(*it1, it1.ptr_->prev_->value_))
          it1 = erase(it1);
        else
          it1++;
      }
    };

    void merge(list& x) {
      if (&x == this)
        return ;
      iterator it1 = begin();
      iterator it2 = x.begin();

      while (it1 != end() && it2 != x.end()) {
        if (*it2 < *it1) {
          splice(it1, x, it2);
          it2 = x.begin();
        }
        else
          it1++;
      }
      splice(it1, x);
    }

    template <class Compare>
    void merge(list& x, Compare comp) {
      iterator it1 = begin();
      iterator it2 = x.begin();

      while (it1 != end() && it2 != x.end()) {
        if (comp(*it2, *it1)) {
          splice(it1, x, it2);
          it2 = x.begin();
        }
        else
          it1++;
      }
      splice(it1, x);
    }

    void sort() {
      iterator it1;
      iterator it2;

      for (size_type i = 0; i < size_; i++) {
        it1 = begin();
        it2 = ++begin();

        while (it2 != end()) {
          if (*it2 < *it1) {
            splice(it1, *this, it2);
            it2 = it1;
            it2++;
          }
          else {
            it1 = it2;
            it2++;
          }
        }
      }
    };

    template <class Compare>
    void sort (Compare comp) {
      iterator it1 = begin();
      iterator it2 = ++begin();

      while (it2 != end()) {
        if (comp(*it2, *it1)) {
          splice(it1, *this, it2);
          it1 = begin();
          it2 = ++begin();
        }
        else {
          it1++;
          it2++;
        }
	    }
    }

    void reverse() {
      iterator    it = begin();
      node*  tmp;

      elem_->next_ = elem_->prev_;
      elem_->prev_ = it.ptr_;

      while (it != end()) {
        tmp = it.ptr_;
        it++;
        tmp->next_ = tmp->prev_;
        tmp->prev_ = it.ptr_;
      }
    };

   private:
    typedef node_list<T> node;
    typename allocator_type::template rebind<node>::other alloc_node_;

    node                      *elem_;
    size_type                 size_;
    allocator_type            alloc_;
  };

  template <class T>
  bool operator== (const list<T>& lhs, const list<T>& rhs) {
    if (lhs.size() != rhs.size())
      return false;
    typename list<T>::const_iterator it1 = lhs.begin();
    typename list<T>::const_iterator it2 = rhs.begin();

    while (it1 != lhs.end() && it2 != rhs.end()) {
      if (*it1 != *it2)
        return false;
      it1++;
      it2++;
    }
    return (it1 == lhs.end()) && (it2 == rhs.end());
  };

  template <class T>
  bool operator!= (const list<T>& lhs, const list<T>& rhs) { return !(lhs == rhs); };

  template <class T>
  bool operator<  (const list<T>& lhs, const list<T>& rhs) {
    typename list<T>::const_iterator it1 = lhs.begin();
    typename list<T>::const_iterator it2 = rhs.begin();

    while (it1 != lhs.end() && it2 != rhs.end()) {
      if (*it1 < *it2)
        return true;
      if (*it2 < *it1)
        return false;
      it1++;
      it2++;
    }
    return (it1 == lhs.end()) && (it2 != rhs.end());
  };

  template <class T>
  bool operator<= (const list<T>& lhs, const list<T>& rhs) { return !(rhs < lhs); };

  template <class T>
  bool operator>  (const list<T>& lhs, const list<T>& rhs) { return rhs < lhs; };

  template <class T>
  bool operator>= (const list<T>& lhs, const list<T>& rhs) { return !(lhs < rhs); };

  template <class T>
  void swap (list<T>& x, list<T>& y) { x.swap(y); };
}

#endif