// 栈

#ifndef __stack__
#define __stack__

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "utils.hpp"

#define STACK_MAX_SIZE 20

template <typename T>
class Stack : public BaseObject {
private:
  std::unique_ptr<T[]> data;
  int top_ptr; // point at index of the last element
  int max_size; // just for convenience, fix the max size of the stack

public:
  Stack(int size = STACK_MAX_SIZE) : top_ptr(-1), max_size(size) {
    data = std::make_unique<T[]>(max_size);
  }

  bool push(T ele) {
    assert(top_ptr < max_size - 1, "Stack full.");
    top_ptr++;
    data[top_ptr] = ele;
    return true;
  }

  T pop() {
    assert(top_ptr != -1, "Stack empty");
    // c++机制: overload resolution. 如果T有移动构造，会执行移动构造，
    //  否则会自动执行拷贝构造，创建 element
    T element = std::move(data[top_ptr]);
    top_ptr--;
    return element;
  }

  const T& get_top() {
    assert(top_ptr != -1, "Stack empty");
    /*
    不应该返回中间变量，否则会造成悬空引用；
    同理，返回值为 T* 会造成悬空指针。

    但若是直接返回成员变量中的值则没有问题，因为不是局部变量，不会被销毁；
    或者返回非引用、指针变量，触发类型(移动/拷贝)构造，这样也不用担心作为局部变量被销毁的问题
    */
    // T element = data[top_ptr];
    // return element;
    return data[top_ptr];
  }

  const T& get_bottom() {
    assert(top_ptr != -1, "Stack empty");
    return data[0];
  }

  std::string __str__() const override {
    std::string __str_obj{"栈底{ "};
    for (int i = 0; i <= top_ptr; i++) {
      __str_obj.append(std::to_string(data[i]) + ", ");
    }
    __str_obj.append("}栈顶;");
    return __str_obj;
  }
};

template <typename T>
void stack_test(std::vector<T> default_vector) {
  int stack_size = 5;
  std::cout << "creating stack with size=" << stack_size << std::endl;
  Stack<T> stack{stack_size};
  std::cout << "test push\n";
  for (T ele : default_vector) {
    try {
      stack.push(ele);
    } catch (std::exception& e) {
        std::cout << "error raised: " << e.what() << std::endl;
        break;
    }
  }
  std::cout << "after pushing:\n" << stack << std::endl;

  std::cout<< "test get_top:\n" << stack.get_top() << std::endl;
  std::cout<< "test get_bottom:\n" << stack.get_bottom() << std::endl;

  std::cout << "test pop:\n"
  << "pop result: " << stack.pop() << std::endl;

  std::cout << "after poping:\n" << stack;
}

#endif