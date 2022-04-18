#include <vector>
#include "histogram.h"
#include <iostream>
#include <string>

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if (numbers.size() == 0) {
        return;
    }
    min = numbers[0];
    max = numbers[0];
    for (auto num : numbers)
    {
        if (num < min)
        {
            min = num;
        }
        if (num > max)
        {
            max = num;
        }
    }
}


bool check_color(string color) {
    if (color.length() == 0){
        return false;
    }
    return (color[0] == '#') || (color.find(' ') == string::npos);
}
