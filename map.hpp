#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <limits>
# include <cstddef>

# include "map_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {
  template <class Key, class T, class Compare = ft::less<Key>,
              class Alloc = std::allocator<ft::pair<const Key, T> > >
  class map {
   public:

    typedef Key                                     key_type;
    typedef T                                       mapped_type;
    typedef ft::pair<const key_type, mapped_type>   value_type;
    typedef Compare                                 key_compare;
    typedef ft::comp<Compare, value_type>           value_compare;

    typedef Alloc                                     allocator_type;;
    typedef typename allocator_type::reference        reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer          pointer;
    typedef typename allocator_type::const_pointer    const_pointer;

    typedef ft::map_iterator<key_type, mapped_type>        iterator;
    typedef ft::map_iterator<key_type, mapped_type, true>  const_iterator;
    typedef ft::reverse_iterator<iterator>                 reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>           const_reverse_iterator;

    typedef std::ptrdiff_t                  difference_type;
    typedef size_t                          size_type;

    explicit map(const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type()) {
      alloc_ = alloc;
      comp_ = comp;
      size_ = 0;

      container_ = alloc_node_.allocate(1);
      container_->left_ = container_;
      container_->right_ = container_;
      container_->parent_ = NULL;

      alloc_.construct(&container_->pair_, value_type());
    }

    template <class InputIterator>
    map(InputIterator first, InputIterator last,
          const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
      alloc_ = alloc;
      comp_ = comp;
      size_ = 0;

      container_ = alloc_node_.allocate(1);
      container_->left_ = container_;
      container_->right_ = container_;
      container_->parent_ = NULL;
      alloc_.construct(&container_->pair_, value_type());

      insert(first, last);
    };

    map(const map& x) {
      comp_ = x.comp_;
      size_ = 0;
      alloc_ = x.alloc_;

      container_ = alloc_node_.allocate(1);
      container_->left_ = container_;
      container_->right_ = container_;
      container_->parent_ = NULL;
      alloc_.construct(&container_->pair_, value_type());

      insert(x.begin(), x.end());
    };

    ~map() {
      clear();
      alloc_.destroy(&container_->pair_);
      alloc_node_.deallocate(container_, 1);
    };

    map& operator= (const map& x) {
      clear();
      insert(x.begin(), x.end());
      return *this;
    };

    iterator begin() { return iterator(get_left()); };
    iterator end() { return iterator(container_); };
    const_iterator begin() const { return const_iterator(get_left()); };
    const_iterator end() const { return const_iterator(container_); };

    reverse_iterator rbegin() { return reverse_iterator(end()); };
    reverse_iterator rend() { return reverse_iterator(begin()); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

    mapped_type& operator[] (const key_type& k) {
      return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
    };

    bool        empty() const     { return size_ == 0; };
    size_type   size() const      { return size_; };
    size_type   max_size() const  { return alloc_node_.max_size(); };

    pair<iterator, bool> insert (const value_type& val) {
      tree *exist = key_exists_recurse(get_root(), val.first);

      if (exist)
        return ft::make_pair(iterator(exist), false);
      size_++;
      return ft::make_pair(iterator(insert_node(container_, comp_, val)), true);
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
                typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
      while (first != last) {
        insert(*first);
        first++;
      }
    };

    void      erase(iterator position) {
      tree *current = position.ptr_;
      tree *tmp = NULL;

      if (current->left_) {
        tmp = current->left_;
        while (tmp->right_)
          tmp = tmp->right_;
        if (tmp->parent_->right_ == tmp) {
          if (tmp->left_) {
            tmp->parent_->right_ = tmp->left_;
            tmp->left_->parent_ = tmp->parent_;
          }
          else
            tmp->parent_->right_ = NULL;
        }
        tmp->right_ = current->right_;
        if (current->right_)
          current->right_->parent_ = tmp;
        if (current->left_ != tmp)
          tmp->left_ = current->left_;
        if (current->left_)
          current->left_->parent_ = tmp;
        tmp->parent_ = current->parent_;
      }
      else if (current->right_) {
        tmp = current->right_;
        tmp->parent_ = current->parent_;
      }
      if (current->parent_->left_ == current)
        current->parent_->left_ = tmp;
      else
        current->parent_->right_ = tmp;
      if (current == get_root())
        container_->parent_ = tmp;
      alloc_.destroy(&current->pair_);
      alloc_node_.deallocate(current, 1);
      size_--;
      set_left_right();
    };

    size_type erase(const key_type& k) {
      iterator it = begin();
      size_type count = 0;

      erase(find(k));
      return count;
    };

    void      erase(iterator first, iterator last) {
      iterator tmp;

      while (first != last) {
        tmp = first++;
        erase(tmp);
      }
    };

    void swap (map& x) {
      tree *tmp;
      size_type size_tmp;

      size_tmp = size_;
      size_ = x.size_;
      x.size_ = size_tmp;

      tmp = container_;
      container_ = x.container_;
      x.container_ = tmp;
    };

    void clear() { erase(begin(), end()); };

    key_compare key_comp() const { return key_compare(); };
    value_compare value_comp() const { return value_compare(key_compare()); };

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

    iterator        lower_bound (const key_type& k) {
      iterator it = begin();

      while (it != end()) {
        if (!comp_(it->first, k))
          return it;
        it++;
      }
      return it;
    };
    const_iterator  lower_bound (const key_type& k) const {
      const_iterator it = begin();

      while (it != end()) {
        if (!comp_(it->first, k))
          return it;
        it++;
      }
      return it;
    };

    iterator        upper_bound (const key_type& k) {
      iterator it = begin();

      while (it != end()) {
        if (comp_(k, it->first))
          return it;
        it++;
      }
      return it;
    };
    const_iterator  upper_bound (const key_type& k) const {
      const_iterator it = begin();

      while (it != end()) {
        if (comp_(k, it->first))
          return it;
        it++;
      }
      return it;
    };

    ft::pair<iterator, iterator>             equal_range (const key_type& k) {
      return make_pair(lower_bound(k), upper_bound(k));
    };

    ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
      return make_pair(lower_bound(k), upper_bound(k));
    };;

   private:
    typedef Tree<value_type>  tree;

    tree *key_exists_recurse(tree *root, key_type key) const {
      tree *found = get_root();

      if (!root)
        return NULL;
      found = key_exists_recurse(root->left_, key);
      if (!comp_(root->pair_.first, key) && !comp_(key, root->pair_.first))
        found = root;
      if (!found)
        found = key_exists_recurse(root->right_, key);
	    return found;
    }

    size_type key_count_recurse(tree *root, key_type key) const {
      if (!root)
        return 0;
      if (!comp_(root->pair_.first, key) && !comp_(key, root->pair_.first))
        return 1;
	    return key_count_recurse(root->left_, key) + key_count_recurse(root->right_, key);
    }

    void  set_left_right() {
      tree *tmp = get_root();

      if (!tmp) {
        container_->left_ = container_;
        container_->right_ = container_;
        return ;
      }
      while (tmp && tmp->left_)
        tmp = tmp->left_;
      container_->left_ = tmp;

      tmp = get_root();
      while (tmp && tmp->right_)
        tmp = tmp->right_;
      container_->right_ = tmp;
    }

    tree	*insert_node(tree *node, key_compare comp, value_type pair)
    {
      if (node == container_) {
        if (!node->parent_) {
          node->parent_ = alloc_node_.allocate(1);
          node->parent_->left_ = NULL;
          node->parent_->right_ = NULL;
          node->parent_->parent_ = node;
          alloc_.construct(&node->parent_->pair_, pair);

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
          node->left_ = alloc_node_.allocate(1);
          node->left_->left_ = NULL;
          node->left_->right_ = NULL;
          node->left_->parent_ = node;
          alloc_.construct(&node->left_->pair_, pair);

          set_left_right();
          return node->left_;
        }
        else
          node = insert_node(node->left_, comp, pair);
      }
      else
      {
        if (!node->right_) {
          node->right_ = alloc_node_.allocate(1);
          node->right_->left_ = NULL;
          node->right_->right_ = NULL;
          node->right_->parent_ = node;
          alloc_.construct(&node->right_->pair_, pair);

          set_left_right();
          return node->right_;
        }
        else
          node = insert_node(node->right_, comp, pair);
      }
      return node;
    }

    tree *get_root() const { return container_->parent_; };
    tree *get_left() const { return container_->left_; };
    tree *get_right() const { return container_->right_; };

    typename allocator_type::template rebind<tree>::other alloc_node_;

    tree            *container_;
    allocator_type  alloc_;
    key_compare     comp_;
    size_type       size_;
  };

  template <class Key, class T>
  bool operator== (const map<Key, T>& lhs, const map<Key, T>& rhs) {
    if (lhs.size() != rhs.size())
      return false;
    typename map<Key, T>::const_iterator it1 = lhs.begin();
    typename map<Key, T>::const_iterator it2 = rhs.begin();

    while (it1 != lhs.end() && it2 != rhs.end()) {
      if (*it1 != *it2)
        return false;
      it1++;
      it2++;
    }
    return (it1 == lhs.end()) && (it2 == rhs.end());
  };

  template <class Key, class T>
  bool operator!= (const map<Key, T>& lhs, const map<Key, T>& rhs) { return !(lhs == rhs); };

  template <class Key, class T>
  bool operator<  (const map<Key, T>& lhs, const map<Key, T>& rhs) {
    typename map<Key, T>::const_iterator it1 = lhs.begin();
    typename map<Key, T>::const_iterator it2 = rhs.begin();

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

  template <class Key, class T>
  bool operator<= (const map<Key, T>& lhs, const map<Key, T>& rhs) { return !(rhs < lhs); };

  template <class Key, class T>
  bool operator>  (const map<Key, T>& lhs, const map<Key, T>& rhs) { return rhs < lhs; };

  template <class Key, class T>
  bool operator>= (const map<Key, T>& lhs, const map<Key, T>& rhs) { return !(lhs < rhs); };

  template <class Key, class T, class Compare, class Alloc>
  void swap (map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
    x.swap(y);
  };
};

#endif