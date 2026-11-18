// 链表
#pragma once

#include <iostream>

struct LNode{
    int data;
    struct LNode *next=NULL; // 初始化为NULL用于判断是否为空。C++11后可以初始化为nullptr。NULL一般被宏定义为0，但nullptr编译器明确为空指针
};

typedef struct LNode LNode;
typedef struct LNode *LinkList;
