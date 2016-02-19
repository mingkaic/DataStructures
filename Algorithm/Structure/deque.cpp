//
//  deque.cpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __DEQUE__H

#include <stdexcept>

template <class T>
deque<T>::deque()
    {
    this->head = this->tail = NULL;
    }

template <class T>
deque<T>::deque(const deque& src) : queue<T>(src)
    {
    }

template <class T>
deque<T>::~deque()
    {
    }

template <class T>
deque<T>& deque<T>::operator =(const deque<T>& src)
    {
    queue<T>::operator = (src);
    return *this;
    }

template <class T>
void deque<T>::push_back(T data) {
    this->tail->next = new biNode<T>(this->tail, data, NULL);
    this->tail = this->tail->next;

    if (NULL == this->head)
        {
        this->head = this->tail;
        }
}

template <class T>
T deque<T>::pop_front() {
    if (NULL == this->head)
        {
        throw std::runtime_error("removing from empty list");
        }
    
    T data = this->head->getData();
    biNode<T>* buffer = this->head;
    if (this->tail == this->head)
        {
        this->tail = this->head = NULL;
        }
    else
        {
        this->head = this->head->next;
        }
    delete buffer;

    return data;
}

#endif /* __DEQUE__H */