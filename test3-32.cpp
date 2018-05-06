/*利用C++ vector实现的循环队列*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<iterator>

using namespace std;

template <typename Object>
class queue
{
public:
	queue() { length = 0; front = -1; back = -1; }
	
	queue(size_t len) { v.resize(len); v.assign(len, 0); length = len; front = -1; back = -1; }

	bool isfull()
	{
		bool ret = true;
		if ((back == front - 1) || ((front == 0) &&( back == length-1)))
		{
			return ret;
		}
		else
		{
			ret = false;
			return ret;
		}
	}
	bool isempty()
	{
		bool ret = true;
		if (((front == -1) && (back == -1)))
		{
			return ret;
		}
		else
		{
			ret = false;
			return ret;
		}
	}

	void enque(const Object& obj)
	{
		if (back == -1)
		{
			back++;
			front++;
			v[back] = obj;
			return;
		}
		if ( !isfull())
		{
			back++;
			if (back == length)
			{
				back = 0;
			}
			v[back] = obj;
		}
	}

	Object& deque()
	{
		Object temp;
		if (!isempty())
		{
			if (back == front)
			{
				temp = v[back];
				back = front = -1;
				return temp;
			}
			temp = v[front];
			front++;
			if (front == length)
				front = 0;
			return temp;
		}
	}

	
	void _print()
	{
		if (front < back)
		{
			for (int i = front; i <= back; i++)
				cout << v[i] << " ";
			cout << endl;
		}
		else if (front == back && front != -1)
		{
			cout << v[front] << endl;
		}
		else if (front > back)
		{
			for (int i = 0; i <= back; i++)
				cout << v[i] << " ";
			for (int j = front; j < length; j++)
				cout << v[j] << " ";
			cout << endl;
		}
		else
		{
			cout << "no element" << endl;
		}
	}
	~queue() {  }
private:
	int front;
	int back;
	vector<Object>v;
	size_t length;
	size_t thesize;
};

int main()
{
	queue<int>q(10);
	for (int i = 0; i < 10; i++)
		q.enque(i);
	q.deque();
	q.deque();
	q.enque(99);
	q._print();
	return 0;
}