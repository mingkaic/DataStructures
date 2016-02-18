//
//  pTreeNode.hpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __P_TREE_NODE__H
#define __P_TREE_NODE__H

#include "node.hpp"

template <class T>
class pTreeNode : public node<T>
    {
    private:
        enum direction {LEFT, RIGHT, TOP};
        pTreeNode<T>* copyHelper(direction caller, pTreeNode<T>* from);
        void trickleDelete();
    protected:
        pTreeNode(){left = right = parent = NULL;}
    public:
        pTreeNode<T>* left;
        pTreeNode<T>* right;
        pTreeNode<T>* parent;
        
        pTreeNode(T data);
        virtual ~pTreeNode(){}
        
        void cascadeDelete();
        virtual pTreeNode<T>* cascadeCopy();

        void injectData(T data){this->dataInit(data);}
        T& getDataRef(){return this->data;}
    };

#include "pTreeNode.cpp"

#endif /* __P_TREE_NODE__H */