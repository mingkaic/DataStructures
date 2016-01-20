//
//  tuple.hpp
//  List
//
//  Created by Ming Kai Chen on 2014-08-30.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifndef __TUPLE__H
#define __TUPLE__H

template <class K, T>
bool operator == (const tuple<K, T>& left, const tuple<K, T>& right);

template <class K, T>
class tuple
    {
    private:
        K key;
        T data;
    public:
        tuple(K key, T data);
        K getKey();
        T getData();
    };

#endif /* __TUPLE__H */