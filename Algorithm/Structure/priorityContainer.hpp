//
//  priorityContainer.hpp
//  dataContainer
//
//  Created by Ming Kai Chen on 2015-09-30.
//  Copyright (c) 2015 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __PRIORITY__H
#define __PRIORITY__H

template <class T>
class priorityContainer
    {
    private:
        size_t priority;
        T content;
    public:
        priorityContainer(T content);
        priorityContainer(T content, size_t priority);
        priorityContainer(const priorityContainer<T>& src);
        ~priorityContainer();
        priorityContainer<T>& operator = (const priorityContainer<T>& src);
        
        T& getContent();
        size_t getPriority();
    };
    
template <class T>
bool operator == (const priorityContainer<T>& left, const priorityContainer<T>& right);

template <class T>
bool operator == (const T& left, const priorityContainer<T>& right);

template <class T>
bool operator == (const priorityContainer<T>& left, const T& right);

template <class T>
bool operator != (const priorityContainer<T>& left, const priorityContainer<T>& right);

template <class T>
bool operator != (const T& left, const priorityContainer<T>& right);

template <class T>
bool operator != (const priorityContainer<T>& left, const T& right);

template <class T>
bool operator > (const priorityContainer<T>& left, const priorityContainer<T>& right);

template <class T>
bool operator < (const priorityContainer<T>& left, const priorityContainer<T>& right);

#include "priorityContainer.cpp"

#endif /* __PRIORITY__H */