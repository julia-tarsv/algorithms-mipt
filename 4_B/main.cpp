#include <iostream>

/*
    add(i)  — добавить в множество машин тачку с разгоном в i миллисекунд.
    next(i)  — узнать машину с минимальным временем
    разгона, не меньшим i. Если искомая машина отсутствует, необходимо вывести
    -1 и попросить Доминика быть внимательнее.
*/

class AVLTree {
 public:
  AVLTree() : node_(nullptr) {}

  void Insert(int key) { node_ = InsertHelp(node_, key); }
  int Find(int key) { return FindHelp(node_, key); }

 private:
  struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int key) : key(key), left(nullptr), right(nullptr), height(1) {}

  }* node_;

  static Node* LeftBalance(Node* main);
  static Node* Balance(Node* main);

  static Node* SmallRotateRight(Node* vertex);
  static Node* SmallRotateLeft(Node* vertex);
  static Node* BigRotateRight(Node* vertex);
  static Node* BigRotateLeft(Node* vertex);

  Node* InsertHelp(Node*& main, int key);

  int FindHelp(Node* main, int key);
  static void IsHeight(Node*& vertex);

 public:
  void Delete(Node*& vertex) {
    if (vertex == nullptr) {
      return;
    }
    Delete(vertex->right);
    Delete(vertex->left);
    delete vertex;
  }

  ~AVLTree() { Delete(node_); }
};

void AVLTree::IsHeight(Node*& vertex) {
  size_t left_height;
  size_t right_height;
  left_height = (vertex->left == nullptr ? 0 : vertex->left->height);
  right_height = (vertex->right == nullptr ? 0 : vertex->right->height);
  vertex->height = std::max(left_height, right_height) + 1;
}

AVLTree::Node* AVLTree::LeftBalance(Node* main) {
  int left_height;
  int right_height;

  left_height = (main->left->left == nullptr ? 0 : main->left->left->height);
  right_height = (main->left->right == nullptr ? 0 : main->left->right->height);

  if (right_height - left_height > 0) {
    return BigRotateRight(main);
  }

  return main;
}

AVLTree::Node* AVLTree::Balance(Node* main) {
  if (main == nullptr) {
    return main;
  }
  IsHeight(main);
  int left_height = (main->left != nullptr ? main->left->height : 0);
  int right_height = (main->right != nullptr ? main->right->height : 0);

  if (left_height - right_height > 1) {
    if (main->left != nullptr) {
      return LeftBalance(main);
    }
    return SmallRotateRight(main);
  }

  if (right_height - left_height > 1) {
    if (main->right != nullptr) {
      left_height =
          (main->right->left == nullptr ? 0 : main->right->left->height);
      right_height =
          (main->right->right == nullptr ? 0 : main->right->right->height);
      if (left_height - right_height > 0) {
        return BigRotateLeft(main);
      }
    }
    return SmallRotateLeft(main);
  }

  return main;
}

AVLTree::Node* AVLTree::InsertHelp(Node*& main, int key) {
  if (main == nullptr) {
    return new Node(key);
  }
  if (key < main->key) {
    main->left = InsertHelp(main->left, key);
  } else {
    main->right = InsertHelp(main->right, key);
  }
  return Balance(main);
}

AVLTree::Node* AVLTree::SmallRotateLeft(Node* vertex) {
  if (vertex == nullptr) {
    return nullptr;
  }
  if (vertex->right == nullptr) {
    return vertex;
  }
  Node* right_son = vertex->right;
  vertex->right = right_son->left;
  IsHeight(right_son);
  Node* old_vertex = vertex;
  vertex = right_son;
  vertex->left = old_vertex;
  IsHeight(vertex);
  return vertex;
}

AVLTree::Node* AVLTree::SmallRotateRight(Node* vertex) {
  if (vertex == nullptr) {
    return nullptr;
  }
  if (vertex->left == nullptr) {
    return vertex;
  }
  Node* left_son = vertex->left;
  vertex->left = left_son->right;
  IsHeight(left_son);
  Node* old_vertex = vertex;
  vertex = left_son;
  vertex->right = old_vertex;
  IsHeight(vertex);
  return vertex;
}

AVLTree::Node* AVLTree::BigRotateLeft(Node* vertex) {
  Node* right_son = vertex->right;
  vertex->right = SmallRotateRight(right_son);
  return SmallRotateLeft(vertex);
}

AVLTree::Node* AVLTree::BigRotateRight(Node* vertex) {
  Node* left_son = vertex->left;
  vertex->left = SmallRotateLeft(left_son);
  return SmallRotateRight(vertex);
}

int AVLTree::FindHelp(Node* main, int key) {
  if (main == nullptr) {
    return -1;
  }
  if (key == main->key) {
    return key;
  }
  if (key > main->key) {
    return FindHelp(main->right, key);
  }
  int result = FindHelp(main->left, key);
  if (result != -1) {
    return result;
  }
  return main->key;
}

void Acceleration() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Acceleration();
  size_t numbers;
  std::cin >> numbers;
  AVLTree main;
  char previous = '+';
  int previous_result = 0;
  const int kMod = 1e9;

  for (size_t i = 0; i < numbers; ++i) {
    char symbol;
    int key;
    std::cin >> symbol >> key;
    if (symbol == '+') {
      if (previous == '?') {
        key = (key + previous_result) % kMod;
      }
      if (main.Find(key) != key) {
        main.Insert(key);
      }
      previous = '+';
    } else {
      previous_result = main.Find(key);
      std::cout << previous_result << "\n";
      previous = '?';
    }
  }
}
