#include <iostream>
#include <vector>
#include <exception>
#include "utils.hpp"
#include "linear_list/sequence_list.hpp"

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
    std::vector<int> default_vector{0,1,2,3,4,5,6,7,8,9,10};
    int static_size = 5;
    SequenceList<int> static_list{false, static_size};
    // check static array
    std::cout << "[static array test]" << std::endl;
    std::cout << "append\n";
    for(auto ele : default_vector){
        try {
            static_list.append(ele);
        }
        catch ( std::exception& e ) {
            std::cout << "Exception raised: " << e.what() << std::endl;
            break;
        }
    }
    std::cout << "Max size of this static list is " << static_list.get_max_size() << std::endl
    << "Length already is " << static_list.get_length() << std::endl
    << "Source list: " << static_list << std::endl;

    static_list._delete(0);
    std::cout << "after deleting index=0\n";
    std::cout << static_list << std::endl;

    static_list._insert(10, 2);
    std::cout << "after inserting index=2 with value=10\n";
    std::cout << static_list << std::endl;

    // test index search
    unsigned int index=1;
    std::cout << "index search: index=" << index <<"; result=" << static_list.search(index)
    << " with its pointer: " << static_list.search_ptr(index) << std::endl;

    // test element search
    int element=10;
    std::cout << "element search: element=" << element << "; result=" << static_list.search(element) << std::endl;

    // dynamic array
    SequenceList<int> dynamic_list{true, static_size};
    // check dynamic array
    std::cout << "[static array test]" << std::endl;
    std::cout << "append\n";
    for(auto ele : default_vector){
        try {
            dynamic_list.append(ele);
        }
        catch ( std::exception& e ) {
            std::cout << "Exception raised: " << e.what() << std::endl;
            break;
        }
    }
    std::cout << "Max size of this static list is " << dynamic_list.get_max_size() << std::endl
    << "Length already is " << dynamic_list.get_length() << std::endl
    << "Source list: " << dynamic_list << std::endl;

}