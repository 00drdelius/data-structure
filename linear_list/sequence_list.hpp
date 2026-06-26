#ifndef __sequance_list
#define __sequance_list

#include <iostream>
#include <memory>
#include <string>
#include "utils.hpp"

#define DefaultMaxSize 10

template <typename T>
class SequenceList : public BaseObject {
 private:
  int length;
  std::unique_ptr<T[]> data;
  unsigned int max_size;
  bool dynamic;

 public:
  // initialize sequence list
  SequenceList(bool __dy = false, int __size = DefaultMaxSize)
      : length(0), max_size(__size), dynamic(__dy) {
    data = std::make_unique<T[]>(max_size);
  }

  unsigned int get_max_size() const {
    return max_size;
  }

  unsigned int get_length() const {
    return length;
  }

  bool _expand_list(unsigned int expand_size) {
    assert(dynamic == true, "dynamic must be true to use function `expand_list`");

    unsigned int new_max_size = max_size + expand_size;
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_max_size);
    for (int i = 0; i < length; ++i) {
      new_data[i] = data[i]; // Or use std::copy
    }
    data = std::move(new_data); // cannot `T* data = new_data` when both of them
                                // are unique_ptr, only std::move is allowed
    max_size = new_max_size;
    return true;
  }

  /*
  param must starts with const, otherwise error raises when calling this function:
  Non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
  */
  bool append(const T& ele) {
    if (dynamic == false) {
      assert(length + 1 <= max_size, "sequence list is full. Cannot insert additional element.");
    } else {
      if (length + 1 > max_size) {
        _expand_list(max_size);
      }
    }
    data[length] = ele;
    length++;
    return true;
  }

  bool _insert(const T& ele, unsigned int loc) {
    assert(loc < max_size, "the position you attempt to insert is out of bound");
    if (dynamic == false) {
      assert(length + 1 <= max_size, "sequence list is full. Cannot insert additional element.");
    } else {
      if (length + 1 > max_size) {
        _expand_list(max_size);
      }
    }
    for (int i = length - 1; i > loc - 1; i--) {
      // move the right elements to make the loc available
      data[i + 1] = data[i];
    }
    data[loc] = ele;
    length++;
    return true;
  }

  bool _delete(unsigned int loc) {
    assert(loc < length, "the position you attempt to delete is out of bound");
    // data[loc] = nullptr; // no need. Just directly replace this position with
    // other elements
    for (int i = loc + 1; i < length; i++) {
      data[i - 1] = data[i];
    }
    data[length - 1] = T();
    length--;
    if (length <= max_size) {
      // anyway, it's just an exercise. No need to deallocate the memory
    }
    return true;
  }

  T search(unsigned int loc) {
    assert(loc < length, "the position you attempt to insert is out of bound");
    return data[loc];
  }

  T* search_ptr(unsigned int loc) {
    assert(loc < length, "the position you attempt to insert is out of bound");
    return &data[loc];
  }

  int search(const T& ele) {
    for (int i = 0; i < length; i++) {
      if (data[i] == ele) {
        return i;
      }
    }
    return -1;
  }

  std::string __str__() const override { // overide the parent class::__str__
    std::string __str_obj{};
    __str_obj.append("[ ");

    // for (T ele : data) { // only allowed for array which implements begin() and end()
    for (int i = 0; i < length; i++) {
      __str_obj.append(std::to_string(data[i]) + ", "); // to_string to convert int-like to string
    }
    __str_obj.append(" ]");
    return __str_obj;
  }
};

#endif
