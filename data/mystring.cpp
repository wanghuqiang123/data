#include "mystring.h"
/*#include <cstring>
#include <cstdlib>


using namespace std;
namespace Wanglib
{

    void String::init(const char *s)
    {
        m_str = strdup(s?s:"");

        if(m_str)
        {
            m_length = strlen(m_str);
        }
   
    }

    String::String()
    {
        init("");
    }
    String::String(const char* s)
    {
        init(s ? s : "");
    }

    String::String(const String& s)
    {
        init(s.m_str);
    }
    String::String(char c)
    {
        char s[] = {c,'\0'};

        init(s);
    }

    int String::length()const
    {
        return m_length;
    }

    const char* String::str()const
    {
        return m_str;
    }
    bool String::operator ==(const String& s)const
    {
        return (strcmp(m_str,s.m_str) == 0);
    }

    bool String::operator ==(const char* s)const
    {
        return (strcmp(m_str,s?s:"") == 0);
    }
    bool String::operator !=(const String& s)const
    {
        return !(*this == s);
    }
    bool String::operator !=(const char* s)const
    {
        return !(*this == s);
    }
    bool String::operator >(const String& s)const
    {
        return (strcmp(m_str,s.m_str) > 0);
    }
    bool String::operator >(const char* s)const
    {
        return (strcmp(m_str,s?s:"") > 0);
    }
    bool String::operator <(const String& s)const
    {
        return (strcmp(m_str,s.m_str) < 0);
    }
    bool String::operator <(const char* s)const
    {
        return (strcmp(m_str,s?s:"") < 0);
    }

    bool String::operator >=(const String& s)const
    {
        return (strcmp(m_str,s.m_str) >= 0);
    }
    bool String::operator >=(const char* s)const
    {
        return (strcmp(m_str,s?s:"") >= 0);
    }
    bool String::operator <=(const String& s)const
    {
        return (strcmp(m_str,s.m_str) <= 0);
    }
    bool String::operator <=(const char* s)const
    {
        return (strcmp(m_str,s?s:"") <= 0);
    }

    String String::operator+(const String& s)const
    {
        return (*this + s.m_str);
    }
    String String::operator +(const char* s)const
    {
        String ret;
        int len = m_length+strlen(s?s:"");
        char* str = reinterpret_cast<char*>(malloc(len+1));
        if(str)
        {
            strcpy(str,m_str);
            strcat(str, s ? s : "");

            free(ret.m_str);

            ret.m_str = str;
            ret.m_length = len;
        }
       
        return ret;
    }
    String& String::operator=(const String& s)
    {
        return (*this = s.m_str);
    }
    String& String::operator =(const char* s)
    {
        if(m_str != s)
        {
            char* str = strdup(s?s:"");
            if(str != NULL)
            {
                free(m_str);
                m_str = str;
                m_length = strlen(m_str);

            }
         
        }
        return *this;
    }
    String& String::operator =(char c)
    {
        char s[] = {c,'\0'};

        return (*this = s);
    }
    String& String::operator+=(const String& s)
    {
        return (*this = *this+s);
    }
    String& String::operator +=(const char* s)
    {
        return (*this = *this + s);
    }
    char& String::operator[](int i)
    {
        if(0<=i&&i<m_length)
        {
            return m_str[i];
        }
       
    }
    char String::operator[](int i)const
    {
        return (const_cast<String&>(*this))[i];
    }
    bool String::equal(const char* l,const char* r,int len)const
    {
        bool ret = true;
        for(int i= 0;i<len&&ret;i++)
        {
            ret = ret && (l[i] == r[i]);
        }

        return ret;
    }

    bool String::starWith(const char* s)const
    {
        bool ret = (s != NULL);

        if(ret)
        {
            int len = strlen(s);
            ret = (len<m_length)&&equal(m_str,s,len);
        }
        return ret;
    }
    bool String::starWith(const String& s) const
    {
        return starWith(s.m_str);
    }
    bool String::endOf(const  String& s)const
    {
        return endOf(s.m_str);
    }
    bool String::endOf(const char* s)const
    {
        bool ret = (s != NULL);

        if(ret)
        {
            int len = strlen(s);
            char* str = m_str+(m_length - len);
            ret = (len<m_length)&&equal(str,s,len);
        }

        return ret;
    }
    String& String::insert(int i,const char* s)
    {
        if( (0<=i) && (i<=m_length) )
        {
            if((s != NULL) && (s[0]!= '\0'))
            {
                int len = strlen(s);
                char* str = reinterpret_cast<char*>(malloc(m_length+len+1));
                if(str != NULL)
                {
                    strncpy(str,m_str,i);
                    strncpy(str+i,s,len);
                    strncpy(str+i+len,m_str+i,m_length-i);
                    str[m_length+len] = '\0';

                    free(m_str);
                    m_str = str;
                    m_length = m_length+len;
                }
              
            }
        }
        
        return *this;
    }
    String& String::insert(int i,const String& s)
    {
        return insert(i,s.m_str);
    }

    String& String::trim()
    {
        int b= 0;
        int e = m_length-1;
        while (m_str[b] == ' ')
        {
            b++;
        }
        while (m_str[e] == ' ')
        {
            e--;
        }
        if( b== 0)
        {
            m_str[e+1] = '\0';
            m_length = e + 1;
        }
        else
        {
            for(int i = 0,j=b;j<=e;i++,j++)
            {
                m_str[i] = m_str[j];
            }
            m_str[e - b + 1] = '\0';
            m_length = e - b +1;
        }
        return *this;
    }

    String::~String()
    {
        free(m_str);
    }
	
}*/
