#ifndef QUEUE_H
#define QUEUE_H
#include "object.h"

namespace Wanglib
{

template <typename T>
class  Queue:public Object
{
public:
    virtual void add(const T& e) = 0;
    virtual void remove() = 0;
    virtual T front() = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;

};

}

#endif // QUEUE_H
