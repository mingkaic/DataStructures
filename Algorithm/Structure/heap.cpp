//
//  heap.cpp
//  List
//
//  Created by Mingkai Chen on 2016-02-01.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __HEAP__H

#include <stdexcept>
#include "dynamicArr.hpp"
#include "genericHandles.hpp"

template <class T>
void swap(dynamicArr<T>* arr, size_t index1, size_t index2)
	{
	T buffer = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = buffer;
	}
	
// assumes treeArr at index violates heap property (min heap in this case)
template <class T>
void heap<T>::reheap(size_t index)
	{
	// bubble up
	for (size_t p = (index-1)/2; index > 0 && treeArr[index] < treeArr[p]; p = (index-1)/2)
		{
		swap(treeArr, p, index);
		index = p;
		}
	// bubble down
	for (size_t left = index*2+1, right = index*2+2;
		treeArr[index] > treeArr[left] || treeArr[index] > treeArr[right];
		left = index*2+1, right = index*2+2)
		{
		if (treeArr[left] < treeArr[right])
			{
			swap(treeArr, left, index);
			index = left;
			}
		else
			{
			swap(treeArr, right, index);
			index = right;
			}
		}
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
	treeArr[currSize++] = data;
	reheap(currSize-1);
	}
	
template <class T>
T heap<T>::extract()
	{
	if (0 == currSize)
		{
        throw std::runtime_error("removing from empty heap"); 
		}
	T data = treeArr[0];
	swap(treeArr, 0, currSize-1);
	g_delete(treeArr[--currSize]);
	reheap(0);
	return data;
	}
	
template <class T>
T heap<T>::peek()
	{
	if (0 == currSize)
		{
        throw std::runtime_error("peeking in empty heap"); 
		}
	return treeArr[0];
	}

template <class T>
bool heap<T>::remove(T data, bool (*eqCb)(const T&, const T&))
	{
	bool dataRemoved = false;
	
	signed i = treeArr.indexOf(data, eqCb);
		
	if (i > 0) // assert that i < currSize
		{
		dataRemoved = true;
		swap(treeArr, i, currSize);
		g_delete(treeArr[--currSize]);
		reheap(i);
		}
	
	return dataRemoved;
	}

template <class T>
bool heap<T>::exists(T& data, bool (*eqCb)(const T&, const T&))
	{
	bool dataFound = false;
	
	signed i = treeArr.indexOf(data, eqCb);
		
	if (i > 0) // assert that i < currSize
		{
		dataFound = true;
		data = treeArr[i];
		}
	
	return dataFound;
	}

template <class T>
void heap<T>::modified(T data, bool (*eqCb)(const T&, const T&))
	{
	signed i = treeArr.indexOf(data, eqCb);
		
	if (i > 0) // assert that i < currSize
		{
		reheap(i);
		}
	}

#endif /* __HEAP__H */