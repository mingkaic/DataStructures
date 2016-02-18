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
#include "pair.hpp"
#include "pBSTree.hpp"

template <class T>
bool& isBlack(pTreeNode<pair<bool, T> >* rb_node)
    {
    return rb_node->getDataRef()->getKeyRef();
    }

template <class T>
class RBTree : public pBSTree<pair<bool, T> >
    {
    private:
        void deleteFixUp(pTreeNode<pair<bool, T> >* parent, bool childIsLeft);
        void rotate(pTreeNode<pair<bool, T> >* parent, bool rotateLeft);
    public:
        RBTree(const RBTree<T>& src);
        virtual ~RBTree() {} // parent takes care of it
        RBTree<T>& operator = (const RBTree<T>& src);

        bool insert(T key);
        bool remove(T key);
    };

#include "RBTree.cpp"

#endif /* __RB_TREE__H */