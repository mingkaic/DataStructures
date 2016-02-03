//
//  heap.hpp
//  List
//
//  Created by Mingkai Chen on 2016-02-01.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifndef __HEAP__H
#define __HEAP__H

#include "dynamicArray.hpp"

template <class T>
class heap
	{
	private:
		dynamicArray<T> treeArr;
		size_t currSize;
	public:
		heap();
		heap(const heap<T>& src);
		~heap();
		const heap<T>& operator = (const heap<T>& src);
		
		void insert(T data);
		T extract();
		T peek();
	}
    
#include "heap.cpp"

#endif /* __HEAP__H */
