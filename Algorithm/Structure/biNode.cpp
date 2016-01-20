//
//  biNode.cpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __BI_NODE__H

template <class T>
biNode<T>::biNode(T data) :
left(NULL), right(NULL)
    {
    this->dataInit(data);
    }

template <class T>
biNode<T>::biNode(biNode<T>* left, T data, biNode<T>* right) :
left(left), right(right)
    {
    this->dataInit(data);
    }

template <class T>
void biNode<T>::cascadeDelete()
    {
    biNode<T>* buffer = NULL;
    while (NULL != left)
        {
        buffer = left;
        left = left->left;
        delete buffer;
        }
    while (NULL != right)
        {
        buffer = right;
        right = right->right;
        delete buffer;
        }
    delete this;
    }

template <class T>
biNode<T>* biNode<T>::cascadeCopy()
    {
    biNode<T>* copy = new biNode<T>(this->data);
    biNode<T>* buffer = copy;
    for (biNode<T>* src = left; NULL != src; src = src->left)
        {
        buffer->left = new biNode<T>(buffer, src->getData(), NULL);
        buffer = buffer->left;
        }
    buffer = copy;
    for (biNode<T>* src = right; NULL != src; src = src->right)
        {
        buffer->right = new biNode<T>(NULL, src->getData(), buffer);
        buffer = buffer->right;
        }
    return copy;
    }

#endif /* __BI_NODE__H */