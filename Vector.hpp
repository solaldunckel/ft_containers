#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <type_traits>

# include "Iterators.hpp"

namespace ft {
  template <class T, bool isconst = false>
  struct vector_iterator {
    typedef vector_iterator<T, isconst>      self;

    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef typename choose_type<isconst, const T&, T&>::type  reference;
    typedef typename choose_type<isconst, const T*, T*>::type  pointer;

    vector_iterator() : ptr_(nullptr) {};
    vector_iterator(value_type *ptr) : ptr_(ptr) {};
    vector_iterator(const vector_iterator<T, true> &copy) : ptr_(copy.ptr_) {};
    vector_iterator(const vector_iterator<T> &copy) : ptr_(copy.ptr_) {};

    virtual ~vector_iterator() {};

    self   &operator = (const self &rhs)   {
      ptr_ = rhs.ptr_;
      return *this;
    };

    self     operator ++ () {
      ptr_++;
      return *this;
    };
    self     operator ++ (int) {
      self tmp = *this;
      ++(*this);
      return tmp;
    };
    self     operator -- () {
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
    self     operator + (int n) {
      self  tmp(*this);
      return tmp += n;
    };
    self     operator - (int n) {
      self  tmp(*this);
      return tmp -= n;
    };
    difference_type     operator - (self it) {
      return ptr_ - it.ptr_;
    };
    reference operator[] (size_t n) const {
      return ptr_[n];
    };

    bool      operator < (const self &rhs) const   { return ptr_ < rhs.ptr_; };
    bool      operator > (const self &rhs) const   { return ptr_ > rhs.ptr_; };
    bool      operator <= (const self &rhs) const  { return ptr_ <= rhs.ptr_; };
    bool      operator >= (const self &rhs) const  { return ptr_ >= rhs.ptr_; };

    bool      operator == (const self &rhs) const  { return ptr_ == rhs.ptr_; };
    bool      operator != (const self &rhs) const  { return ptr_ != rhs.ptr_; };
    reference operator *  () const                 { return *ptr_; };
    pointer   operator -> () const                 { return ptr_; };

    pointer ptr_;
  };

  template <class T, class Alloc = std::allocator<T> >
  class Vector {
   public:
    typedef T       value_type;
    typedef Alloc   allocator_type;

    typedef typename allocator_type::reference        reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer          pointer;
    typedef typename allocator_type::const_pointer    const_pointer;

    typedef ft::vector_iterator<T>               iterator;
    typedef ft::vector_iterator<T, true>         const_iterator;
    typedef ft::reverse_iterator<iterator>       reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::ptrdiff_t                  difference_type;
    typedef size_t                          size_type;

    explicit Vector(const allocator_type& alloc = allocator_type()) {
      container_ = nullptr;
      alloc_ = alloc;
      size_ = 0;
      capacity_ = 0;
    }

    explicit Vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) {
      container_ = nullptr;
      alloc_ = alloc;
      size_ = 0;
      capacity_ = 0;
      insert(begin(), n, val);
    };

    template <class InputIterator>
    Vector(InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type(),
              typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0) {
      container_ = nullptr;
      alloc_ = alloc;
      size_ = 0;
      capacity_ = 0;
      insert(begin(), first, last);
    };

    Vector(const Vector& x) {
      container_ = nullptr;
      alloc_ = x.alloc_;
      size_ = 0;
      capacity_ = 0;
      assign(x.begin(), x.end());
    };

    Vector& operator= (const Vector& x) {
      assign(x.begin(), x.end());
      return *this;
    };

    ~Vector() {
      clear();
      alloc_.deallocate(container_, capacity_);
    };

    iterator begin()              { return iterator(container_); };
    const_iterator begin() const  { return const_iterator(container_); };
    iterator end()                { return iterator(&container_[size_]); };
    const_iterator end() const    { return const_iterator(&container_[size_]); };

    reverse_iterator rbegin()             { return reverse_iterator(end()); };
    reverse_iterator rend()               { return reverse_iterator(begin()); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
    const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); };

    size_type size() const      { return size_; };
    size_type max_size() const  {
      size_type first = std::numeric_limits<difference_type>::max();
      size_type second = std::numeric_limits<size_type>::max() / sizeof(T);
      return first > second ? second : first;
    };

    void resize (size_type n, value_type val = value_type()) {
      if (size_ < n) {
        insert(end(), n, val);
      }
      while (size_ > n) {
        pop_back();
      };
    }

    size_type capacity() const  { return capacity_; };
    bool      empty() const     { return size_ == 0; };

    void reserve (size_type n) {
      if (n > max_size())
        throw std::length_error("'n' exceeds maximum supported size");
      if (n < capacity_)
        return;

      value_type *new_container = alloc_.allocate(sizeof(T) * n);

      for (size_type i = 0; i < size_; i++) {
        alloc_.construct(&new_container[i], container_[i]);
        alloc_.destroy(&container_[i]);
      }
      alloc_.deallocate(container_, capacity_);
      capacity_ = n;
      container_ = new_container;
    };

    reference operator[] (size_type n) { return container_[n]; };
    const_reference operator[] (size_type n) const { return container_[n]; };

