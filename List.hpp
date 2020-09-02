#ifndef LIST_HPP
# define LIST_HPP

# include "Iterators.hpp"

namespace ft {
  template <typename T>
  struct Node {
    Node *prev_;
    Node *next_;
    T    value_;

    Node() {};
    Node(Node *prev, Node *next, T val) : prev_(prev), next_(next), value_(val) {};
  };

  template <class T>
  class ListIterator {
   public:
    typedef ListIterator<T>                 self_;
    typedef Node<T>                         node_;

    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef T&                              reference;
    typedef T*                              pointer;

    ListIterator() : ptr_(0) {};
    ListIterator(node_ *ptr) : ptr_(ptr) {};
    ListIterator(const self_ &copy) : ptr_(copy.ptr_) {};

    virtual ~ListIterator() {};

    self_   operator = (const self_ &rhs)   {
      ptr_ = rhs.ptr_;
      return *this;
    };

    self_     operator ++ () {
      ptr_ = ptr_->next_;
      return *this;
    };
    self_     operator ++ (int) {
      self_ tmp = *this;
      ++(*this);
      return tmp;
    };
    self_     operator -- () {
      ptr_ = ptr_->prev_;
      return *this;
    };
    self_     operator -- (int) {
      self_ tmp = *this;
      --(*this);
      return tmp;
    };

    bool      operator == (const self_ &rhs)  { return ptr_ == rhs.ptr_; };
    bool      operator != (const self_ &rhs)  { return ptr_ != rhs.ptr_; };
    reference operator *  ()                  { return ptr_->value_; };
    pointer   operator -> ()                  { return &ptr_->value_; };

    node_ *ptr_;
  };

  template <class T>
  class ConstListIterator : public ListIterator<T> {
   public:
    ConstListIterator() {};
    ConstListIterator(Node<T> *ptr) { this->ptr_ = ptr; };
    ConstListIterator(const ConstListIterator<T> &copy) { this->ptr_ = copy.ptr_; };

    virtual ~ConstListIterator() {};

    ConstListIterator<T>   operator = (const ConstListIterator<T> &rhs)   {
      this->ptr_ = rhs.ptr_;
      return *this;
    };

    const T operator * () { return this->ptr_->value_; };
  };

  template <class T>
  class List {
   public:
    typedef T           value_type;
    typedef size_t      size_type;

    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;

    typedef ListIterator<T>           iterator;
		typedef ConstListIterator<T>      const_iterator;
		typedef ReverseIterator<iterator>        reverse_iterator;
		typedef ReverseIterator<const_iterator>  const_reverse_iterator;

    typedef typename iterator::difference_type     difference_type;

    explicit List() {
      elem_ = new node_();
      elem_->prev_ = elem_;
      elem_->next_ = elem_;
      elem_->value_ = T();
      size_ = 0;
    };

    explicit List(size_type n, const value_type& val) {
      elem_ = new node_();
      elem_->prev_ = elem_;
      elem_->next_ = elem_;
      elem_->value_ = T();
      size_ = 0;
      insert(end(), n, val);
    };

    template <class InputIterator>
    List(InputIterator first, InputIterator last) {
      elem_ = new node_();
      elem_->prev_ = elem_;
      elem_->next_ = elem_;
      elem_->value_ = T();
      size_ = 0;
      insert(end(), first, last);
    };

    List(List &x) {
      elem_ = new node_();
      elem_->prev_ = elem_;
      elem_->next_ = elem_;
      elem_->value_ = T();
      size_ = 0;
      assign(x.begin(), x.end());
    };

    ~List() {
      clear();
      delete elem_;
    };

    List& operator = (const List& x) {
      assign(x.begin(), x.end());
      return *this;
    };

    iterator begin() { return iterator(elem_->next_); };
    iterator end() { return iterator(elem_); };
    const_iterator begin() const { return const_iterator(elem_->next_); };
    const_iterator end() const { return const_iterator(elem_); };

    reverse_iterator rbegin() { return reverse_iterator(elem_->prev_); };
    reverse_iterator rend() { return reverse_iterator(elem_); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(elem_->prev_); };
    const_reverse_iterator rend() const { return const_reverse_iterator(elem_); };

