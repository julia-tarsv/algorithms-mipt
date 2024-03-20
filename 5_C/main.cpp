#include <iostream>
#include <vector>

void Accelerate() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Accelerate();
  size_t numbers;
  size_t planes;
  std::cin >> numbers >> planes;
  std::vector<size_t> column(planes + 2);
  for (size_t i = 0; i <= planes; ++i) {
    column[i] = 1;
  }
  if (numbers == 1) {
    std::cout << 0;
    return 0;
  }

  for (size_t j = 1; j <= numbers; ++j) {
    std::vector<size_t> save_column;
    save_column = column;
    for (size_t i = 1; i <= planes; ++i) {
      column[i] = save_column[i - 1] + save_column[i];
    }
    if (column[planes] >= numbers) {
      std::cout << j;
      return 0;
    }
  }
  std::cout << -1;
}
