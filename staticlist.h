#ifndef STATICLIST_H
#define STATICLIST_H
#include "seqlist.h"

namespace Wanglib
{
    template<typename T,int N>
    class StaticList : public SeqList<T>
    {
        protected:
            T m_space[N];
        public:
            StaticList()
            {
                this->m_array = m_space;
                this->m_length = N;
            }

       int capacity()const
            {
                return N;
            }
    };

}

#endif // STATICLIST_H
