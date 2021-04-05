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
  class comp {
   public:
    comp(Compare c) : comp_(c) {};

    bool operator()(const T& x, const T& y) const { return comp_(x.first, y.first); };

    Compare comp_;
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
