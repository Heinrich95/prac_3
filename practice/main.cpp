#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    size_t number_count, bin_count;

    cerr << "Enter number count: ";
    cin >> number_count;
    vector<double> numbers(number_count);
    cerr << "Enter numbers: ";
    for(int i = 0; i < number_count; i++){
        cin >> numbers[i];
    }
    cerr << "Enter bin's count: ";
    cin >> bin_count;

    vector<size_t> bins(bin_count);
    double min = numbers[0];
    double max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
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
    /*
    for(auto bin : bins){
        for (int i = 0; i < bin; i++){
            cout << '*';
        }
        cout << "| " << bin;
        cout << endl;
    }
    */
    size_t max_bin = *max_element(bins.begin(), bins.end());

    for(auto bin : bins){
        // Вывести пробелы для выравнивания
        for (size_t i = 0; i < max_bin - bin; i++){
            cout << ' ';
        }
        // Вывести звёздочки
        for (size_t i = 0; i < bin; i++){
            cout << '*';
        }
        cout << "| " << bin;
        cout << endl;
    }
}
