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

template <typename T_key, typename T_value, template <typename T> class T_comparator = comparator>
class map {
private:
    template <typename t_key, typename t_value>
    class node {
    public:
        t_key key;
        t_value value;
        int height;
        node *parent, *left, *right;

        node(t_key key, t_value value, int height, node<t_key, t_value> *parent = NULL, node<t_key, t_value> *left = NULL, node<t_key, t_value> *right = NULL) {
            this->key = key;
            this->value = value;
            this->height = height;
            this->parent = parent;
            this->left = left;
            this->right = right; 
        }
    };

    node<T_key, T_value> *root = NULL;

    void copyMap(node<T_key, T_value> *&to, node<T_key, T_value> *from) {
        if (from == NULL)
            return;

        to = new node<T_key, T_value>(from->key, from->value, from->height);
        copyMap(to->left, from->left);
        copyMap(to->right, from->right);
        if (to->left != NULL)
            to->left->parent = to;
        if (to->right != NULL)
            to->right->parent = to;
    }
    
    void deleteMap(node<T_key, T_value> *to) {
        if (to == NULL)
            return;
   
        deleteMap(to->left);
        deleteMap(to->right);

        delete to;
    }

    int getDifferenceOfNodes(node<T_key, T_value>* left, node<T_key, T_value>* right) {
        return getHeight(left) - getHeight(right);
    }

    int getHeight(node<T_key, T_value> *root) {
        return (root != NULL) ? root->height : 0;
    }

    void changeHeight(node<T_key, T_value> *root) {
        if(getHeight(root->left) <= getHeight(root->right)) {
            root->height = getHeight(root->right) + 1;
        } else {
            root->height = getHeight(root->left) + 1;
        }
    }

    void simpleLeftTurn(node<T_key, T_value> *root) {
        //std::cout << "SLT\n";
        node<T_key, T_value> *tmp;
        if (root->parent != NULL) {
            if(root == root->parent->left) {
                root->parent->left = root->right;
            } else {
                root->parent->right = root->right;
            }
        }
        root->right->parent = root->parent;
        root->parent = root->right;
        //std::cout << "STL:mid\n";
        tmp = root->right->left;
        root->right->left = root;
        root->right = tmp;
        if (tmp != NULL) {
            tmp->parent = root;
        }

        //std::cout << "STL:end\n";
        changeHeight(root);
        changeHeight(root->parent);   
    }

    void simpleRightTurn(node<T_key, T_value> *root) {
        //std::cout << "SRT\n";
        node<T_key, T_value> *tmp;
        if(root->parent != NULL) {
            if(root == root->parent->left) {
                root->parent->left = root->left;
            } else {
                root->parent->right = root->left;
            }
        }
        root->left->parent = root->parent;
        root->parent = root->left;
        
        tmp = root->left->right;
        root->left->right = root;
        root->left = tmp;
        if(tmp != NULL) {
            tmp->parent = root;
        }

        changeHeight(root);
        changeHeight(root->parent);
    }

    void bigLeftTurn(node<T_key, T_value> *root) {
        //std::cout << "BLT\n";
        simpleRightTurn(root->right);
        simpleLeftTurn(root);
    }

    void bigRightTurn(node<T_key, T_value> *root) {
        //std::cout << "BRT\n";
        simpleLeftTurn(root->left);
        simpleRightTurn(root);
    }

    void balanceNode(node<T_key, T_value>* root) {
        int tmp = getDifferenceOfNodes(root->left, root->right);
        switch (tmp)
        {
        case -2:
            if (getDifferenceOfNodes(root->right->left, root->right->right) <= 0) {
                simpleLeftTurn(root);
            } else {
                bigLeftTurn(root);
            }
            break;
        case 2:
            if (getDifferenceOfNodes(root->left->left, root->left->right) >= 0) {
                simpleRightTurn(root);
            } else {
                bigRightTurn(root);
            }
            break;
        default:
            break;
        }
        //std::cout << "balance node\n";
    }

    void balanceMap(node<T_key, T_value> *node) {
        while(node != NULL) {
            changeHeight(node);
            //std::cout << "Change height" << std::endl;
            balanceNode(node);        
            //std::cout << "Balancing" << std::endl;
            node = node->parent;
        }
    }

    bool isBalanced(node<T_key, T_value> *root) {
        if(root == NULL) {
            return true;
        }

        bool result = isBalanced(root->left);
        if(result == false) {
            return false;
        }

        result = isBalanced(root->right);
        if(result == false) {
            return false;
        }
        
        int tmp = getDifferenceOfNodes(root->left, root->right);
        if (tmp < -1 || tmp > 1) {
            std::cout << tmp << std::endl;
            return false;
        } else {
            return true;
        }
    }

    node<T_key, T_value>* getNode(T_key key) {
        node<T_key, T_value>* node = root;
        T_comparator<T_key> cmp;
        while(node != NULL && node->key != key) {
            if(cmp(key, node->key)) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return node;
    }

public:
    map() {}

    map(std::vector<T_key> keys, std::vector<T_value> values) {
        if (keys.size() != values.size())
            throw std::invalid_argument("map: sizes of vectors 'keys' and 'values' don't equal.");

        for (int i = 0; i < keys.size(); i++) {
            add(keys[i], values[i]);
        }
    }

    map(map &other) {
        copyMap(root, other.root);
    }

    ~map() {
        deleteMap(root);
        root = NULL;
    }

    map& operator=(map &other) {
        deleteMap(root);
        root = NULL;
        copyMap(root, other.root);
        return *this;
    }

    bool empty() {
        return root == NULL;
    }

    void deleteAll() {
        deleteMap(root);
        root = NULL;
    }

    void add(T_key key, T_value value) {
        node<T_key, T_value> **tmp = &root, *parent = NULL;
        T_comparator<T_key> cmp;
        while(*tmp != NULL) {
            parent = *tmp;
            if(cmp(key, (*tmp)->key)) {
                tmp = &((*tmp)->left);
            } else {
                tmp = &((*tmp)->right);
            }
        }
        //std::cout << "Create new" << std::endl;
        *tmp = new node<T_key, T_value>(key, value, 1, parent);
        balanceMap(*tmp);
    }

    bool isBalanced() {
        if(root == NULL) {
            return true;
        }

        return isBalanced(root);   
    }

    bool searchKey(T_key key) {
        return getNode(key) != NULL;
    }

    T_value& operator[](T_key key) {
        node<T_key, T_value>* node = getNode(key);
        if(node == NULL) {
            throw std::invalid_argument("map: Element don't exist.");
        }
        return node->value;
    }

};

#endif