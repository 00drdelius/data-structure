#ifndef __circular_queue__
#define __circular_queue__

#include <type_traits>
#include "utils.hpp"

template <typename T>
class CircularQueue : public BaseObject {
private:
  T* data;
  int max_size;

public:
  CircularQueue(int size) : max_size(size) {
    data = new T[max_size];
  }

  CircularQueue(const CircularQueue& other) = delete; // 删除拷贝构造函数
  CircularQueue& operator=(const CircularQueue& other) = delete; //删除拷贝赋值运算符重载函数

  // 移动构造函数
  // other属于右值引用，但是是被右值赋值，所以属于左值变量。可以引用访问
  CircularQueue(CircularQueue&& other) : data(other.data), max_size(other.max_size) {
    other.data = nullptr;
    other.max_size = 0;
    return *this;
  }

  // 移动赋值运算符重载
  CircularQueue& operator=(CircularQueue&& other) {
    if (this != &other) {
      // 这是赋值运算符，不能保证原data是否为空，所以需要先手动删除 data，
      // 防止后面赋值指针造成原指针内存泄露
      delete[] data;

      // 指针赋值，是一种直接转移覆盖指针地址的行为；被覆盖的指针地址不会自动删除自己的内容
      data = other.data;
      max_size = other.max_size;

      // 必须显式指定 data=nullptr。否则other执行析构函数，会导致 this->data 指向的地址也被删除。
      // 因为 this->data 只是被 other.data 所覆盖；
      // 而赋值 nullptr后，析构函数执行`delete[] other.data`是允许的行为
      other.data = nullptr;
      other.max_size = 0;
    }
    return *this;
  }

  ~CircularQueue() {
    delete[] data;
  }
};

#endif