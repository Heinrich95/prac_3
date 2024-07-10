#include <iostream>
#include <vector>
#include <algorithm>
#include "histogram.h"
#include "input_numbers.h"
#include "make_histogram.h"
#include "output_histogram.h"
#include "SVG.h"
using namespace std;

int main()
{
    size_t number_count, bin_count;
    //���� �����
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);
    //������ ������
    cerr << "Enter bin's count: ";
    cin >> bin_count;
    const auto bins = make_histogram(numbers, bin_count, number_count);
    //�����
    show_histogram_text(bins);
    show_histogram_svg(bins);
}
