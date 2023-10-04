#include <cmath>
#include <iostream>
#include <vector>

std::pair<int, int> Partition(std::vector<int>& mas, int left, int right) {
  int index_pivot = left + rand() % (right - left + 1);
  int pivot = mas[index_pivot];
  int point = left;

  for (int i = left; i <= right; ++i) {
    if (mas[i] < pivot) {
      std::swap(mas[i], mas[point]);
      ++point;
    }
  }

  int point1 = point;
  for (int i = point; i <= right; ++i) {
    if (mas[i] == pivot) {
      std::swap(mas[i], mas[point]);
      ++point;
    }
  }
  return {point1 - 1, point};
}

void QuickSort(std::vector<int>& mas, int left, int right) {
  if (left >= right) {
    return;
  }

  std::pair<int, int> inxs = Partition(mas, left, right);

  if (inxs.first == left - 1) {
    if (inxs.second != right + 1) {
      QuickSort(mas, inxs.second, right);
    }
  } else {
    if (inxs.second == right + 1) {
      QuickSort(mas, left, inxs.first);
    } else {
      QuickSort(mas, left, inxs.first);
      QuickSort(mas, inxs.second, right);
    }
  }
}

int main() {
  int number;
  std::cin >> number;

  std::vector<int> mas(number);
  for (int i = 0; i < number; i++) {
    std::cin >> mas[i];
  }

  QuickSort(mas, 0, number - 1);

  for (int i = 0; i < number; i++) {
    std::cout << mas[i] << "\n";
  }
}