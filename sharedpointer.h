#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include<cstdlib>
#include "pointer.h"
#include  "Exception.h"
using namespace std;

namespace Wanglib
{
template<typename T>
class SharedPointer:public Pointer<T>
{
protected:
    int *m_ref;

    void assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if(this->m_ref)
        {
            (*(this->m_ref))++;

        }
    }
public:
    SharedPointer(T* p = NULL)
    {
        if(p)
        {
            this->m_ref =static_cast<int*>(malloc(sizeof(int)));

            if(this->m_ref)
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no more memory to be use!");
            }
        }
    }
    SharedPointer(const SharedPointer<T>& obj):Pointer<T>(NULL)
    {
       assign(obj);
    }
  SharedPointer<T>& operator=(const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* todel = this->m_pointer;

            this->m_pointer = NULL;

            if(m_ref)
            {
               (*m_ref)--;
                if(*m_ref == 0)
                {
                    free(m_ref);
                    delete todel;
                }
            }
            m_ref = NULL;
            assign(obj);
        }

        return *this;
    }

    void clear()
    {

        T* todel = this->m_pointer;
        int *ref = this->m_ref;

        this->m_ref =NULL;
        this->m_pointer = NULL;

        if(ref)
        {
            (*ref)--;
            if((*ref) == 0)
            {
                free(ref);
                delete todel;
            }
        }

    }
    ~SharedPointer()
    {
        clear();  //专门有一个指向int类型的空间的指针，指针来控制计数；
    }
};

template<typename T>
bool operator == (const SharedPointer<T>& l,const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template<typename T>
bool operator != (const SharedPointer<T>& l,const SharedPointer<T>& r)
{
    return !(l == r);
}

}

#endif // SHAREDPOINTER_H
