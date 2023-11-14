#include <deque>
#include <iostream>

int main() {
  int requests;
  std::cin >> requests;
  std::deque<int> left;
  std::deque<int> right;
  for (int i = 0; i < requests; ++i) {
    char operation;
    std::cin >> operation;
    if (operation == '-') {
      std::cout << left.front() << std::endl;
      left.pop_front();
      if (right.size() > left.size()) {
        left.push_back(right.front());
        right.pop_front();
      }
    } else if (operation == '+') {
      int goblin;
      std::cin >> goblin;
      right.push_back(goblin);
      if (right.size() > left.size()) {
        left.push_back(right.front());
        right.pop_front();
      }
    } else {
      int goblin;
      std::cin >> goblin;
      if (left.size() == right.size()) {
        left.push_back(goblin);
      } else {
        right.push_front(goblin);
      }
    }
  }
}