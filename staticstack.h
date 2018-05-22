#ifndef STATICSTACK_H
#define STATICSTACK_H
#include "stack.h"
//#include "Exception.h"

namespace  Wanglib {
template <typename T,int N>
class StaticStack:public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;
public:
    StaticStack()
    {
        m_top = -1;
        m_size  = 0;
    }
    int capacity()const
    {
        return N;
    }
    void push(const T& e)
    {
        if(m_size < N)
        {
            m_space[m_top+1] = e;
            m_top++;
            m_size++;
        }
        else
        {
           // THROW_EXCEPTION(InvalidOperationException,"No space in current...");
        }
    }

    void pop()
    {
        if(m_size>0)
        {
            m_top--;
            m_size--;
        }
        else
        {
         //   THROW_EXCEPTION(InvalidOperationException,"No space in current...");
        }
    }

    T top() 
    {
        if(m_size>0)
        {
            return m_space[m_top];
        }
        else
        {
           // THROW_EXCEPTION(InvalidOperationException,"No space in current...");
        }
    }
    void clear()
    {
        m_top = -1;
        m_size = 0;
    }
    int size()const
    {
        return m_size;
    }
};

}

#endif // STATICSTACK_H
