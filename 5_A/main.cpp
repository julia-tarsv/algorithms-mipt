#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  size_t numbers;
  std::cin >> numbers;
  std::vector<int> arr(numbers + 1);
  for (size_t i = 1; i <= numbers; ++i) {
    std::cin >> arr[numbers - i + 1];
  }
  const int kInf = 2147483647;
  std::vector<int> dp(numbers + 1, kInf);
  // dp[i] - число, на которое оканчивается невозрастающая посл-ть длины i
  dp[0] = -kInf;
  std::vector<int> path(numbers + 1);  // позиция предыдущего эл-та a[i]
  std::vector<int> prev_index(
      numbers + 1);  // индекс эл-та, на кот-ый заканчивается посл-ть длины i
  prev_index[0] = -1;
  size_t cnt = 0;
  for (size_t i = 1; i <= numbers; ++i) {
    size_t index = std::lower_bound(dp.begin(), dp.end(), arr[i]) - dp.begin();
    dp[index] = arr[i];
    path[i] = prev_index[index - 1];
    prev_index[index] = i;
    cnt = std::max(cnt, index);
  }
  std::cout << cnt << "\n";
  std::vector<size_t> result;
  int prev = prev_index[cnt];
  while (prev != -1) {
    result.push_back(prev);
    prev = path[prev];
  }
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << numbers - result[i] + 1 << ' ';
  }
}

