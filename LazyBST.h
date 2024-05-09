#ifndef LAZYBST_H
#define LAZYBST_H

#include <iostream>
#include <cmath> // For mathematical functions
using namespace std;

template <class T>
class LazyTreeNode {
public:
    T key;
    LazyTreeNode *left, *right;
    int leftDepth, rightDepth; // Depth of left and right subtrees

    LazyTreeNode(T k) : key(k), left(nullptr), right(nullptr), leftDepth(0), rightDepth(0) {}
    ~LazyTreeNode() {}
};

template <class T>
class LazyBST {
public:
    LazyBST() : root(nullptr) {}
    ~LazyBST() {
        clearTree(root); // Deallocate memory
    }

    // Public Interface

    // Inserts a value into the tree
    void insert(T value);

    // Checks if the tree contains a value
    bool contains(T value);

    // Deletes a node with given key
    bool deleteNode(T k);

    // Returns a pointer to the minimum value in the tree
    T* getMin();

    // Returns a pointer to the maximum value in the tree
    T* getMax();

    // Retrieves the value associated with the given key
    bool get(const T& value, T& output);

    // Checks if the tree is empty
    bool isEmpty() { return root == nullptr; }

    // Prints the tree
    void printTree();

    // Prints the tree to a specified ostream
    void printTree(ostream& out);

private:
    LazyTreeNode<T>* root;

    // Private Methods

    // Inserts a value into the tree and checks for imbalance
    LazyTreeNode<T>* insert(LazyTreeNode<T> *node, T value, bool &isImbalanced);

    // Deletes a node with the given key and checks for imbalance
    LazyTreeNode<T>* deleteNode(LazyTreeNode<T> *node, T k, bool &isImbalanced, bool &deleted);

    // Finds the successor of a node during deletion
    LazyTreeNode<T>* getSuccessor(LazyTreeNode<T> *d);

    // Updates the depths of the left and right subtrees
    void updateDepths(LazyTreeNode<T> *node);

    // Checks for imbalance and rebalances the tree if necessary
    void checkAndBalance();

    // Collects the size of the subtree rooted at the given node
    int collectSize(LazyTreeNode<T> *node);

    // Builds a balanced tree from an array of sorted values
    LazyTreeNode<T>* buildBalancedTree(T *sortedValues, int start, int end);

    // Collects values from the subtree rooted at the given node into an array
    int collectValues(LazyTreeNode<T> *node, T *values, int index);

    // Recursive function to print the tree
    void recPrint(LazyTreeNode<T> *node) const;

    // Recursive function to print the tree to a specified ostream
    void recPrint(LazyTreeNode<T> *node, ostream& out) const;

    // Clears the tree recursively, deallocating memory
    void clearTree(LazyTreeNode<T> *node);
};

template <class T>
void LazyBST<T>::insert(T value) {
    bool isImbalanced = false;
    root = insert(root, value, isImbalanced);
    if (isImbalanced) {
        checkAndBalance();
    }
}

template <class T>
void LazyBST<T>::printTree(ostream& out) {
    recPrint(root, out);
}

template <class T>
void LazyBST<T>::recPrint(LazyTreeNode<T> *node, ostream& out) const {
    if (node == nullptr) {
        return;
    }
    // preorder traversal
    out << node->key << endl;
    recPrint(node->left, out);
    recPrint(node->right, out);
}

