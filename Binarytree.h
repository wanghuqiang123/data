#pragma once
#include <iostream>
#include <queue>
using namespace std;
namespace Wanglib 
{
	template<typename Comparable>
	class BinarySreachTree
	{
	public:
		BinarySreachTree()
		{
			root = NULL;
		}
		BinarySreachTree(const BinarySreachTree<Comparable> & rhs)
		{
			this->root = rhs.root;
			this->count = rhs.count;
			++*count;
		}
		BinarySreachTree<Comparable>& operator=(const BinarySreachTree<Comparable>& rhs)
		{
			if (this != &rhs)
			{
				if (this->root != NULL)
				{
					if ((--*count) == 0)
						delete this->root;
					this->root = rhs.root;
					this->count = rhs.count;
					++*count;
				}
				else if(this->root == NULL)
				{
					this->count = rhs.count;
					this->root = rhs.root;
					++*this->root;
				}
			}
		}
		~BinarySreachTree()
		{
			if ((--*count) == 0)
				makeEmpty(this->root);
			root = NULL;
		}

		const Comparable& findMin()const
		{
			BinaryNode* min = findMin(this->root);
			return min->element;
		}
		const Comparable& findMax()const
		{
			BinaryNode* max = findMax(this->root);
			return max->element;
		}
		bool contains(const Comparable& x)const
		{
			return contains(x,root);
		}
		bool isEmpty()const
		{
			return (root == NULL);
		}
		void printTree()const
		{
			cout << "ÖÐÐò±éÀú" << endl;
			queue<Comparable> q;
			if (root == NULL)
			{
				cout << "root is NULL" << endl;
				return;
			}
			
		}
		void makeEmpty();
		void insert(const Comparable & x);
		void remove(const Comparable & x);

	protected:
		struct BinaryNode
		{
			Comparable element;
			BinaryNode *left;
			BinaryNode *right;
			BinaryNode *parent;
			BinaryNode() { left = NULL, right = NULL; parent = NULL; }
			BinaryNode(const Comparable & theElement) {
				element = theElement; left = NULL;
				right = NULL; parent = NULL;
			}
			BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt,
				BinaryNode *pt)
				: element(theElement), left(lt), right(rt), parent(pt) { }
		};
		BinaryNode *root;
		int * count;
	private:
		void insert(const Comparable& x, BinaryNode* &t)const;
		void remove(const Comparable& x, BinaryNode* &t)const;
		BinaryNode* findMin(BinaryNode* t)const;
		BinaryNode* findMax(BinaryNode* t)const;
		bool contains(const Comparable & x, BinaryNode * t)const;
		void makeEmpty(BinaryNode* & t);
		void printTree(BinaryNode* t)const;
		BinaryNode* clone(BinaryNode* t)const;
	};
}