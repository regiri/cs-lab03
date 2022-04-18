#include "histogram.h"

#include <cassert>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative() {
    double min = -1000;
    double max = -1000;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_equal() {
    double min = -3000;
    double max = -1000;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_solo() {
    double min = -3000;
    double max = -1000;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_zero() {
    double min = -3000;
    double max = -1000;
    find_minmax({}, min, max);
    assert(min == -3000);
    assert(max == -1000);
}

int main()
{
    test_positive();
    test_negative();
    test_equal();
}
