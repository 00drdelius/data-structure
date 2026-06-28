// 顺序表

#ifndef __sequance_list
#define __sequance_list

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

  /*
  const配合指针时用法：
  `const int * const p`
   首个(底层)const: 修饰指向的内容; 第二个(顶层)const: 修饰指针本身
   即：
   ```
   int a = 1, b = 2;
   int* const p1 = &a;
   p1=&b; //❎, const修饰指针，无法修改指针；
   *p1=b; //✅, const修饰指针，可以修改值
   const int* p2 = &a;
   p2=&b; //✅, const修饰值，可以修改指针；
   *p2=b; //❎, const修饰值，不可修改值
   ```

  this传入机制:
  `T& function(size_t var)`会被编译器编译成`T& function(T* const this, size_t var)`
  如果函数名后加上const:
  `T& function(size_t var) const`会被编译器编译成`T& function(const T* const this, size_t var)`
  此时在函数内无法修改成员对象，因为加上了修饰指向内容的底层const

  若是 `const T& function() {}`:
  意味着返回对象是const: `const T& var = function()`
  */
  unsigned int get_max_size() const {
    return max_size;
  }

  unsigned int get_length() const {
    return length;
  }

  T& operator[](unsigned int index) const {
    // return value is not decorated by const, I may modify the value in the index
    return search(index);
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

  bool _insert(const T& ele, unsigned int index) {
    assert(index < max_size, "the position you attempt to insert is out of bound");
    if (dynamic == false) {
      assert(length + 1 <= max_size, "sequence list is full. Cannot insert additional element.");
    } else {
      if (length + 1 > max_size) {
        _expand_list(max_size);
      }
    }
    for (int i = length - 1; i > index - 1; i--) {
      // move the right elements to make the index available
      data[i + 1] = data[i];
    }
    data[index] = ele;
    length++;
    return true;
  }

  bool _delete(unsigned int index) {
    assert(index < length, "the position you attempt to delete is out of bound");
    // data[index] = nullptr; // no need. Just directly replace this position with
    // other elements
    for (int i = index + 1; i < length; i++) {
      data[i - 1] = data[i];
    }
    data[length - 1] = T();
    length--;
    if (length <= max_size) {
      // anyway, it's just an exercise. No need to deallocate the memory
    }
    return true;
  }

  T& search(unsigned int index) {
    assert(index < length, "the position you attempt to insert is out of bound");
    return data[index];
  }

  T* search_ptr(unsigned int index) {
    assert(index < length, "the position you attempt to insert is out of bound");
    return &data[index];
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