    reference at (size_type n) {
      if (n >= size_)
        throw std::out_of_range("Vector");
      return container_[n];
    };
    const_reference at (size_type n) const {
      if (n >= size_)
        throw std::out_of_range("Vector");
      return container_[n];
    };

    reference front() { return container_[0]; };
    const_reference front() const { return container_[0]; };

    reference back() { return container_[size_ - 1]; };
    const_reference back() const { return container_[size_ - 1]; };

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last) {
      clear();
      insert(begin(), first, last);
    };

    void assign (size_type n, const value_type& val) {
      clear();
      insert(begin(), n, val);
    };

    void push_back (const value_type& val) {
      if (size_ + 1 > capacity_) {
        if (capacity_ == 0)
          reserve(1);
        else
          reserve(capacity_ * 2);
      }
      alloc_.construct(&container_[size_], val);
      size_++;
    };

    void pop_back() {
      alloc_.destroy(&container_[size_ - 1]);
      size_--;
    };

    iterator insert (iterator position, const value_type& val) {
      size_type offset = position - begin();

      if (size_ + 1 > capacity_) {
        if (capacity_ == 0)
          reserve(1);
        else
          reserve(capacity_ * 2);
      }
      if (offset < size_ - 1) {
        for (size_type i = size_; i > offset; i--) {
          alloc_.construct(&container_[i], container_[i - 1]);
          alloc_.destroy(&container_[i - 1]);
        }
      }
      alloc_.construct(&container_[offset], val);
      size_++;
      return iterator(&container_[offset]);
    };

    void insert (iterator position, size_type n, const value_type& val) {
      size_type offset = position - begin();

      if (size_ + n > capacity_)
        reserve(capacity_ + n);

      for (size_type i = n + size_ - 1; i > offset + n - 1; i--) {
        alloc_.construct(&container_[i], container_[i - n]);
        alloc_.destroy(&container_[i - n]);
      }
      for (size_type i = offset; i < offset + n; i++) {
        alloc_.construct(&container_[i], val);
        size_++;
      }
    }

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last,
                  typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0) {
      size_type offset = position - begin();
      difference_type n = last - first;

      if (size_ + n > capacity_)
        reserve(capacity_ + n);

      for (size_type i = n + size_ - 1; i > offset + n - 1; i--) {
        alloc_.construct(&container_[i], container_[i - n]);
        alloc_.destroy(&container_[i - n]);
      }
      for (size_type i = offset; i < offset + n; i++) {
        alloc_.construct(&container_[i], *first);
        first++;
        size_++;
      }
    };

    iterator erase (iterator position) {
      size_type offset = position - begin();

      alloc_.destroy(&container_[offset]);
      if (offset < size_ - 1) {
        for (size_type i = offset; i < size_ + offset; i++)
          alloc_.construct(&container_[i], container_[i + 1]);
      }
      size_--;
      return iterator(&container_[offset]);
    };

    iterator erase (iterator first, iterator last) {
      size_type start = first - begin();
      size_type end = last - begin();
      difference_type offset = last - first;

      for (size_type i = start; i < end; i++) {
        alloc_.destroy(&container_[i]);
      }
      if (start < size_ - 1) {
        for (size_type i = start; i < size_ + offset; i++) {
          alloc_.construct(&container_[i], container_[i + offset]);
        }
      }
      size_ -= offset;
      return iterator(&container_[start]);
    };

    void swap (Vector& x) {
      value_type *tmp = x.container_;
      size_type tmp_size = x.size_;
      size_type tmp_capacity = x.capacity_;

      x.container_ = container_;
      container_ = tmp;

      x.size_ = size_;
      size_ = tmp_size;

      x.capacity_ = capacity_;
      capacity_ = tmp_capacity;
    };

    void clear() { erase(begin(), end()); };

   private:
    value_type      *container_;
    allocator_type  alloc_;
    size_type       size_;
    size_type       capacity_;
  };

  template <class T>
  bool operator== (const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size())
      return false;
    for (size_t i = 0; i < lhs.size(); i++) {
      if (lhs[i] != rhs[i])
        return false;
    }
    return true;
  };

  template <class T>
  bool operator!= (const Vector<T>& lhs, const Vector<T>& rhs) { return !(lhs == rhs); };

  template <class T>
  bool operator<  (const Vector<T>& lhs, const Vector<T>& rhs) {
    typename Vector<T>::const_iterator it1 = lhs.begin();
    typename Vector<T>::const_iterator it2 = rhs.begin();

    while (it1 != lhs.end() && it2 != rhs.end()) {
      if (*it1 < *it2)
        return true;
      else if (*it1 > *it2)
        return false;
      it1++;
      it2++;
    }
    return (it2 != rhs.end());
  };

  template <class T>
  bool operator<= (const Vector<T>& lhs, const Vector<T>& rhs) { return !(rhs < lhs); };

  template <class T>
  bool operator>  (const Vector<T>& lhs, const Vector<T>& rhs) { return rhs < lhs; };

  template <class T>
  bool operator>= (const Vector<T>& lhs, const Vector<T>& rhs) { return !(lhs < rhs); };

  template <class T>
  void swap (Vector<T>& x, Vector<T>& y) { x.swap(y); };
};

#endif