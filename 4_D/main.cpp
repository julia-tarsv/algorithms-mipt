#include <iostream>
#include <stack>
#include <vector>

/*
insert x — добавить в дерево члена семьи с настроением x. Если такой уже есть, то ничего делать не надо.
delete x — удалить из дерева члена семьи с настроением x. Если его там нет, то ничего делать не надо.
exists x — если имеется член семьи с настроением x, выведите true, иначе, false.
next x — выведите настроение такого члена семьи, что оно лучше чем x, но минимально среди таких.
prev x — выведите настроение такого члена семьи, что оно хуже чем x, но максимально среди таких.
kth k — выведите k-ю величину настроения (нумерация с нуля).
*/


class Tree {
 private:
  struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;
    int size_tree;

    Node() : key(0), priority(0), left(nullptr), right(nullptr), size_tree(0) {}
    Node(int key, int priority)
        : key(key),
          priority(priority),
          left(nullptr),
          right(nullptr),
          size_tree(1) {}
  }* node_;

  Node* Merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->priority <= right->priority) {
      left->size_tree -= (left->right != nullptr ? left->right->size_tree : 0);
      left->right = Merge(left->right, right);
      left->size_tree += (left->right != nullptr ? left->right->size_tree : 0);
      return left;
    }
    right->size_tree -= (right->left != nullptr ? right->left->size_tree : 0);
    right->left = Merge(left, right->left);
    right->size_tree += (right->left != nullptr ? right->left->size_tree : 0);
    return right;
  }

  std::pair<Node*, Node*> Split(Node* main, int key) {
    if (main == nullptr) {
      return {0, 0};
    }
    if (main->key < key) {
      main->size_tree -= (main->right != nullptr ? main->right->size_tree : 0);
      std::pair<Node*, Node*> new_tree = Split(main->right, key);
      main->right = new_tree.first;
      main->size_tree += (main->right != nullptr ? main->right->size_tree : 0);
      return {main, new_tree.second};
    }
    main->size_tree -= (main->left != nullptr ? main->left->size_tree : 0);
    std::pair<Node*, Node*> new_tree = Split(main->left, key);
    main->left = new_tree.second;
    main->size_tree += (main->left != nullptr ? main->left->size_tree : 0);
    return {new_tree.first, main};
  }

  std::string ExistsHelp(Node* main, int key);
  int NextHelp(Node* main, int key);
  int PrevHelp(Node* main, int key);
  int KthHelp(Node* main, int key);

 public:
  Tree() : node_(nullptr) {}

  void DeleteMemory(Node*& vertex) {
    if (vertex == nullptr) {
      return;
    }
    DeleteMemory(vertex->right);
    DeleteMemory(vertex->left);
    delete vertex;
  }

  void Insert(int key, int priority);
  void Delete(int key);
  std::string Exists(int key) { return ExistsHelp(node_, key); }
  int Next(int key) { return NextHelp(node_, key); }
  int Prev(int key) { return PrevHelp(node_, key); }
  int Kth(int key) { return KthHelp(node_, key); }

  ~Tree() { DeleteMemory(node_); }
};

void Tree::Insert(int key, int priority) {
  Node* new_node = new Node(key, priority);
  std::pair<Node*, Node*> new_tree = Split(node_, key);
  node_ = Merge(new_tree.first, Merge(new_node, new_tree.second));
}

void Tree::Delete(int key) {
  std::pair<Node*, Node*> new_tree = Split(node_, key);
  std::pair<Node*, Node*> new_tree1 = Split(new_tree.second, key + 1);
  delete new_tree1.first;
  node_ = Merge(new_tree.first, new_tree1.second);
}

std::string Tree::ExistsHelp(Node* main, int key) {
  if (main == nullptr) {
    return "false";
  }
  if (main->key == key) {
    return "true";
  }
  if (main->key < key) {
    return ExistsHelp(main->right, key);
  }
  return ExistsHelp(main->left, key);
}

int Tree::NextHelp(Node* main, int key) {
  if (main == nullptr) {
    return -1;
  }

  if (key > main->key) {
    return NextHelp(main->right, key);
  }
  int ans = NextHelp(main->left, key);
  if (ans != -1) {
    return ans;
  }
  return main->key;
}

int Tree::PrevHelp(Node* main, int key) {
  if (main == nullptr) {
    return -1;
  }

  if (key < main->key) {
    return PrevHelp(main->left, key);
  }
  int ans = PrevHelp(main->right, key);
  if (ans != -1) {
    return ans;
  }
  return main->key;
}

int Tree::KthHelp(Node* main, int key) {
  if (main == nullptr || key + 1 > main->size_tree) {
    return -1;
  }
  if (key == 0 && main->size_tree == 1) {
    return main->key;
  }
  if (key + 1 == main->size_tree) {
    if (main->left == nullptr) {
      return KthHelp(main->right, key - 1);
    }
    return KthHelp(main->right, key - main->left->size_tree - 1);
  }

  return KthHelp(main->left, key);
}

int main() {
  Tree node;
  std::string str;
  int key;
  while (std::cin >> str >> key) {
    if (str == "insert") {
      node.Insert(key, rand());
    } else if (str == "delete") {
      node.Delete(key);
    } else if (str == "exists") {
      std::cout << node.Exists(key) << "\n";
    } else if (str == "next") {
      if (node.Next(key) == -1) {
        std::cout << "none"
                  << "\n";
      } else {
        std::cout << node.Next(key) << "\n";
      }
    } else if (str == "prev") {
      if (node.Prev(key) == -1) {
        std::cout << "none"
                  << "\n";
      } else {
        std::cout << node.Prev(key) << "\n";
      }
    } else {
      if (node.Kth(key) == -1) {
        std::cout << "none"
                  << "\n";
      } else {
        std::cout << node.Kth(key) << "\n";
      }
    }
  }
}