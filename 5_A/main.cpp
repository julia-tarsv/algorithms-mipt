#include <iostream>
#include <vector>

/*минимизировать максимальное число экспериментов при запуске самолётов*/

void Calculate(size_t numbers, size_t planes, std::vector<size_t> column) {
  for (size_t j = 1; j <= numbers; ++j) {
    std::vector<size_t> save_column;
    save_column = column;
    for (size_t i = 1; i <= planes; ++i) {
      column[i] = save_column[i - 1] + save_column[i];
    }
    if (column[planes] >= numbers) {
      std::cout << j;
      return;
    }
  }
  std::cout << -1;
}

int main() {
  size_t numbers;
  size_t planes;
  std::cin >> numbers >> planes;
  std::vector<size_t> column(planes + 2);
  // column[i] - max высота дома при запуске i самолётиков
  for (size_t i = 0; i <= planes; ++i) {
    column[i] = 1;
  }
  if (numbers == 1) {
    std::cout << 0;
    return 0;
  }
  Calculate(numbers, planes, column);
}
