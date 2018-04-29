#include<iostream>
#include<string>
#include<stack>
#include<deque>
using namespace std;

deque<int>d;
template <typename T>
T findMin(stack<T> s)
{
	T a;
	a = s.top();
	s.pop();
	while(!s.empty())
	{
		if (s.top() < a)
			a = s.top();
		s.pop();
	}
	return a;
}
int main()
{
	stack<int>s;
	int a;
	for (int i = 0; i < 10; i++)
		s.push(i);
	a = findMin(s);
	cout << a << endl;
	return 0;
}