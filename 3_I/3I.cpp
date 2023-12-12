#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Forth {
  int min1;
  int min2;
  size_t ind1;
  size_t ind2;
};

void Func(std::vector<std::vector<Forth>>& sparces, int num) {
  for (int j = 2; j <= log2(num); ++j) {
    for (int i = 0; i < num - pow(2, j - 1); ++i) {
      std::vector<std::pair<int, int>> minimums;
      int min1_left = sparces[i][j - 1].min1;
      minimums.push_back({min1_left, sparces[i][j - 1].ind1});
      int min2_left = sparces[i][j - 1].min2;
      minimums.push_back({min2_left, sparces[i][j - 1].ind2});
      int min1_right = sparces[i + pow(2, j - 1)][j - 1].min1;
      minimums.push_back({min1_right, sparces[i + pow(2, j - 1)][j - 1].ind1});
      int min2_right = sparces[i + pow(2, j - 1)][j - 1].min2;
      minimums.push_back(
          {min2_right, sparces[i + pow(2, j - 1) - 1][j - 1].ind2});
      sort(minimums.begin(), minimums.end());
      sparces[i][j].min1 = minimums[0].first;
      sparces[i][j].min2 = minimums[1].first;
      sparces[i][j].ind1 = minimums[0].second;
      sparces[i][j].ind2 = minimums[1].second;
    }
  }
}

int main() {
  size_t num;
  size_t req;
  std::cin >> num >> req;
  std::vector<int> mas(num);
  std::vector<std::vector<Forth>> sparces(
      num, std::vector<Forth>(static_cast<int>(log2(num) + 1)));
  for (size_t i = 0; i < num; ++i) {
    std::cin >> mas[i];
  }
  for (size_t i = 0; i < num - 1; ++i) {
    sparces[i][1].min1 = std::min(mas[i], mas[i + 1]);
    sparces[i][1].min2 = std::max(mas[i], mas[i + 1]);
    if (mas[i] < mas[i + 1]) {
      sparces[i][1].ind1 = i;
      sparces[i][1].ind2 = i + 1;
    } else {
      sparces[i][1].ind1 = i + 1;
      sparces[i][1].ind2 = i;
    }
  }
  Func(sparces, num);
  for (size_t i = 0; i < req; ++i) {
    size_t left;
    size_t right;
    std::cin >> left >> right;
    --left;
    --right;
    int length = log2(right - left + 1);
    std::vector<std::pair<int, int>> minimums;
    int min1_left = sparces[left][length].min1;
    minimums.push_back({min1_left, sparces[left][length].ind1});
    int min2_left = sparces[left][length].min2;
    minimums.push_back({min2_left, sparces[left][length].ind2});
    int min1_right = sparces[right - pow(2, length) + 1][length].min1;
    minimums.push_back(
        {min1_right, sparces[right - pow(2, length) + 1][length].ind1});
    int min2_right = sparces[right - pow(2, length) + 1][length].min2;
    minimums.push_back(
        {min2_right, sparces[right - pow(2, length) + 1][length].ind2});
    sort(minimums.begin(), minimums.end());
    if (minimums[0].second != minimums[1].second) {
      std::cout << minimums[1].first << "\n";
      continue;
    }
    std::cout << minimums[2].first << "\n";
  }
}
