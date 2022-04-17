#include <iostream>
#include <vector>

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double> input_numbers(size_t cnt) {
    vector<double> result(cnt);
    for (size_t i = 0; i < cnt; i++) {
        cin >> result[i];
    }
    return result;
}


void find_minmax(const vector<double>& numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (auto num : numbers) {
        if (num < min) {
            min = num;
        }
        if (num > max) {
            max = num;
        }
    }
}


vector<double> make_histogram(const vector<double>& numbers, const size_t bin_count) {
    double min, max;
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    vector<double> bins(bin_count, 0);
    for (size_t i = 0; i < numbers.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; j < bin_count - 1 && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;

            if (lo <= numbers[i] && numbers[i] < hi) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}


void show_histogram_text(const vector<double>& bins) {
    size_t max_count = bins[0];
    for (size_t bin : bins) {
        if (max_count < bin) {
            max_count = bin;
        }
    }

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << " ";
        }
        if (bin < 10) {
            cout << " ";
        }
        cout << bin << "|";
        size_t height;
        if (max_count > MAX_ASTERISK) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
        } else {
            height = bin;
        }
        for (size_t i = 0; i < height; i++) {
            cout << "*";
        }
        cout << endl;
    }
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
    show_histogram_text(bins);

    return 0;
}
