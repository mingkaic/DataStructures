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

#include "node.hpp"

template <class T>
class treeNode : public node<T>
    {
    protected:
        treeNode(){left = right = NULL;}
    public:
        treeNode<T>* left;
        treeNode<T>* right;
        
        treeNode(T data);
        virtual ~treeNode() {}
        
        void cascadeDelete();
        virtual treeNode<T>* cascadeCopy();

        void injectData(T data) {this->dataInit(data);}
    };

#include "treeNode.cpp"

#endif /* __TREE_NODE__H */