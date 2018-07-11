#include<iostream>
  #include<algorithm>
 -#include<forward_list>
 +#include<vector>
  #include<string>
 +#include<iterator>
 +
  using namespace std;
  
 -template <typename Object>
 -struct node
 -{
 -	node() { next = NULL; }
 -	node(Object obj) : data(obj) {}
 -	node(Object obj, node * ptr) : data(obj), next(ptr) {}
 -	Object data;
 -	node * next;
 -};
 -//´ËÀý²»´ú±íÑ­»·¶ÓÁÐ
  template <typename Object>
  class queue
  {
  public:
 -	queue() { front = NULL; rear = NULL; thesize = 0; }
 -	~queue() { while (front) deque(); }
 -	void enque(Object obj)
 +	queue() { length = 0; front = -1; back = -1; }
 +	
 +	queue(size_t len) { v.resize(len); v.assign(len, 0); length = len; front = -1; back = -1; }
 +
 +	bool isfull()
  	{
 -		node<Object> * ptr = new node<Object>(obj, NULL);
 -		if (rear)
 -			rear = rear->next = ptr;
 +		bool ret = true;
 +		if ((back == front - 1) || ((front == 0) &&( back == length-1)))
 +		{
 +			return ret;
 +		}
  		else
 -			front = rear = ptr;
 -		thesize++;
 +		{
 +			ret = false;
 +			return ret;
 +		}
  	}
 -	Object deque()
 +	bool isempty()
  	{
 -		Object temp = front->data;
 -		node<Object> * ptr = front;
 -		if (front->next == NULL) // only 1 node
 -			front = rear = NULL;
 +		bool ret = true;
 +		if (((front == -1) && (back == -1)))
 +		{
 +			return ret;
 +		}
  		else
 -			front = front->next;
 -		delete ptr;
 -		thesize--;
 -		return temp;
 +		{
 +			ret = false;
 +			return ret;
 +		}
 +	}
  
 +	void enque(const Object& obj)
 +	{
 +		if (back == -1)
 +		{
 +			back++;
 +			front++;
 +			v[back] = obj;
 +			return;
 +		}
 +		if ( !isfull())
 +		{
 +			back++;
 +			if (back == length)
 +			{
 +				back = 0;
 +			}
 +			v[back] = obj;
 +		}
 +	}
 +
 +	Object& deque()
 +	{
 +		Object temp;
 +		if (!isempty())
 +		{
 +			if (back == front)
 +			{
 +				temp = v[back];
 +				back = front = -1;
 +				return temp;
 +			}
 +			temp = v[front];
 +			front++;
 +			if (front == length)
 +				front = 0;
 +			return temp;
 +		}
  	}
 +
 +	
  	void _print()
  	{
 -		node<Object>*iter = front;
 -		for (int i = 0; i < thesize; i++,iter = iter->next)
 -			cout << (*iter).data << " ";
 -		cout << endl;
 +		if (front < back)
 +		{
 +			for (int i = front; i <= back; i++)
 +				cout << v[i] << " ";
 +			cout << endl;
 +		}
 +		else if (front == back && front != -1)
 +		{
 +			cout << v[front] << endl;
 +		}
 +		else if (front > back)
 +		{
 +			for (int i = 0; i <= back; i++)
 +				cout << v[i] << " ";
 +			for (int j = front; j < length; j++)
 +				cout << v[j] << " ";
 +			cout << endl;
 +		}
 +		else
 +		{
 +			cout << "no element" << endl;
 +		}
  	}
 +	~queue() {  }
  private:
 -	node<Object> * front;
 -	node<Object> * rear;
 +	int front;
 +	int back;
 +	vector<Object>v;
 +	size_t length;
  	size_t thesize;
  };
 +
  int main()
  {
 -	queue<int>q;
 -	for (int i = 0; i < 5; i++)
 +	queue<int>q(10);
 +	for (int i = 0; i < 10; i++)
  		q.enque(i);
 +	q.deque();
 +	q.deque();
 +	q.enque(99);
  	q._print();
  	return 0;
  } 