#ifndef LIST_H
#define LIST_H
#include "object.h"

namespace Wanglib
{
    template<typename T>
    class List : public Object
    {
    protected:
        List(const List&);
        List& operator= (const List&);
    public:
        List(){}      //将List设置为protected的函数后 自定义了构造函数 因此编译器不会再安排默认构造函数 但是自定义构造函数是保护类型的
        virtual bool insert(const T& e) = 0;
        virtual bool insert(int i,const T& e) = 0;
        virtual bool remove(int i) = 0;
        virtual bool set(int i,const T& e) = 0;
        virtual bool get(int i, T& e) = 0;
        virtual int find(const T& e)const = 0;
        virtual int length() const = 0;
        virtual void clear() = 0;
    };

}
#endif // LIST_H
