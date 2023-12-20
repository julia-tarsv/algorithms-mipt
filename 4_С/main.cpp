#include <iostream>
#include <stack>
#include <vector>

/*
Программа получает на вход количество участников в виде позывной гонщика —имя машины N.
Далее следует N строк, каждая строка содержит ровно два слова.
Затем идет число Q - количество запросов к модулю.
На каждой следующей из Q строк идет слово, к которому надо вывести, если на входе имя,
соответствующий позывной гонщика, иначе — имя машины, соответствующей гонщику.
*/

class Tree {
 private:
  struct Node {
    std::string key;
    int priority;
    Node* left;
    Node* right;
    std::string value;

    Node() : priority(0), left(nullptr), right(nullptr) {}
    Node(const std::string& key, int priority, const std::string& value)
        : key(key),
          priority(priority),
          left(nullptr),
          right(nullptr),
          value(value) {}
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

  void Insert(const std::string& key, int priority, const std::string& value);
  std::string Find(const std::string& key) { return FindHelp(node_, key); }
  ~Tree() { Delete(node_); }
};

void Tree::Insert(const std::string& key, int priority,
                  const std::string& value) {
  Node* new_node = new Node(key, priority, value);
  std::pair<Node*, Node*> new_tree = Split(node_, key);
  node_ = Merge(new_tree.first, Merge(new_node, new_tree.second));
}

std::string Tree::FindHelp(Node* main, const std::string& key) {
  if (main == nullptr) {
    return "";
  }
  if (main->key == key) {
    return main->value;
  }
  if (main->key < key) {
    return FindHelp(main->right, key);
  }
  return FindHelp(main->left, key);
}

int main() {
  size_t numbers;
  std::cin >> numbers;
  Tree node_name;
  Tree node_car;
  for (size_t i = 0; i < numbers; ++i) {
    std::string name;
    std::string car;
    std::cin >> name >> car;
    node_name.Insert(name, rand(), car);
    node_car.Insert(car, rand(), name);
  }

  size_t requests;
  std::cin >> requests;
  for (size_t i = 0; i < requests; ++i) {
    std::string key;
    std::cin >> key;
    std::string name = node_name.Find(key);
    std::string car = node_car.Find(key);
    if (name.empty()) {
      std::cout << car << "\n";
    } else {
      std::cout << name << "\n";
    }
  }
}
