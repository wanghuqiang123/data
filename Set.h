#pragma once
#include "Binarytree.h"
#include <iostream>

using namespace std;

namespace Wanglib
{
	template <typename key>
	class Set
	{
		BinarySreachTree<key>data;
		size_t length;
	public:
		Set() = default;
		Set(const Set<key>& obj)
		{
			data = obj.data;
		}
		Set<key>& operator=(const Set<key>& obj)
		{
			data = obj.data;
			return *this;
		}
		void _print()
		{
			data.printTree();
		}
		void insert(const key& x)
		{
			data.insert(x);
			length++;
		}
		void erase(const key& x)
		{
			data.remove(x);
			length--;
		}
		size_t size()
		{
			return length;
		}
		~Set()
		{

		}
	};
}