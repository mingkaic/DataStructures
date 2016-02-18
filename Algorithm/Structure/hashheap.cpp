//
//  hashheap.cpp
//  hybrid
//
//  Created by Ming Kai Chen on 2016-01-30.
//  Copyright (c) 2016 Ming Kai Chen. All rights reserved.
//

#ifdef __HASH_HEAP__H

#include <stdexcept>
#include <string>
#include "pair.hpp"
#include "priorityContainer.hpp"

static const size_t ASCII_SIZE = 256;

template <class T>
static bool contentEquality(const priorityContainer<pair<std::string, T> >& left,
                    const priorityContainer<pair<std::string, T> >& right)
    {
    return left.getContent().getDataRef() == right.getContent().getDataRef();
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

template <class T>
size_t hashheap<T>::hashFunction(std::string str) const
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
    dictionary = new heap<priorityContainer<pair<std::string, T> > >[numBuckets];
    }

template <class T>
hashheap<T>::hashheap(size_t intendedSize) : N(0)
    {
    numBuckets = nearestPrime((int)2*intendedSize);
    dictionary = new heap<priorityContainer<pair<std::string, T> > >[numBuckets];
    }

template <class T>
hashheap<T>::hashheap(const hashheap<T>& src) : numBuckets(src.numBuckets), N(src.N)
    {
    dictionary = new heap<priorityContainer<pair<std::string, T> > >[numBuckets];
    for (size_t i = 0; i < src.numBuckets; i++)
        {
        dictionary[i] = src.dictionary[i];
        }
    }

template <class T>
hashheap<T>::~hashheap()
    {
    delete[] dictionary;
    }

template <class T>
hashheap<T>& hashheap<T>::operator = (const hashheap<T>& src)
    {
    if (this != &src)
        {
        N = src.N;
        numBuckets = src.numBuckets;

        delete[] dictionary;
            
        dictionary = new heap<priorityContainer<pair<std::string, T> > >[numBuckets];
        for (size_t i = 0; i < src.numBuckets; i++)
            {
            dictionary[i] = src.dictionary[i];
            }
        }
    
    return *this;
    }

template <class T>
T& hashheap<T>::operator [] (std::string key)
    {
    size_t hashIndex = hashFunction(key);
    pair<std::string, T> p(key);
    priorityContainer<pair<std::string, T> > pri(p);
    if (true == dictionary[hashIndex].exists(pri, &contentEquality))
        {
        return pri.getContent().getDataRef();
        }
    dictionary[hashIndex].insert(pri);
    return p.getDataRef();
    }

template <class T>
bool hashheap<T>::insert(std::string key, T data)
    {
    bool uniqueKey = false;
    size_t hashIndex = hashFunction(key);
    pair<std::string, T> p(key, data);
    priorityContainer<pair<std::string, T> > pri(p);
    if (false == dictionary[hashIndex].exists(pri, &contentEquality))
        {
        uniqueKey = true;
        dictionary[hashIndex].insert(pri);
        }
    else
        {
        // overwrite data : no change to priority (heap is good)
        pri.getContent().getDataRef() = data;
        }
    return uniqueKey;
    }

template <class T>
bool hashheap<T>::remove(std::string key)
    {
    size_t hashIndex = hashFunction(key);
    pair<std::string, T> p(key);
    priorityContainer<pair<std::string, T> > pri(p);
    return dictionary[hashIndex].remove(pri, &contentEquality);
    }

template <class T>
bool hashheap<T>::search(std::string key, T& data) const
    {
    size_t hashIndex = hashFunction(key);
    pair<std::string, T> p(key, data);
    priorityContainer<pair<std::string, T> > pri(p);
    bool existence = dictionary[hashIndex].exists(pri, &contentEquality);
    data = pri.getContent().getData();
    return existence;
    }

template <class T>
std::string hashheap<T>::priorityRemove() // remove min priority
    {
    size_t min_priority = -1,
        cur_priority;
    signed min_index = -1;
    for (size_t i = 0; i < numBuckets; i++)
        {
        try
            {
            cur_priority = dictionary[i].peek().getPriority();
            
            if (cur_priority < min_priority)
                {
                min_priority = cur_priority;
                min_index = i;
                }
            }
        catch (const std::exception& e)
            {
            }
        }
    if (min_index < 0)
        {
        throw std::runtime_error("hashmap is empty");
        }
    return dictionary[min_index].extract().getContent.getKey();
    }

#endif /* __HASH_HEAP__H */