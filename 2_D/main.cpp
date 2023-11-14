#include <iostream>
#include <stack>

void Push(std::stack<int>& base, std::stack<int>& min, int value) {
  if (min.empty()) {
    base.push(value);
    min.push(value);
  } else {
    int tmp = min.top();
    base.push(value);
    min.push(std::min(tmp, value));
  }
}

void Pop(std::stack<int>& base, std::stack<int>& min) {
  base.pop();
  min.pop();
}

void SwapStacks(std::stack<int>& first, std::stack<int>& first_min,
                std::stack<int>& second, std::stack<int>& second_min) {
  while (!first.empty()) {
    Push(second, second_min, first.top());
    first.pop();
    first_min.pop();
  }
}

void Min(std::stack<int>& first_min, std::stack<int>& second_min) {
  if (second_min.empty()) {
    if (first_min.empty()) {
      std::cout << "error\n";
    } else {
      std::cout << first_min.top() << "\n";
    }
  } else {
    if (first_min.empty()) {
      std::cout << second_min.top() << "\n";
    } else {
      std::cout << std::min(first_min.top(), second_min.top()) << "\n";
    }
  }
}

void Clear(std::stack<int>& base, std::stack<int>& min) {
  while (!base.empty()) {
    Pop(base, min);
  }
}

void Dequeue(std::stack<int>& first, std::stack<int>& first_min,
             std::stack<int>& second, std::stack<int>& second_min) {
  if (second.empty()) {
    if (first.empty()) {
      std::cout << "error\n";
    } else {
      SwapStacks(first, first_min, second, second_min);
      int cur = second.top();
      Pop(second, second_min);
      std::cout << cur << "\n";
    }
  } else {
    int cur = second.top();
    Pop(second, second_min);
    std::cout << cur << "\n";
  }
}

void Front(std::stack<int>& first, std::stack<int>& first_min,
           std::stack<int>& second, std::stack<int>& second_min) {
  if (second.empty()) {
    if (first.empty()) {
      std::cout << "error\n";
    } else {
      SwapStacks(first, first_min, second, second_min);
      std::cout << second.top() << "\n";
    }
  } else {
    std::cout << second.top() << "\n";
  }
}

int main() {
  int requests;
  std::cin >> requests;

  std::stack<int> first;
  std::stack<int> first_min;
  std::stack<int> second;
  std::stack<int> second_min;

  for (int i = 0; i < requests; ++i) {
    std::string str;
    std::cin >> str;

    if (str == "enqueue") {
      int cur;
      std::cin >> cur;
      Push(first, first_min, cur);
      std::cout << "ok\n";
    } else if (str == "dequeue") {
      Dequeue(first, first_min, second, second_min);
    } else if (str == "min") {
      Min(first_min, second_min);
    } else if (str == "size") {
      std::cout << first.size() + second.size() << "\n";
    } else if (str == "front") {
      Front(first, first_min, second, second_min);
    } else {
      Clear(first, first_min);
      Clear(second, second_min);
      std::cout << "ok\n";
    }
  }
}