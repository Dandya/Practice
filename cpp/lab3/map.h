#ifndef MAP_H

#define MAP_H
#include <iostream>
#include <vector>

template <typename T>
class comparator {
public:
    bool operator()(T &arg1, T &arg2) {
        return arg1 < arg2;
    }
};

template <typename t_key, typename t_value>
class Node {
public:
    t_key key;
    t_value value;
    int height;
    Node<t_key, t_value> *parent, *left, *right;

    Node(t_key key, t_value value, int height, Node<t_key, t_value> *parent = NULL, Node<t_key, t_value> *left = NULL, Node<t_key, t_value> *right = NULL) {
        this->key = key;
        this->value = value;
        this->height = height;

        this->parent = parent;
        this->left = left;
        this->right = right;
    }
};

template <typename T_key, typename T_value, template <typename T> class T_comparator = comparator>
class map {
private:
    Node<T_key, T_value> *root = NULL;
    int count_nodes = 0;

    void copyMap(Node<T_key, T_value> *&to, Node<T_key, T_value> *from) {
        if (from == NULL)
            return;

        to = new Node<T_key, T_value>(from->key, from->value, from->height);
        copyMap(to->left, from->left);
        copyMap(to->right, from->right);
        if (to->left != NULL)
            to->left->parent = to;
        if (to->right != NULL)
            to->right->parent = to;
    }

    void deleteMap(Node<T_key, T_value> *to) {
        if (to == NULL)
            return;

        deleteMap(to->left);
        deleteMap(to->right);

        delete to;
    }

    int getDifferenceHeightsOfNodes(Node<T_key, T_value> *left, Node<T_key, T_value> *right) {
        return getHeight(left) - getHeight(right);
    }

    int getHeight(Node<T_key, T_value> *root) {
        return (root != NULL) ? root->height : 0;
    }

    void changeHeight(Node<T_key, T_value> *root) {
        if (getHeight(root->left) <= getHeight(root->right)) {
            root->height = getHeight(root->right) + 1;
        } else {
            root->height = getHeight(root->left) + 1;
        }
    }

    Node<T_key, T_value> *simpleLeftTurn(Node<T_key, T_value> *root) {
        // std::cerr << "Was SLT" << std::endl;
        Node<T_key, T_value> *tmp;
        if (root->parent != NULL) {
            if (root == root->parent->left) {
                root->parent->left = root->right;
            } else {
                root->parent->right = root->right;
            }
        } else {
            this->root = root->right;
        }
        root->right->parent = root->parent;
        root->parent = root->right;

        tmp = root->right->left;
        root->right->left = root;
        root->right = tmp;
        if (tmp != NULL) {
            tmp->parent = root;
        }

        changeHeight(root);
        changeHeight(root->parent);
        return root->parent;
    }

    Node<T_key, T_value> *simpleRightTurn(Node<T_key, T_value> *root) {
        // std::cerr << "Was SRT" << std::endl;
        Node<T_key, T_value> *tmp;
        if (root->parent != NULL) {
            if (root == root->parent->left) {
                root->parent->left = root->left;
            } else {
                root->parent->right = root->left;
            }
        } else {
            this->root = root->left;
        }
        root->left->parent = root->parent;
        root->parent = root->left;

        tmp = root->left->right;
        root->left->right = root;
        root->left = tmp;
        if (tmp != NULL) {
            tmp->parent = root;
        }

        changeHeight(root);
        changeHeight(root->parent);
        return root->parent;
    }

    Node<T_key, T_value> *bigLeftTurn(Node<T_key, T_value> *root) {
        // std::cerr << "Was BLT" << std::endl;
        simpleRightTurn(root->right);
        return simpleLeftTurn(root);
    }

    Node<T_key, T_value> *bigRightTurn(Node<T_key, T_value> *root) {
        // std::cerr << "Was BRT" << std::endl;
        simpleLeftTurn(root->left);
        return simpleRightTurn(root);
    }

