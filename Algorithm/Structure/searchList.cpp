//
//  searchList.cpp
//  List
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __SEARCH_LIST__H

template <class T>
searchList<T>::searchList() : head(NULL)
    {
    }

template <class T>
searchList<T>::searchList(const searchList& src) : head(NULL)
    {
    if (NULL != src.head)
        {
        head = src.head->cascadeCopy();
        }
    }

template <class T>
searchList<T>::~searchList()
    {
    if (NULL != head)
        {
        head->cascadeDelete();
        }
    }

template <class T>
searchList<T>& searchList<T>::operator = (const searchList<T>& src)
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
            }
        }
    
    return *this;
    }

template <class T>
signed searchList<T>::search(T elem)
    {
    signed index = -1;
    size_t incr = 0;
    for (listNode<T>* buffer = head; NULL != buffer; buffer = buffer->next)
        {
        if (buffer->getData() == elem)
            {
            index = incr;
            }
        incr++;
        }
    return index;
    }

template <class T>
void searchList<T>::nInsert(T elem, size_t N)
    {
    if (N == 0 || NULL == head)
        {
        head = new listNode<T>(data, head);
        }
    else
        {
        listNode<T>* buffer = head;
        for (size_t incr = 0; incr < N-1 && NULL != buffer->next; incr++)
            {
            buffer = buffer->next;
            }
        buffer->next = new listNode<T>(elem, buffer->next);
        }
    }

template <class T>
T searchList<T>::nRemove(size_t N)
    {
    // checks for special case: empty list
    if (NULL == head)
        {
        throw std::runtime_error("removing from empty list");
        }

    listNode<T>* detached = NULL;
    if (N == 0)
        {
        detached = head;
        head = head->next;
        }
    else
        {
        listNode<T>* buffer = head;
        for (size_t incr = 0; incr < N-1 && NULL != buffer->next; incr++)
            {
            buffer = buffer->next;
            }
        detached = buffer->next;
        if (NULL != detached)
            {
            buffer->next = detached->next;
            }
        }
    
    if (NULL == detached)
        {
        throw std::out_of_range("index greater than size of list");
        }

    T removeData = detached->getData();
    delete detached;

    return removeData;
    }

template <class T>
T searchList<T>:nPeek(size_t N)
    {
    // checks for special case: empty list
    if (NULL == head)
        {
        throw std::runtime_error("peeking in empty list");
        }
        
    listNode<T>* buffer = head;
    for (size_t incr = 0; incr < N && NULL != buffer; incr++)
        {
        buffer = buffer->next;
        }
    
    if (NULL == buffer)
        {
        throw std::out_of_range("index greater than size of list");
        }
        
    return buffer->getData();
    }
    
template <class T>
bool searchList<T>::nReplace(T elem, size_t N)
    {
    bool isReplaced = false;
    
    if (NULL != head)
        {
        listNode<T>* replaced = NULL;
        if (N == 0)
            {
            replaced = head;
            head = new listNode<T>(elem, replaced->next);
            delete replaced;
            isReplaced = true;
            }
        else
            {
            listNode<T>* buffer = head;
            for (size_t incr = 0; incr < N-1 && NULL != buffer->next; incr++)
                {
                buffer = buffer->next;
                }
            replaced = buffer->next;
            if (NULL != replaced)
                {
                buffer->next = new listNode<T>(elem, replaced->next);
                delete replaced;
                isReplaced = true;
                }
            }
        }
        
    return isReplaced;
    }

template <class T>
size_t searchList<T>::size() const
    {
    size_t incr = 0;
    for (listNode<T>* buffer = head; NULL != buffer; buffer = buffer->next)
        {
        incr++;
        }
    return incr;
    }

#endif /* __SEARCH_LIST__H */