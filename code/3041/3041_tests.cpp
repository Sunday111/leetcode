#include "3041.hpp"
#include "3041_flat_bitset.hpp"
#include "3041_pyramid_bitset.hpp"
#include "3041_radix.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution_adaptive::maxSelectedElements;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3]      2
[1,4,7,10]  1
[1,2,2]    3
[2,1,5,1,1] 3
[1] 1
[1000000] 1
[1,1,1,1] 2
[1000000,1000000] 2
[1,1,3,3,5,5] 6
[1,2,4] 3
[63,64,65,65,66] 5
[4095,4096,4096,4097] 4
[262143,262144,262144,262145] 4
[999998,999999,1000000,1000000] 4
[1,64,4096,262144,1000000] 1
)");

using t3041 = SolutionTests<
    Solution_adaptive,
    Solution_flat_bitset,
    Solution_pyramid_bitset,
    Solution_radix>;

TEST_P(t3041, Test)
{
    check(
        kCases,
        [](auto& solution, auto& nums)
        { return solution.maxSelectedElements(nums); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3041,
    t3041::parameters(kCases.size()),
    t3041::name);