    void balanceNode(Node<T_key, T_value> *&root) {
        int tmp = getDifferenceHeightsOfNodes(root->left, root->right);
        switch (tmp) {
        case -2:
            if (getDifferenceHeightsOfNodes(root->right->left, root->right->right) <= 0) {
                root = simpleLeftTurn(root);
            } else {
                root = bigLeftTurn(root);
            }
            break;
        case 2:
            if (getDifferenceHeightsOfNodes(root->left->left, root->left->right) >= 0) {
                root = simpleRightTurn(root);
            } else {
                root = bigRightTurn(root);
            }
            break;
        default:
            break;
        }
    }

    void balanceMap(Node<T_key, T_value> *node) {
        while (node != NULL) {
            // std::cerr << node << "  with parent: " << node->parent << std::endl;
            changeHeight(node);
            balanceNode(node);
            node = node->parent;
        }
    }

    bool isBalanced(Node<T_key, T_value> *root) {
        if (root == NULL) {
            return true;
        }

        bool result = isBalanced(root->left);
        if (result == false) {
            return false;
        }

        result = isBalanced(root->right);
        if (result == false) {
            return false;
        }

        int tmp = getDifferenceHeightsOfNodes(root->left, root->right);
        if (tmp < -1 || tmp > 1) {
            std::cout << tmp << std::endl;
            return false;
        } else {
            return true;
        }
    }

