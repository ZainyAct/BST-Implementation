#include "binary-search-tree.h"
#include <iostream>

BinarySearchTree::Node::Node(DataType newval) : val(newval), left(nullptr), right(nullptr), avlBalance(0) {
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if (n == nullptr) {
        return -1;
    }

    int leftDepth = getNodeDepth(n->left);
    int rightDepth = getNodeDepth(n->right);

    return 1 + std::max(leftDepth, rightDepth);
}

BinarySearchTree::BinarySearchTree() : root_(nullptr), size_(0) {
}

BinarySearchTree::~BinarySearchTree() {
    while (size_) {
        remove(root_->val);
    }
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node* temp = root_;
    while (temp->right != nullptr) {
        temp = temp->right;
    }
    return temp->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node* temp = root_;
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    return temp->val;
}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print(Node* n) const {
    // In Order Printing
    if (n == nullptr)
        return;
    print(n->left);
    std::cout << (n->val) << ",";
    print(n->right);
}

bool BinarySearchTree::exists(DataType val) const {
    Node* temp = root_;
    while (temp != nullptr) {
        if (temp->val == val)
            return true;
        if (temp->val < val)
            temp = temp->right;
        else
            temp = temp->left;
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    Node** pT = getRootNodeAddress();
    Node* T = *pT;

    if (T == nullptr) {
        *pT = new Node(val);
    } else {
        Node* temp = T;
        while (true) {
            if (val <= temp->val) {
                if (temp->left == nullptr) {
                    temp->left = new Node(val);
                    break;
                } else {
                    temp = temp->left;
                }
            } else {
                if (temp->right == nullptr) {
                    temp->right = new Node(val);
                    break;
                } else {
                    temp = temp->right;
                }
            }
        }
    }

    size_++;
    return true;
}

bool BinarySearchTree::remove(DataType val) {
    Node** pT = getRootNodeAddress();
    Node* T = *pT;

    if (T == nullptr) {
        return false;
    }

    Node* current_node = T;
    Node* parent_node = nullptr;
    bool isLeftChild = false;
    bool found = false;
    while (current_node != nullptr) {
        if (current_node->val == val) {
            found = true;
            break;
        } else if (val < current_node->val) {
            parent_node = current_node;
            current_node = current_node->left;
            isLeftChild = true;
        } else {
            parent_node = current_node;
            current_node = current_node->right;
            isLeftChild = false;
        }
    }

    if (!found)
        return false;

    if (current_node->left == nullptr && current_node->right == nullptr) {
        if (current_node == T) {
            delete *pT;
            *pT = nullptr;
        } else {
            if (isLeftChild)
                parent_node->left = nullptr;
            else
                parent_node->right = nullptr;
            delete current_node;
        }
    } else if (current_node->left != nullptr && current_node->right == nullptr) {
        if (current_node == T) {
            *pT = current_node->left;
        } else {
            if (isLeftChild)
                parent_node->left = current_node->left;
            else
                parent_node->right = current_node->left;
        }
        delete current_node;
    } else if (current_node->left == nullptr && current_node->right != nullptr) {
        if (current_node == T) {
            *pT = current_node->right;
        } else {
            if (isLeftChild)
                parent_node->left = current_node->right;
            else
                parent_node->right = current_node->right;
        }
        delete current_node;
    } else {
        Node* successor = current_node->right;
        Node* successor_parent = current_node;
        isLeftChild = false;

        while (successor->left != nullptr) {
            successor_parent = successor;
            successor = successor->left;
            isLeftChild = true;
        }

        current_node->val = successor->val;

        if (isLeftChild)
            successor_parent->left = successor->right;
        else
            successor_parent->right = successor->right;

        delete successor;
    }

    size_--;
    return true;
}
