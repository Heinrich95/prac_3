#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    size_t number_count, bin_count;
    //��� 3 - ��������� ��� ���������������
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    //����
    cerr << "Enter number count: ";
    cin >> number_count;
    vector<double> numbers(number_count);
    cerr << "Enter numbers: ";
    for(int i = 0; i < number_count; i++){
        cin >> numbers[i];
    }
    cerr << "Enter bin's count: ";
    cin >> bin_count;
    //������ ������
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
    //���������� ������ ����� ���������
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
    //���������� ���������� ������� ��� ���� 3 � ������������ ��������
    size_t max_bin = *max_element(bins.begin(), bins.end());
    //�����
    for(auto bin : bins){
        //����� ����������� � ��������� ���������������
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

        // ��� 2 - ������������ ������� ������ �����������
        if (bin < 100){
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << endl;
    }
}
