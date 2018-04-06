#include<iostream>
#include<vector>
#include<string>
#include<list>

using namespace std;

template<typename Object>
list<Object> intersection( const list<Object>&l1,const list<Object>&l2)
{
	auto p1 = l1.begin();
	list<Object>intersection;
	for(;p1!=l1.end();p1++)
		for(auto p2 = l2.begin();p2 != l2.end();p2++)
			if (*p1 == *p2)
			{
				intersection.push_back(*p1);
				break;
			}
	return intersection;
}

int main()
{
	int a;
	list<int>l1 = { 1,2,3,4,5,6,7,8,9,10 };
	list<int>l2 = { 2,4,6,8 };
	list<int>l3 = intersection(l1, l2);
	for (auto p = l3.cbegin(); p != l3.cend(); p++)
		cout << *p << " " << endl;
	
	cin >> a;

	return 0;
}

