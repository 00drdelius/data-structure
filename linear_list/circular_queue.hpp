// 循环队列，头尾指针实现

#ifndef __circular_queue__
#define __circular_queue__

#include <exception>
#include <iostream>
#include <ostream>
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
      rear = other.rear;
      front = other.front;

      // 必须显式指定 data=nullptr。否则other执行析构函数，会导致 this->data 指向的地址也被删除。
      // 因为 this->data 只是被 other.data 所覆盖；
      // 而赋值 nullptr后，析构函数执行`delete[] other.data`是允许的行为
      other.data = nullptr;
      other.max_size = 0;
    }
    return *this;
  }

  int get_length() const {
    return (max_size + front - rear) % max_size;
  }

  bool is_empty() const {
    return front == rear;
  }

  bool is_full() const {
    // return front-rear==1; // 因为是 circular 的，所以front有概率小于rear，不能直接front-rear判断
    return (front + 1) % max_size == rear;
  }

  const T& get_front() const {
    return data[front - 1];
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
    T ele = std::move(data[rear]);
    rear = (rear + 1) % max_size;
    return ele;
  }

  ~CircularQueue() {
    delete[] data;
  }

  /*
  const成员函数也必须调用const成员函数，保证内部调用的成员函数不会修改对象变量
  这里的 get_length() 不是
  const，get_length中可能出现修改对象变量的代码。因此必须const声明才能被const调用
  */
  std::string __str__() const override {
    std::string __obj{"{"};
    int length = get_length();
    for (int i = 0; i < length; i++) {
      __obj.append(std::to_string(data[(i + rear) % max_size]) + ", ");
    }
    __obj.append("}");
    return __obj;
  }
};

template <typename T>
void test_circular_queue(std::vector<T> default_vector) {
  int static_size = 5;
  CircularQueue<int> queue{static_size};

  std::cout << "testing enqueue:\n";
  for (T ele : default_vector) {
    try {
      queue.enqueue(ele);
    } catch (std::exception& e) {
      std::cout << "Exception raised: " << e.what() << std::endl;
      break;
    }
  }
  std::cout << "Length is: " << queue.get_length() << std::endl
            << "after enqueue: " << queue << std::endl;

  std::cout << "testing dequeue:\n";
  T out1 = queue.dequeue();
  T out2 = queue.dequeue();
  std::cout << "dequeue out1: " << out1 << std::endl
            << "dequeue out2: " << out2 << std::endl
            << "after dequeue: " << queue << std::endl;

  std::cout << "testing get_front:\n" << queue.get_front() << std::endl;

  std::cout << "testing enqueue again:\n";
  queue.enqueue(101);
  std::cout << "enqueue: 101\n";
  queue.enqueue(178);
  std::cout << "enqueue: 178\n";
  std::cout << "after enqueue:\n"
            << "If is_full: " << queue.is_full() << std::endl
            << "Current queue: " << queue << std::endl;

  /*
  注意1：不应该显式调用析构函数。∵编译器会在作用域结束时自动调用各局部变量的析构函数，
  如果这里已经手动调用，编译器的自动调用就会出现UB(undefined behavior)。
  当然上述适用于栈上的，堆上的仍需手动调用

   注意2：堆上的变量也不要手动调用`~Object()`，应该使用`delete obj`。
   手动调用只是调用析构函数，但是`delete`会调用析构，再删除分配的动态内存
  */
  //    queue.~CircularQueue();
  //   delete queue;
}

#endif