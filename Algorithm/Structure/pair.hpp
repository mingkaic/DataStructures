//
//  pair.hpp
//  dataContainer
//
//  Created by Ming Kai Chen on 2014-08-30.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __PAIR__H
#define __PAIR__H

#include <cstdlib>

template <class K, class T>
class pair
    {
    private:
        K key;
        T data;
    public:
        pair(K key); // used for key checking
        pair(K key, T data);
        pair(const pair<K,T>& src);
        ~pair();
        pair<K,T>& operator = (const pair<K,T>& src);
        
        K getKey();
        K& getKeyRef();
        T getData();
        T& getDataRef();
    };

template <class K, class T>
bool operator == (const pair<K, T>& left, const pair<K, T>& right);

template <class K, class T>
bool operator == (const K& left, const pair<K, T>& right);

template <class K, class T>
bool operator == (const pair<K, T>& left, const K& right);

template <class K, class T>
bool operator != (const pair<K, T>& left, const pair<K, T>& right);

template <class K, class T>
bool operator != (const K& left, const pair<K, T>& right);

template <class K, class T>
bool operator != (const pair<K, T>& left, const K& right);

template <class K, class T>
bool operator > (const pair<K, T>& left, const pair<K, T>& right);

template <class K, class T>
bool operator < (const pair<K, T>& left, const pair<K, T>& right);
    
#include "pair.cpp"

#endif /* __PAIR__H */