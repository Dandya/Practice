#ifndef BTREE_MAP_H

#define BTREE_MAP_H
#include <iostream>
#include <map>
#include <vector>

template <typename T>
class comparator {
public:
    bool operator()(T &arg1, T &arg2) {
        return arg1 < arg2;
    }
};

template <typename T_key, typename T_value, template <typename T> class T_comparator = comparator>
class btree_map {
private:
    typedef struct
    {
        T_key key;
        T_value value;
    } entry;

    class node_btree {
    public:
        node_btree *parent = NULL;
        std::vector<entry> data;
        std::vector<node_btree *> childs;

        node_btree() {}
        node_btree(node_btree *parent) : parent{parent} {}
        node_btree(node_btree *parent, std::vector<entry>::interator data_it_begin, std::vector<entry>::interator data_it_end) : parent{parent} {
            for(; data_it_begin != data_it_end; data_it_begin++) {
                data.push_back(*data_it_begin);
            }
        }
        node_btree(node_btree *parent, std::vector<entry>::interator data_it_begin, std::vector<entry>::interator data_it_end,
                std::vector<node_btree *>::interator childs_it_begin, std::vector<node_btree *>::interator childs_it_end) : 
                node_btree(parent, data_it_begin, data_it_end) {
            for(; childs_it_begin != childs_it_end; childs_it_begin++) {
                childs.push_back(*childs_it_begin);
            }
        }
    };

    int min_degree; // min degree of b-tree
    node_btree *root;

    int searchKeyInNode(node_btree *node, T_key key) {
        int left_border = 0;
        int right_border = node->data.size() - 1;
        T_comparator<T_key> cmp;

        int index;
        int previous_index;
        while (left_border <= right_border) {
            index = (left_border + right_border) / 2;

            if (node->data[index] == key) {
                return index;
            } else if (cmp(node->data[index], key)) {
                right_border = index - 1;
            } else {
                left_border = index + 1;
            }
            previous_index = index;
        }
        return -1;
    }

    void separationNode(node_btree *&node) {
        node_btree *parent = node->parent;
        
        int index_child;
        for(int i = 0; i < parent->childs.size(); i++) {
            if(parent->childs[i] == node) {
                index_child = i;
                break;
            }
        }

        parent->data.insert(parent->data.begin() + index_child, node->data[min_degree-1]);
        parent->childs[index_child] = new btree_map(parent, node->data.begin(), node->data.begin()+(min_degree-1),
                                                    node->childs.begin(), node->childs.begin()+);
        parent->childs.insert(parent->childs.begin()+index_child+1, new  btree_map(parent, node->data.begin()+(min_degree), node->data.end()));
    }

public:
    btree_map(int min_degree_btree) {
        if (2 * min_degree_btree < 0) {
            throw std::invalid_argument("btree_map: @param min_degree_btree has invalid value.");
        }
        min_degree = min_degree_btree;
        root = new node_btree();
    }
    btree_map(int min_degree_btree, std::map<T_key, T_value> data) : btree_map(min_degree) {
        for (const auto &[key, value] : data) {
            add(key, value);
        }
    }

    void add(T_key key, T_value value) {
        node_btree *node = root;
        int index = 0;

        while (node->childs.size() != 0 || node->data.size() == 2 * min_degree - 1) {
            if (node->data.size() == 2 * min_degree - 1) {
                node = separationNode(node);
                continue;
            }

            if (node->childs.size() != 0) {
                index = 0;
                while (index < node->data.size() && node->data[index] < key) {
                    index++;
                }

                node = node->childs[index];
            }
        }
        index = 0;
        while (index < node->data.size() && node->data[index] < key) {
            index++;
        }
        node->data.insert(node->data.begin() + index, {key, value});
    }

    bool search(T_key key) {
        node_btree *node = root;
    }
};
#endif