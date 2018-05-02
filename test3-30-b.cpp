#include<iostream>
#include<string>
#include<list>
#include<algorithm>

using namespace std;
template <typename T>

void myprint(const T& element)
{
	cout << element << "  ";
}
template <typename T,int N>
class adjustlist : public list<T>
{
public:
	adjustlist()
	{
		index = N - 1;
		length = N;
	}
	bool insert(T i)
	{
		if (index != -1 && N != 0)
		{
			array.push_front(i);
			return true;
		}
		else
			return false;
	}
	T& get(int i)
	{
		list<T>::iterator iter = array.begin();
		if (0 <= i && i < length)
		{
			for (int j = 0; j < i;j++)
				iter++;
			return *iter;
		}
				
	}
	void find(T a)
	{
		list<T>::iterator iter;
		for (iter = array.begin(); iter != array.end(); iter++)
		{
			if (*iter == a)
			{
				list<T>::iterator iter1 = iter;
				iter1--;
				while (iter != array.begin())
				{
					*iter = *iter1;
					iter--;
					if(iter != array.begin())
						iter1--;
				}
				*iter = a;
			}
		}
	}
	~adjustlist()
	{

	}

private:
	list<T>array;
	int index;
	size_t length ;
};


int main()
{
	adjustlist<int,5>a;
	for (int i = 0; i < 5; i++)
		a.insert(i);
	
	for (int i = 0; i < 5; i++)
		cout << a.get(i) << endl;

	a.find(3);

	for (int i = 0; i < 5; i++)
		cout << a.get(i) << endl;
	return 0;
}