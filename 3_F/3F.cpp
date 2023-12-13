#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
  std::vector<int> sort_elem;
};

int Get(std::vector<Node>& tree, int vertex, std::pair<size_t, size_t> tree_l_r,
        std::pair<size_t, size_t> left_right, std::pair<int, int> bounderies) {
  if (tree_l_r.first > left_right.second ||
      left_right.first > tree_l_r.second) {
    return 0;
  }

  if (left_right.first <= tree_l_r.first &&
      tree_l_r.second <= left_right.second) {
    size_t ans1 = upper_bound(tree[vertex].sort_elem.begin(),
                              tree[vertex].sort_elem.end(), bounderies.second) -
                  tree[vertex].sort_elem.begin();
    size_t ans2 = lower_bound(tree[vertex].sort_elem.begin(),
                              tree[vertex].sort_elem.end(), bounderies.first) -
                  tree[vertex].sort_elem.begin();
    return ans1 - ans2;
  }

  size_t tree_mid = (tree_l_r.first + tree_l_r.second) / 2;
  return Get(tree, 2 * vertex, {tree_l_r.first, tree_mid},
             {left_right.first, left_right.second}, bounderies) +
         Get(tree, 2 * vertex + 1, {tree_mid + 1, tree_l_r.second},
             {left_right.first, left_right.second}, bounderies);
}

void Build(std::vector<Node>& tree, std::vector<int>& mas, int vertex,
           size_t tree_left, size_t tree_right) {
  if (tree_left == tree_right) {
    tree[vertex].sort_elem.push_back(mas[tree_left]);
    return;
  }

  size_t tree_mid = (tree_left + tree_right) / 2;
  Build(tree, mas, 2 * vertex, tree_left, tree_mid);
  Build(tree, mas, 2 * vertex + 1, tree_mid + 1, tree_right);

  size_t index1 = 0;
  size_t index2 = 0;

  while (index1 < tree[2 * vertex].sort_elem.size() &&
         index2 < tree[2 * vertex + 1].sort_elem.size()) {
    if (tree[2 * vertex].sort_elem[index1] <=
        tree[2 * vertex + 1].sort_elem[index2]) {
      tree[vertex].sort_elem.push_back(tree[2 * vertex].sort_elem[index1]);
      ++index1;
    } else {
      tree[vertex].sort_elem.push_back(tree[2 * vertex + 1].sort_elem[index2]);
      ++index2;
    }
  }
  while (index1 < tree[2 * vertex].sort_elem.size()) {
    tree[vertex].sort_elem.push_back(tree[2 * vertex].sort_elem[index1]);
    ++index1;
  }
  while (index2 < tree[2 * vertex + 1].sort_elem.size()) {
    tree[vertex].sort_elem.push_back(tree[2 * vertex + 1].sort_elem[index2]);
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
  std::vector<Node> tree(4 * num);
  std::vector<int> mas(num);
  for (size_t i = 0; i < num; ++i) {
    std::cin >> mas[i];
  }
  Build(tree, mas, 1, 0, num - 1);
  for (size_t i = 0; i < requests; ++i) {
    int lr1;
    int lr2;
    int boundery1;
    int boundery2;
    std::cin >> lr1 >> lr2 >> boundery1 >> boundery2;
    std::cout << Get(tree, 1, {0, num - 1}, {lr1 - 1, lr2 - 1},
                     {boundery1, boundery2})
              << "\n";
  }
}
