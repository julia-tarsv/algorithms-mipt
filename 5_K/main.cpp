#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  size_t number;
  size_t max_weight;
  std::cin >> number >> max_weight;

  std::vector<int> weights(number + 1);
  for (size_t i = 1; i <= number; ++i) {
    std::cin >> weights[i];
  }

  std::vector<int> costs(number + 1);
  for (size_t i = 1; i <= number; ++i) {
    std::cin >> costs[i];
  }
  std::vector<std::vector<int>> dp(number + 1,
                                   std::vector<int>(max_weight + 1));
  // dp[i][j] - max стоимость рюкзака вместимости j, если использовать первые i
  // предметов
  for (size_t i = 0; i <= number; ++i) {
    dp[i][0] = 0;
  }
  for (size_t j = 1; j <= max_weight; ++j) {
    dp[0][j] = 0;
  }

  std::vector<std::vector<std::pair<size_t, size_t>>> path(
      number + 1, std::vector<std::pair<size_t, size_t>>(max_weight + 1));
  for (size_t i = 1; i <= number; ++i) {
    for (size_t j = 1; j <= max_weight; ++j) {
      if (static_cast<int>(j) >= weights[i] &&
          dp[i - 1][j] < dp[i - 1][j - weights[i]] + costs[i]) {
        dp[i][j] = dp[i - 1][j - weights[i]] + costs[i];
        path[i][j] = {i - 1, j - weights[i]};
      } else {
        dp[i][j] = dp[i - 1][j];
        path[i][j] = {i - 1, j};
      }
    }
  }

  size_t index1 = number;
  size_t index2 = max_weight;
  std::vector<size_t> result;
  while (index1 != 0 && index2 != 0) {
    if (path[index1][index2].second != index2) {
      result.push_back(index1);
    }
    size_t index = index1;
    index1 = path[index1][index2].first;
    index2 = path[index][index2].second;
    if (index1 == 0 || index2 == 0) {
      break;
    }
  }

  std::reverse(result.begin(), result.end());
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i] << "\n";
  }
}
