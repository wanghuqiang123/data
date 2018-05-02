#include<iostream>
#include<algorithm>
#include<forward_list>
#include<string>
using namespace std;

template <typename Object>
struct node
{
	node() { next = NULL; }
	node(Object obj) : data(obj) { next = NULL }
	node(Object obj, node * ptr = NULL) : data(obj), next(ptr) {}
	Object data;
	node * next;
};
template <typename Object>
class stack
{
public:
	stack() { head = NULL; }
	~stack() { while (head) pop(); }
	void push(Object obj)
	{
		node<Object> * ptr = new node<Object>(obj, head);
		head = ptr;
	}
	Object top()
	{
		return (head->data);
	}
	void pop()
	{
		node<Object> * ptr = head->next;
		delete head;
		head = ptr;
	}
private:
	node<Object> * head;
};

int main()
{
	stack<int>s;
	for (int i = 0; i < 5; i++)
		s.push(i);
	
	return 0;
}