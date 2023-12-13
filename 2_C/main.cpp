#include <deque>
#include <iostream>

/*
    «+ i» — гоблин с номером i (1 ≤ i ≤ N) встает в конец очереди;
    «* i» — привилегированный гоблин с номером i встает в середину очереди;
    «-» — первый гоблин из очереди уходит к шаманам. Гарантируется,
    что на момент такого запроса очередь не пуста.
*/

class Goblins {
 private:
  std::deque<int> left_;
  std::deque<int> right_;

 public:
  Goblins() = default;

  int PopFront();
  void PushBack(int num_goblin);
  void PushMiddle(int num_goblin);

  ~Goblins() = default;
};

int Goblins::PopFront() {
  int front_elem = left_.front();
  left_.pop_front();
  if (right_.size() > left_.size()) {
    left_.push_back(right_.front());
    right_.pop_front();
  }
  return front_elem;
}

void Goblins::PushBack(int num_goblin) {
  right_.push_back(num_goblin);
  if (right_.size() > left_.size()) {
    left_.push_back(right_.front());
    right_.pop_front();
  }
}

void Goblins::PushMiddle(int num_goblin) {
  if (left_.size() == right_.size()) {
    left_.push_back(num_goblin);
  } else {
    right_.push_front(num_goblin);
  }
}

int main() {
  size_t requests;
  std::cin >> requests;
  Goblins goblin;
  for (size_t i = 0; i < requests; ++i) {
    char operation;
    std::cin >> operation;
    if (operation == '-') {
      std::cout << goblin.PopFront() << std::endl;
    } else if (operation == '+') {
      int num_goblin;
      std::cin >> num_goblin;
      goblin.PushBack(num_goblin);
    } else {
      int num_goblin;
      std::cin >> num_goblin;
      goblin.PushMiddle(num_goblin);
    }
  }
}
