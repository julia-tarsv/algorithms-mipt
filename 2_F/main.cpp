#include <iostream>
#include <string>
#include <vector>

class BinHeap {
public:
  void Insert(long long element, int ind);
  void ExtractMin();
  void DecreaseKey(int index, long long delta);
  long long GetMin();

  BinHeap() : tree_(1) {}

private:
  std::vector<std::pair<long long, int>> tree_;

  void SiftUp(int ind) {
    if (ind == 1) {
      return;
    }
    int pred = ind >> 1;
    if (tree_[ind].first < tree_[pred].first) {
      std::swap(tree_[ind], tree_[pred]);
      SiftUp(pred);
    }
  }

  void SiftDown(int ind) {
    if (ind << 1 >= int(tree_.size())) {
      return;
    }
    int uu = ind << 1;
    if (uu + 1 < int(tree_.size()) && tree_[uu + 1].first < tree_[uu].first) {
      ++uu;
    }
    if (tree_[uu].first < tree_[ind].first) {
      std::swap(tree_[uu], tree_[ind]);
      SiftDown(uu);
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

void BinHeap::Insert(long long element, int ind) {
  tree_.emplace_back(std::make_pair(element, ind));
  SiftUp(int(tree_.size()) - 1);
}

void BinHeap::DecreaseKey(int index, long long delta) {
  int ind1 = 0;
  for (int i = 1; i < int(tree_.size()); ++i) {
    if (tree_[i].second == index) {
      ind1 = i;
      break;
    }
  }
  tree_[ind1].first -= delta;
  SiftUp(ind1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int requests;
  std::cin >> requests;
  BinHeap heap;
  for (int i = 0; i < requests; ++i) {
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
      int ind;
      long long delta;
      std::cin >> ind >> delta;
      heap.DecreaseKey(ind, delta);
    }
  }
}