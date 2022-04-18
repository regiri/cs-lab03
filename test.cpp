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

void check_colour_true() {
    assert(check_color("green") == true);
    assert(check_color("red") == true);
    assert(check_color("#010101") == true);
}

void check_colour_false() {
    assert(check_color("gre en") == false);
    assert(check_color("423 255") == false);
    assert(check_color("") == false);
}

int main()
{
    test_positive();
    test_negative();
    test_equal();
    test_solo();
    test_zero();
    check_colour_true();
    check_colour_false();
}
