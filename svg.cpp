#include <iostream>
#include <vector>
#include "svg.h"
#include <windows.h>
#include <sstream>
using namespace std;


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

string
make_info_text() {
    stringstream buffer;
    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD platform = info >> 16;
    DWORD mask1 = 0x0000ff00;
    DWORD mask2 = 0x000000ff;
    DWORD version_major = version & mask2;
    DWORD version_minor = (version & mask1) >> 8;
    DWORD build;
    if ((info & 0x80000000) == 0) {
        build = platform;
    } else {
        build = platform & 0x7fff0000;
    }
    unsigned long len = MAX_COMPUTERNAME_LENGTH + 1;
    char buf[len] = "";
    sprintf(buf, "Windows v%u.%u (build %d) ", version_major, version_minor, build);
    buffer << buf;
    GetComputerNameA(buf, &len);
    buffer << buf;
    return buffer.str();
}

void show_histogram_svg(const vector<size_t>& bins, vector<string> colours)
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
    for (size_t i = 0; i < bins.size(); i++) {
        size_t height = bins[i] * BLOCK_WIDTH;
        if (max_count * BLOCK_WIDTH > IMAGE_WIDTH - TEXT_WIDTH)
        {
            height = (IMAGE_WIDTH - TEXT_WIDTH) * (static_cast<double>(bins[i]) / max_count);
        }
        const double bin_width = height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, colours[i], colours[i]);
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, make_info_text());
    svg_end();
}

