// 循环队列，头尾指针实现

#ifndef __circular_queue__
#define __circular_queue__

#include <string>
#include <type_traits>
#include "utils.hpp"

template <typename T>
class CircularQueue : public BaseObject {
private:
  T* data;
  int max_size;

  // enqueue: front+1; dequeue: rear+1
  int rear;
  int front;

public:
  // max_size(size+1): left data[last_size] to be empty to make difference between is_empty and
  // is_full; front=rear+1: full; front==rear; empty
  CircularQueue(int size) : max_size(size + 1), rear(0), front(0) {
    data = new T[max_size];
  }

  CircularQueue(const CircularQueue& other) = delete; // 删除拷贝构造函数
  CircularQueue& operator=(const CircularQueue& other) = delete; //删除拷贝赋值运算符重载函数

  // 移动构造函数
  // other属于右值引用，但是是被右值赋值，所以属于左值变量。可以引用访问
  CircularQueue(CircularQueue&& other)
      : data(other.data), max_size(other.max_size), rear(0), front(0) {
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

  int get_length() {
    return (max_size + front - rear) % max_size;
  }

  bool is_empty() {
    return front == rear;
  }

  bool is_full() {
    // return front-rear==1; // 因为是 circular 的，所以front有概率小于rear，不能直接front-rear判断
    return (max_size + front - rear) % max_size == 1;
  }

  const T& get_front() {
    return data[front];
  }

  // setting data as const T& to compatible with right value
  bool enqueue(const T& ele) {
    assert(!is_full(), "Cannot enqueue more, queue is full");
    data[front] = ele;
    front = (front + 1) % max_size;
    return true;
  }

  T dequeue() {
    assert(!is_empty(), "Cannot dequeue more, queue is empty");
    // return data[++rear]; // of course cannot return directly as data[rear] is logically dropped
    rear = (rear + 1) % max_size;
    T ele = std::move(data[rear]);
    return ele;
  }

  ~CircularQueue() {
    delete[] data;
  }

  std::string __str__() const override {
    std::string __obj{"{"};
    for (int i = 0; i < get_length(); i++) {
      __obj.append(std::to_string(data[i]) + ", ");
    }
    __obj.append("}");
    return __obj;
  }
};

template <typename T>
void test_circular_queue(std::vector<T> default_vector) {
  int static_size = 5;
  CircularQueue<int> queue{static_size};

//   queue.~CircularQueue();
}

#endif