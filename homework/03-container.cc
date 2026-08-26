
#include <algorithm>
#include <compare>
#include <concepts>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

// ==========================================
// 题目 1: 模板函数练习
// 写一个模板函数，对第一个元素*2，并累加所有的元素
// ==========================================
template <typename Range>
auto Function(Range& range) {
    auto beg = std::ranges::begin(range);
    auto end = std::ranges::end(range);

    // 类型萃取
    using ValueType = std::ranges::range_value_t<Range>;

    // 处理空容器情况
    if (beg == end) {
        return ValueType{0};
    }

    // 使用 std::ranges::begin(range) 统一适配标准容器（如 vector/list）和原生数组（如 int arr[]），因为原生数组没有 .begin() 成员函数。
    *beg *= 2;

    // 2. 累加所有元素
    // 使用 C++23 的 std::ranges::fold_left 进行区间求和
    auto sum = std::ranges::fold_left(range, ValueType{0}, std::plus<>{});

    return sum;
}

void Test1() {
    std::println("=== 题目 1 测试 ===");
    std::vector v{1, 2, 3};
    auto sum_v = Function(v);
    std::println("std::vector 修改后: {}, 累加和: {}", v, sum_v);

    std::list l{2, 2, 3};
    auto sum_l = Function(l);
    std::println("std::list   修改后: {}, 累加和: {}", l, sum_l);

    int arr[] = {1, 2, 3}; // 原生数组没有 .begin() 成员函数
    auto sum_arr = Function(arr);
    std::println("原生数组     修改后: {}, 累加和: {}", arr, sum_arr);
}

// ==========================================
// 题目 2: std::vector API 练习
// 本题要求：输出 vector 请包装为一个函数，并用 ostream_iterator 输出
// ==========================================
template <typename T>
void PrintVector(const std::vector<T>& v, std::string_view prefix = "") {
    if (!prefix.empty()) {
        std::cout << prefix << ": ";
    }
    // 使用 std::ranges::copy 与 std::ostream_iterator 输出容器元素
    std::ranges::copy(v, std::ostream_iterator<T>(std::cout, " "));
    std::cout << '\n';
}

void Test2() {
    std::println("\n=== 题目 2: std::vector API 练习 ===");

    // 1. 创建一个 std::vector v1，包含 10 个 5（使用构造函数填充）
    std::vector<int> v1(10, 5);
    PrintVector(v1, "1. 创建 v1(10, 5)");

    // 2. 创建第二个 std::vector v2，包含 {2, 1, 4}
    std::vector<int> v2{2, 1, 4};
    PrintVector(v2, "2. 创建 v2{2, 1, 4}");

    // 3. 将 v2 反向插入到 v1 的第三个位置（即 5,5,4,1,2,5,5...），注意使用反向迭代器
    // 第三个位置索引为 2（从 0 开始计数），对应迭代器 v1.begin() + 2
    v1.insert(v1.begin() + 2, v2.rbegin(), v2.rend());
    PrintVector(v1, "3. 将 v2 反向插入 v1 第三个位置");

    // 4. 移除从第 5 个元素开始的所有元素（即保留前 5 个元素 5,5,4,1,2）
    // 下标 0~4 保留，擦除区间 [v1.begin() + 5, v1.end())
    v1.erase(v1.begin() + 5, v1.end());
    PrintVector(v1, "4. 移除第 5 个元素之后的所有元素");

    // 5. 移除所有奇数，不使用 O(n^2) 的方法
    // 使用 C++20 提供的 std::erase_if，时间复杂度为 O(n)
    std::erase_if(v1, [](int n) { return n % 2 != 0; });
    PrintVector(v1, "5. 移除所有奇数后");

    // 6. 与 vector v{1, 7} 做三路比较，打印结果
    std::vector<int> v{1, 7};
    auto cmp = v1 <=> v;
    std::cout << "6. 与 vector{1, 7} 三路比较结果: ";
    if (cmp < 0) {
        std::println("v1 < v");
    } else if (cmp > 0) {
        std::println("v1 > v");
    } else {
        std::println("v1 == v");
    }
}

// ==========================================
// 题目 3: std::list API 练习
// ==========================================
void Test3() {
    std::println("\n=== 题目 3: std::list API 练习 ===");

    // 1. 创建一个 std::list l1，包含 10 个 5
    std::list<int> l1(10, 5);
    std::println("1. 创建 l1(10, 5): {}", l1);

    // 2. 创建第二个 std::list l2，包含 {2, 1, 4}
    std::list<int> l2{2, 1, 4};
    std::println("2. 创建 l2{{2, 1, 4}}: {}", l2);

    // 3. 将 l2 融合到 l1 中，操作后 l2 变为空
    // std::list::splice 将 l2 的节点全部剪切转移到 l1 末尾，时间复杂度 O(1)，无内存重新分配
    l1.splice(l1.end(), l2);
    std::println("3. 将 l2 融合到 l1 中: l1 = {}, l2 是否为空: {}", l1, l2.empty());

    // 4. 对 l1 去除相邻的重复元素
    // std::list::unique 移除连续重复节点（10 个连续的 5 只保留 1 个）
    l1.unique();
    std::println("4. 对 l1 去除相邻重复元素: {}", l1);

    // 5. 对 l1 排序
    // std::list 的迭代器为双向迭代器（Bidirectional），不支持 std::sort，需调用成员函数 l1.sort()
    l1.sort();
    std::println("5. 对 l1 排序后: {}", l1);
}


void problem6() {
  std::vector vec{ 10,2,3,10,4 };
  auto it = std::ranges::max_element(vec);

  // 参数 value 直接绑定到了 vec[0] 的物理内存上！
  // 在 C++ 中，解引用操作 *it 产生的并不是一个新的「值拷贝」，而是原内存位置的「左值引用（T&）」
  std::erase(vec, *it);
  for (auto& i : vec)
    std::print("{}", i);
}

int main() {
    Test1();
    Test2();
    Test3();
    return 0;
}