    bool empty() const { return size_ == 0; };
    size_type size() const { return size_; };
    size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(node_); };

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
    void pop_back()                         { erase(end()); };

    iterator insert (iterator position, const value_type& val) {
      node_ *node = new node_(position.ptr_->prev_, position.ptr_, val);

      node->prev_->next_ = node;
      node->next_->prev_ = node;
      size_++;
      return iterator(node);
    };

    void insert (iterator position, size_type n, const value_type& val) {
      while (n) {
        insert(position, val);
        n--;
      }
    };

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last) {
      while (first != last) {
        insert(position, *first);
        first++;
      }
    };

    iterator erase (iterator position) {
      node_ *elem = position.ptr_;
      node_ *next = position.ptr_->next_;

      if (position == end()) {
        next = elem;
        elem = elem->prev_;
      }
      elem->prev_->next_ = next;
      next->prev_ = elem->prev_;
      delete elem;
      size_--;
      return iterator(next);
    };

    iterator erase (iterator first, iterator last) {
      while (first != last) {
        erase(first);
        first++;
      }
      return last;
    };

    void swap (List& x) {
      node_ *tmp;
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
        pop_back(val);
      };
    };

    void clear() {
      erase(begin(), end());
    };

    void splice (iterator position, List& x) {
      splice(position, x, x.begin(), x.end());
    }

    void splice (iterator position, List& x, iterator i) {
      node_ *old = i.ptr_;
      node_ *frsh = position.ptr_;

      old->prev_->next_ = old->next_;
      old->next_->prev_ = old->prev_;

      old->prev_ = frsh->prev_;
      old->next_ = frsh;

      frsh->prev_->next_ = old;
      frsh->prev_ = old;

      size_++;
      x.size_--;
    }

    void splice (iterator position, List& x, iterator first, iterator last) {
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
        if (it1.ptr_->next_ != end().ptr_ && *it1 == it1.ptr_->next_->value_)
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
        if (it1.ptr_->next_ != end().ptr_ && binary_pred(*it1, it1.ptr_->next_->value_))
          it1 = erase(it1);
        else
          it1++;
      }
    };

    void merge(List& x) {
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
    void merge(List& x, Compare comp) {
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
      iterator it1 = begin();
      iterator it2 = ++begin();

			while (it2 != end())
			{
        if (*it2 < *it1) {
          splice(it1, *this, it2);
          it1 = begin();
          it2 = ++begin();
        }
        else {
          it1++;
          it2++;
        }
			}
    };

    template <class Compare>
    void sort (Compare comp) {
			iterator it1 = begin();
      iterator it2 = ++begin();

			while (it2 != end())
			{
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
      iterator it = begin();
      node_* tmp;

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
    typedef Node<T> node_;

    node_       *elem_;
    size_type   size_;
  };

  template <class T>
  bool operator== (const List<T>& lhs, const List<T>& rhs) {
    if (lhs.size() != rhs.size())
      return false;

    typename List<T>::iterator it1 = lhs.begin();
    typename List<T>::iterator it2 = rhs.begin();

    while (it1 != lhs.end()) {
      if (*it1 != *it2)
        return false;
      it1++;
      it2++;
    }
    return true;
  };

  template <class T>
  bool operator!= (const List<T>& lhs, const List<T>& rhs) { return !(lhs == rhs); };

  template <class T>
  bool operator<  (const List<T>& lhs, const List<T>& rhs) {
    typename List<T>::iterator it1 = lhs.begin();
    typename List<T>::iterator it2 = rhs.begin();

    while (it1 != lhs.end()) {
      if (*it1 < *it2)
        return true;
      else if (*it1 > *it2)
        return false;
      it1++;
      it2++;
    }
    return false;
  };

  template <class T>
  bool operator<= (const List<T>& lhs, const List<T>& rhs) { return !(lhs < rhs); };

  template <class T>
  bool operator>  (const List<T>& lhs, const List<T>& rhs) { return rhs < lhs; };

  template <class T>
  bool operator>= (const List<T>& lhs, const List<T>& rhs) { return !(rhs < lhs); };

  template <class T>
  void swap (List<T>& x, List<T>& y) { x.swap(y); };
}

#endif