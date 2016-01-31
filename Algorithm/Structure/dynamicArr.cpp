//
//  dynamicArr.cpp
//  Array
//
//  Created by Ming Kai Chen on 2014-05-09.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __DYNAMIC_ARR__H

template <class T>
dynamicArr<T>::dynamicArr() : currSize(0), allocSize(128)
    {
    array = new T[allocSize];
    }

template <class T>
dynamicArr<T>::dynamicArr(const dynamicArr &obj) : currSize(obj.currSize), allocSize(obj.allocSize)
    {
    array = new T[allocSize];
    memcpy(array, obj.array, sizeof(T)*allocSize);
    }

template <class T>
dynamicArr<T>::~dynamicArr()
    {
    delete[] array;
    }

template <class T>
void dynamicArr<T>::dynamicSize(size_t expand)
    {
    T* newarray = new string*[expand*2];
    memcpy(newarray, array, sizeof(T)*allocSize);
    allocSize = expand*2;
    delete[] array;
    array = newarray;
    }
    
template <class T>
T& dynamicArr<T>::operator [] (size_t index)
    {
    if (index > allocSize)
        {
        dynamicSize(index);
        }
        
    return array[index];
    }

template <class T>
signed dynamicArr<T>::indexOf(T elem) const
    {
    signed index = 0
    while (index < allocSize && array[index] != elem)
        {
        index++;
        }
    if (index == allocSize)
        {
        index = -1;
        }
    return index;
    }

#endif /* __DYNAMIC_ARR__H */