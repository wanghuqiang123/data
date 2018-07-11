#pragma once
#include <iostream>
using namespace std;

namespace Wanglib
{
	template<typename Comparable>
	class LeftistHeap   //利用类指针的拷贝形式
	{
	public:
		LeftistHeap()
		{
			root = NULL;
			count = new int(1);
		}
		LeftistHeap(const LeftistHeap& rhs)
		{
			delete count;
			count = rhs.count;
			root = rhs.root;
			++*count;
		}
		LeftistHeap& operator=(const LeftistHeap& rhs)  
		{
			if (--*count == 0)
			{
				makeEmpty();
				delete count;
			}
			count = rhs.count;
			root = rhs.root;
			++*count;

			return *this;
		}
		
		bool isEmpty()const
		{
			bool ret = false;
			if (root == NULL)
				ret = true;
			return ret;
		}
		const Comparable& findMin()const
		{
			return root->element;
		}

		void insert(const Comparable& x)
		{
			root = merge(new LeftistNode(x), root);
		}
		void deleteMin()
		{
			if (isEmpty())
				throw UnderflowException();

			LeftistNode* oldRoot = root;
			root = merge(root->left, root->right);
			delete oldRoot;
		}
		void makeEmpty()
		{
			while(root != NULL)
			{
				deleteMin();
			}
		}
		void merge(LeftistHeap& rhs)
		{
			if (rhs != this)
				return;
			root = merge(root, rhs.root);
			rhs.root = NULL;
		}
		~LeftistHeap()
		{
			if ((--*count) == 0)
			{
				makeEmpty();  //because tree root is new() , every node is create by computer memory heap ,so we must take makeEmpty() function delete every Node;
				delete count;
			}
		}
	private:
		struct LeftistNode
		{
			Comparable element;
			LeftistNode * left;
			LeftistNode * right;
			int npl;

			LeftistNode(const Comparable & theElement, LeftistNode* lt = NULL, LeftistNode *rt = NULL, int np = 0)
				:element(theElement), left(lt), right(rt), npl(np) { }
		};
			LeftistNode *root;
			int *count;

			LeftistNode* merge(LeftistNode* h1, LeftistNode* h2)
			{
				if (h1 == NULL)
					return h2;
				if (h2 == NULL)
					return h1;
				if (h1->element < h2->element)   //判断谁的数值小谁就作为根节点
					return merge1(h1, h2);
				else
					return merge1(h2, h1);
			}
			//trees are not empty,and h1's root contains smallest item.
			LeftistNode* merge1(LeftistNode* h1, LeftistNode* h2)
			{
				if (h1->left == NULL)
					h1->left = h2;     //先往左边插
				else
				{
					h1->right = merge(h1->right, h2);
					if (h1->left->npl < h1->right->npl)
						swapChildren(h1);
					h1->npl = h1->right->npl + 1;
				}
				return h1;
			}
			void swapChildren(LeftistNode* t)
			{
				LeftistNode* temp = t->right;
				t->right = t->left;
				t->left = temp;
				temp = NULL;
			}
			void reclaimMemory(LeftistNode *t)
			{			
			}
			LeftistNode* clone(LeftistNode* t)const
			{
			}
			string UnderflowException()
			{
				string s = "Trees is Empty";
				return s;
			}
	};
}