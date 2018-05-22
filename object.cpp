#include "object.h"
#include<cstdlib>
#include<iostream>

using namespace std;

namespace Wanglib
{
    void* Object::operator new(unsigned int size) throw() //在这里的throw()跟在函数后面表示不会抛出异常；
    {

        return malloc(size);        //new是一个操作符；new[]时分配数组的操作符
    }

    void Object::operator delete(void* p)
    {

        free(p);
    }

    void* Object::operator new[](unsigned int size)throw()
    {
        return malloc(size);
    }

    void Object::operator delete[](void* p)
    {
        free(p);
    }
    bool Object::operator == (const Object& Obj)
    {
        return (this == &Obj);
    }
    bool Object::operator != (const Object& Obj)
    {
        return (this != &Obj);
    }
    Object::~Object()
    {

    }

}
