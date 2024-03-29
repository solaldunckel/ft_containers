#ifndef UTILITY_HPP
# define UTILITY_HPP

# include <memory>
# include <limits>
# include <cstddef>

namespace ft {
  template <class T>
  struct less {
    typedef bool  result_type;
    typedef T     first_argument_type;
    typedef T     second_argument_type;

    bool operator() (const T &lhs, const T &rhs) const { return lhs < rhs; };
  };

  template <class Compare, class T>
  class Comp {
   public:
    Comp(Compare c) : comp_(c) {};

    bool operator()(const T& x, const T& y) const { return comp_(x.first, y.first); };

    Compare comp_;
  };

  // ALLOCATOR

  template <class T>
  class allocator {
   public:
    typedef T        value_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    template <class U>
    struct rebind { typedef ft::allocator<U> other; };

    // return address of values
    pointer address (reference value) const { return &value; }
    const_pointer address (const_reference value) const { return &value; }

    allocator() throw() {}
    allocator(const allocator&) throw() {}

    template <class U>
    allocator (const allocator<U>&) throw() {}

    ~allocator() throw() {}

    size_type max_size () const throw() { return std::numeric_limits<std::size_t>::max() / sizeof(T); }

    pointer allocate (size_type num, const void* = 0) {
      return reinterpret_cast<pointer>(::operator new(num * sizeof (T)));
    }

    void construct (pointer p, const T& value) {
      new(p) T(value);
    }

    void destroy (pointer p) {
      p->~T();
    }

    void deallocate (pointer p, size_type) {
      ::operator delete(p);
    }
    bool operator== (const allocator&) throw() { return true; }
    bool operator!= (const allocator &a) throw() { return !operator==(a); }
  };

  // ENABLE_IF / IS_INTEGRAL

  template<bool B, class T = void>
  struct enable_if {};

  template<class T>
  struct enable_if<true, T> { typedef T type; };

  template <typename T>
  struct is_integral { static const bool value = false; };

  template <>
  struct is_integral<bool> { static const bool value = true; };

  template <>
  struct is_integral<char> { static const bool value = true; };

  template <>
  struct is_integral<short> { static const bool value = true; };

  template <>
  struct is_integral<int> { static const bool value = true; };

  template <>
  struct is_integral<long> { static const bool value = true; };

  template <>
  struct is_integral<long long> { static const bool value = true; };

  template <>
  struct is_integral<unsigned char> { static const bool value = true; };

  template <>
  struct is_integral<unsigned short> { static const bool value = true; };

  template <>
  struct is_integral<unsigned int> { static const bool value = true; };

  template <>
  struct is_integral<unsigned long> { static const bool value = true; };

  template <>
  struct is_integral<unsigned long long> { static const bool value = true; };

  // PAIR

  template <class T1, class T2>
  struct pair {
    typedef T1   first_type;
    typedef T2   second_type;

    pair() : first(), second() {};
    pair (const first_type &a, const second_type &b) : first(a), second(b) {};

    template<class U, class V>
    pair (const pair<U, V> &pr) : first(pr.first), second(pr.second) {};

    ~pair() {};

    pair<T1, T2>  &operator= (const pair<T1, T2> &pr) {
      first = pr.first;
      second = pr.second;
      return *this;
    };

    first_type  first;
    second_type second;
  };

  template <class T1, class T2>
  bool operator== (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  };

  template <class T1, class T2>
  bool operator!= (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    return !(lhs == rhs);
  };

  template <class T1, class T2>
  bool operator<  (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    return lhs.first < rhs.first
      || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
  };

  template <class T1, class T2>
  bool operator<= (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    return !(rhs < lhs);
  };

  template <class T1, class T2>
  bool operator>  (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    return rhs < lhs;
  };

  template <class T1, class T2>
  bool operator>= (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    return !(lhs < rhs);
  };

  template <class T1, class T2>
  ft::pair<T1, T2> make_pair(T1 t, T2 u) {
    return ft::pair<T1, T2>(t, u);
  };
};

#endif
