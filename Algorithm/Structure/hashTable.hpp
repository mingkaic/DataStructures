//
//  hashTable.hpp
//  List
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifndef __HASH_TABLE__H
#define __HASH_TABLE__H

#include "pair.hpp"
#include "searchList.hpp"
#include <cstring>
#include <vector>

template <class T>
class hashTable
    {
    private:
        searchList<pair<std::string, T>*>* dictionary;
        size_t curSize;
        size_t indexSize;
        
        size_t nearestPrime(int n);
        bool isPrime(int n);
        void copy(searchList<pair<std::string, T>*>* srcDict);
        size_t hashFunction(std::string str) const;
    public:
        hashTable();
        hashTable(size_t intendedSize);
        hashTable(const hashTable<T>& src);
        ~hashTable();
        hashTable& operator = (const hashTable<T>& src);
        
        T& operator [] (std::string key);

        bool insert(std::string, T data);
        bool remove(std::string);
        bool search(std::string, T& data) const;
        size_t numInserted() const;
        size_t numSlot() const;
        double loadFactor() const;
        
        // returns vectors of keys
        std::vector<std::string> hashIntersect(const hashTable<T>& src) const;
        std::vector<std::string> hashUnion(const hashTable<T>& src) const;
        std::vector<std::string> hashDifference(const hashTable<T>& src) const;
    };

#include "hashTable.cpp

#endif /* __HASH_TABLE__H */
