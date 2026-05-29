#include <bit>
#include <cmath>
#include <cstdint>
#include <limits>
#include <print>

float GetInvSqrt(float num) noexcept
{
    auto bits = std::bit_cast<std::int32_t>(num);
    bits = 0x5f3759df - (bits >> 1);
    const auto approx = std::bit_cast<float>(bits);
    return approx * (1.5f - (num * 0.5f * approx * approx));
}

void work1() {
    int a = std::numeric_limits<int>::max();
    int b = a + 1;
    static_cast<void>(b);
}

void work2() {
    std::uint8_t val = 0x42;
    // cout << &val << endl;
    std::println("{}", static_cast<const void*>(&val));
}

void work3() {
    constexpr float test_values[] = {
        0.25f,
        1.0f,
        4.0f,
        16.0f,
        0.01f,
        100.0f,
        0.15625f,
        3.14159265f,
        65536.0f,
        0.0001f,
    };

    std::println("{:>12}  {:>14}  {:>14}  {:>10}  {:>12}",
                 "num", "GetInvSqrt(num)", "1/sqrt(num)", "误差(绝对)", "误差(相对)");
    std::println("{:-^12}  {:-^14}  {:-^14}  {:-^10}  {:-^12}",
                 "", "", "", "", "");

    for (const auto num : test_values) {
        const auto approx = GetInvSqrt(num);
        const auto exact = 1.0f / std::sqrt(num);
        const auto abs_err = std::fabs(approx - exact);
        const auto rel_err = abs_err / exact;

        std::println("{:>12.8f}  {:>14.10f}  {:>14.10f}  {:>10.3e}  {:>12.3e}",
                     num, approx, exact, abs_err, rel_err);
    }
}

int main()
{
    work3();
    return 0;
}
    
