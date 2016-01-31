//
//  searchList.hpp
//  List
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

ifndef __SEARCH_LIST__H
#define __SEARCH_LIST__H

#include "stack.hpp"

template <class T>
class searchList : public stack
    {
    public:
        searchList();
        searchList(const searchList& src);
        virtual ~searchList();
        searchList<T>& operator = (const searchList<T>& src);
        
        signed search(T elem); // find and return the index of the node containing elem -1 if not found
        void nInsert(T elem, size_t N);
        T nRemove(size_t N);
        T nPeek(size_t N);
        bool nReplace(T elem, size_t N);
        
        size_t size() const;
    }

#endif /* __SEARCH_LIST__H */