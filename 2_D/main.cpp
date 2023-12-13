#include <iostream>
#include <stack>

class Hat {
 private:
  std::stack<int> first_;
  std::stack<int> first_min_;
  std::stack<int> second_;
  std::stack<int> second_min_;

 public:
  void Push(int value) {
    if (first_min_.empty()) {
      first_.push(value);
      first_min_.push(value);
    } else {
      int tmp = first_min_.top();
      first_.push(value);
      first_min_.push(std::min(tmp, value));
    }
    std::cout << "ok\n";
  }

  void SwapStacks() {
    while (!first_.empty()) {
      if (second_min_.empty()) {
        second_.push(first_.top());
        second_min_.push(first_.top());
      } else {
        int tmp = second_min_.top();
        second_.push(first_.top());
        second_min_.push(std::min(tmp, first_.top()));
      }
      first_.pop();
      first_min_.pop();
    }
  }

  void Min() {
    if (second_min_.empty()) {
      if (first_min_.empty()) {
        std::cout << "error\n";
      } else {
        std::cout << first_min_.top() << "\n";
      }
    } else {
      if (first_min_.empty()) {
        std::cout << second_min_.top() << "\n";
      } else {
        std::cout << std::min(first_min_.top(), second_min_.top()) << "\n";
      }
    }
  }

  void Clear() {
    while (!first_.empty()) {
      first_.pop();
      first_min_.pop();
    }
    while (!second_.empty()) {
      second_.pop();
      second_min_.pop();
    }
    std::cout << "ok\n";
  }

  void Dequeue() {
    if (second_.empty()) {
      if (first_.empty()) {
        std::cout << "error\n";
      } else {
        SwapStacks();
        int cur = second_.top();
        second_.pop();
        second_min_.pop();
        std::cout << cur << "\n";
      }
    } else {
      int cur = second_.top();
      second_.pop();
      second_min_.pop();
      std::cout << cur << "\n";
    }
  }

  void Front() {
    if (second_.empty()) {
      if (first_.empty()) {
        std::cout << "error\n";
      } else {
        SwapStacks();
        std::cout << second_.top() << "\n";
      }
    } else {
      std::cout << second_.top() << "\n";
    }
  }

  void Size() { std::cout << first_.size() + second_.size() << "\n"; }
};

int main() {
  int requests;
  std::cin >> requests;

  Hat hat;

  for (int i = 0; i < requests; ++i) {
    std::string str;
    std::cin >> str;

    if (str == "enqueue") {
      int cur;
      std::cin >> cur;
      hat.Push(cur);
    } else if (str == "dequeue") {
      hat.Dequeue();
    } else if (str == "min") {
      hat.Min();
    } else if (str == "size") {
      hat.Size();
    } else if (str == "front") {
      hat.Front();
    } else {
      hat.Clear();
    }
  }
}
