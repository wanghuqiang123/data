#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

namespace Wanglib
{
	template <typename Comparable>
	class BinaryHeap
	{
	public:
	    BinaryHeap()
		{
			curruentSize = 0;
			array.resize(100);
		}
		BinaryHeap(int capacity )
		{
			curruentSize = 0;
			array.resize(capacity);
		}
		 BinaryHeap(const vector<Comparable> & item) :array(item.size() + 10), curruentSize(item.size())
		{
			for (int i = 1; i<item.size(); i++)
				array[i] = item[i];
			buildHeap();
		}
		BinaryHeap(const BinaryHeap<Comparable>& rhs)
		{
			this->curruentSize = rhs.curruentSize;
			this->array.resize(rhs.array.size());
			this->array = rhs.array;
		}
		BinaryHeap<Comparable>& operator=(const BinaryHeap<Comparable>& rhs)
		{
			this->array.resize(rhs.array.size());
			array = rhs.array;
			this->curruentSize = rhs.curruentSize;
		}

		bool isEmpty()const
		{
			bool ret = true;
			if (array.size() == 0)
				ret = false;
			return ret;
		}
		const Comparable& findMin()const
		{
			return array[1];
		}

		void insert(const Comparable& x)
		{
			if (curruentSize == array.size())
				array.resize(array.size() * 2);

			int hole = ++curruentSize;
			for (; hole > 1 && x<array[hole / 2]; hole /= 2)
				array[hole] = array[hole / 2];
			array[hole] = x;
		}
		void deleteMin()
		{
			if (isEmpty())
				throw UnderflowException();
			array[1] = array[curruentSize--];
			percolateDown(1);
		}
		void deleteMin(Comparable& minItem) //把最尾巴的元素份赋值给根结点，再往下渗透；
		{
			if (isEmpty())
				throw UnderflowException();
			minItem = array[1];
			array[1] = array[curruentSize--]; //把最尾巴的元素份赋值给根结点，再往下渗透；
			percolateDown(1);
		}
		void makeEmpty()
		{
			array.clear();
			curruentSize = 0;
		}

		void decreaseKey(int pos, Comparable val)
		{
			array[pos] = array[pos] - val;
			percolateUp(pos);
		}

		void increaseKey(int pos, Comparable val)
		{
			array[pos] = array[pos] + val;
			percolateDown(pos);
		}

		void remove(int pos)
		{
			decreaseKey(pos, array[pos]);
			deleteMin();
		}

		void print()const
		{
			int h = log2(curruentSize - 1) + 1;
			int current = 1;
			for (int i = 1; i <= h; i++)
			{
				for (int j = 1; j <= pow(2, i - 1) && current <= curruentSize; j++)
				{
					cout << array[current]<<" ";
					current++;
				}
				cout << endl;
			}
		}
		~BinaryHeap()
		{
			makeEmpty();
		}

	private:
		int curruentSize;
		vector<Comparable>array;

		void buildHeap()
		{
			for (int i = curruentSize / 2; i > 0; i--) //相当去排序一次
			{
				percolateDown(i);
			}
		}
		void percolateDown(int hole) // void percolateDown(int hole) 下渗 hole :孔
		{
			int child;
			Comparable tmp = array[hole];

			for (; hole * 2 <= curruentSize; hole = child)
			{
				child = hole * 2;
				if (child != curruentSize && array[child + 1] < array[child])
					child++;
				if (array[child]<tmp)
					array[hole] = array[child];
				else
					break;
			}
			array[hole] = tmp;
		}

		void percolateUp(int hole)
		{
			int parent;
			Comparable tmp = array[hole];

			for (; hole / 2 > 0; hole = parent)
			{
				parent = hole / 2;
				if (parent > 0 && array[parent] > tmp)
					array[hole] = array[parent];
				else
					break;
			}
			array[hole] = tmp;
		}

		string UnderflowException()
		{
			string s = "This BinaryHeap is empty";
			return s;
		}
	};

}


