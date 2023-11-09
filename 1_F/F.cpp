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

int QuickSelect(std::vector<int>& elements, int left, int right, int stat) {
  if (left > right) {
    return elements[stat];
  }

  int index_pivot = left + rand() % (right - left + 1);
  int pivot = elements[index_pivot];

  std::pair<int, int> inxs = Partition(elements, left, right, pivot);
  if (stat > inxs.first && stat < inxs.second) {
    return pivot;
  }
  if (stat <= inxs.first) {
    return QuickSelect(elements, left, inxs.first, stat);
  }
  return QuickSelect(elements, inxs.second, right, stat);
}

int main() {
  size_t size_of_elements;
  std::cin >> size_of_elements;
  int k_static;
  std::cin >> k_static;

  std::vector<int> elements(size_of_elements);
  std::cin >> elements[0] >> elements[1];

  const int kFactor1 = 123;
  const int kFactor2 = 45;
  const int kMod = 1e7 + 4321;
  for (size_t i = 2; i < size_of_elements; ++i) {
    elements[i] =
        (elements[i - 1] * kFactor1 + elements[i - 2] * kFactor2) % kMod;
  }

  std::cout << QuickSelect(elements, 0, size_of_elements - 1, k_static - 1);
}
