#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <cstddef>
#include <stdexcept>

using std::size_t;
using std::cout;
using std::endl;

template <typename Comparable>
class AVLNode{
    public:
        AVLNode() : _parent(nullptr), _left(nullptr), _right(nullptr), _data(), _depth(0), _heightL(-1), _heightR(-1) {};
    private:
        AVLNode<Comparable>* _parent;
        AVLNode<Comparable>* _left;
        AVLNode<Comparable>* _right;
        Comparable _data;
        size_t _depth;
        int _heightL;
        int _heightR;

    template <typename A>
    friend class AVLTree;
};

template <typename Comparable>
class AVLTree {
    public:
        AVLTree();
        AVLTree(const AVLTree<Comparable>& other);
        ~AVLTree() { LRS_delete(this->_root); this->_root = nullptr; };
        AVLTree& operator=(const AVLTree<Comparable>& other);
        bool contains(const Comparable& other) const;
        void insert(const Comparable& other);
        void remove(const Comparable& other);
        const Comparable& find_min() const;
        const Comparable& find_max() const;
        void print_tree(std::ostream& stream = std::cout) const;
    private:
        AVLNode<Comparable>* _root;
        void LRS_delete(AVLNode<Comparable>* node);
        void SLR_copy(AVLNode<Comparable>* node, AVLNode<Comparable>* other);
        bool search(AVLNode<Comparable>* node, const Comparable& other) const;
        AVLNode<Comparable>* find_min_helper(AVLNode<Comparable>* node) const;
        AVLNode<Comparable>* find_max_helper(AVLNode<Comparable>* node) const;
        AVLNode<Comparable>* remove_helper(AVLNode<Comparable>* node, const Comparable& other) const;
        AVLNode<Comparable>* insert_helper(AVLNode<Comparable>* node, const Comparable& other) const;
        void depth_update(AVLNode<Comparable>* node, size_t dep);
        void height_update_up(AVLNode<Comparable>* curr);
        void node_height_update(AVLNode<Comparable>* node);
        void print_tree_helper(std::ostream& stream, AVLNode<Comparable>* node) const;
        void left_rotation(AVLNode<Comparable>* parent);
        void right_rotation(AVLNode<Comparable>* parent);
        void left_right_rotation(AVLNode<Comparable>* grandparent);
        void right_left_rotation(AVLNode<Comparable>* grandparent);
        AVLNode<Comparable>* imbalance(AVLNode<Comparable>* node);
        bool height_imbalanced(AVLNode<Comparable>* node);
        void fix_imbalance(AVLNode<Comparable>* imbalanced_node);
};

template <typename Comparable>
void AVLTree<Comparable>::node_height_update(AVLNode<Comparable>* node) {
    if (node->_left)
        node->_heightL = std::max(node->_left->_heightL, node->_left->_heightR) + 1;
    else
        node->_heightL = -1;

    if (node->_right)
        node->_heightR = std::max(node->_right->_heightL, node->_right->_heightR) + 1;
    else
        node->_heightR = -1;
}

