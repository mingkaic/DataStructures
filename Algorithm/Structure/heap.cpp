//
//  heap.cpp
//  List
//
//  Created by Mingkai Chen on 2016-02-01.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __HEAP__H

void swap(dynamicArray<T>* arr, size_t index1, size_t index2)
	{
	T buffer = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = buffer;
	}
	
template <class T>
heap<T>::heap() : currSize(0)
	{
	}
	
template <class T>
heap<T>::heap(const heap<T>& src) : currSize(src.currSize)
	{
	treeArr = src.treeArr;
	}
	
template <class T>
heap<T>::~heap()
	{
	}
	
template <class T>
const heap<T>& heap<T>::operator = (const heap<T>& src)
	{
	if (this != &src)
		{
		currSize = src.currSize;
		treeArr = src.treeArr;
		}
	return *this;
	}
	
template <class T>
void heap<T>::insert(T data)
	{
	T buffer;
	size_t c = currSize, p = (c-1)/2;
	treeArr[c] = data;
	while (c > 0 && treeArr[c] < treeArr[p])
		{
		swap(treeArr, c, p);
		c = p;
		p = (c-1)/2;
		}
	currSize++;
	}
	
template <class T>
T heap<T>::extract()
	{
	size_t i = 0, left = 1, right = 2;
	T data = treeArr[i];
	treeArr[i] = treeArr[currSize];
	treeArr[currSize--] = (T) 0;
	while (treeArr[i] < treeArr[left] ||
			treeArr[i] < treeArr[right])
		{
		if (treeArr[left] > treeArr[right])
			{
			swap(treeArr, left, i);
			i = left;
			}
		else
			{
			swap(treeArr, right, i);
			i = right;
			}
		left = 2*i+1;
		right = 2*i+2;
		}
	return data;
	}
	
template <class T>
T heap<T>::peek()
	{
	return treeArr[0];
	}

#endif /* __HEAP__H */