template <class T>
bool LazyBST<T>::get(const T& value, T& output) {
    LazyTreeNode<T>* current = root;
    while (current != nullptr) {
        if (value == current->key) {
            output = current->key;
            return true;
        } else if (value < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

template <class T>
LazyTreeNode<T>* LazyBST<T>::insert(LazyTreeNode<T> *node, T value, bool &isImbalanced) {
    if (node == nullptr) {
        return new LazyTreeNode<T>(value);
    }

    if (value < node->key) {
        node->left = insert(node->left, value, isImbalanced);
    } else {
        node->right = insert(node->right, value, isImbalanced);
    }

    updateDepths(node);

    if (std::max(node->leftDepth, node->rightDepth) > 1.5 * std::min(node->leftDepth, node->rightDepth)) {
        isImbalanced = true;
    }

    return node;
}


template <class T>
bool LazyBST<T>::deleteNode(T k) {
    bool isImbalanced = false;
    bool deleted = false;
    root = deleteNode(root, k, isImbalanced, deleted);
    if (isImbalanced) {
        checkAndBalance();
    }
    return deleted;
}

template <class T>
LazyTreeNode<T>* LazyBST<T>::deleteNode(LazyTreeNode<T> *node, T k, bool &isImbalanced, bool &deleted) {
    if (node == nullptr) {
        return node;
    }

    if (k < node->key) {
        node->left = deleteNode(node->left, k, isImbalanced, deleted);
    } else if (k > node->key) {
        node->right = deleteNode(node->right, k, isImbalanced, deleted);
    } else {
        deleted = true;
        if (node->left == nullptr) {
            LazyTreeNode<T> *temp = node->right;
            delete node;
            node = temp;
        } else if (node->right == nullptr) {
            LazyTreeNode<T> *temp = node->left;
            delete node;
            node = temp;
        } else {
            LazyTreeNode<T> *successor = getSuccessor(node);
            node->key = successor->key;
            node->right = deleteNode(node->right, successor->key, isImbalanced, deleted);
        }
    }

    if (node != nullptr) {
        updateDepths(node);
        if (std::max(node->leftDepth, node->rightDepth) > 1.5 * std::min(node->leftDepth, node->rightDepth)) {
            isImbalanced = true;
        }
    }

    return node;
}

template <class T>
LazyTreeNode<T>* LazyBST<T>::getSuccessor(LazyTreeNode<T> *d) {
    LazyTreeNode<T> *successorParent = d;
    LazyTreeNode<T> *successor = d;
    LazyTreeNode<T> *current = d->right;

    while (current != nullptr) {
        successorParent = successor;
        successor = current;
        current = current->left;
    }

    if (successor != d->right) {
        successorParent->left = successor->right;
        successor->right = d->right;
    }

    return successor;
}

template <class T>
void LazyBST<T>::updateDepths(LazyTreeNode<T> *node) {
    if (node->left == nullptr) {
        node->leftDepth = 0;
    } else {
        node->leftDepth = std::max(static_cast<LazyTreeNode<T>*>(node->left)->leftDepth, static_cast<LazyTreeNode<T>*>(node->left)->rightDepth) + 1;
    }

    if (node->right == nullptr) {
        node->rightDepth = 0;
    } else {
        node->rightDepth = std::max(static_cast<LazyTreeNode<T>*>(node->right)->leftDepth, static_cast<LazyTreeNode<T>*>(node->right)->rightDepth) + 1;
    }
}

template <class T>
void LazyBST<T>::checkAndBalance() {
    int size = collectSize(root);
    T *values = new T[size];
    collectValues(root, values, 0);
    root = buildBalancedTree(values, 0, size - 1);
    delete[] values;
}

template <class T>
int LazyBST<T>::collectSize(LazyTreeNode<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    return collectSize(node->left) + 1 + collectSize(node->right);
}

template <class T>
int LazyBST<T>::collectValues(LazyTreeNode<T> *node, T *values, int index) {
    if (node == nullptr) {
        return index;
    }

    index = collectValues(node->left, values, index);
    values[index++] = node->key;
    index = collectValues(node->right, values, index);

    return index;
}

template <class T>
LazyTreeNode<T>* LazyBST<T>::buildBalancedTree(T *sortedValues, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = start + (end - start) / 2;
    LazyTreeNode<T> *node = new LazyTreeNode<T>(sortedValues[mid]);
    node->left = buildBalancedTree(sortedValues, start, mid - 1);
    node->right = buildBalancedTree(sortedValues, mid + 1, end);
    updateDepths(node);
    return node;
}

template <class T>
bool LazyBST<T>::contains(T value) {
    LazyTreeNode<T> *current = root;
    while (current != nullptr) {
        if (value == current->key) {
            return true;
        } else if (value < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

template <class T>
T* LazyBST<T>::getMin() {
    if (isEmpty()) {
        return nullptr;
    }

    LazyTreeNode<T> *current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return &(current->key);
}

template <class T>
T* LazyBST<T>::getMax() {
    if (isEmpty()) {
        return nullptr;
    }

    LazyTreeNode<T> *current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return &(current->key);
}

template <class T>
void LazyBST<T>::printTree() {
    recPrint(root);
}

template <class T>
void LazyBST<T>::recPrint(LazyTreeNode<T> *node) const {
    if (node == nullptr) {
        return;
    }
    // preorder traversal
    cout << node->key << endl;
    recPrint(node->left);
    recPrint(node->right);
}

template <class T>
void LazyBST<T>::clearTree(LazyTreeNode<T> *node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

#endif
