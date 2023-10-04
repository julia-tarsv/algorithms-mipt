#include <cmath>
#include <iostream>
#include <vector>

int pivot = 0;
std::pair<int, int> Partition(std::vector<int>& mas, int left, int right) {
  int index_pivot = left + rand() % (right - left + 1);
  pivot = mas[index_pivot];
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

int QuickSelect(std::vector<int>& mas, int left, int right, int stat) {
  if (left > right) {
    return mas[stat];
  }
  std::pair<int, int> inxs = Partition(mas, left, right);
  if (stat > inxs.first && stat < inxs.second) {
    return pivot;
  }
  if (stat <= inxs.first) {
    return QuickSelect(mas, left, inxs.first, stat);
  }
  return QuickSelect(mas, inxs.second, right, stat);
}

int main() {
  int number;
  std::cin >> number;
  int k_static;
  std::cin >> k_static;
  int elem0;
  int elem1;
  std::cin >> elem0 >> elem1;
  std::vector<int> mas(number);
  mas[0] = elem0;
  mas[1] = elem1;
  const int kP123 = 123;
  const int kP45 = 45;
  const int kPer = 1e7 + 4321;
  for (int i = 2; i < number; ++i) {
    mas[i] = (mas[i - 1] * kP123 + mas[i - 2] * kP45) % kPer;
  }

  std::cout << QuickSelect(mas, 0, number - 1, k_static - 1);
}
