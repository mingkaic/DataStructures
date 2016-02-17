//
//  hashheap.cpp
//  hybrid
//
//  Created by Ming Kai Chen on 2016-01-30.
//  Copyright (c) 2016 Ming Kai Chen. All rights reserved.
//

#ifdef __HASH_HEAP__H

#include <string>

static const size_t ASCII_SIZE = 256;

static size_t nearestPrime(size_t optimus)
    {
    if (optimus == 2)
        return 2;
    else if (0 == optimus % 2)
        optimus++;
    while (!isPrime(optimus++))
        {
        optimus++;
        }
    return optimus;
    }

static bool isPrime(size_t n)
    {
    for (size_t i = 3; i < n/2; i += 2)
        {
        if (0 == n % i)
            {
            return false;
            }
        }
    return true;
    }

template <class T>
size_t hashheap<T>::::hashFunction(std::string str) const
    {
    // string to index conversion
	size_t index = 0;
    size_t key = 0;
    
    for (size_t i = 0; i <= str.size(); i++)
        {
        key = (size_t)str[i];
        
	    index = (index*ASCII_SIZE+key)%N;
        }
    
    return index;
    }

template <class T>
hashheap<T>::hashheap() : numBuckets(101), N(0)
    {
    dictionary = new heap<pair<std::string, T>>[numBuckets];
    }

template <class T>
hashheap<T>::hashheap(size_t intendedSize) : curSize(0)
    {
    numBuckets = nearestPrime((int)2*intendedSize);
    dictionary = new heap<pair<std::string, T>>[numBuckets];
    }

template <class T>
hashheap<T>::hashheap(const hashheap<T>& src) : numBuckets(src.numBuckets), curSize(src.curSize)
    {
    dictionary = new heap<pair<std::string, T>>[numBuckets];
    copy(src.dictionary);
    }

template <class T>
hashheap<T>::~hashheap()
    {
    }

template <class T>
hashheap<T>& hashheap<T>::operator = (const hashheap<T>& src)
    {
    }

template <class T>
T& hashheap<T>::operator [] (std::string key)
    {
    }

template <class T>
bool hashheap<T>::insert(std::string, T data);

template <class T>
bool hashheap<T>::remove(std::string);

template <class T>
bool hashheap<T>::search(std::string, T& data) const;

template <class T>
std::string hashheap<T>::priorityRemove();

#endif /* __HASH_HEAP__H */