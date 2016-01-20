//
//  RBTree.h
//  Tree
//
//  Created by Ming Kai Chen on 2014-06-26.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __RB_TREE__H
#define __RB_TREE__H

#include <cstdlib>
#include <stdexcept>
#include "BSTree.hpp"

template <class T>
class RBNode : private treeNode<T>
    {
    public:
        bool isBlack;
        RBNode<T>* left;
        RBNode<T>* right;
        RBNode<T>* parent;

        RBNode(T data);
        RBNode(T data, bool isBlack);
        RBNode(RBNode<T>* left, T data, RBNode<T>* right);
        
        RBNode<T>* cascadeCopy();
    };

template <class T>
class RBTree : private BSTree<T>
    {
    private:
        RBNode<T>* root;
        RBNode<T>* closestNode(RBNode<T>*& root, T data) const;
    public:
        RBTree();
        RBTree(const RBTree<T>& src);
        ~RBTree();
        RBTree<T>& operator = (const RBTree<T>& src);

        virtual bool insert(T key);
        virtual bool remove(T key);
    };

#include "RBTree.cpp"

#endif /* __RB_TREE__H */