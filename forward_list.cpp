#include <iostream>
#include <memory>
#include <vector>

template <typename T> struct Node {
  T data;
  std::unique_ptr<Node<T>> next;

  Node(T newData, std::unique_ptr<Node<T>> _next = nullptr)
      : data{newData}, next{std::move(_next)} {};
};

template <typename T> class forward_list {
private:
  std::unique_ptr<Node<T>> head;
  size_t _size{0};

public:
  bool empty() const {
    // Checks if list is empty.
    return _size == 0;
  }

  bool contains(T dataToFind) const {
    // Checks if list contains the given element.
    auto iter = head.get();
    while (iter) {
      if (iter->data == dataToFind) {
        return true;
      }
      iter = iter->next.get();
    }
    return false;
  }

  T front() const {
    // Returns the first element of the List.
    // No bounds checking for speed.
    return head->data;
  }

  T back() const {
    // Returns the Last element of the List.
    auto iter = head.get();
    while (iter->next) {
      iter = iter->next.get();
    }
    return iter->data;
  };

  void push_front(T newData) {
    // Adds given element of the beginning of the list.
    if (empty()) {
      head = std::make_unique<Node<T>>(newData);
    } else {
      head = std::make_unique<Node<T>>(newData, std::move(head));
    }
    _size++;
  }

  void push_back(T newData) {
    // Adds given element at the end of the list.
    if (empty()) {
      push_front(newData);
    } else {
      auto iter = head.get();
      while (iter->next) {
        iter = iter->next.get();
      }
      iter->next = std::make_unique<Node<T>>(newData);
      _size++;
    }
  };

  void pop_front() {
    // Removes the first element of the list.
    if (!empty()) {
      head = std::move(head->next);
      _size--;
    }
  }

  void pop_back() {
    // Removes the last element of the list.
    if (size() < 2) {
      pop_front();
    } else {
      auto iter = head.get();
      while (iter->next->next) {
        iter = iter->next.get();
      }
      iter->next = std::move(nullptr);
      _size--;
    }
  };

  bool remove(T dataToRemove) {
    // Removes the first element of the list with the given value.
    Node<T> *prev = nullptr;
    auto curr = head.get();
    for (prev, curr; curr; prev = curr, curr = curr->next.get()) {
      if (curr->data == dataToRemove) {
        if (prev) {
          prev->next = std::move(curr->next);
        } else {
          head = std::move(curr->next);
        }
        _size--;
        return true;
      }
    }
    return false;
  };

  void clear() {
    // Empties the list. While smart pointers would do that
    // automatically, it is done here manually as the unique_ptr
    // will clean all the elements recursively which will result
    // in a stack overflow for a list with large number of elements.
    while (head) {
      head = std::move(head->next);
    }
  }

  size_t size() const {
    // Returns the number of elements in the list.
    return _size;
  }

  void display() const {
    // Prints the elements of the list to stdout.
    // Type T should have an overloaded << operator.
    auto iter = head.get();
    while (iter) {
      std::cout << iter->data << ' ';
      iter = iter->next.get();
    }
  }

  ~forward_list() {
    // Clears list on destruction.
    clear();
  }
};

int main() {}