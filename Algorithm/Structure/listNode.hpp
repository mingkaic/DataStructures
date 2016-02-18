//
//  listNode.hpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __LIST_NODE__H
#define __LIST_NODE__H

#include <cstdlib>
#include "node.hpp"

template <class T>
class listNode : public node<T>
    {
    public:
        listNode<T>* next;
        
        listNode(T data);
        listNode(T data, listNode<T>* next);
        // shallow copying data right now. no worries
        virtual ~listNode() {}
        
        void cascadeDelete();
        listNode<T>* cascadeCopy();
    };

#include "listNode.cpp"

#endif /* __LIST_NODE__H */