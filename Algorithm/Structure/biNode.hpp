//
//  biNode.hpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __BI_NODE__H
#define __BI_NODE__H

#include <cstdlib>
#include "node.hpp"
#include "genericHandles.hpp"

// doubly linked node
template <class T>
class biNode : public node<T>
    {
    protected:
        biNode(){prev = next = NULL;}
    public:
        biNode<T>* prev;
        biNode<T>* next;
        
        biNode(T data);
        biNode(biNode<T>* prev, T data, biNode<T>* next);
        virtual ~biNode() {}

        void cascadeDelete();
        virtual biNode<T>* cascadeCopy();
    };

#include "biNode.cpp"

#endif /* __BI_NODE__H */