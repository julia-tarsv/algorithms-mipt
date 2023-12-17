#include <iostream>

/*
    add(i)  — добавить в множество машин тачку с разгоном в i миллисекунд (если
    такая там уже есть, то Доминик отвлекся на семейные разговоры и подсунул вам
    второй раз ту же машину); next(i)  — узнать машину с минимальным временем
    разгона, не меньшим i. Если искомая машина отсутствует, необходимо вывести
    -1 и попросить Доминика быть внимательнее.
*/

class AVLTree {
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

  static Node* SmallRotateRight(Node* vert);
  static Node* SmallRotateLeft(Node* vert);
  static Node* BigRotateRight(Node* vert);
  static Node* BigRotateLeft(Node* vert);

  Node* InsertHelp(Node*& main, int key);

  int FindHelp(Node* main, int key);
  static void Height(Node*& vert);

public:
  AVLTree() : node_(nullptr) {}
  ~AVLTree() { Delete(node_); }

  void Delete(Node*& vert) {
    if (vert == nullptr) {
      return;
    }
    Delete(vert->right);
    Delete(vert->left);
    delete vert;
  }

  void Insert(int key) { node_ = InsertHelp(node_, key); }
  int Find(int key) { return FindHelp(node_, key); }
};

void AVLTree::Height(Node*& vert) {
  if (vert->left == nullptr && vert->right == nullptr) {
    vert->height = 1;
  } else if (vert->left == nullptr) {
    vert->height = vert->right->height + 1;
  } else if (vert->right == nullptr) {
    vert->height = vert->left->height + 1;
  } else {
    vert->height = std::max(vert->left->height, vert->right->height) + 1;
  }
}

AVLTree::Node* AVLTree::LeftBalance(Node* main) {
  int left_height;
  int right_height;

  if (main->left->left == nullptr) {
    left_height = 0;
  } else {
    left_height = main->left->left->height;
  }
  if (main->left->right == nullptr) {
    right_height = 0;
  } else {
    right_height = main->left->right->height;
  }
  if (right_height - left_height > 0) {
    return BigRotateRight(main);
  }

  return main;
}

AVLTree::Node* AVLTree::Balance(Node* main) {
  if (main == nullptr) {
    return main;
  }
  Height(main);
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
      if (main->right->left == nullptr) {
        left_height = 0;
      } else {
        left_height = main->right->left->height;
      }
      if (main->right->right == nullptr) {
        right_height = 0;
      } else {
        right_height = main->right->right->height;
      }
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

AVLTree::Node* AVLTree::SmallRotateLeft(Node* vert) {
  if (vert == nullptr) {
    return nullptr;
  }
  if (vert->right == nullptr) {
    return vert;
  }
  Node* right_son = vert->right;
  vert->right = right_son->left;
  Height(right_son);
  Node* old_vert = vert;
  vert = right_son;
  vert->left = old_vert;
  Height(vert);
  return vert;
}

AVLTree::Node* AVLTree::SmallRotateRight(Node* vert) {
  if (vert == nullptr) {
    return nullptr;
  }
  if (vert->left == nullptr) {
    return vert;
  }
  Node* left_son = vert->left;
  vert->left = left_son->right;
  Height(left_son);
  Node* old_vert = vert;
  vert = left_son;
  vert->right = old_vert;
  Height(vert);
  return vert;
}

AVLTree::Node* AVLTree::BigRotateLeft(Node* vert) {
  Node* right_son = vert->right;
  vert->right = SmallRotateRight(right_son);
  return SmallRotateLeft(vert);
}

AVLTree::Node* AVLTree::BigRotateRight(Node* vert) {
  Node* left_son = vert->left;
  vert->left = SmallRotateLeft(left_son);
  return SmallRotateRight(vert);
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
  int ans = FindHelp(main->left, key);
  if (ans != -1) {
    return ans;
  }
  return main->key;
}

int main() {
  size_t num;
  std::cin >> num;
  AVLTree main;
  char prev = '+';
  int prev_res = 0;
  const int kMod = 1e9;
  for (size_t i = 0; i < num; ++i) {
    char symbol;
    int key;
    std::cin >> symbol >> key;
    if (symbol == '+') {
      if (prev == '+') {
        if (main.Find(key) == key) {
          continue;
        }
        main.Insert(key);
      } else {
        prev = '+';
        if (main.Find(key + prev_res) == key) {
          continue;
        }
        main.Insert((key + prev_res) % (kMod));
      }
    } else {
      prev_res = main.Find(key);
      std::cout << prev_res << "\n";
      prev = '?';
    }
  }
}