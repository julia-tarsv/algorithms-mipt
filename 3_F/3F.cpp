#include <algorithm>
#include <iostream>
#include <vector>

/*
  сколько среди чисел, стоящих на позициях с left по right,
  по величине лежат в интервале от boundery1 до boundery2
*/

class Tree {
 private:
  struct Node {
    std::vector<int> sort_elem;
  };
  std::vector<Node> tree_;

 public:
  int Get(size_t vertex, std::pair<size_t, size_t> tree_l_r,
          std::pair<size_t, size_t> left_right, std::pair<int, int> bounderies);
  void Build(std::vector<int>& mas, size_t vertex, size_t tree_left,
             size_t tree_right);
};

int Tree::Get(size_t vertex, std::pair<size_t, size_t> tree_l_r,
              std::pair<size_t, size_t> left_right,
              std::pair<int, int> bounderies) {
  if (tree_l_r.first > left_right.second ||
      left_right.first > tree_l_r.second) {
    return 0;
  }

  if (left_right.first <= tree_l_r.first &&
      tree_l_r.second <= left_right.second) {
    size_t ans1 =
        upper_bound(tree_[vertex].sort_elem.begin(),
                    tree_[vertex].sort_elem.end(), bounderies.second) -
        tree_[vertex].sort_elem.begin();
    size_t ans2 = lower_bound(tree_[vertex].sort_elem.begin(),
                              tree_[vertex].sort_elem.end(), bounderies.first) -
                  tree_[vertex].sort_elem.begin();
    return ans1 - ans2;
  }

  size_t tree_mid = (tree_l_r.first + tree_l_r.second) / 2;
  return Get(2 * vertex, {tree_l_r.first, tree_mid},
             {left_right.first, left_right.second}, bounderies) +
         Get(2 * vertex + 1, {tree_mid + 1, tree_l_r.second},
             {left_right.first, left_right.second}, bounderies);
}

void Tree::Build(std::vector<int>& mas, size_t vertex, size_t tree_left,
                 size_t tree_right) {
  tree_.resize(4 * mas.size());
  if (tree_left == tree_right) {
    tree_[vertex].sort_elem.push_back(mas[tree_left]);
    return;
  }

  size_t tree_mid = (tree_left + tree_right) / 2;
  Build(mas, 2 * vertex, tree_left, tree_mid);
  Build(mas, 2 * vertex + 1, tree_mid + 1, tree_right);

  size_t index1 = 0;
  size_t index2 = 0;

  while (index1 < tree_[2 * vertex].sort_elem.size() &&
         index2 < tree_[2 * vertex + 1].sort_elem.size()) {
    if (tree_[2 * vertex].sort_elem[index1] <=
        tree_[2 * vertex + 1].sort_elem[index2]) {
      tree_[vertex].sort_elem.push_back(tree_[2 * vertex].sort_elem[index1]);
      ++index1;
    } else {
      tree_[vertex].sort_elem.push_back(
          tree_[2 * vertex + 1].sort_elem[index2]);
      ++index2;
    }
  }
  while (index1 < tree_[2 * vertex].sort_elem.size()) {
    tree_[vertex].sort_elem.push_back(tree_[2 * vertex].sort_elem[index1]);
    ++index1;
  }
  while (index2 < tree_[2 * vertex + 1].sort_elem.size()) {
    tree_[vertex].sort_elem.push_back(tree_[2 * vertex + 1].sort_elem[index2]);
    ++index2;
  }
}

void Acceleration() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Acceleration();
  size_t num;
  size_t requests;
  std::cin >> num >> requests;
  Tree tree;
  std::vector<int> mas(num);
  for (size_t i = 0; i < num; ++i) {
    std::cin >> mas[i];
  }
  tree.Build(mas, 1, 0, num - 1);
  for (size_t i = 0; i < requests; ++i) {
    size_t left;
    size_t right;
    int boundery1;
    int boundery2;
    std::cin >> left >> right >> boundery1 >> boundery2;
    std::cout << tree.Get(1, {0, num - 1}, {left - 1, right - 1},
                          {boundery1, boundery2})
              << "\n";
  }
}
