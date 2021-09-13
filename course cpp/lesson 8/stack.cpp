#include <iostream>
#include <cassert>
//----------------------------------------------------------------
class Stack
{
private:
    int m_array[10];
    int m_size;
public:
    Stack()
    {
        m_size = 0;
    }
    //*************
    void reset()
    {
        for(; m_size > 0;)
        {
            m_array[--m_size] = 0;
        }
    }
    //*************
    bool push(int x)
    {
        if(m_size == 10)
        {
            return false;
        }
        else
        {
            m_array[m_size++] = x;
            return true;
        }
    }
    //*************
    int pop()
    {
        assert(m_size > 0);
        return m_array[--m_size];
    }
    //*************
    void print()
    {
        std::cout << "( ";
        for (int index = 0; index < m_size; index++)
        {
            std::cout << m_array[index] << " ";
        }
        std::cout << ")" << std::endl;
    }
};
//----------------------------------------------------------------	
int main()
{
	Stack stack;
	stack.reset();
 
	stack.print();
 
	stack.push(3);
	stack.push(7);
	stack.push(5);
	stack.print();
 
	stack.pop();
	stack.print();
 
	stack.pop();
	stack.pop();
 
	stack.print();
 
	return 0;
}