//
//  hashheap.hpp
//  hybrid
//
//  Created by Ming Kai Chen on 2016-01-30.
//  Copyright (c) 2016 Ming Kai Chen. All rights reserved.
//

#ifndef __HASH_HEAP__H
#define __HASH_HEAP__H

#include <cstring>
#include "heap.hpp"
#include "pair.hpp"

template <class T>
class hashheap
    {
    private:
        heap<pair<std::string, T>>* dictionary;
        size_t numBuckets;
        size_t N;
        
        size_t hashFunction(std::string str) const;
    public:
        hashheap();
        hashheap(size_t intendedSize);
        hashheap(const hashheap<T>& src);
        ~hashheap();
        hashheap<T>& operator = (const hashheap<T>& src);
        
        T& operator [] (std::string key);
        
        bool insert(std::string, T data);
        bool remove(std::string);
        bool search(std::string, T& data) const;
        std::string priorityRemove();
    };

#include "hashheap.cpp"

#endif /* __HASH_HEAP__H */