//
//  listNode.cpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __LIST_NODE__H

template <class T>
listNode<T>::listNode(T data) : next(NULL)
    {
    dataInit(data);
    }

template <class T>
listNode<T>::listNode(T data, listNode<T>* next) : next(next)
    {
    dataInit(data);
    }

template <class T>
void listNode<T>::cascadeDelete()
    {
    if (NULL != next)
        {
        next->cascadeDelete();
        }
    delete this;
    }

template <class T>
listNode<T>* listNode<T>::cascadeCopy()
    {
    listNode<T>* copy = new listNode<T>(data);
    listNode<T>* buffer = copy;
    for (listNode<T>* src = next; NULL != src; src = src->next)
        {
        buffer->next = new listNode<T>(src->getData());
        buffer = buffer->buffer;
        }
    return copy;
    }

#endif /* __LIST_NODE__H */