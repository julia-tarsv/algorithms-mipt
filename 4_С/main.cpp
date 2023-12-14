#include <iostream>
#include <stack>
#include <vector>

class Tree {
 private:
  struct Node {
    std::string key;
    int priority;
    Node* left;
    Node* right;
    std::string meaning;

    Node() : priority(0), left(nullptr), right(nullptr) {}
    Node(const std::string& key, int priority, const std::string& meaning)
        : key(key),
          priority(priority),
          left(nullptr),
          right(nullptr),
          meaning(meaning) {}
  }* node_;

  Node* Merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->priority <= right->priority) {
      left->right = Merge(left->right, right);
      return left;
    }
    right->left = Merge(left, right->left);
    return right;
  }

  std::pair<Node*, Node*> Split(Node* main, const std::string& key) {
    if (main == nullptr) {
      return {0, 0};
    }
    if (main->key < key) {
      std::pair<Node*, Node*> new_tree = Split(main->right, key);
      main->right = new_tree.first;
      return {main, new_tree.second};
    }
    std::pair<Node*, Node*> new_tree = Split(main->left, key);
    main->left = new_tree.second;
    return {new_tree.first, main};
  }

  std::string FindHelp(Node* main, const std::string& key);

 public:
  Tree() : node_(nullptr) {}

  void Delete(Node*& vert) {
    if (vert == nullptr) {
      return;
    }
    Delete(vert->right);
    Delete(vert->left);
    delete vert;
  }

  void Insert(const std::string& key, int priority, const std::string& meaning);
  std::string Find(const std::string& str) { return FindHelp(node_, str); }
  ~Tree() { Delete(node_); }
};

void Tree::Insert(const std::string& key, int priority,
                  const std::string& meaning) {
  Node* new_node = new Node(key, priority, meaning);
  std::pair<Node*, Node*> new_tree = Split(node_, key);
  node_ = Merge(new_tree.first, Merge(new_node, new_tree.second));
}

std::string Tree::FindHelp(Node* main, const std::string& key) {
  if (main == nullptr) {
    return "";
  }
  if (main->key == key) {
    return main->meaning;
  }
  if (main->key < key) {
    return FindHelp(main->right, key);
  }
  return FindHelp(main->left, key);
}

int main() {
  size_t num;
  std::cin >> num;
  Tree node1;
  Tree node2;
  for (size_t i = 0; i < num; ++i) {
    std::string elem1;
    std::string elem2;
    std::cin >> elem1 >> elem2;
    node1.Insert(elem1, rand(), elem2);
    node2.Insert(elem2, rand(), elem1);
  }

  size_t requests;
  std::cin >> requests;
  for (size_t i = 0; i < requests; ++i) {
    std::string str;
    std::cin >> str;
    std::string variant1 = node1.Find(str);
    std::string variant2 = node2.Find(str);
    if (variant1.empty()) {
      std::cout << variant2 << "\n";
    } else {
      std::cout << variant1 << "\n";
    }
  }
}