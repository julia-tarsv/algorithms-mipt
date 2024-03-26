#include <algorithm>
#include <iostream>
#include <vector>

/*найти наибольшую невозрастающую подпоследовательность*/ 

size_t CalculateDp(std::vector<int>& dp, std::vector<int>& elements,
                   std::vector<int>& previous_index, std::vector<int>& path) {
  size_t max_index = 0;
  for (size_t i = 1; i < dp.size(); ++i) {
    size_t index =
        std::lower_bound(dp.begin(), dp.end(), elements[i]) - dp.begin();
    dp[index] = elements[i];
    path[i] = previous_index[index - 1];
    previous_index[index] = i;
    max_index = std::max(max_index, index);
  }
  return max_index;
}

void CalculatePath(std::vector<size_t>& result,
                   std::vector<int>& previous_index, size_t max_index,
                   std::vector<int>& path) {
  int prev = previous_index[max_index];
  while (prev != -1) {
    result.push_back(prev);
    prev = path[prev];
  }
}

int main() {
  size_t numbers;
  std::cin >> numbers;
  std::vector<int> elements(numbers + 1);
  for (size_t i = 1; i <= numbers; ++i) {
    std::cin >> elements[numbers - i + 1];
  }

  const int kInf = 2147483647;
  std::vector<int> dp(numbers + 1, kInf);
  // dp[i] - число, на которое оканчивается невозрастающая посл-ть длины i

  dp[0] = -kInf;
  std::vector<int> path(numbers + 1);  // позиция предыдущего эл-та a[i]
  std::vector<int> previous_index(
      numbers + 1);  // индекс эл-та, на кот-ый заканчивается посл-ть длины i
  previous_index[0] = -1;

  size_t max_index = CalculateDp(dp, elements, previous_index, path);
  std::cout << max_index << "\n";
  std::vector<size_t> result;
  CalculatePath(result, previous_index, max_index, path);

  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << numbers - result[i] + 1 << ' ';
  }
}
