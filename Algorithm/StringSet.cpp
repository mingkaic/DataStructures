//
//  stringSet.cpp
//  cmpt225Assign1
//
//  Created by Ming Kai Chen on 2014-05-09.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#include "StringSet.h"

// Default constructor
StringSet::StringSet(): _curSize(0), _maxSize(4)
{
    _data = new string*[_maxSize];
}

// Copy constructor
StringSet::StringSet(const StringSet &obj):
    _curSize(obj._curSize),
    _maxSize(obj._maxSize)
{
    _data = new string*[_maxSize];
    
    // make deep copy
    for (int i = 0; i < _curSize; i++) {
        _data[i] = new string(*(obj._data[i]));
    }
}

// Destructor
StringSet::~StringSet()
{
    for (int i = 0; i < _curSize; i++) {
        delete _data[i];
    }
    
    delete[] _data;
}

// Checks and expands the array to make it dynamic
void StringSet::dynamicSize()
{
    if (_curSize < _maxSize) return;
    
    // Doubles the size
    _maxSize *= 2;
    string** newData = new string*[_maxSize];
    
    // shallow copy is fine
    for (int i = 0; i < _curSize; i++) {
        newData[i] = _data[i];
    }
    
    delete[] _data;
    _data = newData;
}

// Return true if the inserting obj is unique in the arr, else false
bool StringSet::insert(string str)
{
    // the condition is true only if the obj is in the data array
    if (find(str) != -1) return false;

    dynamicSize();
    
    _data[_curSize] = new string(str);
    
    _curSize++;
    
    return true;
}

// Return true if str is removed, else false
bool StringSet::remove(string str)
{
    int index = find(str);

    if (index == -1) return false;
    
    // Element at _curSize doesn't belong, _data[_curSize-1] would pick up garabage.
    // Better to ignore it.
    delete _data[index];
    
    for (; index < _curSize - 1; index++) {
        _data[index] = _data[index+1];
    }
    
    _curSize--;
    return true;
}

// Return -1 if str not found, else index of str
// Since _data is unsorted, use linear search
int StringSet::find(string str) const
{
    for (int i = 0; i < _curSize; i++) {
        // comparison issues???
        if (*_data[i] == str) {
            return i;
        }
    }
    
    return -1;
}

// Returns _curSize
int StringSet::size() const
{
    return _curSize;
}

/* 
 * NOTE: set manipulation methods all return object by value,
 * as such local objects are made in stack. 
 */

// Returns StringSet object that holds the union of the _data arrays in this and obj
StringSet StringSet::unions(const StringSet &obj) const
{
    // new Set is identical to obj Set
    StringSet jointSet(obj);
    
    for (int i = 0; i < _curSize; i++) {
        //insert automatically filters out repeated entries
        jointSet.insert(*_data[i]);
    }
    
    return jointSet;
}

// Returns object that holds the intersection of _data arrays in this & obj
StringSet StringSet::intersection(const StringSet &obj) const
{
    // new Set is empty!
    StringSet jointSet;
    
    for (int i = 0; i < _curSize; i++) {
        // only insert if the _data is found in both this and obj Sets
        if (obj.find(*_data[i]) != -1) {
            jointSet.insert(*_data[i]);
        }
    }
    
    return jointSet;
}

// Returns object that holds the difference of _data arrays in this & obj
// NOTE: Even Though difference = union - intersection. performing two functions would increase the leading coefficient of the running time by two
StringSet StringSet::difference(const StringSet &obj) const
{
    // new Set is empty
    StringSet jointSet;
    
    for (int i = 0; i < _curSize; i++) {
        // insert elements unique to this
        if (obj.find(*_data[i]) == -1) {
            jointSet.insert(*_data[i]);
        }
    }
    
    return jointSet;
}

void StringSet::print() const
{
    for (int i = 0; i < _curSize; i++) {
        cout << *_data[i] << endl;
    }
}