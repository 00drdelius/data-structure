// 链表

#ifndef __linked_list__
#define __linked_list__

#include "utils.hpp"

template <typename T>
struct Node {
  T data;
  std::unique_ptr<Node<T>> next = nullptr;
  Node(T data) : data(data) {}
};

template <typename T>
class SinglyLinkedList : public BaseObject {
private:
  std::unique_ptr<Node<T>> head;
  int length;

public:
  SinglyLinkedList() : head(nullptr), length(0) {}

  // head insertion || tail insertion to create linked list
  SinglyLinkedList(std::vector<T> vector, bool head_insertion = false) {
    if (vector.empty()) {
      head = nullptr;
      length = 0;
      return;
    }
    head = std::make_unique<Node<T>>(vector[0]);
    if (head_insertion) {
      // 头插法
      for (int i = 1; i < vector.size(); i++) {
        std::unique_ptr<Node<T>> current_node = std::make_unique<Node<T>>(vector[i]);
        current_node->next = std::move(head);
        head = std::move(current_node);
      }
    } else {
      //尾插法
      Node<T>* last_node = head.get();
      for (int i = 1; i < vector.size(); i++) {
        std::unique_ptr<Node<T>> current_node = std::make_unique<Node<T>>(vector[i]);
        last_node->next = std::move(current_node);
        last_node = last_node->next.get();
      }
    }
    length = vector.size();
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
  int get_length() const {
    // 这里返回值不加const。对于T为小类型时无所谓，但若T是大类型时，若返回值const修饰，
    // 则接收该函数返回值的变量无法使用移动构造函数，只能使用拷贝构造函数。造成性能上的损失
    return length;
  }

  /*
  param must starts with const, otherwise error raises when calling this function:
  Non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
  意思是没有const修饰的左值引用无法绑定临时对象（右值）；
  而加了const即可绑定是因为你已经通过const约束该变量不会被修改，毕竟修改一个临时变量是没有意义的
  */
  bool append(const T& value) {
    // 必须在堆上创建(用new或者指针)。否则离开函数时局部变量会被销毁
    /*
    观点：这里若T支持移动构造，可以用std::move优化拷贝性能，目前是拷贝构造
    但其实无法实现，因为value是const类的左值引用，就算`Node<T>(std::move(value))`也不会触发移动构造函数：
    移动构造: T(T&&); 神奇的构造: T(const
    T&&):基本不会有人用，因为const实际无法move，只会退回到拷贝构造函数; 拷贝构造: T(const T&),
    注意这里const是左值引用+const用于应付传入右值的情况
    */
    std::unique_ptr<Node<T>> new_node = std::make_unique<Node<T>>(value);

    if (head == nullptr) {
      // 这里的std::move调用的是std::unique_ptr的移动构造函数。
      // 不需要Node自己写一个移动构造函数
      head = std::move(new_node);
      length++;
      return true;
    }

    // Node<T> last_node=head; // 值拷贝，对其next的修改无法给到链表中。因此需要用指针
    Node<T>* last_node = head.get();
    while (last_node->next != nullptr) {
      last_node = last_node->next.get();
    }
    // 调用last_node->next(unique_ptr)的operator=(unique_ptr&&)，移动赋值运算符
    last_node->next = std::move(new_node);
    length++;
    return true;
  }

  /*
  注意这里的返回值是引用。如果通过引用返回了局部变量会造成“返回悬空引用”
  因为局部变量保存在函数栈上，函数返回后会被销毁，造成悬空引用。
  因此若是需要返回局部变量，不应该返回引用，直接返回对象类型。现代C++一般会调用移动构造函数（若对象实现）创建，不会有很大开销。
  我这里是查询成员变量，不是函数栈，没有问题。

  index search for node. index starts from 0
  */
  Node<T>* node_search(unsigned int index) {
    assert(index < length, "index is out of bound;");

    // unique_ptr的拷贝构造函数=delete，不支持值拷贝。直接.get()获取裸指针
    // std::unique_ptr<Node<T>> target_node = head;
    Node<T>* target_node = head.get();
    while (target_node != nullptr && index != 0) {
      // index-1: 进行一次跳跃。想查找到第n个节点，需要执行n次跳跃
      target_node = target_node->next.get();
      index--;
    }
    return target_node;
  }

  // index search. index starts from 0
  T& search(unsigned int index) {
    Node<T>* target_node = node_search(index);
    return target_node->data;
  }

  // value search. Returns index
  int search(const T& value) {
    Node<T>* target_node = head.get();
    int index = 0;
    while (target_node != nullptr && target_node->data != value) {
      target_node = target_node->next.get();
      index++;
    }
    if (target_node == nullptr) {
      return -1;
    }
    return index;
  }

  bool _insert(const T& value, unsigned int index) {
    std::unique_ptr<Node<T>> insert_node = std::make_unique<Node<T>>(value);
    if (index == 0) {
      // insert head node
      insert_node->next = std::move(head);
      head = std::move(insert_node);
    } else {
      Node<T>* before_insert = node_search(index - 1);
      // 必须注意! unique_ptr 没有拷贝构造，不能直接值拷贝，必须通过 std::move，
      // 调用operator=(unique_ptr&&)，移动赋值运算符!
      // std::unique_ptr<Node<T>> after_insert = before_insert->next;
      std::unique_ptr<Node<T>> after_insert = std::move(before_insert->next);

      /*
      make_unique会调用Node<T>的拷贝构造，我没有实现，因此调用默认的拷贝构造：即逐成员拷贝。
      这样问题就来了：Node<T>.next 是unique_ptr，其拷贝构造=delete，因此会报错。
      所以这里不能解引用再调用make_unique
      */
      // insert_node->next = std::make_unique<Node<T>>(*after_insert);
      insert_node->next = std::move(after_insert);
      before_insert->next = std::move(insert_node);
    }
    length++;
    return true;
  }

  bool _delete(unsigned int index) {
    assert(length != 0, "linked list attempted to delete is empty");
    if (index == 0) {
      // delete head node
      std::unique_ptr<Node<T>> next_node = std::move(head->next);
      head = std::move(next_node);
    } else {
      Node<T>* before_node = node_search(index - 1);
      before_node->next = std::move(before_node->next->next);
    }
    length--;
    return true;
  }

  std::string __str__() const override {
    std::string __str_obj{};
    __str_obj.append("[ ");
    Node<T>* current_node = head.get();
    while (current_node != nullptr) {
      __str_obj.append(std::to_string(current_node->data) + " -> ");
      current_node = current_node->next.get();
    }
    __str_obj.append(" ]");
    return __str_obj;
  }
};

template <typename T>
void linked_list_test(std::vector<T> default_vector) {
  int static_size = 5;
  SinglyLinkedList<T> linked_list1{default_vector, false};
  std::cout << "尾插法创建链表: " << linked_list1 << std::endl;

  SinglyLinkedList<T> linked_list2{default_vector, true};
  std::cout << "头插法创建链表: " << linked_list2 << std::endl;

  std::cout << "[linked list test]" << std::endl;
  std::cout << "append\n";
  for (auto ele : default_vector) {
    try {
      linked_list1.append(ele);
    } catch (std::exception& e) {
      std::cout << "Exception raised: " << e.what() << std::endl;
      break;
    }
  }
  std::cout << "Length is " << linked_list1.get_length() << std::endl
            << "Source list: " << linked_list1 << std::endl;

  linked_list1._delete(0);
  std::cout << "after deleting index=0\n";
  std::cout << linked_list1 << std::endl;

  linked_list1._insert(10, 2);
  std::cout << "after inserting index=2 with value=10\n";
  std::cout << linked_list1 << std::endl;

  // test index search
  unsigned int index = 1;
  std::cout << "index search: index=" << index << "; result=" << linked_list1.search(index)
            << std::endl;

  // test element search
  int element = 10;
  std::cout << "element search: element=" << element << "; result=" << linked_list1.search(element)
            << std::endl;
}

#endif