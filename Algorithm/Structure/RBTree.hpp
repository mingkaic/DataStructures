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
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "BSTree.hpp"

template <class T>
class RBNode : public treeNode<T>
    {
    public:
        bool isBlack;
        RBNode<T>* left;
        RBNode<T>* right;
        RBNode<T>* parent;

        RBNode(T data);
        RBNode(T data, bool isBlack);
        RBNode(RBNode<T>* left, T data, RBNode<T>* right);
        
        void cascadeDelete();
        RBNode<T>* cascadeCopy();
    };

template <class T>
class RBTree
    {
    private:
        RBNode<T>* root;
        void deleteFixUp(RBNode<T>* parent, bool childIsLeft);
        void rotate(RBNode<T>* parent, bool rotateLeft);
        RBNode<T>* successor(RBNode<T>* i_root);
        // gets exact match if key found, closest match otherwise
        RBNode<T>* BinSearch(T key, RBNode<T>* root) const;
    public:
        RBTree();
        RBTree(const RBTree<T>& src);
        virtual ~RBTree();
        RBTree<T>& operator = (const RBTree<T>& src);

        bool insert(T key);
        bool remove(T key);
        bool exists(T key);
        
        RBNode<T>* getRoot() {return root;}
    };

#include "RBTree.cpp"

#endif /* __RB_TREE__H */