#ifndef DUALINKLIST_H
#define DUALINKLIST_H

#include "list.h"
#include "Exception.h"


namespace Wanglib
{
    template <typename T>
    class DuaLinkList : public List<T>
    {
    protected:
        struct Node:public Object
        {
            T value;
            Node* next;
            Node* pre;
        };

        mutable struct:public Object  //mutable 指的是被定义的变量永远处于可变的状态，即使在const的函数中
        {
            char reserved[sizeof(T)];
            Node* next;
            Node* pre;
        }m_header;

        int m_length;
        int m_step;
        Node* m_current;

        Node* position(int i)const
        {
           Node* ret = reinterpret_cast<Node*>(&m_header);
            for(int p = 0;p<i;p++)
            {
                ret =ret->next;
            }
            return ret;
        }

        virtual Node* create()

        {
            return new Node();
        }

        virtual void destroy(Node* pn)
        {
            delete pn;
        }
    public:
        DuaLinkList()
        {
            m_header.next = NULL;
            m_header.pre = NULL;
            m_length = 0;
            m_step = 1;
            m_current = NULL;
        }
        bool insert(const T& e)
        {

            return insert(m_length,e);
        }

        bool insert(int i,const T& e)   //往下标为i的元素后插入一个元素；
        {
           bool ret = ((0 <= i) && (i<=m_length));

           if(ret)
            {
                Node* node = create();

                if(node != NULL)
                {
                    Node* current = position(i);
                    Node* next = current->next;

                    node->value = e;

                    node->next = next;
                    current->next = node;

                    if(current != reinterpret_cast<Node*>(&m_header))
                    {
                        node->pre = current;
                    }
                    else
                    {
                        node->pre = NULL;
                    }

                    if(next != NULL)
                    {
                        next->pre = node;
                    }
                    m_length++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"No more memory  to create...");
                }
           }

            return ret;
        }


         bool remove(int i)  // 删除下标为i的元素；
         {
             bool ret = ((0<=i)&&(i<m_length));

             if(ret)
             {
                Node* current = position(i);
                Node* temp = current;
                Node* pre = current->pre;
                Node* next = current->next;
                 if(pre != NULL)
                 {
                    pre->next = current->next;
                 }

                 if(next != NULL)
                 {
                     next->pre = pre;
                 }
                 if(m_current == current)
                 {
                     m_current = current->next;
                 }
                 m_length--;

               destroy(temp);
             }
             else
             {
                 THROW_EXCEPTION(IndexOutOfBoundsException,"IndexOutOfBoundsException");
             }

             return ret;
         }
        bool set(int i,const T& e)
        {
            bool ret = ((0<=i)&&(i<m_length));
            if(ret)
            {
                position(i)->next->value = e;
            }

            return ret;
        }

        virtual T get(int i)
        {
            T ret;

            if(get(i,ret))
            {
                return ret;
            }
            else
            {
                THROW_EXCEPTION(IndexOutOfBoundsException,"Invaild parameter...");
            }

            return ret;
        }

        bool get(int i, T& e)
        {
            bool ret = ((0<=i)&&(i<m_length));
            if(ret)
            {
                e = position(i)->next->value;
            }

            return ret;
        }

        int find(const T& e)const
        {
            int ret = -1;

            int i = 0;
            Node* node = m_header.next;

            while(node)
            {
                if(node->value == e)
                {
                    ret = i;

                    break;
                }
                else
                {
                    node = node->next;
                    i++;
                }
            }

            return ret;
        }
        int length() const
        {
            return m_length;
        }
        void clear()
        {
            while(length() > 0)
            {
               remove(0);
            }

            //m_length = 0;
        }

       virtual bool move(int i,int step = 1)
        {
            bool ret = ((0<=i)&&(i<m_length)&&(step>0));

            if(ret)
            {
                m_step = step;
                m_current = position(i)->next;
                //bug here
            }

                    return ret;
        }

        virtual bool end()
        {
            return (m_current == NULL);

        }
        virtual T current()
        {
            if(!end())
            {
                return m_current->value;
            }
            else
            {
                THROW_EXCEPTION(IndexOutOfBoundsException,"no value at current ");
            }

        }

        virtual bool next()
        {
            int i = 0;
            if((i<m_length)&&!end())
            {
                m_current = m_current->next;
                i++;
            }

            return (i == 1);
        }
        virtual bool pre()
        {
            int i = 0;
            if((i<m_length) && !end())
            {
                m_current = m_current->pre;
                i++;
            }

            return (i == 1);
        }
        ~DuaLinkList()
        {
            clear();
        }
    };


}

#endif // DUALINKLIST_H