    Node<T_key, T_value> *getNode(T_key key) {
        Node<T_key, T_value> *node = root;
        T_comparator<T_key> cmp;
        while (node != NULL && node->key != key) {
            if (cmp(key, node->key)) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return node;
    }

    Node<T_key, T_value> *getMinNode(Node<T_key, T_value> *node) {
        if (node != NULL && node->left != NULL) {
            return getMinNode(node->left);
        }
        return node;
    }

    Node<T_key, T_value> *getMaxNode(Node<T_key, T_value> *node) {
        if (node != NULL && node->right != NULL) {
            return getMinNode(node->right);
        }
        return node;
    }

    void deleteNode(Node<T_key, T_value> *node) {
        if (node->right != NULL) {
            Node<T_key, T_value> *min_node = getMinNode(node->right);
            node->key = min_node->key;
            node->value = min_node->value;
            if (min_node != node->right) {
                if (min_node->right != NULL) {
                    min_node->parent->left = min_node->right;
                    min_node->right->parent = min_node->parent;
                    balanceMap(min_node->right);
                } else {
                    min_node->parent->left = NULL;
                    balanceMap(min_node->parent);
                }
            } else {
                if (min_node->right != NULL) {
                    node->right = min_node->right;
                    min_node->right->parent = node;
                    balanceMap(min_node->right);
                } else {
                    node->right = NULL;
                    balanceMap(node);
                }
            }
            delete min_node;
        } else {
            if (node->parent != NULL) {
                if (node->parent->left == node) {
                    node->parent->left = node->left;
                } else {
                    node->parent->right = node->left;
                }
            } else {
                this->root = node->left;
            }

            if (node->left != NULL) {
                node->left->parent = node->parent;
                balanceMap(node->left);
            } else {
                balanceMap(node->parent);
            }
            delete node;
        }
    }

public:
    map() {
    }

    map(std::vector<T_key> keys, std::vector<T_value> values) {
        if (keys.size() != values.size())
            throw std::invalid_argument("map: sizes of vectors 'keys' and 'values' don't equal.");

        for (int i = 0; i < keys.size(); i++) {
            add(keys[i], values[i]);
        }
    }

    map(map &other) {
        copyMap(root, other.root);
        count_nodes = other.count_nodes;
    }

    ~map() {
        deleteMap(root);
        root = NULL;
        count_nodes = 0;
    }

    map &operator=(map &other) {
        deleteMap(root);
        root = NULL;
        count_nodes = other.count_nodes;
        copyMap(root, other.root);
        return *this;
    }

    bool empty() {
        return root == NULL;
    }

    int size() {
        int size = 0;
        for(auto it = this->begin(); it != this->end(); it++) {
            size++;
        }
        return size;
    }

    void deleteAll() {
        deleteMap(root);
        root = NULL;
    }

    void add(T_key key, T_value value) {
        Node<T_key, T_value> **child = &root, *parent = NULL;
        T_comparator<T_key> cmp;
        while (*child != NULL) {
            parent = *child;
            if (cmp(key, (*child)->key)) {
                child = &((*child)->left);
            } else {
                child = &((*child)->right);
            }
        }
        // std::cout << "Create new" << std::endl;
        *child = new Node<T_key, T_value>(key, value, 1, parent);
        balanceMap(*child);
        count_nodes++;
    }

    bool isBalanced() {
        if (root == NULL) {
            return true;
        }

        return isBalanced(root);
    }

    bool searchKey(T_key key) {
        return getNode(key) != NULL;
    }

    T_value &operator[](T_key key) {
        Node<T_key, T_value> *node = getNode(key);
        if (node == NULL) {
            throw std::invalid_argument("map: Element don't exist.");
        }
        return node->value;
    }

    T_value del(T_key key) {
        Node<T_key, T_value> *node = getNode(key);
        if (node == NULL) {
            throw std::invalid_argument("map: Element don't exist.");
        }
        T_value tmp = node->value;
        deleteNode(node);
        count_nodes--;
        return tmp;
    }

    class iterator {
    private:
        map<T_key, T_value, T_comparator> *iter_map;
        Node<T_key, T_value> *position;

        Node<T_key, T_value> *next(Node<T_key, T_value> *position) {
            if (position == NULL) {
                return NULL;
            }

            if (position->right == NULL) {
                if (position->parent == NULL) {
                    position = NULL;
                } else if (position->parent->left == position) {
                    position = position->parent;
                } else {
                    while (position != NULL && position->parent != NULL && position != position->parent->left) {
                        position = position->parent;
                    }
                    position = (position != NULL) ? position->parent : NULL;
                }
            } else {
                position = iter_map->getMinNode(position->right);
            }

            return position;
        }

        Node<T_key, T_value> *back(Node<T_key, T_value> *position) {
            if (position == NULL) {
                return iter_map->getMaxNode(iter_map->root);
            }

            if (position->left == NULL) {
                if (position->parent == NULL) {
                    return position;
                } else if (position->parent->right == position) {
                    position = position->parent;
                } else {
                    while (position != NULL && position->parent != NULL && position != position->parent->right) {
                        position = position->parent;
                    }
                    position = (position != NULL) ? position->parent : NULL;
                }
            } else {
                position = position->left;
            }
            return position;
        }

    public:
        iterator(Node<T_key, T_value> *pos_node, map<T_key, T_value, T_comparator> *obj) : position(pos_node), iter_map(obj) {}

        iterator(iterator &other) {
            this->iter_map = other.iter_map;
            this->position = other.position;
        }

        void operator=(iterator &other) {
            this->iter_map = other.iter_map;
            this->position = other.position;
        }

        iterator &operator+(unsigned int offset) {
            while (offset != 0 && position != NULL) {
                position = next(position);
                offset--;
            }
            return *this;
        }

        iterator &operator++(int) {
            position = next(position);
            return *this;
        }

        iterator &operator-(unsigned int offset) {
            while (offset != 0 && position != NULL) {
                position = back(position);
                offset--;
            }
            return *this;
        }

        iterator &operator--(int) {
            position = back(position);
            return *this;
        }

        T_value &operator*() {
            return position->value;
        }

        bool operator==(iterator &other) {
            return position == other.position && iter_map == other.iter_map;
        }

        bool operator!=(iterator &other) {
            return position != other.position || iter_map != other.iter_map;
        }

        Node<T_key, T_value> *getPosition() {
            return position;
        }
    };

    T_value del(iterator &it) {
        if (it == this->end()) {
            throw std::invalid_argument("map: Iterator don't support.");
        }
        T_value tmp = *it;
        it++;
        iterator it_copy = it;
        
        it--;
        deleteNode(it.getPosition());
        it = it_copy;
        count_nodes--;
        return tmp;
    }

    iterator begin() {
        return iterator(getMinNode(root), this);
    }

    iterator end() {
        return iterator(NULL, this);
    }
};

#endif