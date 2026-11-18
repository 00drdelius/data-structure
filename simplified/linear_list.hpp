// 简化实现的动态数组
#pragma once

#include <iostream>


class DynArray{
private:
    int* _array = NULL; // 初始化为NULL用于判断是否为空。C++11后可以初始化为nullptr。NULL一般被宏定义为0，但nullptr编译器明确为空指针
    int length;

public:
    DynArray(int _len=0){length=_len;}

    int push(int ele) {
        int* new_arr = new int[++length];
        for(int i=0;i<length-1;i++){
            new_arr[i] = _array[i];
        }
        new_arr[length-1] = ele;
        delete [] _array;
        _array = new_arr;
        return 1;
    }

    int get(int index) {
        return _array[index];
    }
};
