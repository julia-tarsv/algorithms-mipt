#include <iostream>
#include <string>
#include <vector>

/*
    insert x — вставить целое число x в кучу;
    getMin — вывести значение минимального элемента в куче;
    extractMin — удалить минимальный элемент из кучи, выводить его не нужно;
    decreaseKey i Δ — уменьшить число, вставленное на i-м запросе, на целое
    число Δ≥0
*/

class BinHeap {
 public:
  void Insert(long long element, int index);
  void ExtractMin();
  void DecreaseKey(int index, long long delta);
  long long GetMin();

  BinHeap() : tree_(1) {}

 private:
  std::vector<std::pair<long long, int>> tree_;

  void SiftUp(int index) {
    if (index == 1) {
      return;
    }
    int previous = index / 2;
    if (tree_[index].first < tree_[previous].first) {
      std::swap(tree_[index], tree_[previous]);
      SiftUp(previous);
    }
  }

  void SiftDown(int index) {
    if (index * 2 >= (int)tree_.size()) {
      return;
    }
    int vertex = index << 1;
    if (vertex + 1 < (int)tree_.size() &&
        tree_[vertex + 1].first < tree_[vertex].first) {
      ++vertex;
    }
    if (tree_[vertex].first < tree_[index].first) {
      std::swap(tree_[vertex], tree_[index]);
      SiftDown(vertex);
    }
  }
};

long long BinHeap::GetMin() {
  long long value = tree_[1].first;
  return value;
}

void BinHeap::ExtractMin() {
  std::swap(tree_[1], tree_.back());
  tree_.pop_back();
  SiftDown(1);
}

void BinHeap::Insert(long long element, int index) {
  tree_.push_back({element, index});
  SiftUp(tree_.size() - 1);
}

void BinHeap::DecreaseKey(int index, long long delta) {
  int index1 = 0;
  for (size_t i = 1; i < tree_.size(); ++i) {
    if (tree_[i].second == index) {
      index1 = i;
      break;
    }
  }
  tree_[index1].first -= delta;
  SiftUp(index1);
}

void Acceleration() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Acceleration();
  size_t requests;
  std::cin >> requests;

  BinHeap heap;

  for (size_t i = 0; i < requests; ++i) {
    std::string str;
    std::cin >> str;

    if (str == "insert") {
      long long elem;
      std::cin >> elem;
      heap.Insert(elem, i + 1);
    } else if (str == "getMin") {
      std::cout << heap.GetMin() << std::endl;
    } else if (str == "extractMin") {
      heap.ExtractMin();
    } else {
      int index;
      long long delta;
      std::cin >> index >> delta;
      heap.DecreaseKey(index, delta);
    }
  }
}
