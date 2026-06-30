#include <exception>
#include <iostream>
#include <vector>
#include "linear_list/linked_list.hpp"
#include "linear_list/sequence_list.hpp"
#include "linear_list/stack.hpp"

#define MAX_SIZE      100 // Maximum size
#define MIN_SIZE      10 // Minimum size
#define DEFAULT_VALUE 42 // Default value

struct Config {
  int width; // display width
  int height; // display height
  const char* title; // window title
};

void deprecated_main(int, char**) { // first comment
  std::cout << "Hello, from test!\n"; // second comment
  float x, y;
  std::cout << "invoke power function" << std::endl;
  std::cout << "please input your source float and power float:\n";
  std::cin >> x >> y;
  std::cout << "result: " << x + y << std::endl;
}

int main() {
  std::cout << "Hello, from test!\n";
  std::vector<int> default_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  //   sequence_list_test(default_vector);
//   linked_list_test(default_vector);
    stack_test(default_vector);
}