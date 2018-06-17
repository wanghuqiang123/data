#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

namespace Wanglib 
{   
	template<typename T>
	struct Node
	{
		int x, y;
		T element;
	};
	template<typename Comparable>
	class BinarySreachTree
	{
	public:
		BinarySreachTree()
		{
			root = NULL;
			count = new int(1);
		}
		BinarySreachTree(const BinarySreachTree<Comparable> & rhs)
		{
			this->root = rhs.root;
			this->count = rhs.count;
			++*count;
			length = rhs.length;
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
					length = rhs.length;
				}
				else if(this->root == NULL)
				{
					this->count = rhs.count;
					this->root = rhs.root;
					++*this->root;
					length = rhs.length;
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
			if(min != NULL)
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
			printTree(root);
		}
		void makeEmpty()
		{
			makeEmpty(root);
		}
		virtual void insert(const Comparable & x)
		{
			insert(x,root,root);
		}
		void remove(const Comparable & x)
		{
			remove(x,root);
		}
		vector<Node<Comparable>> TreeStorage()
		{
			printTreetoStorage(root);
			return v;
		}
		void DrawLine(Mat &img)
		{
			DrawLine(img,root);
		}
		void print_v()
		{
			for (auto iter = v.begin(); iter != v.end(); iter++)
			{
				cout << "the element is:"<<iter->element << "the (x,y) is:("<<iter->x<<","<<iter->y<<")"<<endl;
			}
		}
	protected:
		struct BinaryNode
		{
			Comparable element;
			BinaryNode *left;
			BinaryNode *right;
			BinaryNode *parent;
			int x;
			int y;
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
		vector<Node<Comparable>>v;
	private:
		void insert(const Comparable& x, BinaryNode* &t,BinaryNode* parent)const
		{
			if (t == NULL)
				t = new BinaryNode(x,NULL,NULL,parent);
			else if (x < t->element)
				insert(x, t->left,t);
			else if (x > t->element)
				insert(x, t->right,t);
			
		}
		void remove(const Comparable& x, BinaryNode* &t)const  //这里与上上层节点相关；
		{
			if (t == NULL)
				return;
			if (x < t->element)
				remove(x, t->left);
			else if (x > t->element)
				remove(x, t->right);
			else if ((t->left != NULL) && (t->right != NULL))
			{
				t->element = findMin(t->right)->element;
				remove(t->element, t->right);
			}
			else
			{
				BinaryNode* oldNode = t;
				t = (t->left != NULL) ? t->left : t->right;
				delete oldNode;
			}
			
		}
		BinaryNode* findMin(BinaryNode* t)const
		{
			if (t == NULL)
				return NULL;
			if (t->left == NULL)
				return t;
			return findMin(t->left);
		}
		BinaryNode* findMax(BinaryNode* t)const
		{
			if (t == NULL)
				return NULL;
			while (t->right != NULL)
			{
				t = t->right;
			}
			return t;
		}
		bool contains(const Comparable & x, BinaryNode * t)const
		{
			if (t == NULL)
				return false;
			else if (x < t->element)
				return contains(x, t->left);
			else if (x > t->element)
				return contains(x, t->right);
			else
				return true;
		}
		void makeEmpty(BinaryNode* & t)
		{
			if (t != NULL)
			{
				makeEmpty(t->left);
				makeEmpty(t->right);
				delete t;
			}
			t = NULL;
		}
		void printTree(BinaryNode* t)const
		{
			if (t != NULL)
			{
				printTree(t->left);
				cout << t->element << endl;
				printTree(t->right);
			}
		}
		void printTreetoStorage(BinaryNode* t) //从最小的最底层的节点开始利用中序遍历向上存储各节点的值以及坐标
		{
			if (t != NULL)
			{
				printTreetoStorage(t->left);
				add(t);
				printTreetoStorage(t->right);
			}
		}
		void add(BinaryNode* t)
		{
			static int w = 0;
			Node<Comparable>N;
			N.x = w + 10;
			t->x = N.x;
			w += 20;
			N.y = depth(t)*40;
			t->y = N.y;
			N.element = t->element;
			v.push_back(N);
		}
		int depth(BinaryNode* t)
		{
			if (t->element == root->element)
				return 1;
			else
				return 1 + depth(t->parent);
		}
		void DrawLine(Mat& img,BinaryNode* t)
		{
			deque<BinaryNode*>q;
			BinaryNode* p = t;
			if (p)
				q.push_back(p);
			putText(img, to_string(p->element), Point(p->x+3, p->y), FONT_HERSHEY_PLAIN, 1, Scalar(255, 100, 100));
			while (!q.empty())
			{
				p = q.front();
				q.pop_front();
				if (p->left != NULL)
				{
					line(img, Point(p->x, p->y), Point(p->left->x, p->left->y), Scalar(0, 255, 0), 2, 8);
					putText(img,to_string(p->left->element), Point(p->left->x+3, p->left->y), FONT_HERSHEY_PLAIN,1,Scalar(255, 100, 100));
					q.push_back(p->left);
				}
				if (p->right != NULL)
				{
					line(img, Point(p->x, p->y), Point(p->right->x, p->right->y), Scalar(0, 255, 0), 2, 8);
					putText(img, to_string(p->right->element), Point(p->right->x+3, p->right->y), FONT_HERSHEY_PLAIN, 1, Scalar(255, 100, 100));
					q.push_back(p->right);
				}
			}
		}
		//BinaryNode* clone(BinaryNode* t)const;
	};
	template <typename T>
	bool DrawTree(BinarySreachTree<T>& B, Mat &img)
	{
		bool ret = false;
		vector<Node<T>>v;
		v = B.TreeStorage();
		if (v.size() != 0)
		{
			ret = true;
		}
		auto iter1 = v.begin();
		for(auto iter = v.begin();iter != v.end();iter++)
		{
			circle(img, Point(iter->x, iter->y),5 ,Scalar(0, 0, 255), -1, 8);
			/*iter1 = iter;
			iter1++;
			if (iter1 != v.end())
			{
				line(img, Point(iter->x, iter->y), Point(iter1->x, iter1->y), Scalar(0, 255, 0), 2, 8); 
			}*/
		}
		B.DrawLine(img);
		return ret;
	}
	
}