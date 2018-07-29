#include "BinaryHeap.h"
#include <iostream>
using namespace std;
using namespace Wanglib;

int main()
{
	int a[5] = { 5,4,1,2,3 };
	BinaryHeap<int>BH;
	for (int i = 0; i < 5; i++)
	{
		BH.insert(a[i]);
	}

	BH.print();

	for (int i = 0; i < 3; i++)
	{
		BH.deleteMin();
	}

	cout << endl;

	BH.print();


	return 0;
}