template <typename Comparable>
void AVLTree<Comparable>::LRS_delete(AVLNode<Comparable>* node) {
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
AVLTree<Comparable>::AVLTree() : _root(nullptr) {}

template <typename Comparable>
void AVLTree<Comparable>::SLR_copy(AVLNode<Comparable>* node, AVLNode<Comparable>* other) {
    // process
    if (node == nullptr) {
        node = new AVLNode<Comparable>;
        node->_data = other->_data;
        node->_depth = other->_depth;
        node->_heightL = other->_heightL;
        node->_heightR = other->_heightR;
        this->_root = node;
    }
    if (other->_left != nullptr) {
        node->_left = new AVLNode<Comparable>;
        node->_left->_data = other->_left->_data;
        node->_left->_depth = other->_left->_depth;
        node->_left->_parent = node;
        node->_left->_heightL = other->_left->_heightL;
        node->_left->_heightR = other->_left->_heightR;
    }

    if (other->_right != nullptr) {
        node->_right = new AVLNode<Comparable>;
        node->_right->_data = other->_right->_data;
        node->_right->_depth = other->_right->_depth;
        node->_right->_parent = node;
        node->_right->_heightL = other->_right->_heightL;
        node->_right->_heightR = other->_right->_heightR;
    }

    // left
    if (node->_left != nullptr)
        SLR_copy(node->_left, other->_left);
    // right
    if (node->_right != nullptr)
        SLR_copy(node->_right, other->_right);
}

template <typename Comparable>
AVLTree<Comparable>::AVLTree(const AVLTree<Comparable>& other) : _root(nullptr) {
    if (other._root == nullptr)
        return;

    // copy over SLR
    SLR_copy(this->_root, other._root);
}

template <typename Comparable>
AVLTree<Comparable>& AVLTree<Comparable>::operator=(const AVLTree<Comparable>& other) {
    // copy itself - while empty vs while not empty
    // copying other - while empty vs while not empty
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
bool AVLTree<Comparable>::search(AVLNode<Comparable>* node, const Comparable& other) const {
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
bool AVLTree<Comparable>::contains(const Comparable& other) const {
    if (this->_root == nullptr)
        return false;
    
    if (search(this->_root, other))
        return true;
    
    return false;    
}

template <typename Comparable>
AVLNode<Comparable>* AVLTree<Comparable>::insert_helper(AVLNode<Comparable>* node, const Comparable& other) const {
    AVLNode<Comparable>* ans = nullptr;
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
void AVLTree<Comparable>::height_update_up(AVLNode<Comparable>* curr) {
    if (curr->_parent != nullptr) {
        if (curr->_data > curr->_parent->_data)
            curr->_parent->_heightR = std::max(curr->_heightL, curr->_heightR) + 1;
        else
            curr->_parent->_heightL = std::max(curr->_heightL, curr->_heightR) + 1;
        height_update_up(curr->_parent);
    }
}

template <typename Comparable>
void AVLTree<Comparable>::left_rotation(AVLNode<Comparable>* parent) {
    AVLNode<Comparable>* child = parent->_right;

    if (parent == this->_root)
        this->_root = child;
    else if (parent->_parent->_data < parent->_data)
        parent->_parent->_right = child;
    else
        parent->_parent->_left = child;

    AVLNode<Comparable>* subtree = child->_left;
    parent->_right = subtree; // can either be nullptr (if no subtree) or an actual tree
    if (subtree)
        subtree->_parent = parent;
    child->_left = parent;
    if (child == this->_root)
        child->_parent = nullptr;
    else
        child->_parent = parent->_parent;

    parent->_parent = child;

    // update L & R heights of child & parent
    node_height_update(parent);
    height_update_up(parent);
}

template <typename Comparable>
void AVLTree<Comparable>::right_rotation(AVLNode<Comparable>* parent) {
    AVLNode<Comparable>* child = parent->_left;

    if (parent == this->_root)
        this->_root = child;

    else if (parent->_parent->_data > parent->_data)
        parent->_parent->_left = child;
    else
        parent->_parent->_right = child;

    AVLNode<Comparable>* subtree = child->_right;
    parent->_left = subtree;
    if (subtree)
        subtree->_parent = parent;
    child->_right = parent;

    if (child == this->_root)
        child->_parent = nullptr;
    else
        child->_parent = parent->_parent;
    parent->_parent = child;

    // update L & R heights of child & parent
    node_height_update(parent);
    height_update_up(parent);
}

template <typename Comparable>
void AVLTree<Comparable>::left_right_rotation(AVLNode<Comparable>* grandparent) {
    left_rotation(grandparent->_left);
    right_rotation(grandparent);
}

template <typename Comparable>
void AVLTree<Comparable>::right_left_rotation(AVLNode<Comparable>* grandparent) {
    right_rotation(grandparent->_right);
    left_rotation(grandparent);
}

template <typename Comparable>
bool AVLTree<Comparable>::height_imbalanced(AVLNode<Comparable>* node) {
    int heightL = node->_heightL;
    int heightR = node->_heightR;
    size_t diff;

    if (heightL >= heightR)
        diff = heightL - heightR;
    else
        diff = heightR - heightL;

    if (diff > 1)
        return true;
    return false;
}

template <typename Comparable>
AVLNode<Comparable>* AVLTree<Comparable>::imbalance(AVLNode<Comparable>* node) {
    // going up
    if (height_imbalanced(node))
        return node;

    if (!node->_parent)
        return nullptr;
    
    return imbalance(node->_parent);
}

template <typename Comparable>
void AVLTree<Comparable>::fix_imbalance(AVLNode<Comparable>* imbalanced_node) {
    // consider imbalanced node grandparent
    AVLNode<Comparable>* parent;
    if (imbalanced_node->_heightL > imbalanced_node->_heightR)
        parent = imbalanced_node->_left;
    else
        parent = imbalanced_node->_right;

    AVLNode<Comparable>* child;
    if (parent->_heightL == parent->_heightR) {
        if (imbalanced_node->_data < parent->_data)
            child = parent->_right;
        else
            child = parent->_left;
    }
    else if (parent->_heightL > parent->_heightR)
        child = parent->_left;
    else
        child = parent->_right;
    // find type of rotation & perform
    // left
    if (child->_data > imbalanced_node->_data && child->_data > parent->_data) {
        // cout << "left rotation" << endl;
        left_rotation(imbalanced_node);
    }
    // right
    else if (child->_data < imbalanced_node->_data && child->_data < parent->_data) {
        // cout << "right rotation" << endl;
        right_rotation(imbalanced_node);
    }
    // left-right
    else if (child->_data < imbalanced_node->_data && child->_data > parent->_data){
        // cout << "left-right rotation" << endl;
        left_right_rotation(imbalanced_node);
    }
    // right-left
    else {
        // cout << "right-left rotation" << endl;
        right_left_rotation(imbalanced_node);
    }
    
    if (imbalanced_node->_parent) {
        if (!imbalanced_node->_parent->_parent)
            depth_update(this->_root, 0); // O(n) because rotated root
        else {
            depth_update(imbalanced_node->_parent, imbalanced_node->_parent->_parent->_depth + 1);
        }
    }
}

template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable& other) {    
    if (this->_root == nullptr) {
        this->_root = new AVLNode<Comparable>;
        this->_root->_data = other;
        this->_root->_depth = 0;
        this->_root->_heightL = -1;
        this->_root->_heightR = -1;
        return;
    }

    AVLNode<Comparable>* tmp = insert_helper(this->_root, other);
    AVLNode<Comparable>* imbalanced_node;
    if (tmp == nullptr) // already in list
        return;

    else if (tmp->_data < other) {
        tmp->_right = new AVLNode<Comparable>;
        tmp->_right->_data = other;
        tmp->_right->_depth = tmp->_depth + 1;
        tmp->_right->_parent = tmp;
        height_update_up(tmp->_right);
        imbalanced_node = imbalance(tmp->_right); // TODO: technically save one or two interations?
    }
    else if (tmp->_data > other) {
        tmp->_left = new AVLNode<Comparable>;
        tmp->_left->_data = other;
        tmp->_left->_depth = tmp->_depth + 1;
        tmp->_left->_parent = tmp;
        height_update_up(tmp->_left);
        imbalanced_node = imbalance(tmp->_left);
    }
    
    if (imbalanced_node) {
        fix_imbalance(imbalanced_node);
    }
}

template <typename Comparable>
void AVLTree<Comparable>::depth_update(AVLNode<Comparable>* node, size_t dep) {
    node->_depth = dep;

    if (node->_left != nullptr)
        depth_update(node->_left, dep+1);
    if (node->_right != nullptr)
        depth_update(node->_right, dep+1);   
}

template <typename Comparable>
AVLNode<Comparable>* AVLTree<Comparable>::remove_helper(AVLNode<Comparable>* node, const Comparable& other) const {
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
void AVLTree<Comparable>::remove(const Comparable& other) {
    if (this->_root == nullptr) // empty tree case
        return;

    // find node to remove and its parent
    AVLNode<Comparable>* remove_parent = remove_helper(this->_root, other);
    AVLNode<Comparable>* remove;

    if (remove_parent == nullptr) // couldn't find node in tree
        return;

    // cases: removing a node with children vs no children
    if (remove_parent->_data == other) // removing root case
        remove = this->_root; 
    else if (remove_parent->_left != nullptr && remove_parent->_left->_data == other)
        remove = remove_parent->_left; // remove is on left
    
    if (remove_parent->_right != nullptr && remove_parent->_right->_data == other)  // remove is on right
        remove = remove_parent->_right;
    
    AVLNode<Comparable>* replacement;

    if (!remove->_left && !remove->_right) { // no replacement case
        if (this->_root == remove)
            this->_root = nullptr;
        else if (remove_parent->_left == remove)
            remove_parent->_left = nullptr;
        else if (remove_parent->_right == remove)
            remove_parent->_right = nullptr;

        delete remove;

        if (!this->_root)
            return;

        // update L & R heights of child & parent
        node_height_update(remove_parent);
        height_update_up(remove_parent);
        // recurse from remove_parent to root updating heights
        AVLNode<Comparable>* imbalanced_node = imbalance(remove_parent);
        // recurse from remove_parent to root checking for imbalances

        if (imbalanced_node)
            fix_imbalance(imbalanced_node);

        return;
    }

    else if (!remove->_right)
        replacement = find_max_helper(remove->_left);
    else
        replacement = find_min_helper(remove->_right);

    AVLNode<Comparable>* replacement_parent = remove_helper(this->_root, replacement->_data);

    // assuming found min of right
    if (replacement->_data > remove->_data && replacement_parent != remove)
        replacement_parent->_left = replacement->_right;

    // assuming found max of left
    else if (replacement->_data < remove->_data && replacement_parent != remove)
        replacement_parent->_right = replacement->_left;

    if (replacement_parent->_right)
        node_height_update(replacement_parent->_right);
    if (replacement_parent->_left)
        node_height_update(replacement_parent->_left);
    if (replacement_parent)
        node_height_update(replacement_parent);
    
    AVLNode<Comparable>* imbalanced_node = imbalance(replacement_parent);

    if (imbalanced_node)
        fix_imbalance(imbalanced_node);

    if (remove != this->_root) {
        if (remove_parent->_left) {
            if (remove_parent->_left->_data == other)
                remove_parent->_left = replacement;
            else 
                remove_parent->_right = replacement;
        }
        replacement->_parent = remove_parent;
    } else { replacement->_parent = nullptr; }

    if (remove->_left)
        if (remove->_left != replacement) {
            replacement->_left = remove->_left;
            replacement->_left->_parent = replacement;
        }
    if (remove->_right)
        if (remove->_right != replacement) {
            replacement->_right = remove->_right;
            replacement->_right->_parent = replacement;
        }
    replacement->_depth = remove->_depth;

    if (remove_parent->_right)
        node_height_update(remove_parent->_right);
    if (remove_parent->_left)
        node_height_update(remove_parent->_left);
    if (remove_parent)
        node_height_update(remove_parent);

    if (remove_parent != remove) {
        imbalanced_node = imbalance(replacement);

    if (imbalanced_node)
        fix_imbalance(imbalanced_node);
    }

    // TODO: make more efficient?
    depth_update(replacement, replacement->_depth);
    
    if (replacement_parent == remove && remove != this->_root)
        replacement_parent = replacement_parent->_parent;

    delete remove;

    if (remove == this->_root) {
        this->_root = replacement;
        if (this->_root) {
            node_height_update(this->_root);
            if (this->_root->_left)
                node_height_update(this->_root->_left);
            if (this->_root->_right)
                node_height_update(this->_root->_right);

            // recurse from remove_parent to root updating heights
            AVLNode<Comparable>* imbalanced_node = imbalance(this->_root);
            // recurse from remove_parent to root checking for imbalances

            if (imbalanced_node)
                fix_imbalance(imbalanced_node);
        }
        return;
    }
        
    // recurse from remove_parent to root updating heights
    node_height_update(replacement_parent);
    imbalanced_node = imbalance(replacement_parent);
    // recurse from remove_parent to root checking for imbalances

    if (imbalanced_node)
        fix_imbalance(imbalanced_node);

    node_height_update(replacement);

    // update L & R heights of child & parent
    node_height_update(remove_parent);
    height_update_up(remove_parent);
    // recurse from remove_parent to root updating heights
    imbalanced_node = imbalance(remove_parent);
    // recurse from remove_parent to root checking for imbalances

    if (imbalanced_node)
        fix_imbalance(imbalanced_node);
}

template <typename Comparable>
AVLNode<Comparable>* AVLTree<Comparable>::find_min_helper(AVLNode<Comparable>* node) const {
    if (node->_left == nullptr)
        return node;
    
    return find_min_helper(node->_left);
}

template <typename Comparable>
AVLNode<Comparable>* AVLTree<Comparable>::find_max_helper(AVLNode<Comparable>* node) const {
    if (node->_right == nullptr)
        return node;
    
    return find_max_helper(node->_right);
}

template <typename Comparable>
const Comparable& AVLTree<Comparable>::find_min() const {
    if (this->_root == nullptr)
        throw std::invalid_argument("No minimum in empty tree.");
    return find_min_helper(this->_root)->_data;
}

template <typename Comparable>
const Comparable& AVLTree<Comparable>::find_max() const {
    if (this->_root == nullptr)
        throw std::invalid_argument("No maximum in empty tree.");
    return find_max_helper(this->_root)->_data;
}

// int temp = 0;

template <typename Comparable>
void AVLTree<Comparable>::print_tree_helper(std::ostream& stream, AVLNode<Comparable>* node) const {
    // RSL
    if (node->_right != nullptr)
        print_tree_helper(stream, node->_right);
    
    // if (temp == 0) {
        size_t spaces = node->_depth * 2;
        for (size_t i = 0; i < spaces; i++)
            stream << " ";

        stream << node->_data << endl;
    // }

    // if (temp == 1) {
    //     stream << node->_data << ": L - " << node->_heightL << " : R - " << node->_heightR << endl;
    // }

    if (node->_left != nullptr)
        print_tree_helper(stream, node->_left);
    
}

template <typename Comparable>
void AVLTree<Comparable>::print_tree(std::ostream& stream) const {
    if (this->_root == nullptr) {
        stream << "<empty>\n";
    } else {
        print_tree_helper(stream, this->_root);
        // temp++;
        // print_tree_helper(stream, this->_root);
        // temp = 0;
    }
}

#endif