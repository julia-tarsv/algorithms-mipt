#include <cmath>
#include <iostream>
#include <vector>

std::pair<int, int> Partition(std::vector<int>& elements, int left, int right,
                              int pivot) {
  int point = left;
  for (int i = left; i <= right; ++i) {
    if (elements[i] < pivot) {
      std::swap(elements[i], elements[point]);
      ++point;
    }
  }

  int point1 = point;
  for (int i = point; i <= right; ++i) {
    if (elements[i] == pivot) {
      std::swap(elements[i], elements[point]);
      ++point;
    }
  }

  return {point1 - 1, point};
}

void QuickSort(std::vector<int>& elements, int left, int right) {
  if (left >= right) {
    return;
  }

  int index_pivot = left + rand() % (right - left + 1);
  int pivot = elements[index_pivot];

  std::pair<int, int> inxs = Partition(elements, left, right, pivot);

  QuickSort(elements, left, inxs.first);
  QuickSort(elements, inxs.second, right);
}

int main() {
  size_t size_of_elements;
  std::cin >> size_of_elements;

  std::vector<int> elements(size_of_elements);

  for (size_t i = 0; i < size_of_elements; ++i) {
    std::cin >> elements[i];
  }

  QuickSort(elements, 0, size_of_elements - 1);

  for (size_t i = 0; i < size_of_elements; ++i) {
    std::cout << elements[i] << ' ';
  }
}
