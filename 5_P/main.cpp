#include <iostream>
#include <vector>

bool AlternatingMask(size_t mask, size_t num) {
  for (size_t i = 1; i < num; ++i) {
    if (((mask >> i) & 1) == ((mask >> (i - 1)) & 1)) {
      return false;
    }
  }
  return true;
}

void Calculate(size_t numbers1, size_t numbers2,
               std::vector<std::vector<char>>& arr,
               std::vector<std::vector<int>>& can_mask) {
  for (size_t i = 0; i < numbers1; ++i) {
    for (size_t j = 0; j < numbers2; ++j) {
      for (size_t mask = 0; mask < (1 << numbers1); ++mask) {
        if ((arr[i][j] == '+' && ((mask >> i) & 1) == 0) ||
            (arr[i][j] == '-' && ((mask >> i) & 1) == 1)) {
          can_mask[j][mask] = 0;
        }
      }
    }
  }
}

int main() {
  size_t numbers1;
  size_t numbers2;
  std::cin >> numbers1 >> numbers2;
  const int kMod = 1e9 + 7;
  std::vector<std::vector<char>> arr(numbers1, std::vector<char>(numbers2));
  std::vector<std::vector<long long>> dp(numbers2,
                                         std::vector<long long>(1 << numbers1));
  // dp[i][mask] - число раскрасок первых i столбцов, если за ними следует mask
  std::vector<std::vector<int>> can_mask(numbers2,
                                         std::vector<int>(1 << numbers1, 1));
  for (size_t i = 0; i < numbers1; ++i) {
    for (size_t j = 0; j < numbers2; ++j) {
      std::cin >> arr[i][j];
    }
  }
  Calculate(numbers1, numbers2, arr, can_mask);
  for (size_t mask = 0; mask < (1 << numbers1); ++mask) {
    dp[0][mask] = can_mask[0][mask];
  }
  for (size_t j = 1; j < numbers2; ++j) {
    for (size_t mask = 0; mask < (1 << numbers1); ++mask) {
      if (can_mask[j][mask] == 1) {
        size_t back_mask = (1 << numbers1) - 1 - mask;
        if (AlternatingMask(mask, numbers1)) {
          dp[j][mask] = (dp[j - 1][mask] + dp[j - 1][back_mask]) % kMod;
          continue;
        }
        dp[j][mask] = dp[j - 1][back_mask];
      }
    }
  }
  size_t result = 0;
  for (size_t i = 0; i < (1 << numbers1); ++i) {
    result = (result + dp[numbers2 - 1][i]) % kMod;
  }
  std::cout << result;
}