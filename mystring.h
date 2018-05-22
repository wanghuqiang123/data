#ifndef MYSTRING_H
#define MYSTRING_H
#include "object.h"
using namespace Wanglib;

namespace Wanglib {


class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* l,const char* r,int len)const;
public:
    String();
    String(const char* s);
    String(char c);
    String(const String& s);

    int length()const;
    const char* str()const;

    bool operator ==(const String& s)const;
    bool operator ==(const char* s)const;
    bool operator !=(const String& s)const;
    bool operator !=(const char* s)const;
    bool operator >(const String& s)const;
    bool operator >(const char* s)const;
    bool operator <(const String& s)const;
    bool operator <(const char* s)const;
    bool operator >=(const String& s)const;
    bool operator >=(const char* s)const;
    bool operator <=(const String& s)const;
    bool operator <=(const char* s)const;

    String operator+(const String& s)const;
    String operator +(const char* s)const;
    String& operator+=(const String& s);
    String& operator +=(const char* s);

    char& operator[](int i);
    char operator [](int i)const;

    String& operator=(const String& s);
    String& operator =(const char* s);
    String& operator =(char c);

    bool starWith(const char* s)const;
    bool starWith(const String& s) const;
    bool endOf(const  char* s)const;
    bool endOf(const String& s)const;

    String& insert(int i,const char* s);
    String& insert(int i,const String& s);
    String& trim();
    ~String();
};


}
#endif // MYSTRING_H
