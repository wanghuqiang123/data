#include<iostream>
#include<algorithm>
#include<forward_list>
#include<string>
using namespace std;

template <typename Object>
struct node
{
	node() { next = NULL; }
	node(Object obj) : data(obj) {}
	node(Object obj, node * ptr) : data(obj), next(ptr) {}
	Object data;
	node * next;
};
//此例不代表循环队列
template <typename Object>
class queue
{
public:
	queue() { front = NULL; rear = NULL; thesize = 0; }
	~queue() { while (front) deque(); }
	void enque(Object obj)
	{
		node<Object> * ptr = new node<Object>(obj, NULL);
		if (rear)
			rear = rear->next = ptr;
		else
			front = rear = ptr;
		thesize++;
	}
	Object deque()
	{
		Object temp = front->data;
		node<Object> * ptr = front;
		if (front->next == NULL) // only 1 node
			front = rear = NULL;
		else
			front = front->next;
		delete ptr;
		thesize--;
		return temp;

	}
	void _print()
	{
		node<Object>*iter = front;
		for (int i = 0; i < thesize; i++,iter = iter->next)
			cout << (*iter).data << " ";
		cout << endl;
	}
private:
	node<Object> * front;
	node<Object> * rear;
	size_t thesize;
};
int main()
{
	queue<int>q;
	for (int i = 0; i < 5; i++)
		q.enque(i);
	q._print();
	return 0;
}