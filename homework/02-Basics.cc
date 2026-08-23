#include <bit>
#include <cassert>
#include <cstdio>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <print>

#include <type_traits>
#include <vector>

#include <ranges>
#include <map>
#include <algorithm>

std::uint32_t ToNetworkByteOrder(std::uint32_t data) {
    if constexpr (std::endian::native == std::endian::big) {
        return data;
    } else if constexpr (std::endian::native == std::endian::little) {
        return std::byteswap(data);
    } else {
        std::println(stderr, "警告：当前机器既不是大端序，也不是小端序");
        return data;
    }
}

void Second() {
    std::uint8_t a;
    std::println("{}", static_cast<const void*>(&a));
}

int SixHelper(float f, double d){
  return static_cast<int> (f + d) ;
}

void Six(int (*f)(float, double)) {
  std::println("{}", f(1.0F, 2.0));
}

enum class Op : uint8_t {
  READ = 1U << 0,
  WRITE = 1U << 1,
  EXEC = 1U << 2,
};

constexpr Op operator|(Op lhs, Op rhs) noexcept {
  return static_cast<Op>(
    std::to_underlying(lhs) | std::to_underlying(rhs)
  );
}

constexpr Op operator&(Op lhs, Op rhs) noexcept {
  return static_cast<Op>(
    std::to_underlying(lhs) & std::to_underlying(rhs)
  );
}

void Test(int);

// 合法。
//  - 两个声明合法，可以放在同一个重载集合中。
//  - Test(1) 只会选择普通函数，因为 T 无法推导。
//  - Test<int>(1) 显式选择函数模板。
//  - 返回类型仍然不参与普通的重载决议或模板参数推导。
template<typename T>
T Test(int);

void FillFibonacci(std::vector<int>& v)
{
    std::ranges::generate(
        v,
        [current = 0, next = 1]() mutable {
          const int result = current;
          const int sum = current + next;
          current = next;
          next = sum;
          return result;
        }
    );
}

enum class Color : uint8_t {
  RED,
  BLUE,
  GREEN,
};

void GetRes(Color c) {
  using enum Color;

  switch (c) {
    case RED:
      [[fallthrough]];
    case GREEN:
      std::println("Hello");
        break;
    case BLUE:
      std::println("World");
        break;
  }
}

struct DijkstraInfo
{
    int vertexID;
    int distance; // 作为比较的标准
};

void SortByDistance(std::vector<DijkstraInfo>& v) {
  // 使用投影函数
  std::ranges::sort(v, {}, &DijkstraInfo::distance);
}

int main() {
  return 0;
}
