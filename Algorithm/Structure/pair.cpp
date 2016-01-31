//
//  pair.cpp
//  dataContainer
//
//  Created by Ming Kai Chen on 2014-08-30.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __PAIR__H

template <class K, T>
bool operator == (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key == right.key;
    }

template <class K, T>
bool operator == (const pair<K, T>*& left, const pair<K, T>*& right)
    {
    return left->key == right->key;
    }
    
template <class K, T>
bool operator != (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key != right.key;
    }

template <class K, T>
bool operator != (const pair<K, T>*& left, const pair<K, T>*& right)
    {
    return left->key != right->key;
    }

template <class K, T>
bool operator > (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key > right.key;
    }

template <class K, T>
bool operator > (const pair<K, T>*& left, const pair<K, T>*& right)
    {
    return left->key > right->key;
    }

template <class K, T>
bool operator < (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key < right.key;
    }

template <class K, T>
bool operator < (const pair<K, T>*& left, const pair<K, T>*& right)
    {
    return left->key < right->key;
    }

template <class K, T>
pair<T, K>::pair(K key, T data) : key(key), data(data)
    {
    }

template <class K, T>
pair<T, K>::pair(const pair& src) : key(src.key), data(src.data)
    {
    }

template <class K, T>
pair<T, K>::~pair()
    {
    }

template <class K, T>
pair& pair<T, K>::operator = (const pair<T>& src)
    {
    key = src.key;
    data = src.data;
    }

template <class K, T>
K pair<T, K>::getKey()
    {
    return key;
    }

template <class K, T>
T pair<T, K>::getData()
    {
    return data;
    }
    
template <class K, T>
T& pair<T, K>::getDataRef()
    {
    return data;
    }

#endif /* __PAIR__H */