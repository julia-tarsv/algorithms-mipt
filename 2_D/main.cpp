#include <iostream>
#include <optional>
#include <stack>

class Hat {
 private:
  std::stack<int> first_main_;
  std::stack<int> first_min_;
  std::stack<int> second_main_;
  std::stack<int> second_min_;

 public:
  void Push(int value) {
    if (first_min_.empty()) {
      first_main_.push(value);
      first_min_.push(value);
    } else {
      int tmp = first_min_.top();
      first_main_.push(value);
      first_min_.push(std::min(tmp, value));
    }
  }

  void SwapStacks() {
    while (!first_main_.empty()) {
      if (second_min_.empty()) {
        second_min_.push(first_main_.top());
      } else {
        int tmp = second_min_.top();
        second_min_.push(std::min(tmp, first_main_.top()));
      }
      second_main_.push(first_main_.top());
      first_main_.pop();
      first_min_.pop();
    }
  }

  std::optional<int> Min() {
    if (second_min_.empty()) {
      if (first_min_.empty()) {
        return {};
      }
      return first_min_.top();
    }
    if (first_min_.empty()) {
      return second_min_.top();
    }
    return std::min(first_min_.top(), second_min_.top());
  }

  void Clear() {
    while (!first_main_.empty()) {
      first_main_.pop();
      first_min_.pop();
    }
    while (!second_main_.empty()) {
      second_main_.pop();
      second_min_.pop();
    }
  }

  std::optional<int> Dequeue() {
    if (second_main_.empty()) {
      if (first_main_.empty()) {
        return {};
      }
      SwapStacks();
      int cur = second_main_.top();
      second_main_.pop();
      second_min_.pop();
      return cur;
    }
    int cur = second_main_.top();
    second_main_.pop();
    second_min_.pop();
    return cur;
  }

  std::optional<int> Front() {
    if (second_main_.empty()) {
      if (first_main_.empty()) {
        return {};
      }
      SwapStacks();
      return second_main_.top();
    }
    return second_main_.top();
  }

  size_t Size() { return first_main_.size() + second_main_.size(); }
};

int main() {
  size_t requests;
  std::cin >> requests;

  Hat hat;

  for (size_t i = 0; i < requests; ++i) {
    std::string str;
    std::cin >> str;

    if (str == "enqueue") {
      int cur;
      std::cin >> cur;
      hat.Push(cur);
      std::cout << "ok\n";
    } else if (str == "dequeue") {
      std::optional<int> elem = hat.Dequeue();
      if (elem) {
        std::cout << elem.value() << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (str == "min") {
      std::optional<int> elem = hat.Min();
      if (elem) {
        std::cout << elem.value() << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (str == "size") {
      std::cout << hat.Size() << "\n";
    } else if (str == "front") {
      std::optional<int> elem = hat.Front();
      if (elem) {
        std::cout << elem.value() << "\n";
      } else {
        std::cout << "error\n";
      }
    } else {
      hat.Clear();
      std::cout << "ok\n";
    }
  }
}
