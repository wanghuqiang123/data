#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
namespace Wanglib
{
	template<typename Comparable>
	class BinomialQueue
	{
	public:
		BinomialQueue() :currentSize(0), theTrees(){ }
		BinomialQueue(const Comparable& item) :currentSize(1),theTrees(1)
		{
			insert(item);

		}
		BinomialQueue(const BinomialQueue& rhs);
		BinomialQueue& operator=(const BinomialQueue& rhs);
		~BinomialQueue()
		{

		}

		bool isEmpty()const;
		const Comparable& findMin()const
		{
			int minIndex = findMinIndex();
			return theTrees[minIndex];
		}
		
		void insert(const Comparable& x);
		void deleteMin();
		void deleteMinret(Comparable& minItem)
		{
			if (isEmpty())
				throw UnderflowException();

			int minIndex = findMinIndex();
			minItem = theTrees[minIndex]->element;

			BinomialNode* oldRoot = theTrees[minIndex];
			BinomialNode* deletedTree = oldRoot->leftChild;
			delete oldRoot;

			BinomialQueue deleteQueue;
			deleteQueue.theTrees.resize(minIndex + 1);
			deleteQueue.currentSize = (1 << minIndex) - 1;
			for (int j = minIndex - 1; j >= 0; j--)
			{
				deleteQueue.theTrees[j] = deletedTree;
				deletedTree = deletedTree->nextSibling;
				deleteQueue.theTrees[j]->nextSibling = NULL;
			}

			theTrees[minIndex] = NULL;
			currentSize -= deleteQueue.currentSize + 1;
			
			merge(deleteQueue);
		}

		void makeEmpty();
		void merge(BinomialQueue& rhs)
		{
			if (this == &rhs)
				return;

			currentSize += rhs.currentSize;

			if (currentSize > capacity())
			{
				int oldNumTrees = theTrees.size();
				int newNumTrees = max(theTrees.size(), rhs.theTrees.size()) + 1;
				theTrees.resize(newNumTrees);
				for (int i = oldNumTrees; i < newNumTrees; i++)
					theTrees[i] = NULL;
			}

			BinomialNode* carry = NULL;
			for (int i = 0, j = i; j <= currentSize; i++, j *= 2)
			{
				BinomialNode* t1 = theTrees[i];
				BinomialNode* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : NULL;
				
				int whichcase = t1 == NULL ? 0 : 1;
				whichcase += t2 == NULL ? 0 : 2;
				whichcase += carry == NULL ? 0 : 4;

				switch (whichcase)
				{
				case 0:
				case 1:
					break;
				case 2:
					theTrees[i] = t2;
					rhs.theTrees[i] = NULL;
					break;
				case 4:
					theTrees[i] = carry;
					carry = NULL;
					break;
				case 3:
					carry = comBineTrees(t1, t2);
					theTrees[i] = rhs.theTrees[i] = NULL;
					break;
				case 5:
					carry = comBineTrees(t1, carry);
					theTrees[i] = NULL;
					break;
				case 6:
					carry = comBineTrees(t2, carry);
					rhs.theTrees[i] = NULL;
					break;
				case 7:
					theTrees[i] = carry;
					carry = comBineTrees(t1, t2);
					rhs.theTrees[i] = NULL;
					break;
			
				}
			}
			for (int k = 0; k < rhs.theTrees.size(); k++)
				rhs.theTrees[k] = NULL;
			rhs.currentSize = 0;
		}

		const BinomialQueue& operator=(const BinomialQueue& rhs);

	private:
		struct BinomialNode
		{
			Comparable element;
			BinomialNode *leftChild;
			BinomialNode *nextSibling;

			BinomialNode(const Comparable& theElement, BinomialNode *lt, BinomialNode* rt):element(theElement),leftChild(lt),nextSibling(rt)
			{

			}
		};
		enum{DEFAULT_TREES = 1};

		int currentSize;
		vector<BinomialNode*>theTrees;

		int findMinIndex()const
		{
			int i;
			int minIndex;

			for (i = 0; theTrees[i] == NULL; i++)
			{

			}
			for (minIndex = i; i < theTrees.size(); i++)
				if (theTrees[i] != NULL && theTrees[i]->element < theTrees[minIndex]->element)
					minIndex = i;

			return minIndex;

		}
		int capacity()const
		{
			return theTrees.capacity();
		}
		BinomialNode* comBineTrees(BinomialNode* t1, BinomialNode* t2)
		{
			if (t2->element < t1->element)
				return comBineTrees(t2, t1);
			t2->nextSibling = t1->leftChild;
			t1->leftChild = t2;
			return t1;
		}

		string UnderflowException()
		{
			string s = "This BinaryHeap is empty";
			return s;
		}
		void makeEmpty(BinomialNode* &t);
		BinomialNode* clone(BinomialNode* t)const;
	};
}