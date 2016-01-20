//
//  deque.cpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __DEQUE__H

template <class T>
deque<T>::deque(): head(NULL), tail(NULL)
    {
    }

template <class T>
deque<T>::deque(const deque& src)
    {
    if (NULL != sr.head)
        {
        head = src.head->cascadeCopy();
        findTail(head);
        }
    }

template <class T>
deque<T>::~deque()
    {
    if (NULL != head)
        {
        head->cascadeDelete();
        }
    }

template <class T>
deque<T>& deque<T>::operator =(const deque<T>& src)
    {
    // prevent self assignment
    if (&src != this)
        {
        if (NULL != head)
            {
            head->cascadeDelete();
            }
        
        if (NULL != src.head)
            {
            head = src.head->cascadeCopy();
            findTail(head);
            }
        }
    
    return *this;
    }

template <class T>
void deque<T>::push_back(T data) {
    tail->next = new biNode<T>(tail, data, NULL);
    tail = tail->next;

    if (NULL == head)
        {
        head = tail;
        }
}

template <class T>
T deque<T>::pop_front() {
    if (NULL == head)
        {
        throw std::runtime_error("removing from empty list");
        }
    
    T data = head->getData();
    biNode<T>* buffer = head;
    if (tail == head)
        {
        tail = head = NULL;
        }
    else
        {
        head = head->next;
        }
    delete buffer;

    return data;
}

#endif /* __DEQUE__H */