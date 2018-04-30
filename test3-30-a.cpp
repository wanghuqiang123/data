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
class adjustlist //:public list<T>
{
public:
	adjustlist()
	{
		index = N - 1;
		length = N;
	}
	
	~adjustlist()
	{

	}
	bool insert(T i)
	{
		if (index != -1 && N != 0)
		{
			array[index] = i;
			index = index - 1;
			return true;
		}
		else
			return false;
	}
	T& get(int i)
	{
		if (0 <= i && i < length)
			return array[i];
	}
	bool find(T a)
	{
		for(int i = 0;i<length;i++)
			if (array[i] == a)
			{
				for (int j = i; 0<j; j--)
				{
					array[j] = array[j - 1];
				}
				array[0] = a;	
				return true;
			}
	}

private:
	T array[N];
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