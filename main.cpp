#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
using namespace std;

vector<double> input_numbers(size_t cnt)
{
    vector<double> result(cnt);
    for (size_t i = 0; i < cnt; i++)
    {
        cin >> result[i];
    }
    return result;
}


vector<size_t> make_histogram(const vector<double>& numbers, const size_t bin_count)
{
    double min, max;
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    vector<size_t> bins(bin_count, 0);
    for (size_t i = 0; i < numbers.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; j < bin_count - 1 && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;

            if (lo <= numbers[i] && numbers[i] < hi)
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}


void show_histogram_text(const vector<size_t>& bins)
{
    size_t max_count = bins[0];
    for (size_t bin : bins)
    {
        if (max_count < bin)
        {
            max_count = bin;
        }
    }

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << " ";
        }
        if (bin < 10)
        {
            cout << " ";
        }
        cout << bin << "|";
        size_t height;
        if (max_count > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
        }
        else
        {
            height = bin;
        }
        for (size_t i = 0; i < height; i++)
        {
            cout << "*";
        }
        cout << endl;
    }
}


vector<string> input_colours(size_t bin_count) {
    vector<string> colours(bin_count);
    for (int i = 0; i < bin_count; i++) {
        cerr << "Enter bin " << i + 1 << " colour: ";
        cin >> colours[i];
        while (!check_color(colours[i])) {
            cin >> colours[i];
        }
    }
    return colours;
}


int main()
{
    //Ввод данных
    size_t number_count;
    cerr << "enter number count: ";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "enter bin count: ";
    cin >> bin_count;
    //Расчет гистограммы
    const auto bins = make_histogram(numbers, bin_count);
    const auto colours = input_colours(bin_count);
    //Вывод гистограммы
    show_histogram_svg(bins, colours);

    return 0;
}
