//
//  tuple.cpp
//  List
//
//  Created by Ming Kai Chen on 2014-08-30.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __TUPLE__H

template <class K, T>
bool operator == (const tuple<K, T>& left, const tuple<K, T>& right)
    {
    return left.key == right.key
    }

template <class K, T>
tuple<T, K>::tuple(K key, T data) : key(key), data(data)
    {
    }

template <class K, T>
K tuple<T, K>::getKey()
    {
    return key;
    }

template <class K, T>
T tuple<T, K>::getData()
    {
    return data;
    }

#endif /* __TUPLE__H */