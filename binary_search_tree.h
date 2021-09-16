#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <cstddef>
#include <stdexcept>

using std::size_t;
using std::cout;
using std::endl;

template <typename Comparable>
class Node{
    public:
        Node() : _parent(nullptr), _left(nullptr), _right(nullptr), _data(), _depth(0) {};
    private:
        Node<Comparable>* _parent;
        Node<Comparable>* _left;
        Node<Comparable>* _right;
        Comparable _data;
        size_t _depth;

    template <typename A>
    friend class BinarySearchTree;
};

template <typename Comparable>
class BinarySearchTree {
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree<Comparable>& other);
        ~BinarySearchTree() { LRS_delete(this->_root); };
        BinarySearchTree& operator=(const BinarySearchTree<Comparable>& other);
        bool contains(const Comparable& other) const;
        void insert(const Comparable& other);
        void remove(const Comparable& other);
        const Comparable& find_min() const;
        const Comparable& find_max() const;
        void print_tree(std::ostream& stream = std::cout) const;
    private:
        Node<Comparable>* _root;
        void LRS_delete(Node<Comparable>* node);
        void SLR_copy(Node<Comparable>* node, Node<Comparable>* other);
        bool search(Node<Comparable>* node, const Comparable& other) const;
        Node<Comparable>* find_min_helper(Node<Comparable>* node) const;
        Node<Comparable>* find_max_helper(Node<Comparable>* node) const;
        Node<Comparable>* remove_helper(Node<Comparable>* node, const Comparable& other) const;
        Node<Comparable>* insert_helper(Node<Comparable>* node, const Comparable& other) const;
        void depth_update(Node<Comparable>* node, size_t dep);
        void print_tree_helper(std::ostream& stream, Node<Comparable>* node) const;
};

template <typename Comparable>
void BinarySearchTree<Comparable>::LRS_delete(Node<Comparable>* node) {
    // check if current, left, right are nullptrs
    if (node == nullptr)
        return;
    // left
    if (node->_left != nullptr)
        LRS_delete(node->_left);
    // right
    if (node->_right != nullptr)
        LRS_delete(node->_right);
    // shout
    delete node;
}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() : _root(nullptr) {}

template <typename Comparable>
void BinarySearchTree<Comparable>::SLR_copy(Node<Comparable>* node, Node<Comparable>* other) {
    // process
    if (node == nullptr) {
        node = new Node<Comparable>;
        node->_data = other->_data;
        node->_depth = other->_depth;
        this->_root = node;
    }
    
    if (other->_left != nullptr) {
        node->_left = new Node<Comparable>;
        node->_left->_data = other->_left->_data;
        node->_left->_depth = other->_left->_depth;
        node->_left->_parent = node;
    }

    if (other->_right != nullptr) {
        node->_right = new Node<Comparable>;
        node->_right->_data = other->_right->_data;
        node->_right->_depth = other->_right->_depth;
        node->_right->_parent = node;
    }

    // left
    if (node->_left != nullptr)
        SLR_copy(node->_left, other->_left);
    // right
    if (node->_right != nullptr)
        SLR_copy(node->_right, other->_right);
}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree<Comparable>& other) : _root(nullptr) {
    if (other._root == nullptr)
        return;

    // copy over SLR
    SLR_copy(this->_root, other._root);
}

