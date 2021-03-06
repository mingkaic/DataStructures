//
//  priorityContainer.cpp
//  dataContainer
//
//  Created by Ming Kai Chen on 2015-09-30.
//  Copyright (c) 2015 Ming Kai Chen. All rights reserved.
//

#ifdef __PRIORITY__H

#include <cstdlib>

template <class T>
priorityContainer<T>::priorityContainer(T content) : content(content)
    {
    priority = rand();
    }

template <class T>
priorityContainer<T>::priorityContainer(T content, size_t priority) : content(content), priority(priority)
    {
    }

template <class T>
priorityContainer<T>::priorityContainer(const priorityContainer<T>& src) : content(src.content), priority(src.priority)
    {
    }

template <class T>
priorityContainer<T>::~priorityContainer()
    {
    }

template <class T>
priorityContainer<T>& priorityContainer<T>::operator = (const priorityContainer<T>& src)
    {
	if (this != &src)
		{
        content = src.content;
        priority = src.priority;
		}
	return *this;
    }

template <class T>
T& priorityContainer<T>::getContent()
    {
    return content;
    }
        
template <class T>
size_t priorityContainer<T>::getPriority()
    {
    return priority;
    }
    
template <class T>
bool operator == (const priorityContainer<T>& left, const priorityContainer<T>& right)
    {
    return left.priority == right.priority;
    }

template <class T>
bool operator == (const T& left, const priorityContainer<T>& right)
    {
    return left == right.content;
    }
    
template <class T>
bool operator == (const priorityContainer<T>& left, const T& right)
    {
    return left.content == right;
    }

template <class T>
bool operator != (const priorityContainer<T>& left, const priorityContainer<T>& right)
    {
    return left.priority != right.priority;
    }

template <class T>
bool operator != (const T& left, const priorityContainer<T>& right)
    {
    return left != right.content;
    }
    
template <class T>
bool operator != (const priorityContainer<T>& left, const T& right)
    {
    return left.content != right;
    }

template <class T>
bool operator > (const priorityContainer<T>& left, const priorityContainer<T>& right)
    {
    return left.priority > right.priority;
    }

template <class T>
bool operator < (const priorityContainer<T>& left, const priorityContainer<T>& right)
    {
    return left.priority < right.priority;
    }

#endif /* __PRIORITY__H */