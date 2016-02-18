//
//  biNode.cpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __BI_NODE__H

template <class T>
biNode<T>::biNode(T data) : prev(NULL), next(NULL)
    {
    this->dataInit(data);
    }

template <class T>
biNode<T>::biNode(biNode<T>* prev, T data, biNode<T>* next) :
prev(prev), next(next)
    {
    this->dataInit(data);
    }

template <class T>
void biNode<T>::cascadeDelete()
    {
    biNode<T>* buffer = NULL;
    while (NULL != prev)
        {
        buffer = prev;
        prev = prev->prev;
        delete buffer;
        }
    while (NULL != next)
        {
        buffer = next;
        next = next->next;
        delete buffer;
        }
    delete this;
    }

template <class T>
biNode<T>* biNode<T>::cascadeCopy()
    {
    biNode<T>* copy = new biNode<T>(this->data);
    biNode<T>* buffer = copy;
    for (biNode<T>* src = prev; NULL != src; src = src->prev)
        {
        buffer->prev = new biNode<T>(buffer, src->getData(), NULL);
        buffer = buffer->prev;
        }
    buffer = copy;
    for (biNode<T>* src = next; NULL != src; src = src->next)
        {
        buffer->next = new biNode<T>(NULL, src->getData(), buffer);
        buffer = buffer->next;
        }
    return copy;
    }

#endif /* __BI_NODE__H */