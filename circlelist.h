#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "linklist.h"
#include<iostream>

using namespace std;
namespace Wanglib
{
template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    int mod(int i)
    {
        return (this->m_length == 0)?0:(i%this->m_length);
    }
    Node* last()const
    {
        return this->position(this->m_length-1)->next;
    }

    void last_to_first() const
    {
        last()->next = this->m_header.next;
    }
public:
    bool insert(const T &e) //o(n)
    {
        return insert(this->m_length,e);
    }

    bool insert(int i,const T& e) //o(n) = o(2n+1)
    {
        bool ret = true;

        i = i % (this->m_length+1);
        ret = LinkList<T>::insert(i,e);

        if(ret && (i==0))
        {
            last_to_first();
        }
            return ret;
    }

    bool remove(int i)  //下标i
    {
        bool ret = true;
        i = mod(i);
        if(i == 0)
        {
            Node* todel = this->m_header.next;

            if(todel != NULL)
            {
                this->m_header.next = todel->next;
                this->m_length--;
                if(this->m_length > 0)
                {
                     last_to_first();
                     if(this->m_current == todel)
                     {
                         this->m_current = todel->next;
                     }
                }
                else
                {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }
                this->destroy(todel);

            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = LinkList<T>::remove(i);
        }
        return ret;
    }
    bool set(int i,const T& e)
    {
        return LinkList<T>::set((mod(i)),e);
    }

    bool get(int i)const
    {
        return LinkList<T>::get(mod(i));
    }

    bool get(int i,const T& e)const  //o(n)
    {
        return LinkList<T>::get(mod(i),e);
    }

    int find(const T& e)const  //o(n)
    {
        int ret = -1;
        Node* slider = this->m_header.next;
        for(int i = 0;i<this->m_length;i++)
        {
            if(slider->value == e)
            {
                ret =  i;
                break;
            }
            slider = slider->next;
        }
        return ret;
    }
    void clear()
    {
        while(this->m_length > 1)
        {
            remove(1);
        }
        if(this->m_length == 1)
        {
            Node* todel = this->m_header.next;
            this->m_header.next = NULL;
            this->m_length = 0;
            this->m_current = NULL;

            this->destroy(todel);

        }
    }
    bool move(int i,int step)
    {
        return LinkList<T>::move(mod(i),step);
    }

    bool end()
    {
        return (this->m_length == 0)||(this->m_current == NULL);
    }
    ~CircleList()
    {
        clear();
    }
};

}

#endif // CIRCLELIST_H
