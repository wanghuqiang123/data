/*data_struct test3-6.a.cpp*/

#include<iostream>
#include<string>
#include<list>

using namespace std;

int main(int argv, char ** argc)
{
	int n, m, number = 0;
	list<int>l;
	list<int>::iterator iter;
	
	cout << "enter n (# of people) & (#of passes before elimination):)";
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		l.push_back(i);
		cout << i << " ";
	}
	cout << endl;
	iter = l.begin();
	while (l.size() != 1)
	{
		if (iter == l.end())
		{
			iter = l.begin();
		}

		if (number == m)
		{
			number = 0;
			iter = l.erase(iter);
			continue;
		}
		iter++;
		number++;
	}
	iter = l.begin();
	cout << *iter << endl;
	int i;
	cin >> i;

	return 0;
}

