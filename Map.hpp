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
        while (ptr_->left_)
          ptr_ = ptr_->left_;
      }
      else {
        container* tmp = ptr_->parent_;

        while (ptr_ == tmp->right_) {
          ptr_ = tmp;
          tmp = ptr_->parent_;
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

    self     operator -- () {
      if (ptr_->parent_->parent_ == ptr_) {
        ptr_ = ptr_->right_;
      }
      else if (ptr_->left_) {
        ptr_ = ptr_->left_;
        while (ptr_->right_)
          ptr_ = ptr_->right_;
      }
      else {
        container* tmp = ptr_->parent_;

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
    bool      operator != (const self &rhs)         { return ptr_ != rhs.ptr_; };
    reference operator *  ()                        { return ptr_->pair_; };
    pointer   operator -> ()                        { return &ptr_->pair_; };

    container *ptr_;
  };

  template <class Key, class T>
  struct ConstMapIterator {
    typedef ConstMapIterator<Key, T>             self;
    typedef Tree<Key, T>                    container;

    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ft::pair<const Key, T>          value_type;
    typedef value_type&                     reference;
    typedef value_type*                     pointer;

    ConstMapIterator() : ptr_(nullptr) {};
    ConstMapIterator(container *ptr) : ptr_(ptr) {};
    ConstMapIterator(const self &copy) : ptr_(copy.ptr_) {};

    virtual ~ConstMapIterator() {};

    self   &operator = (const self &rhs)   {
      ptr_ = rhs.ptr_;
      return *this;
    };

    self     operator ++ () {
      if (ptr_->right_) {
        ptr_ = ptr_->right_;
        while (ptr_->left_)
          ptr_ = ptr_->left_;
      }
      else {
        container* tmp = ptr_->parent_;

        while (ptr_ == tmp->right_) {
          ptr_ = tmp;
          tmp = ptr_->parent_;
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

    self     operator -- () {
      if (ptr_->parent_->parent_ == ptr_) {
        ptr_ = ptr_->right_;
      }
      else if (ptr_->left_) {
        ptr_ = ptr_->left_;
        while (ptr_->right_)
          ptr_ = ptr_->right_;
      }
      else {
        container* tmp = ptr_->parent_;

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
    typedef ConstMapIterator<key_type, mapped_type>   const_iterator;
    typedef ReverseIterator<iterator>                 reverse_iterator;
    typedef ReverseIterator<const_iterator>           const_reverse_iterator;

    typedef std::ptrdiff_t                  difference_type;
    typedef size_t                          size_type;

    // Constructors
   public:
    explicit Map(const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type()) {
      container_ = new tree();
      alloc_ = alloc;
      comp_ = comp;
      size_ = 0;
    }

    template <class InputIterator>
    Map(InputIterator first, InputIterator last,
          const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
      container_ = new tree();
      alloc_ = alloc;
      comp_ = comp;
      size_ = 0;
      insert(first, last);
    };

    // Map(const Map& x) {

    // };

    Map& operator= (const Map& x);

    // Iterators

    iterator begin() { return iterator(get_left()); };
    iterator end() { return iterator(container_); };
    const_iterator begin() const { return const_iterator(get_left()); };
    const_iterator end() const { return const_iterator(container_); };

    reverse_iterator rbegin() { return reverse_iterator(get_right()); };
    reverse_iterator rend() { return reverse_iterator(container_); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(get_right()); };
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
      tree *exist = key_exists_recurse(get_root(), val.first);

      if (exist)
        return make_pair(iterator(exist), false);
      size_++;
      return make_pair(iterator(insert_node(container_, comp_, val)), true);
    };

    iterator insert (iterator position, const value_type& val) {
      (void)position;
      tree *exist = key_exists_recurse(get_root(), val.first);

      if (exist)
        return iterator(exist);
      size_++;
      return iterator(insert_node(container_, comp_, val));
    };

    template <class InputIterator>
    void insert (InputIterator first, InputIterator last,
                typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0) {
      while (first != last) {
        insert(*first);
        first++;
      }
    };

    // void      erase(iterator position) {};
    // size_type erase(const key_type& k) {};
    // void      erase(iterator first, iterator last) {};

    void swap (Map& x) {
      tree *tmp;
      size_type size_tmp;

      size_tmp = size_;
      size_ = x.size_;
      x.size_ = size_tmp;

      tmp = container_;
      container_ = x.container_;
      x.container_ = tmp;
    };

    void clear();

    key_compare key_comp() const { return comp_; };
    value_compare value_comp() const { return comp_; };

    iterator find (const key_type& k) {
      tree *found = key_exists_recurse(get_root(), k);

      if (found)
        return iterator(found);
      return (end());
    };

    const_iterator find (const key_type& k) const {
      tree *found = key_exists_recurse(get_root(), k);

      if (found)
        return const_iterator(found);
      return (end());
    };

    size_type count (const key_type& k) const {
      return key_count_recurse(get_root(), k);
    };

    iterator        lower_bound (const key_type& k);
    const_iterator  lower_bound (const key_type& k) const;

    iterator        upper_bound (const key_type& k);
    const_iterator  upper_bound (const key_type& k) const;

    pair<iterator, iterator>             equal_range (const key_type& k);
    pair<const_iterator, const_iterator> equal_range (const key_type& k) const;

   private:
    typedef Tree<Key, T>  tree;

    tree  *key_exists_recurse(tree *root, key_type key) {
      tree *found = get_root();

      if (!root)
        return nullptr;
      found = key_exists_recurse(root->left_, key);
      if (root->pair_.first == key)
        found = root;
      if (!found)
        found = key_exists_recurse(root->right_, key);
	    return found;
    }

    size_type key_count_recurse(tree *root, key_type key) {
      size_type found = 0;

      if (!root)
        return 0;
      found = key_count_recurse(root->left_, key);
      if (root->pair_.first == key)
        found += 1;
      found = key_count_recurse(root->right_, key);
	    return found;
    }

    void  get_left_right() {
      tree *tmp = get_left();

      while (tmp->left_)
        tmp = tmp->left_;
      container_->left_ = tmp;

      tmp = get_right();
      while (tmp->right_)
        tmp = tmp->right_;
      container_->right_ = tmp;
    }

    tree	*insert_node(tree *node, key_compare comp, value_type pair)
    {
      if (node == container_) {
        if (!node->parent_) {
          node->parent_ = new tree(nullptr, nullptr, node, pair);
          node->left_ = node->parent_;
          node->right_ = node->parent_;
          return node->parent_;
        }
        else
          node = node->parent_;
      }
      if (comp(pair.first, node->pair_.first))
      {
        if (!node->left_) {
          node->left_ = new tree(nullptr, nullptr, node, pair);
          get_left_right();
          return node->left_;
        }
        else
          node = insert_node(node->left_, comp, pair);
      }
      else
      {
        if (!node->right_) {
          node->right_ = new tree(nullptr, nullptr, node, pair);
          get_left_right();
          return node->right_;
        }
        else
          node = insert_node(node->right_, comp, pair);
      }
      return node;
    }

    tree *get_root() { return container_->parent_; };
    tree *get_left() { return container_->left_; };
    tree *get_right() { return container_->right_; }

    tree            *container_;
    allocator_type  alloc_;
    key_compare     comp_;
    size_type       size_;
  };
};

#endif