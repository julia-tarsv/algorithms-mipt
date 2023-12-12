#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
  std::vector<int> sort_elem;
};

int Get(std::vector<Node>& tree, int vv, std::pair<size_t, size_t> tt,
        std::pair<size_t, size_t> lr, std::pair<int, int> bound) {
  if (tt.first > lr.second || lr.first > tt.second) {
    return 0;
  }

  if (lr.first <= tt.first && tt.second <= lr.second) {
    size_t ans1 = upper_bound(tree[vv].sort_elem.begin(),
                              tree[vv].sort_elem.end(), bound.second) -
                  tree[vv].sort_elem.begin();
    size_t ans2 = lower_bound(tree[vv].sort_elem.begin(),
                              tree[vv].sort_elem.end(), bound.first) -
                  tree[vv].sort_elem.begin();
    return ans1 - ans2;
  }

  size_t tm = (tt.first + tt.second) / 2;
  return Get(tree, 2 * vv, {tt.first, tm}, {lr.first, lr.second}, bound) +
         Get(tree, 2 * vv + 1, {tm + 1, tt.second}, {lr.first, lr.second},
             bound);
}

void Build(std::vector<Node>& tree, std::vector<int>& mas, int vv, size_t tl,
           size_t tr) {
  if (tl == tr) {
    tree[vv].sort_elem.push_back(mas[tl]);
    return;
  }

  size_t tm = (tl + tr) / 2;
  Build(tree, mas, 2 * vv, tl, tm);
  Build(tree, mas, 2 * vv + 1, tm + 1, tr);

  size_t ind1 = 0;
  size_t ind2 = 0;

  while (ind1 < tree[2 * vv].sort_elem.size() &&
         ind2 < tree[2 * vv + 1].sort_elem.size()) {
    if (tree[2 * vv].sort_elem[ind1] <= tree[2 * vv + 1].sort_elem[ind2]) {
      tree[vv].sort_elem.push_back(tree[2 * vv].sort_elem[ind1]);
      ++ind1;
    } else {
      tree[vv].sort_elem.push_back(tree[2 * vv + 1].sort_elem[ind2]);
      ++ind2;
    }
  }
  while (ind1 < tree[2 * vv].sort_elem.size()) {
    tree[vv].sort_elem.push_back(tree[2 * vv].sort_elem[ind1]);
    ++ind1;
  }
  while (ind2 < tree[2 * vv + 1].sort_elem.size()) {
    tree[vv].sort_elem.push_back(tree[2 * vv + 1].sort_elem[ind2]);
    ++ind2;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  size_t num;
  size_t req;
  std::cin >> num >> req;
  std::vector<Node> tree(4 * num);
  std::vector<int> mas(num);
  for (size_t i = 0; i < num; ++i) {
    std::cin >> mas[i];
  }
  Build(tree, mas, 1, 0, num - 1);
  for (size_t i = 0; i < req; ++i) {
    int lr1;
    int lr2;
    int bound1;
    int bound2;
    std::cin >> lr1 >> lr2 >> bound1 >> bound2;
    std::cout << Get(tree, 1, {0, num - 1}, {lr1 - 1, lr2 - 1},
                     {bound1, bound2})
              << "\n";
  }
}
