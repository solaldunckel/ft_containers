#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <limits>
# include <type_traits>

# include "Utility.hpp"
# include "Iterators.hpp"

namespace ft {
  template <class Key, class T>
  struct Tree {
    Tree                      *left_;
    Tree                      *right_;
    Tree                      *parent_;
    ft::pair<const Key, T>    pair_;

    Tree() : left_(this), right_(this), parent_(nullptr), pair_(ft::pair<const Key, T>()) {};
    Tree(Tree *left, Tree *right, Tree *parent, const ft::pair<const Key, T> &pair)
        : left_(left), right_(right), parent_(parent), pair_(pair) {};
  };

  template <class Key, class T>
  struct MapIterator {
    typedef MapIterator<Key, T>             self;
    typedef Tree<Key, T>                    container;

    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ft::pair<const Key, T>          value_type;
    typedef value_type&                     reference;
    typedef value_type*                     pointer;

    MapIterator() : ptr_(nullptr) {};
    MapIterator(container *ptr) : ptr_(ptr) {};
    MapIterator(const self &copy) : ptr_(copy.ptr_) {};

    virtual ~MapIterator() {};

    self   &operator = (const self &rhs)   {
      ptr_ = rhs.ptr_;
      return *this;
    };

    self     operator ++ () {
      if (ptr_->right_) {
        ptr_ = ptr_->right_;
        while (ptr_->left_ && ptr_->left_ != ptr_)
          ptr_ = ptr_->left_;
      }
      else {
        container* tmp = ptr_;

        ptr_ = ptr_->parent_;
        while (ptr_->left_ != tmp) {
          tmp = ptr_;
          ptr_ = ptr_->parent_;
        }
      }
      return *this;
    };

    self     operator ++ (int) {
      self tmp = *this;
      ++(*this);
      return tmp;
    };
    self     operator -- () {
      return *this;
    };
    self     operator -- (int) {
      self tmp = *this;
      --(*this);
      return tmp;
    };

    bool      operator == (const self &rhs) const   { return ptr_ == rhs.ptr_; };
    bool      operator != (const self &rhs)         { return ptr_ != rhs.ptr_; };
    reference operator *  ()                        { return ptr_->pair_; };
    pointer   operator -> ()                        { return &ptr_->pair_; };

    container *ptr_;
  };

  template <class Key, class T, class Compare = ft::less<Key>,
              class Alloc = std::allocator<ft::pair<const Key, T> > >
  class Map {
   public:
    typedef Key                                     key_type;
    typedef T                                       mapped_type;
    typedef ft::pair<const key_type, mapped_type>   value_type;
    typedef Compare                                 key_compare;
    typedef Compare                                 value_compare;

    typedef Alloc                                     allocator_type;;
    typedef typename allocator_type::reference        reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer          pointer;
    typedef typename allocator_type::const_pointer    const_pointer;

    typedef MapIterator<key_type, mapped_type>        iterator;
    typedef MapIterator<key_type, mapped_type>        const_iterator;
    typedef ReverseIterator<iterator>                 reverse_iterator;
    typedef ReverseIterator<const_iterator>           const_reverse_iterator;

    typedef std::ptrdiff_t                  difference_type;
    typedef size_t                          size_type;

    // Constructors
   public:
    explicit Map(const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type()) {
      container_ = new tree();
      begin_ = container_;
      end_ = container_;
      alloc_ = alloc;
      comp_ = comp;
      size_ = 0;
    }

    // Iterators

    iterator begin() { return iterator(begin_); };
    iterator end() { return iterator(container_); };
    const_iterator begin() const { return const_iterator(begin_); };
    const_iterator end() const { return const_iterator(container_); };

    reverse_iterator rbegin() { return reverse_iterator(end_); };
    reverse_iterator rend() { return reverse_iterator(container_); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end_); };
    const_reverse_iterator rend() const { return const_reverse_iterator(container_); };

    mapped_type& operator[] (const key_type& k) {
      return (*((insert(make_pair(k, mapped_type()))).first)).second;
    };

    // Capacity
    bool        empty() const     { return size_ == 0; };
    size_type   size() const      { return size_; };
    size_type   max_size() const  {};

    // Modifiers
  
    pair<iterator, bool> insert (const value_type& val) {
      tree *exist = key_exists_recurse(container_->right_, val.first);

      if (exist)
        return make_pair(iterator(exist), false);

      tree *node = insert_node(container_, comp_, val);
      size_++;
      reset_begin_end();
      return make_pair(iterator(node), true);
    };

    // ft::pair<iterator, bool> insert (const value_type &val) {

    // };


    // BST Functions
   private:
    typedef Tree<Key, T>  tree;
    // Key search

    tree  *key_exists_recurse(tree *root, key_type key) {
      tree *found = nullptr;

      if (root)
        return found;
      found = key_exists_recurse(root->left_, key);
      if (root->pair_.first == key)
        found = root;
      if (!found)
        found = key_exists_recurse(root->right_, key);
	    return found;
    }

    // Insert Node

    void  reset_begin_end() {
      tree *tmp = begin_;

      while (tmp->left_ && tmp->left_ != container_)
        tmp = tmp->left_;
      begin_ = tmp;
      tmp->left_ = container_;

      tmp = container_->right_;
      while (tmp->right_ && tmp->right_ != container_)
        tmp = tmp->right_;
      end_ = tmp;
      tmp->right_ = container_;
    }

    tree	*insert_node(tree *node, key_compare comp, value_type pair)
    {
      if (node == container_) {
        if (node->right_ == node) {
          node->right_ = new tree(nullptr, nullptr, node, pair);
          begin_ = node->right_;
          return begin_;
        }
        else
          node = insert_node(node->right_, comp, pair);
      }
      else if (comp(pair.first, node->pair_.first))
      {
        if (!node->left_ || node->left_ == container_) {
          node->left_ = new tree(nullptr, nullptr, node, pair);
          return node->left_;
        }
        else
          node = insert_node(node->left_, comp, pair);
      }
      else
      {
        if (!node->right_ || node->right_ == container_) {
          node->right_ = new tree(nullptr, nullptr, node, pair);
          return node->right_;
        }
        else
          node = insert_node(node->right_, comp, pair);
      }
      return node;
    }

    tree            *container_;
    tree            *begin_;
    tree            *end_;
    allocator_type  alloc_;
    key_compare     comp_;
    size_type       size_;
  };
};

#endif