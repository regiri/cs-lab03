#include <iostream>
#include <vector>
#include "histogram.h"
using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

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


void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}


void svg_end()
{
    cout << "</svg>\n";
}


void svg_text(double left, double baseline, string text){
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}


void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />\n";
}


void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    size_t max_count = bins[0];
    for (size_t bin : bins)
    {
        if (max_count < bin)
        {
            max_count = bin;
        }
    }


    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        size_t height;
        if (max_count > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
        }
        else
        {
            height = bin;
        }
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(height));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "red");
        top += BIN_HEIGHT;
    }
    svg_end();
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
    //Вывод гистограммы
    show_histogram_svg(bins);

    return 0;
}
