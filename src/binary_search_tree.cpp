#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    if (root_ == nullptr) {
      Node* node = new Node(key, value);
      root_ = node;
      return;
    } else {
      insert(key, value, root_);
    }
  }

  bool BinarySearchTree::Remove(int key) {
    if (root_ == nullptr) return false;
    if (root_->key == key & root_->left == nullptr & root_->right == nullptr) {
      delete root_;
      root_ = nullptr;
      return true;
    }
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    if (root_ == nullptr) return std::nullopt;
    Node* node = find(key, root_);
    if (node != nullptr) {
      return node->value;
    } else {
      return std::nullopt;
    }
  }

  bool BinarySearchTree::Contains(int key) const {
    if (Find(key) != std::nullopt) {
      return true;
    }
    return false;
  }

  bool BinarySearchTree::IsEmpty() const {
    if (root_ == nullptr) return true;
    return false;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if (root_ == nullptr) return std::nullopt;
    Node* node = find_min(root_);
    return node->value;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if (root_ == nullptr) return std::nullopt;
    Node* node = find_max(root_);
    return node->value;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (key == node->key) {
      node->value = value;
      return;
    }
    if (key < node->key) {
      if (node->left == nullptr) {
        node->left = new Node(key, value);
        return;
      }
      insert(key, value, node->left);
      return;
    }
    if (node->right == nullptr) {
      node->right = new Node(key, value);
      return;
    }
    insert(key, value, node->right);
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (key == node->key) {
      Node* nodeParent = root_;
      Node* pointer = nodeParent;
      while (pointer->key != key) {
        nodeParent = pointer;
        pointer = (pointer->key > key) ? pointer->left : pointer->right;
      }
      if (node->left == nullptr & node->right == nullptr) {
        if (nodeParent->key > key) nodeParent->left = nullptr;
        else if (nodeParent->key < key) nodeParent->right = nullptr;
        delete node;
        node = nullptr;
        return true;
      }
      if (node->left != nullptr & node->right == nullptr) {
        Node* nodeReplace = node->left;
        delete node;
        node = nodeReplace;
        return true;
      }
      if (node->left == nullptr & node->right != nullptr) {
        Node* nodeReplace = node->right;
        delete node;
        node = nodeReplace;
        return true;
      }
      if (node->left != nullptr & node->right != nullptr) {
        Node* nodeReplace = find_min(node->right);
        int newKey = nodeReplace->key;
        int newValue = nodeReplace->value;
        remove(nodeReplace->key, root_);
        node->key = newKey;
        node->value = newValue;
        return true;
      }
    }
    if (key > node->key & node->right != nullptr) return remove(key, node->right);
    if (key < node->key & node->left != nullptr) return remove(key, node->left);
    return false;
  }

  void BinarySearchTree::clear(Node* node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node != nullptr) {
      if (node->key == key) return node;
      if (key < node->key) return find(key, node->left);
      return find(key, node->right);
    }
    return nullptr;
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if (node->left == nullptr) return node;
    return find_min(node->left);
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if (node->right == nullptr) return node;
    return find_max(node->right);
  }

}  // namespace assignment