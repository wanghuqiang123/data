#ifndef LINKLIST_H
#define LINKLIST_H
#include "list.h"
#include "Exception.h"


namespace Wanglib
{
    template <typename T>
    class LinkList : public List<T>
    {
    protected:
        struct Node:public Object
        {
            T value;
         Node* next;
        };

        mutable struct:public Object
        {
            char reserved[sizeof(T)];
          Node* next;
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
        LinkList()
        {
            m_header.next = NULL;
            m_length = 0;
            m_step = 1;
            m_current = NULL;
        }
        bool insert(const T& e)
        {

            return insert(m_length,e);
        }

        bool insert(int i,const T& e)
        {
           bool ret = ((0 <= i) && (i<=m_length));

           if(ret)
            {
                Node* node = create();

                if(node != NULL)
                {
                    Node* current = position(i);


                    node->value = e;
                    node->next = current->next;
                    current->next = node;

                    m_length++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"No more memory  to create...");
                }
            }

            return ret;
        }


         bool remove(int i)  //删除之后m_current往后移一个元素；
         {
             bool ret = ((0<=i)&&(i<m_length));

             if(ret)
             {
                Node* current = position(i);
                Node* todel = current->next;
                 if(m_current == todel)
                 {
                     m_current = todel->next;
                 }
                 current->next = todel->next;

                 m_length--;
               destroy(todel);
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
            while(m_header.next)
            {
               Node* todel = m_header.next;

                m_header.next = todel->next;

                m_length--;

               destroy(todel);
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

        ~LinkList()
        {
            clear();
        }
    };


}

#endif // LINKLIST_H
