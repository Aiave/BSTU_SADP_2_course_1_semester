#include <iostream>
#include <vector>
#include <iomanip>

/*14. Написать программы, реализующие алгоритмы сортировки вставками (метод Шелла, сортировка с вычислением
адреса). Сравнить их эффективность (число сравнений и перестановок) для наилучшего и наихудшего вариантов
последовательностей.*/

//вывод
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << std::setw(2) << num << " ";
    }
    std::cout << std::endl;
}

//сортировка Шелла
void shellSort(std::vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size();
    //начинаем с интервала, равного половине размера массива, и уменьшаем вдвое на каждой итерации
    for (int gap = n / 2; gap > 0; gap /= 2) {
        //начинается с элемента, следующего за текущим интервалом
        for (int i = gap; i < n; ++i) {
            //запоминаем значение элемента
            int temp = arr[i];
            int j;

            //цикл для перемещения элементов с шагом интервала влево
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                ++comparisons;
                arr[j] = arr[j - gap];
                ++swaps;
            }

            //вставляем временное значение в правильную позицию
            arr[j] = temp;
            //printArray(arr);
        }
        //printArray(arr);
    }
}

//сортировка с вычислением адреса
void addressCalculationSort(std::vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size();
    //проходится по всем элементам массива, кроме последнего
    for (int i = 0; i < n - 1; ++i) {
        //начинается за элементом, следующим за текущим элементом внешнего цикла
        //количество сравнений для вложенного цикла (n * (n - 1) / 2), где n - размер массива
        for (int j = i + 1; j < n; ++j) {
            ++comparisons;
            if (arr[j] < arr[i]) {
                std::swap(arr[j], arr[i]);
                ++swaps;
            }
            //printArray(arr);
        }
        //printArray(arr);
    }
}

int main() {
    std::vector<int> arr = { 1, 2, 5, 6, 3, 7, 4, 8 };
    int comparisons, swaps;

    //сортировка Шелла
    comparisons = 0;
    swaps = 0;
    std::cout << "\t" << "Shell Sort" << std::endl;
    std::cout << "Original array:   ";
    printArray(arr);
    shellSort(arr, comparisons, swaps);
    std::cout << "Array after sort: ";
    printArray(arr);
    std::cout << "Comparisons: " << comparisons << ", Swaps: " << swaps << std::endl << std::endl;

    //сброс массива
    arr = { 1, 2, 5, 6, 3, 7, 4, 8 };

    //сортировка с вычислением адреса
    comparisons = 0;
    swaps = 0;
    std::cout << "\t" << "Address Calculation Sort" << std::endl;
    std::cout << "Original array:   ";
    printArray(arr);
    addressCalculationSort(arr, comparisons, swaps);
    std::cout << "Array after sort: ";
    printArray(arr);
    std::cout << "Comparisons: " << comparisons << ", Swaps: " << swaps << std::endl;

    return 0;
}

/*
Лучший случай - отсортированный или почти отсортированный массив. Шелл - также большие интервалы.
arr = { 1, 2, 5, 6, 3, 7, 4, 8 };
Худший случай - обратно упорядоченный массив или имеет множество повторяющихся элементов.
arr = { 8, 7, 6, 5, 4, 3, 2, 1 };

Просто массив:
arr = { 1, 2, 5, 6, 3, 7, 4, 8 };
*/