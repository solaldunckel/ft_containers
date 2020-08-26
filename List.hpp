#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include "Iterator.hpp"

namespace ft {
  template <class T>
  class List {
   public:
    typedef T value_type;
    typedef T& reference;
    typedef T const const_reference;
    typedef T* pointer;
    typedef T* const const_pointer;
    typedef ListIterator<T> iterator;
		typedef ListIterator<const T> const_iterator;
		typedef ReverseIterator<T> reverse_iterator;
		typedef ReverseIterator<const T> const_reverse_iterator;
    typedef size_t size_type;

    List() :size_(0) {
      head_ = new DoubleLinkedList<T>();
      tail_ = head_;
    };

    List(size_type n, const value_type& val) {
      DoubleLinkedList<T> *add = new DoubleLinkedList<T>;

      head_ = add;
      tail_ = add;
      size_ = 0;
      insert(iterator(head_), n, val);
    }; // Fill constructor

    template <class InputIterator>
    List(InputIterator first, InputIterator last) {
      DoubleLinkedList<T> *add = new DoubleLinkedList<T>;
      head_ = add;
      tail_ = add;
      size_ = 0;
      insert(iterator(head_), first, last);
    };

    List(List &x) {

    };

    ~List() {
      // clear();
      // erase(iterator(head_), iterator(tail_));
    };

    List& operator = (const List& x) {}; // Assignement

    iterator begin() { return iterator(head_); };
    iterator end() { return iterator(tail_); };
    const_iterator begin() const { return iterator(head_); };
    const_iterator end() const { return iterator(tail_); };

    reverse_iterator rbegin() { return reverse_iterator(tail_); };
    reverse_iterator rend() { return reverse_iterator(head_); };
    const_reverse_iterator rbegin() const { return reverse_iterator(tail_); };
    const_reverse_iterator rend() const { return reverse_iterator(head_); };

    // Capacity

    bool empty() const { return size_ == 0; };
    size_type size() const { return size_; };
    size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(*this); };

    // Element Access

    reference front() { return head_->value_; };
    const_reference front() const { return head_->value_; };

    reference back() { return tail_->value_; };
    const_reference back() const { return tail_->value_; };

    // Modifiers

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last) {
      clear();
      for (InputIterator it = first; it != last; it++)
        push_back(*it);
      push_back(*last);
    };

    void assign (size_type n, const value_type& val) {
      clear();
      for (size_type i = 0; i < n; i++)
        push_back(val);
    };

    void push_front (const value_type& val) {
      insert(begin(), val);
    };

    void pop_front() {
      if (head_) {
        DoubleLinkedList<T> *tmp = head_;

        head_ = head_->next_;;
        if (head_)
          head_->prev_ = NULL;
        else {
          head_ = NULL;
          tail_ = NULL;
        }
        size_--;
        delete tmp;
      }
    };

    void push_back (const value_type& val) {
      // DoubleLinkedList<T> *add = new DoubleLinkedList<T>(tail_, NULL, val);

      // if (!size_) {
      //   head_ = add;
      //   tail_ = add;
      // }
      // else {
      //   tail_->next_ = add;
      //   tail_ = tail_->next_;
      // }
      // size_++;
    };

    void pop_back() {
      if (tail_) {
        DoubleLinkedList<T> *tmp = tail_;

        tail_ = tail_->prev_;
        if (tail_)
          tail_->next_ = NULL;
        else {
          head_ = NULL;
          tail_ = NULL;
        }
        size_--;
        delete tmp;
      }
    };

    iterator insert (iterator position, const value_type& val) {
      DoubleLinkedList<T> *add = new DoubleLinkedList<T>(position.getPtr()->prev_, position.getPtr());
      add->value_ = val;
      if (add->prev_)
        add->prev_->next_ = add;
      else
        head_ = add;
      add->next_->prev_ = add;
      size_++;
      return iterator(add);
    };

    void insert (iterator position, size_type n, const value_type& val) {
      while (n) {
        insert(position, val);
        n--;
      }
    };

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last) {
      
    }; // Range

    iterator erase (iterator position) {
      DoubleLinkedList<T> *ptr = position.getPtr();
      DoubleLinkedList<T> *pos;
      if (ptr) {
        if (!ptr->prev) {
          head_ = ptr->next;
          pos = head_;
          if (ptr->next)
            ptr->next->prev = NULL;
        }
        else {
          ptr->prev->next = ptr->next;
          pos = ptr->next;
        }
        if (!ptr->next)
          tail_ = ptr->prev;
          pos = tail_;
          if (ptr->prev)
            ptr->prev->next = NULL;
        else {
          ptr->next->prev = ptr->prev;
          pos = ptr->next;
        }
        delete ptr;
        size_--;
      }
      return iterator(pos);
    };

    iterator erase (iterator first, iterator last) {
      
    };

    void swap (List& x) {
      DoubleLinkedList<T> *tmp;
      size_type size_tmp;

      size_tmp = size_;
      size_ = x.size_;
      x.size_ = size_tmp;

      tmp = head_;
      head_ = x.head_;
      x.head_ = tmp;

      tmp = tail_;
      tail_ = x.tail_;
      x.tail_ = tmp;
    };

    void resize (size_type n, value_type val = value_type()) {
      while (size_ < n) {
        push_back(val);
      };
      while (size_ > n) {
        pop_back(val);
      };
    };

    void clear() {
      while (this->size_)
        pop_back();
    };

    // Operations

   private:
    DoubleLinkedList<T> *head_;
    DoubleLinkedList<T> *tail_;
    DoubleLinkedList<T> *start_;
    DoubleLinkedList<T> *end_;
    size_type size_;
  };
}




#endif