template <typename Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree<Comparable>& other) {
    if (this == &other)
        return *this;
    // check if current is empty unitialized or not empty initialized
    if (this->_root != nullptr) { // if not empty initialized, delete
        LRS_delete(this->_root);
        this->_root = nullptr;
    }

    if (other._root == nullptr)
        return *this;
    
    // copy over SLR
    SLR_copy(this->_root, other._root);
    return *this;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::search(Node<Comparable>* node, const Comparable& other) const {
    if (node->_data == other) // curr is answer
        return true;

    else if (node->_data > other) {
        if (node->_left == nullptr)
            return false;
        return search(node->_left, other);
    }
    
    else {
        if (node->_right == nullptr)
            return false;
        return search(node->_right, other);
    }
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& other) const {
    if (this->_root == nullptr)
        return false;
    
    if (search(this->_root, other))
        return true;
    
    return false;    
}

template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::insert_helper(Node<Comparable>* node, const Comparable& other) const {
    Node<Comparable>* ans = nullptr;
    if (node->_data > other) {
        if (node->_left == nullptr) {
            ans = node;
            return ans;
        }
        ans = insert_helper(node->_left, other);
    }

    else if (node->_data < other) {
        if (node->_right == nullptr) {
            ans = node;
            return ans;
        }
        ans = insert_helper(node->_right, other);
    }

    return ans; // curr node's data is == other
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& other) {    
    if (this->_root == nullptr) {
        this->_root = new Node<Comparable>;
        this->_root->_data = other;
        this->_root->_depth = 0;
        return;
    }

    Node<Comparable>* tmp = insert_helper(this->_root, other);
    if (tmp == nullptr) // already in list
        return;

    else if (tmp->_data < other) {
        tmp->_right = new Node<Comparable>;
        tmp->_right->_data = other;
        tmp->_right->_depth = tmp->_depth + 1;
        tmp->_right->_parent = tmp;
    }
    else if (tmp->_data > other) {
        tmp->_left = new Node<Comparable>;
        tmp->_left->_data = other;
        tmp->_left->_depth = tmp->_depth + 1;
        tmp->_left->_parent = tmp;
    }
}

template <typename Comparable>
void BinarySearchTree<Comparable>::depth_update(Node<Comparable>* node, size_t dep) {
    node->_depth = dep;

    if (node->_left != nullptr)
        depth_update(node->_left, dep+1);
    if (node->_right != nullptr)
        depth_update(node->_right, dep+1);   
}

template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::remove_helper(Node<Comparable>* node, const Comparable& other) const {
    // return parent of target node, or root
    if (node->_data == other) // root node case
        return node;

    if (node->_left != nullptr)
        if (node->_left->_data == other)
            return node;
    if (node->_right != nullptr)
        if (node->_right->_data == other)
            return node;
    
    if (node->_data > other) {
        if (node->_left == nullptr)
            return nullptr;
        return remove_helper(node->_left, other);
    }
    else {
        if (node->_right == nullptr)
            return nullptr;
        return remove_helper(node->_right, other);
    }
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& other) {
    if (this->_root == nullptr) // empty tree case
        return;

    // find node to remove and its parent
    Node<Comparable>* remove_parent = remove_helper(this->_root, other);
    Node<Comparable>* remove;

    if (remove_parent == nullptr) // couldn't find node in tree
        return;

    // cases: removing a node with children vs no children
    if (remove_parent->_data == other) // removing root case
        remove = this->_root; 
    else if (remove_parent->_left != nullptr && remove_parent->_left->_data == other)
        remove = remove_parent->_left; // remove is on left
    
    if (remove_parent->_right != nullptr && remove_parent->_right->_data == other)  // remove is on right
        remove = remove_parent->_right;
    
    Node<Comparable>* replacement;

    if (!remove->_left && !remove->_right) { // no replacement case
        if (this->_root == remove)
            this->_root = nullptr;
        else if (remove_parent->_left == remove)
            remove_parent->_left = nullptr;
        else if (remove_parent->_right == remove)
            remove_parent->_right = nullptr;

        delete remove;
        return;
    }

    else if (!remove->_right)
        replacement = find_max_helper(remove->_left);
    else
        replacement = find_min_helper(remove->_right);

    Node<Comparable>* replacement_parent = remove_helper(this->_root, replacement->_data);

    // assuming found min of right
    if (replacement->_data > remove->_data && replacement_parent != remove)
        replacement_parent->_left = replacement->_right;

    // assuming found max of left
    else if (replacement->_data < remove->_data && replacement_parent != remove)
        replacement_parent->_right = replacement->_left;

    if (remove != this->_root) {
        if (remove_parent->_left && remove_parent->_left->_data == other)
            remove_parent->_left = replacement;
        else if (remove_parent->_right && remove_parent->_right->_data == other)
            remove_parent->_right = replacement;
        replacement->_parent = remove_parent;
    } else { replacement->_parent = nullptr; }

    if (remove->_left != replacement)
        replacement->_left = remove->_left;
    if (remove->_right != replacement)
        replacement->_right = remove->_right;
    replacement->_depth = remove->_depth;

    depth_update(replacement, replacement->_depth);

    if (remove == this->_root)
        this->_root = replacement;

    delete remove;
}

template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::find_min_helper(Node<Comparable>* node) const {
    if (node->_left == nullptr)
        return node;
    
    return find_min_helper(node->_left);
}

template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::find_max_helper(Node<Comparable>* node) const {
    if (node->_right == nullptr)
        return node;
    
    return find_max_helper(node->_right);
}

template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::find_min() const {
    if (this->_root == nullptr)
        throw std::invalid_argument("No minimum in empty tree.");
    return find_min_helper(this->_root)->_data;
}

template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::find_max() const {
    if (this->_root == nullptr)
        throw std::invalid_argument("No maximum in empty tree.");
    return find_max_helper(this->_root)->_data;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::print_tree_helper(std::ostream& stream, Node<Comparable>* node) const {
    // RSL
    if (node->_right != nullptr)
        print_tree_helper(stream, node->_right);
    
    size_t spaces = node->_depth * 2;
    for (size_t i = 0; i < spaces; i++)
        stream << " ";

    stream << node->_data << endl;

    if (node->_left != nullptr)
        print_tree_helper(stream, node->_left);
    
}

template <typename Comparable>
void BinarySearchTree<Comparable>::print_tree(std::ostream& stream) const {
    if (this->_root == nullptr) {
        stream << "<empty>\n";
    } else {
        print_tree_helper(stream, this->_root);
    }
}



#endif