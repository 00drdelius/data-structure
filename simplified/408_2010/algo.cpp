#include "408_2010/algo.hpp"

int* left_move_function(int *arr, int p, int n){
    int *out = new int[n]();
    for(int i=0;i<n;i++){
        out[(i-p+n)%n]=arr[i];
    }
    return out;
}

int get_int_random(){
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dist{-50,50};

    return dist(gen);
}

void print_array(int *arr, int len){
    std::cout << "array: {";
    for (int i=0;i<len;i++){
        std::cout<<arr[i]<<", ";
    }
    std::cout <<"};"<<std::endl;
}

void _408_2010_algo_test() {
    int length=10;
    int left_move_count=4;
    int arr[length];
    std::cout<<"generating random array;\n";
    for(int i=0;i<length;i++){
        arr[i] = get_int_random();
    }
    print_array(arr, length);
    int* left_move = left_move_function(arr, left_move_count, length);
    std::cout<< "after left moving " << left_move_count<< ":\n";
    print_array(left_move, length);
}

void _408_2010_algo_test(int length, int left_move_count) {
    int arr[length];
    std::cout<<"generating random array;\n";
    for(int i=0;i<length;i++){
        arr[i] = get_int_random();
    }
    print_array(arr, length);
    int* left_move = left_move_function(arr, left_move_count, length);
    std::cout<< "after left moving " << left_move_count<< ":\n";
    print_array(left_move, length);
}