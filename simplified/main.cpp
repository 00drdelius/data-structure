#include <iostream>
#include "linear_list.hpp"


int _2009_408_algo(LinkList head, int k){
    DynArray dyn_array{};
    int linklist_len = 0;
    while (head->next!=NULL){
        linklist_len++;
        head = head->next;
        dyn_array.push(head->data);
    }
    std::cout << "linklist_len: " << linklist_len << "\n";
    for (int i=0;i<linklist_len;i++) {
        std::cout << "ele: " << dyn_array.get(i) << std::endl;
    }
    if(linklist_len<k) {return 0;}
    else {return dyn_array.get(linklist_len-k);};
}

// void _2009_408_algo_test(){
//     LinkList list; // 野指针，在首次调用list->next时因为list为无效地址会报段错误
//     const int init_len = 6; 
//     int arr[init_len] = {11,11451,21,33,32,34};
//     for(int i=0;i<init_len;i++){
//         LNode node{arr[i],}; // 循环体内的局部变量，每次迭代结束其生命周期亦结束，需要使用堆初始化
//         list->next = &node;
//         list = list->next;
//     }
//     int last1 = _2009_408_algo(list, 1); // _2009_408_algo的首参数接受的应该是头结点，但这里的list是尾节点
//     int last3 = _2009_408_algo(list, 3);
//     int last6 = _2009_408_algo(list, 6);
//     std::cout << "last1: " << last1 << "\n"
//     << " last3: " << last3 << "\n"
//     << " last6: " << last6 << std::endl;
// }

void _2009_408_algo_test(){
    LinkList head = new LNode{};
    LinkList node = head;
    const int init_len = 6;
    int arr[init_len] = {11,11451,21,33,32,34};
    for(int i=0;i<init_len;i++){
        // LinkList temp_node = new LNode(arr[i]); // LNode() 这种小括号初始化在C++20以前不适用于没有显式定义构造函数的类（典型的就是struct）
        LinkList temp_node = new LNode{arr[i], NULL}; // 但LNode{arr[i], NULL}会按成员声明顺序依次初始化
        node->next = temp_node;
        node = node->next;
    }
    int last1 = _2009_408_algo(head, 1);
    int last3 = _2009_408_algo(head, 3);
    int last6 = _2009_408_algo(head, 6);
    int last7 = _2009_408_algo(head, 7);
    std::cout << "last1: " << last1 << "\n"
    << " last3: " << last3 << "\n"
    << " last6: " << last6 << "\n"
    << " last7: " << last7 << "\n";
}


int main(){
    _2009_408_algo_test();
    return 0;
}