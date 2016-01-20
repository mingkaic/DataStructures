//
//  stringSet.h
//  cmpt225Assign1
//
//  Created by Ming Kai Chen on 2014-05-09.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifndef __cmpt225Assign1__stringSet__
#define __cmpt225Assign1__stringSet__

#include <iostream>
#include <string>

using namespace std;

class StringSet {    
public:
    StringSet();
    StringSet(const StringSet&);
    ~StringSet();
    StringSet operator =(StringSet o); // prevent copying
    
public:    
    // mutators
    bool insert(string str);
    bool remove(string str);
    
    // accessors
    int find(string str) const;
    int size() const;
    void print() const;

    // set operations
    StringSet unions(const StringSet&) const;
    StringSet intersection(const StringSet&) const;
    StringSet difference(const StringSet&) const;

private:    
    // handles the checking and expansion of the array
    void dynamicSize();

private:
    // array of pointers to string objects
    string** _data;
    unsigned int _curSize;
    unsigned int _maxSize;
};

#endif // defined(__cmpt225Assign1__stringSet__) 
