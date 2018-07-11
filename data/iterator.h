#pragma once
#include <iostream>
#include "Binarytree.h"
using namespace std;
using namespace Wanglib;
namespace Wanglib
{
	template <typename Comparable>
	class const_iterator:public BinarySreachTree<Comparable>
	{
	public:
		const_iterator() : current(NULL)
		{ }
		const Comparable & operator* () const
		{
			return retrieve();
		}
		const_iterator & operator++ ()
		{
			BinaryNode<Comparable> *t;
			if (current->right)
			{
				t = current->right;
				while (t->left != NULL)
					t = t->left;
				current = t;
			}
			else
			{
				t = current->parent;
				cout << "first parent is " << t->element << endl;
				while (t && t->element < current->element)
					t = t->parent;
				current = t;
			}
			return *this;
		}
		const_iterator operator++ (int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}
		bool operator== (const const_iterator & rhs) const
		{
			return current == rhs.current;
		}
		bool operator!= (const const_iterator & rhs) const
		{
			return !(*this == rhs);
		}
	protected:
		BinaryNode *current;
		Comparable & retrieve() const
		{
			return current->element;
		}
		const_iterator(BinaryNode *p) : current(p)
		{ }
		
	};

	template<typename Comparable>
	class iterator : public const_iterator<Comparable>
	{
	public:
		iterator()
		{ }
		Comparable & operator* ()
		{
			return const_iterator::retrieve();
		}
		const Comparable & operator* () const
		{
			return const_iterator ::operator*();
		}
		iterator & operator++ ()
		{
			BinaryNode<Comparable> *t;
			if (current->right)
			{
				t = current->right;
				while (t->left != NULL)
					t = t->left;
				current = t;
			}
			else
			{
				t = current->parent;
				cout << "first parent is " << t->element << endl;
				while (t && t->element < current->element)
					t = t->parent;
				current = t;
			}
			return *this;
		}
		iterator operator++ (int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}
		iterator(BinaryNode<Comparable> *p) : const_iterator(p)
		{ }
		friend class Set;
	};

	//This is the public insert
	template <typename Comparable>
	iterator insert(const Comparable & x) {
		Size++;
		return insert(x, root, root);
	}
	// This is private
	template <typename Comparable>
	iterator insert(const Comparable & x,
		BinaryNode<Comparable> * & t,
		BinaryNode<Comparable> * p) //parent node
	{
		if (t == NULL)
		{
			t = new BinaryNode<Comparable>(x, NULL, NULL, p);
			return iterator(t);
		}
		else if (x < t->element)
			return (insert(x, t->left, t));
		else if (t->element < x)
			return(insert(x, t->right, t));
		return iterator(t);
	}
	template <typename Comparable>
	// This is the public begin (aka minimum element)
	iterator begin()
	{
		BinaryNode<Comparable> *t = root;
		while (t->left)
			t = t->left;
		return iterator(t);
	}

}