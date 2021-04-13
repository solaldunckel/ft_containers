#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <iostream>
# include <string>
# include <cstddef> // ptrdiff_t
# include <sstream> // ostring

# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"
# include "utils_containers.hpp"

namespace ft {
  template <class T, class Alloc = ft::allocator<T> >
  class vector {
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
    typedef std::size_t                     size_type;

    explicit vector(const allocator_type& alloc = allocator_type()) {
      container_ = NULL;
      alloc_ = alloc;
      size_ = 0;
      capacity_ = 0;
    }

    explicit vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) {
      container_ = NULL;
      alloc_ = alloc;
      size_ = 0;
      capacity_ = 0;
      insert(begin(), n, val);
    };

    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type(),
              typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
      container_ = NULL;
      alloc_ = alloc;
      size_ = 0;
      capacity_ = 0;
      insert(begin(), first, last);
    };

    vector(const vector& x) {
      container_ = NULL;
      alloc_ = x.alloc_;
      size_ = 0;
      capacity_ = 0;
      assign(x.begin(), x.end());
    };

    vector& operator= (const vector& x) {
      if (&x == this)
        return *this;
      assign(x.begin(), x.end());
      return *this;
    };

    ~vector() {
      clear();
      alloc_.deallocate(container_, capacity_);
    };

    iterator begin()              { return iterator(container_); };
    const_iterator begin() const  { return const_iterator(container_); };
    iterator end()                { return iterator(container_ + size_); };
    const_iterator end() const    { return const_iterator(container_ + size_); };

    reverse_iterator rbegin()             { return reverse_iterator(end()); };
    reverse_iterator rend()               { return reverse_iterator(begin()); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
    const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); };

    size_type size() const      { return size_; };
    size_type max_size() const  { return alloc_.max_size(); };

    void resize (size_type n, value_type val = value_type()) {
      if (n > capacity_) {
        if (capacity_ == 0)
          reserve(n);
        else {
          if (size_ * 2 >= n)
            reserve(size_ * 2);
          else
            reserve(n);
        }
      }
      while (size_ < n) {
        push_back(val);
      }
      while (size_ > n) {
        pop_back();
      };
    }

    size_type capacity() const  { return capacity_; };
    bool      empty() const     { return size_ == 0; };

    void reserve (size_type n) {
      if (n > max_size())
        throw std::length_error("vector::reserve");
      if (n < capacity_)
        return;

      value_type *new_container = alloc_.allocate(n);

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
      if (n >= size_) {
        std::stringstream ss;
        ss << "vector";
        #ifdef __linux__
          ss << "::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << size_ << ")";
        #endif
        throw std::out_of_range(ss.str().c_str());
      }
      return container_[n];
    };
    const_reference at (size_type n) const {
      if (n >= size_) {
        std::stringstream ss;
        ss << "vector";
        #ifdef __linux__
          ss << "::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << size_ << ")";
        #endif
        throw std::out_of_range(ss.str().c_str());
      }
      return container_[n];
    };

    reference front() { return container_[0]; };
    const_reference front() const { return container_[0]; };

    reference back() { return container_[size_ - 1]; };
    const_reference back() const { return container_[size_ - 1]; };

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last,
          typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
      clear();
      InputIterator tmp = first;
      difference_type n = 0;

      while (tmp != last) {
        n++;
        tmp++;
      }

      reserve(n);
      insert(begin(), first, last);
    };

    void assign (size_type n, const value_type& val) {
      clear();
      reserve(n);
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
      if (size_) {
        alloc_.destroy(&container_[size_ - 1]);
        size_--;
      }
    };

    iterator insert (iterator position, const value_type& val) {
      size_type index = position - begin();

      if (size_ + 1 > capacity_) {
        if (capacity_ == 0)
          reserve(1);
        else
          reserve(capacity_ * 2);
      }
      size_++;
      if (index < size_) {
        for (size_type i = size_ - 1; i > index; i--) {
          alloc_.construct(&container_[i], container_[i - 1]);
          alloc_.destroy(&container_[i - 1]);
        }
      }
      alloc_.construct(&container_[index], val);
      return iterator(&container_[index]);
    };

    void insert (iterator position, size_type n, const value_type& val) {
      size_type index = position - begin();

      if (size_ + n > capacity_) {
        if (capacity_ == 0)
          reserve(n);
        else {
          if (capacity_ * 2 >= size_ + n)
            reserve(capacity_ * 2);
          else
            reserve(size_ + n);
        }
      }

      for (size_type i = n + size_ - 1; i > index + n - 1; i--) {
        alloc_.construct(&container_[i], container_[i - n]);
        alloc_.destroy(&container_[i - n]);
      }
      for (size_type i = index; i < index + n; i++) {
        alloc_.construct(&container_[i], val);
        size_++;
      }
    }

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last,
                  typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
      size_type offset = position - begin();
      InputIterator tmp = first;
      difference_type n = 0;

      while (tmp != last) {
        n++;
        tmp++;
      }

      if (size_ + n > capacity_) {
        if (capacity_ == 0)
          reserve(n);
        else {
          if (capacity_ * 2 >= size_ + n)
            reserve(capacity_ * 2);
          else
            reserve(size_ + n);
        }
      }

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
      size_type index = position - begin();

      alloc_.destroy(&container_[index]);
      size_--;
      if (index < size_) {
        for (size_type i = index; i < size_; i++) {
          alloc_.construct(&container_[i], container_[i + 1]);
          alloc_.destroy(&container_[i + 1]);
        }
      }
      return iterator(&container_[index]);
    };

    iterator erase (iterator first, iterator last) {
      size_type start = first - begin();
      difference_type offset = last - first;

      if (first == last)
        return iterator(first);

      for (iterator it = first; it != last; it++)
        alloc_.destroy(&(*it));

      size_ -= offset;
      if (start < size_) {
        for (size_type i = start; i < size_; i++) {
          alloc_.construct(&container_[i], container_[i + offset]);
          alloc_.destroy(&container_[i + offset]);
        }
      }
      return iterator(&container_[start]);
    };

    void swap (vector& x) {
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
  bool operator== (const vector<T>& lhs, const vector<T>& rhs) {
    if (lhs.size() != rhs.size())
      return false;
    for (size_t i = 0; i < lhs.size(); i++) {
      if (lhs[i] != rhs[i])
        return false;
    }
    return true;
  };

  template <class T>
  bool operator!= (const vector<T>& lhs, const vector<T>& rhs) { return !(lhs == rhs); };

  template <class T>
  bool operator<  (const vector<T>& lhs, const vector<T>& rhs) {
    typename vector<T>::const_iterator it1 = lhs.begin();
    typename vector<T>::const_iterator it2 = rhs.begin();

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
  bool operator<= (const vector<T>& lhs, const vector<T>& rhs) { return !(rhs < lhs); };

  template <class T>
  bool operator>  (const vector<T>& lhs, const vector<T>& rhs) { return rhs < lhs; };

  template <class T>
  bool operator>= (const vector<T>& lhs, const vector<T>& rhs) { return !(lhs < rhs); };

  template <class T>
  void swap (vector<T>& x, vector<T>& y) { x.swap(y); };
};

#endif