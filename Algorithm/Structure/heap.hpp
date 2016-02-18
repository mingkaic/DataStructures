//
//  heap.hpp
//  List
//
//  Created by Mingkai Chen on 2016-02-01.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __HEAP__H
#define __HEAP__H

#include "dynamicArr.hpp"
#include "iterator.hpp"
#include "genericHandles.hpp"

// current implementation: min heap
template <class T>
class heap
	{
	private:
		dynamicArr<T> treeArr;
		size_t currSize;
		
		void reheap(size_t index);
	public:
		heap();
		heap(const heap<T>& src);
		~heap();
		const heap<T>& operator = (const heap<T>& src);
		
		void insert(T data);
		T extract();
		T peek();
		
		bool remove(T data, bool (*eqCb)(const T&, const T&) = &genericEquality);
		
		// at the mercy of the user. praise be the lord
		// data is reference. can break heap property
		bool exists(T& data, bool (*eqCb)(const T&, const T&) = &genericEquality);
		// use if re-heaping is necessary
		void modified(T data, bool (*eqCb)(const T&, const T&) = &genericEquality);
	};
	
#include "heap.cpp"

#endif /* __HEAP__H */
