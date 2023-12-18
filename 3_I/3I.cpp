#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

/*
  вторая порядковая статистика на заданных диапазонах
*/

class SparseTable {
 private:
  struct Node {
    int min1;
    int min2;
    size_t index1;
    size_t index2;
  };

  std::vector<std::vector<Node>> sparsetable_;

 public:
  void Build(size_t num, std::vector<int> elements);
  int SecondStatistics(size_t left, size_t right);
};

void SparseTable::Build(size_t num, std::vector<int> elements) {
  sparsetable_.resize(num);
  for (size_t i = 0; i < num - 1; ++i) {
    sparsetable_[i].resize(static_cast<int>(log2(num) + 1));
    sparsetable_[i][1].min1 = std::min(elements[i], elements[i + 1]);
    sparsetable_[i][1].min2 = std::max(elements[i], elements[i + 1]);
    if (elements[i] < elements[i + 1]) {
      sparsetable_[i][1].index1 = i;
      sparsetable_[i][1].index2 = i + 1;
    } else {
      sparsetable_[i][1].index1 = i + 1;
      sparsetable_[i][1].index2 = i;
    }
  }
  sparsetable_[num - 1].resize(static_cast<int>(log2(num) + 1));
  for (int j = 2; j <= log2(num); ++j) {
    for (int i = 0; i < num - pow(2, j - 1); ++i) {
      std::vector<std::pair<int, int>> minimums;
      int min1_left = sparsetable_[i][j - 1].min1;
      minimums.push_back({min1_left, sparsetable_[i][j - 1].index1});

      int min2_left = sparsetable_[i][j - 1].min2;
      minimums.push_back({min2_left, sparsetable_[i][j - 1].index2});

      int min1_right = sparsetable_[i + pow(2, j - 1)][j - 1].min1;
      minimums.push_back(
          {min1_right, sparsetable_[i + pow(2, j - 1)][j - 1].index1});

      int min2_right = sparsetable_[i + pow(2, j - 1)][j - 1].min2;
      minimums.push_back(
          {min2_right, sparsetable_[i + pow(2, j - 1) - 1][j - 1].index2});

      sort(minimums.begin(), minimums.end());

      sparsetable_[i][j].min1 = minimums[0].first;
      sparsetable_[i][j].min2 = minimums[1].first;
      sparsetable_[i][j].index1 = minimums[0].second;
      sparsetable_[i][j].index2 = minimums[1].second;
    }
  }
}

int SparseTable::SecondStatistics(size_t left, size_t right) {
  int length = log2(right - left + 1);
  std::vector<std::pair<int, int>> minimums;
  int min1_left = sparsetable_[left][length].min1;
  minimums.push_back({min1_left, sparsetable_[left][length].index1});

  int min2_left = sparsetable_[left][length].min2;
  minimums.push_back({min2_left, sparsetable_[left][length].index2});

  int min1_right = sparsetable_[right - pow(2, length) + 1][length].min1;
  minimums.push_back(
      {min1_right, sparsetable_[right - pow(2, length) + 1][length].index1});

  int min2_right = sparsetable_[right - pow(2, length) + 1][length].min2;
  minimums.push_back(
      {min2_right, sparsetable_[right - pow(2, length) + 1][length].index2});

  sort(minimums.begin(), minimums.end());

  if (minimums[0].second != minimums[1].second) {
    return minimums[1].first;
  }
  return minimums[2].first;
}

int main() {
  size_t num;
  size_t requests;
  std::cin >> num >> requests;
  std::vector<int> elements(num);

  for (size_t i = 0; i < num; ++i) {
    std::cin >> elements[i];
  }

  SparseTable sparsetable;
  sparsetable.Build(num, elements);

  for (size_t i = 0; i < requests; ++i) {
    size_t left;
    size_t right;
    std::cin >> left >> right;
    --left;
    --right;

    std::cout << sparsetable.SecondStatistics(left, right) << "\n";
  }
}
