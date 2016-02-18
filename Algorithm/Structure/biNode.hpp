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

// doubly linked node
template <class T>
class biNode : public node<T>
    {
    protected:
        biNode()
            {
            left = NULL;
            right = NULL;
            } // for derived classes
    public:
        biNode<T>* left;
        biNode<T>* right;
        
        biNode(T data);
        biNode(biNode<T>* left, T data, biNode<T>* right);
        virtual ~biNode() {} // shallow copying data right now. no worries
        
        virtual void cascadeDelete();
        virtual biNode<T>* cascadeCopy();
    };

#include "biNode.cpp"

#endif /* __BI_NODE__H */