//
//  dynamicArr.hpp
//  Array
//
//  Created by Ming Kai Chen on 2014-05-09.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __DYNAMIC_ARR__H
#define __DYNAMIC_ARR__H

#include <cstring>
#include "genericHandles.hpp"

template <class T>
class dynamicArr
    {    
    private:
        T* array;
        size_t allocSize;
        void dynamicSize(size_t expand = 2); // handles the checking and expansion of the array
    public:
        dynamicArr();
        dynamicArr(const dynamicArr<T>& src);
        ~dynamicArr();
        dynamicArr<T>& operator = (const dynamicArr<T>& src);

        T& operator [] (size_t index);

        signed indexOf(T elem, bool (*eqCb)(const T&, const T&) = &genericEquality) const;
    };
    
#include "dynamicArr.cpp"

#endif /* __DYNAMIC_ARR__H */
