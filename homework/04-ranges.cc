
#include <array>
#include <iterator>
#include <ranges>

#include <vector>
#include <string>
#include <print>
#include <iostream>
#include <generator>
namespace stdr = std::ranges;
namespace stdv = std::views;


template<typename T>
void PrintVector(const std::vector<T>& v) {
    stdr::copy(v, std::ostream_iterator<T>(std::cout, " "));
    std::cout << '\n';
}

// QuickSort 取第一个元素作为pivot
// 可以分为三部分 然后用 join 把三部分的 view 组装在一起，
// 再用 stdr::to<Cont>() 转化为目标 container 类型
template<typename Cont>
Cont QuickSort(const Cont& cont)
{
    // 如果是空，返回空容器；否则...
    return stdr::empty(cont) 
        ? cont 
        : std::array<Cont, 3> {
            QuickSort(cont | stdv::drop(1) | stdv::filter([&](const auto& elem){
                return elem <= *stdr::begin(cont);
            }) | stdr::to<Cont>()),
            stdv::single(*stdr::begin(cont)) | stdr::to<Cont>(),
            QuickSort(cont | stdv::drop(1) | stdv::filter([&](const auto& elem){
                return elem > *stdr::begin(cont);
            }) | stdr::to<Cont>()),        
        } | stdv::join | stdr::to<Cont>();
}

// 函数参数使用std::string_view更好一点，不过我们还没讲到流与字符串，所以就略过了。
// 可以简单说一下，他和span<const char>十分相似，存储了两个const char指针，代表了一段字符范围。
std::vector<std::string> SplitString(const std::string& str, 
                                     const std::string& delim)
{
    return str 
    | stdv::split(delim) // 此处分离的是subranges 
    | stdr::to<std::vector<std::string>>(); // 不使用CATD 可以省下 一行代码
}

std::string Secret(std::string str) {
    std::string answer {};
    for(auto [idx, elem] : str | stdv::enumerate) {
        elem = (elem - 'a' + idx) % 26 + 'a';
        answer += elem;
    }
    return answer;
}


std::generator<int> Fib(int num)
{
    int a = 0, b = 1;
    for (int i = 0; i < num; i++)
    {
        int temp = a;
        a = b;
        b += temp;
        co_yield a;
    }
}


int main() {
    std::vector<int> v{9,8,7,6,5,4,3,2,1};

    std::println("{}", QuickSort(v));

    std::println("{}", SplitString("a,b,c,1,2", ","));

    std::println("{}", Secret("a,b,c,d,e"));

    auto fib5 = Fib(5);
    for (auto elem : fib5)
        std::print("{} ", elem);
    return 0;
}