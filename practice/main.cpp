#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}
void find_minmax(const vector<double>& numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
}
vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count, size_t number_count) {
    vector<size_t> bins(bin_count);
    double min, max;
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
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
void show_histogram_text(const vector<size_t>& bins){
    for(auto bin : bins){
        //вывод гистограммы с проверкой масштабирования
        size_t max_bin = *max_element(bins.begin(), bins.end());
        size_t height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
        if(max_bin > MAX_ASTERISK){
            for (size_t i = 0; i < MAX_ASTERISK - height; i++){
                cout << ' ';
            }
            for (size_t i = 0; i < height; i++){
                cout << '*';
            }
        }
        else {
            for (size_t i = 0; i < max_bin - bin; i++){
                cout << ' ';
            }
            for (size_t i = 0; i < bin; i++){
                cout << '*';
            }
        }
        cout << "|";

        // шаг 2 - выравнивание подписи корзин гистограммы
        if (bin < 100){
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << endl;
    }
}
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
void svg_rect(double x, double y, double width, double height, string stroke = "blue", string fill = "red") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height <<"' stroke='" << stroke << "' fill='" << fill << "' />";
}
void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto MAX_IMAGE_WIDTH = IMAGE_WIDTH - 60;
    const auto IMAGE_HEIGHT = 300;
    auto TEXT_LEFT = 50;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 20;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    size_t max_bin = *max_element(bins.begin(), bins.end());
    for (size_t bin : bins) {
        const double max_bin_width = BLOCK_WIDTH * max_bin;
        size_t height = MAX_IMAGE_WIDTH * (static_cast<double>(bin) / max_bin);
        if (bin > 9) {
            TEXT_LEFT-=7;
        }
        if (bin > 99){
            TEXT_LEFT-=1;
        }
        if(max_bin_width > MAX_IMAGE_WIDTH) {
            const double height_width = height;
            svg_text(TEXT_LEFT + MAX_IMAGE_WIDTH, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH + MAX_IMAGE_WIDTH - height_width, top, height_width, BIN_HEIGHT);
        }
        else {
            const double bin_width = BLOCK_WIDTH * bin;
            svg_text(TEXT_LEFT + max_bin_width, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH + max_bin_width - bin_width, top, bin_width, BIN_HEIGHT);
        }
        top += BIN_HEIGHT;
    }
    svg_end();
}
//===============================================
int main()
{
    size_t number_count, bin_count;
    //ввод чисел
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);
    //массив корзин
    cerr << "Enter bin's count: ";
    cin >> bin_count;
    const auto bins = make_histogram(numbers, bin_count, number_count);
    //вывод
    show_histogram_svg(bins);
}
