#include "output_histogram.h"

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

void show_histogram_text(const vector<size_t>& bins){
    for(auto bin : bins){
        //����� ����������� � ��������� ���������������
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
