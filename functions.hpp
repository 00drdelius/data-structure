#include <string>
#include <cmath>

namespace math_funcs {

// NOTE: inline 函数的定义必须在使用它的每个翻译单元（即每个 .cpp 文件）中都可见
// 因此 inline 函数基本推荐在头文件中实现
inline constexpr float power(float src_digit, float power)
{
    float result = 0;
    result = std::pow(src_digit, power);
    return result;
}

}
