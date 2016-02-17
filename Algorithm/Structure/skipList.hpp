//
//  skipList.hpp
//  List
//
//  Created by Mingkai Chen on 2016-02-02.
//
//

#ifndef __SKIP_LIST__H
#define __SKIP_LIST__H

#include "node.hpp"

template <class T>
class skipNode : public node<T>
	{
	private:
		skipNode(T data, size_t height);
		void seriesConnection(skipNode<T>* series);
	public:
		skipNode<T>** nexts;
		size_t height;
	
		skipNode(T data);
		skipNode(T data, skipNode<T>* series);
		~skipNode();
		
		void cascadeDelete();
		skipNode<T>* cascadeCopy();
	};
	
template <class T>
class skipList
	{
	private:
		skipNode<T>* head;
	public:
		skipList();
		skipList(const skipList<T>& src);
		~skipList();
		skipList<T>& operator = (const skipList<T>& src);
		
		bool insert(T data);
		bool remove(T data);
		bool search(T data);
		T operator [] (size_t index);
	};

#include "skipList.cpp"

#endif /* __SKIP_LIST__H */
