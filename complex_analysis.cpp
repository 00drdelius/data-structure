#include <iostream>

/**
 * @brief function on data structure book at top page 6.
 * @note 不管给出多大的n，i是指数倍增长的。
 * 假设输入的n需要循环x次退出，则x次循环后：`i = 2^x`
 *
 * 此时可建模： `i = 2**x > n` => `x > log_{2}{n}`，
 * 则有时间复杂度 O(x(x即循环次数)) = O(log_{2}{n})
 */
int func1(int n) {
  int i = 1;
  while (i <= n)
    i *= 2;
  return i;
}

/**
 * @brief datastructure page6 T6
 * @note 建模：循环x次结束时有： `(i+x)^3 > n` => `x > \sqrt[3] {n} + i`
 *
 * 得出时间复杂度 O(x) = O(\sqrt[3] {n})，i忽略不计
 */
void func2(int n) {
  int i = 0;
  while (i * i * i <= n)
    i++;
}

/**
 * @brief datastructure page7 t7
 */
void func3(int n) {}