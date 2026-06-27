#ifndef __utils__
#define __utils__

#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>


// #condition: 将参数值转为字符串变量作为宏展开
// do ... while: 因为宏函数展开后有分号分隔。若使用宏函数的地方如下：
/*
```
if(...)
    assert(...);
else
    ...
```
assert展开后会因为分号间隔，以为if语句结束，导致else编译错误，造成`悬空else`的错误
但是do..while(0)后面需要分号，不会导致这个错误
*/
#define assert(condition, msg)                                                 \
  do {                                                                         \
    if (!(condition)) {                                                        \
      throw std::runtime_error(                                                \
          "\033[31m" + std::string("Assertion error: ") + #condition + ".\n" + \
          "Error Message: " + msg + "\033[0m");                                \
    }                                                                          \
  } while (0)

class BaseObject {
 public:
  // define fucntion as virtual which can be overrided by the sub class
  virtual std::string __str__() const {
    return std::string{"BaseObject"};
  }

  friend std::ostream& operator<<(std::ostream& __out, const BaseObject& __obj) {
    return (__out << __obj.__str__());
  }
};

#endif
