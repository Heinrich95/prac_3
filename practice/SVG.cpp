#include "SVG.h"

//==================SVG=============================
void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string fill = "blue", string stroke = "black") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height <<"' stroke='" << stroke << "' fill='" << fill << "' />";
}

bool check_color(string color) {
    return color != "red";
}

void show_histogram_svg(const vector<size_t>& bins) {

    string fill;
    do {
        cerr << "Enter fill color for the histogram bars (not red): ";
        cin >> fill;
        if (!check_color(fill)) {
            cerr << "Red color is not allowed. Please enter a different color." << endl;
        }
    } while (!check_color(fill));

    const auto IMAGE_WIDTH = 400;
    const auto MAX_IMAGE_WIDTH = IMAGE_WIDTH - 60;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 20;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    auto TEXT_LEFT = 50;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = BIN_HEIGHT;
    size_t max_bin = *max_element(bins.begin(), bins.end());
    double total_width = 0;

    for (size_t bin : bins) {
        const double max_bin_width = BLOCK_WIDTH * max_bin;
        size_t height = MAX_IMAGE_WIDTH * (static_cast<double>(bin) / max_bin);
        const double bin_width = BLOCK_WIDTH * bin;
        if (bin > 9) {
            TEXT_LEFT-=7;
        }
        if (bin > 99){
            TEXT_LEFT-=1;
        }
        if(max_bin_width > MAX_IMAGE_WIDTH) {
            const double height_width = height;
            svg_text(TEXT_LEFT + MAX_IMAGE_WIDTH, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH + MAX_IMAGE_WIDTH - height_width, top, height_width, BIN_HEIGHT, fill);
            total_width = MAX_IMAGE_WIDTH;
        }
        else {
            const double bin_width = BLOCK_WIDTH * bin;
            svg_text(TEXT_LEFT + max_bin_width, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH + max_bin_width - bin_width, top, bin_width, BIN_HEIGHT, fill);
            total_width = max(total_width, TEXT_LEFT + TEXT_WIDTH + bin_width);
        }
        top += BIN_HEIGHT;
    }
    svg_text(total_width / 2, TEXT_BASELINE, "Histogram");
    svg_end();
}
//===============================================
