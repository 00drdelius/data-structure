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
    // data为unique_ptr，其拷贝构造函数=delete，无法值拷贝，因此：
    // 调用unique_ptr的operator=(unique_ptr&&)，移动赋值运算符
    data = std::move(new_data);
    max_size = new_max_size;
    return true;
  }

  /*
  param must starts with const, otherwise error raises when calling this function:
  Non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
  意思是没有const修饰的左值引用无法绑定临时对象（右值）；
  而加了const即可绑定是因为你已经通过const约束该变量不会被修改，毕竟修改一个临时变量是没有意义的
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

template <typename T>
void sequence_list_test(std::vector<T> default_vector) {
  int static_size = 5;
  SequenceList<T> static_list{false, static_size};
  // check static array
  std::cout << "[static array test]" << std::endl;
  std::cout << "append\n";
  for (auto ele : default_vector) {
    try {
      static_list.append(ele);
    } catch (std::exception& e) {
      std::cout << "Exception raised: " << e.what() << std::endl;
      break;
    }
  }
  std::cout << "Max size of this static list is " << static_list.get_max_size() << std::endl
            << "Length already is " << static_list.get_length() << std::endl
            << "Source list: " << static_list << std::endl;

  static_list._delete(0);
  std::cout << "after deleting index=0\n";
  std::cout << static_list << std::endl;

  static_list._insert(10, 2);
  std::cout << "after inserting index=2 with value=10\n";
  std::cout << static_list << std::endl;

  // test index search
  unsigned int index = 1;
  std::cout << "index search: index=" << index << "; result=" << static_list.search(index)
            << " with its pointer: " << static_list.search_ptr(index) << std::endl;

  // test element search
  int element = 10;
  std::cout << "element search: element=" << element << "; result=" << static_list.search(element)
            << std::endl;

  // dynamic array
  SequenceList<int> dynamic_list{true, static_size};
  // check dynamic array
  std::cout << "[static array test]" << std::endl;
  std::cout << "append\n";
  for (auto ele : default_vector) {
    try {
      dynamic_list.append(ele);
    } catch (std::exception& e) {
      std::cout << "Exception raised: " << e.what() << std::endl;
      break;
    }
  }
  std::cout << "Max size of this static list is " << dynamic_list.get_max_size() << std::endl
            << "Length already is " << dynamic_list.get_length() << std::endl
            << "Source list: " << dynamic_list << std::endl;
}

#endif
