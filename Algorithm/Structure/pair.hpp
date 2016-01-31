//
//  pair.hpp
//  dataContainer
//
//  Created by Ming Kai Chen on 2014-08-30.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifndef __PAIR__H
#define __PAIR__H

template <class K, T>
bool operator == (const pair<K, T>& left, const pair<K, T>& right);

template <class K, T>
bool operator != (const pair<K, T>& left, const pair<K, T>& right);

template <class K, T>
bool operator > (const pair<K, T>& left, const pair<K, T>& right);

template <class K, T>
bool operator < (const pair<K, T>& left, const pair<K, T>& right);

template <class K, T>
bool operator == (const pair<K, T>*& left, const pair<K, T>*& right);

template <class K, T>
bool operator != (const pair<K, T>*& left, const pair<K, T>*& right);

template <class K, T>
bool operator > (const pair<K, T>*& left, const pair<K, T>*& right);

template <class K, T>
bool operator < (const pair<K, T>*& left, const pair<K, T>*& right);

template <class K, T>
class pair
    {
    private:
        K key;
        T data;
    public:
        pair(K key, T data);
        pair(const pair& src);
        ~pair();
        pair& operator = (const pair<T>& src);
        
        K getKey();
        T getData();
        T& getDataRef();
    };
    
#include "pair.cpp"

#endif /* __PAIR__H */