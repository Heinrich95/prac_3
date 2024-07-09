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
vector<double> make_histogram(const vector<double>& numbers, size_t bin_count, size_t number_count) {
    vector<double> bins(bin_count);
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
void show_histogram_text(const vector<double>& bins){
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
    show_histogram_text(bins);
}
