//
//  treeNode.hpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __TREE_NODE__H
#define __TREE_NODE__H

#include "biNode.hpp"

template <class T>
class treeNode : public biNode<T>
    {
    protected:
        treeNode() // for derived classes
            {
            left = NULL;
            right = NULL;
            }
    public:
        treeNode<T>* left;
        treeNode<T>* right;
        
        treeNode(T data);
        treeNode(treeNode<T>* left, T data, treeNode<T>* right);
        virtual ~treeNode() {}
        
        void cascadeDelete();
        virtual treeNode<T>* cascadeCopy();

        void injectData(T data);
    };

#include "treeNode.cpp"

#endif /* __TREE_NODE__H */