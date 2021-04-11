#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "utils_iterator.hpp"
# include "utils_containers.hpp"

namespace ft {
  template <typename T>
  struct Tree {
    bool unused_;
    #ifdef __linux__
      int unused2_;
    #endif

    Tree *left_;
    Tree *right_;
    Tree *parent_;
    T pair_;
  };
  
  template <class Key, class T, bool isconst = false>
  struct map_iterator {
    typedef map_iterator<Key, T, isconst>   self;

    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ft::pair<const Key, T>          value_type;
    typedef typename choose_type<isconst,
              const value_type&, value_type&>::type       reference;
    typedef typename choose_type<isconst,
              const value_type*, value_type*>::type       pointer;
    typedef typename choose_type<isconst,
              const Tree<value_type>*, Tree<value_type>*>::type   nodeptr;

    map_iterator() : ptr_(NULL) {};
    map_iterator(nodeptr ptr) : ptr_(ptr) {};
    map_iterator(const map_iterator<Key, T, false> &copy) : ptr_(copy.ptr_) {};
    map_iterator(const map_iterator<Key, T, true> &copy) : ptr_(copy.ptr_) {};

    virtual ~map_iterator() {};

    self   &operator = (const self &rhs) {
      ptr_ = rhs.ptr_;
      return *this;
    };

    self     &operator ++ () {
      if ((ptr_->right_ && ptr_->right_->parent_ != ptr_)
        || (ptr_->left_ && ptr_->left_->parent_ != ptr_))
        ptr_ = ptr_->left_;
      else if (ptr_->right_) {
        ptr_ = ptr_->right_;
        while (ptr_->left_)
          ptr_ = ptr_->left_;
      }
      else {
        nodeptr tmp = ptr_->parent_;

        while (ptr_ == tmp->right_) {
          ptr_ = tmp;
          tmp = tmp->parent_;
        }
        if (ptr_->right_ != tmp)
          ptr_ = tmp;
      }
      return *this;
    };

    self     operator ++ (int) {
      self tmp = *this;
      ++(*this);
      return tmp;
    };

    self     &operator -- () {
      if ((ptr_->right_ && ptr_->right_->parent_ != ptr_)
        || (ptr_->left_ && ptr_->left_->parent_ != ptr_))
        ptr_ = ptr_->right_;
      else if (ptr_->left_) {
        ptr_ = ptr_->left_;
        while (ptr_->right_)
          ptr_ = ptr_->right_;
      }
      else {
        nodeptr tmp = ptr_->parent_;

        while (ptr_ == tmp->left_) {
          ptr_ = tmp;
          tmp = tmp->parent_;
        }
        ptr_ = tmp;
      }
      return *this;
    };

    self     operator -- (int) {
      self tmp = *this;
      --(*this);
      return tmp;
    };

    bool      operator == (const self &rhs) const   { return ptr_ == rhs.ptr_; };
    bool      operator != (const self &rhs) const   { return ptr_ != rhs.ptr_; };
    reference operator *  () const                  { return ptr_->pair_; };
    pointer   operator -> () const                  { return &ptr_->pair_; };

    nodeptr ptr_;
  };
}

#endif