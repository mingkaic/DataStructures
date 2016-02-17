//
//  pair.cpp
//  dataContainer
//
//  Created by Ming Kai Chen on 2014-08-30.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __PAIR__H

template <class K, class T>
bool operator == (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key == right.key;
    }

template <class K, class T>
bool operator == (const pair<K, T>*& left, const pair<K, T>*& right)
    {
    return left->key == right->key;
    }
    
template <class K, class T>
bool operator != (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key != right.key;
    }

template <class K, class T>
bool operator != (const pair<K, T>*& left, const pair<K, T>*& right)
    {
    return left->key != right->key;
    }

template <class K, class T>
bool operator > (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key > right.key;
    }

template <class K, class T>
bool operator > (const pair<K, T>*& left, const pair<K, T>*& right)
    {
    bool bigLeft = false;
    if (NULL == right)
        {
        bigLeft = true;
        }
    else if (NULL != left)
        {
        bigLeft = left->key > right->key;
        }
    return bigLeft;
    }

template <class K, class T>
bool operator < (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key < right.key;
    }

template <class K, class T>
bool operator < (const pair<K, T>*& left, const pair<K, T>*& right)
    {
    bool smallLeft = true;
    if (NULL == right)
        {
        smallLeft = false;
        }
    else if (NULL != left)
        {
        smallLeft = left->key < right->key;
        }
    return smallLeft;
    }

template <class K, class T>
pair<K, T>::pair(K key, T data) : key(key), data(data)
    {
    }

template <class K, class T>
pair<K, T>::pair(const pair<K, T>& src) : key(src.key), data(src.data)
    {
    }

template <class K, class T>
pair<K, T>::~pair()
    {
    }

template <class K, class T>
pair<K, T>& pair<K, T>::operator = (const pair<K, T>& src)
    {
    key = src.key;
    data = src.data;
    }

template <class K, class T>
K pair<K, T>::getKey()
    {
    return key;
    }

template <class K, class T>
T pair<K, T>::getData()
    {
    return data;
    }
    
template <class K, class T>
T& pair<K, T>::getDataRef()
    {
    return data;
    }

#endif /* __PAIR__H */