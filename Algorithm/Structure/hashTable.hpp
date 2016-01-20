//
//  hashTable.hpp
//  List
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifndef __HASH_TABLE__H
#define __HASH_TABLE__H

#include "tuple.hpp"
#include "listNode.hpp"
#include <cstring>

template <class T>
class hashTable
    {
    private:
        listNode<tuple<std::string, T>>** dictionary;
        size_t curSize;
        size_t maxSize;
        
        size_t nearestPrime(int n);
        bool isPrime(int n);
        void copy(listNode<tuple<std::string, T>>* arr);
        size_t hashFunction(std::string str) const;
    public:
        hashTable();
        hashTable(size_t intendedSize);
        hashTable(const hashTable<T>& src);
        ~hashTable();
        hashTable& operator = (const hashTable<T>& src);

        bool insert(std::string);
        bool remove(std::string);
        bool search(std::string) const;
        size_t size() const;
        size_t maxSize() const;
        double loadFactor() const;
        
        std::vector<std::string> intersection(const hashTable<T>& src) const;
        std::vector<std::string> unions(const hashTable<T>& src) const;
        std::vector<std::string> difference(const hashTable<T>& src) const;
    };

#include "hashTable.cpp

#endif /* __HASH_TABLE__H */
