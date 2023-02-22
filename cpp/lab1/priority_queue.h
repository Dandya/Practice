#pragma one

#include <iostream>
#include <vector>

template <typename Type, template <typename T> class Container = std::vector>
class Priority_queue
{
private:
    Container<Type> m_container;

    void changeTree(int index)
    {
        int i_max = index;
        int i_left_node = 2 * index + 1;
        int i_right_node = 2 * index + 2;

        if ((i_right_node < m_container.size())
                ? m_container[i_right_node] > m_container[i_max]
                : false)
        {
            i_max = i_right_node;
        }

        if ((i_left_node < m_container.size())
                ? m_container[i_left_node] > m_container[i_max]
                : false)
        {
            i_max = i_left_node;
        }

        if (index != i_max)
        {
            std::swap(m_container[index], m_container[i_max]);
            changeTree(i_max);
        }
    }

public:
    int getSize() { return m_container.size(); }

    bool isEmpty() { return m_container.empty(); }
    
    void push(Type value)
    {
        m_container.push_back(value);

        int i_new_value = m_container.size() - 1;
        int i_parent = (i_new_value - 1) / 2;

        while (i_new_value > 0 &&
               m_container[i_parent] < m_container[i_new_value])
        {
            std::swap(m_container[i_parent], m_container[i_new_value]);
            i_new_value = i_parent;
            i_parent = (i_new_value - 1) / 2;
        }
    }

    Type top()
    {
        if (m_container.empty())
        {
            throw std::runtime_error("Empty container");
        }
        Type max = m_container[0];
        return max;
    }

    Type pop()
    {
        if (m_container.empty())
        {
            throw std::runtime_error("Empty container");
        }
        Type first_elm = m_container[0];
        m_container[0] = m_container[m_container.size() - 1];
        m_container.resize(m_container.size() - 1);
        changeTree(0);
        return first_elm;
    }
};