+#include<iostream>
 +#include<algorithm>
 +#include<vector>
 +#include<string>
 +using namespace std;
 +
 +template <typename T>
 +class Fw_list
 +{
 +public:
 +	Fw_list() :head(nullptr), tail(nullptr), m_length(0) {  }
 +	Fw_list(const Fw_list<T>& obj)
 +	{
 +		head = obj.head;
 +		tail = obj.tail;
 +		m_length = obj.m_length;
 +	}
 +	Fw_list<T>& operator=(const Fw_list<T>& obj)
 +	{
 +		Fw_list<T>temp(*this);
 +		this->head = obj.head;
 +		this->tail = obj.tail;
 +		this->m_length = obj.m_length;
 +	}
 +	~Fw_list()
 +	{
 +		clear();
 +	}
 +	void clear()
 +	{
 +		while(m_length != 0)
 +			erase(0);
 +		delete tail;
 +	}
 +	void insert(const T& e, int i = 0)
 +	{
 +		if (m_length != 0)
 +		{
 +			if (0 < i && i < m_length-1)
 +			{
 +				Node* temp = head;
 +				Node* newp = new Node();
 +				newp->value = e;
 +				for (int p = 0; p < i-1; p++)
 +				{
 +					temp = temp->next;
 +				}
 +				newp->next = temp->next;
 +				temp->next = newp;
 +				m_length++;
 +			}
 +			else if (i == 0)
 +			{
 +				Node* newp = new Node();
 +				newp->next = head;
 +				newp->value = e;
 +				head = newp;
 +				m_length++;
 +			}
 +			else if (i == m_length)
 +			{
 +				Node* temp = head;
 +				while (temp->next != tail)
 +				{
 +					temp = temp->next;
 +				}
 +				Node* newp = new Node();
 +				newp->next = tail;
 +				temp->next = newp;
 +				m_length++;
 +			}
 +		}
 +		else
 +		{
 +			tail = new Node();
 +			head = new Node();
 +			head->value = e;
 +			head->next = tail;
 +			m_length++;
 +		}
 +	}
 +	void erase(int i)
 +	{
 +		if (i == 0)
 +		{
 +			Node* todel = head;
 +			head = head->next;
 +			delete todel;
 +			m_length--;
 +		}
 +		else if (0 < i && i < m_length)
 +		{
 +			Node* temp = head;
 +			for (int p = 0; p < i - 1; p++)
 +			{
 +				temp = temp->next;
 +			}
 +			Node* todel = temp->next;
 +			temp->next = todel->next;
 +			delete todel;
 +			m_length--;
 +		}
 +	}
 +	int size()
 +	{
 +		return m_length;
 +	}
 +	void _print()
 +	{
 +		Node* temp = head;
 +		while (temp != tail)
 +		{
 +			cout << temp->value << " ";
 +			temp = temp->next;
 +		}
 +		cout << endl;
 +	}
 +protected:
 +	struct Node
 +	{
 +		T value;
 +		Node* next;
 +		Node()
 +		{
 +			value = 0;
 +			next = nullptr;
 +		}
 +	};
 +	Node* head;
 +	Node* tail;
 +	int m_length;
 +};
 +int main()
 +{
 +	Fw_list<int>l;
 +	for (int i = 0; i < 5; i++)
 +	{
 +		l.insert(i);
 +	}
 +	l._print();
 +	l.insert(25, 2);
 +	l._print();
 +	l.erase(3);
 +	l._print();
 +
 +	return 0;
 +} 