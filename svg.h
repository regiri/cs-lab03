#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

void svg_begin(double width, double height);


void svg_end();


void svg_text(double left, double baseline, string text);


void svg_rect(double x, double y, double width, double height, string stroke, string fill);


void show_histogram_svg(const vector<size_t>& bins, vector<string> colours);


#endif // SVG_H_INCLUDED
