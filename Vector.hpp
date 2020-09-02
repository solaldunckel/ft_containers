#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cmath>

namespace ft {
  template <class T, class Alloc = std::allocator<T> >
  class Vector {
   public:
    typedef T     value_type;
    typedef Alloc allocator_type;

    typedef typename allocator_type::reference        reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer          pointer;
    typedef typename allocator_type::const_pointer    const_pointer;

    // typedef VectorIterator<T>               iterator;
    // typedef VectorIterator<const T>         const_iterator;
    // typedef ReverseIterator<iterator>       reverse_iterator;
    // typedef ReverseIterator<const_iterator> const_reverse_iterator;
    typedef std::ptrdiff_t                  difference_type;
    typedef size_t                          size_type;

    Vector(const allocator_type& alloc = allocator_type()) {
      (void)alloc;
      array_ = NULL;
      size_ = 0;
      capacity_ = 0;
    }

    ~Vector() {};

    // Iterators

    // Capacity

    size_type size() const { return size_; };

    size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(T); };

    size_type capacity() const { return capacity_; };

    void reserve (size_type n) {
      if (n > max_size())
        throw std::length_error("'n' exceeds maximum supported size");
      if (n < capacity_)
        return;
      capacity_ = n;
      array_ = new T[n];
    };

    bool empty() const { return size_ == 0; };



   private:
    value_type  *array_;
    size_type   size_;
    size_type   capacity_;
  };
};

#endif