#ifndef LINKQUEUE_H
#define LINKQUEUE_H
#include "queue.h"
#include "LinuxList.h"
#include "Exception.h"

namespace Wanglib {

template<typename T>
class LinkQueue:public Queue<T>
{
protected:
    struct Node:public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    int m_length;
public:
    LinkQueue()
    {
        m_length = 0;
        INIT_LIST_HEAD(&m_header);
    }

    void add(const T& e)
    {
        Node* node = new Node();
        if(node != NULL)
        {
            node->value = e;
            list_add_tail(&node->head,&m_header);
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"no element to add new current queue...");
        }
    }
    void remove()
    {
        if(m_length>0)
        {
            list_head* todel = m_header.next;
            list_del(todel);
            m_length--;
            delete list_entry(todel,Node,head);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in currnt queue..");
        }
    }

    T front()
    {
        if(m_length>0)
        {
            return list_entry(m_header.next,Node,head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in currnt queue..");
        }
    }

    void clear()
    {
        while(m_length>0)
            remove();
    }
    int length()const
    {
        return m_length;
    }
    ~LinkQueue()
    {
        clear();
    }

};

}

#endif // LINKQUEUE_H
